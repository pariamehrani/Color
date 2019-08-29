#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <QImage>
#include <QColor>
#include <QPainter>
#include <QSizeF>
#include <QRgb>
#include <QTimer>

#include <tarzann_gui/SheetImage.h>
#include <tarzann/Matrix.h>
#include <tarzann_gui/GUI_config.h>

using namespace std;
using namespace tarzann;

SheetImage::SheetImage(Sheet *s, QPointF pos, int sizeOfImage, QGraphicsScene *scene, QTimer *timer1, GUI_config* config) : QGraphicsItem()
{
    m_sheet = s;
    m_position = pos;
    m_size = sizeOfImage;
    m_scene = scene;
    m_config = config;

    m_img = new QImage(m_sheet->getWidth(), m_sheet->getHeight(), QImage::Format_ARGB32);

    updatePixels();

    connect(timer1, SIGNAL(timeout()), this, SLOT(updatePixels()));
}

void SheetImage::updatePixels()
{
    this->m_output = m_sheet->getOutput();
    this->m_suppressive_surround = m_sheet->getSuppressiveSurround();
    this->m_gating_control = m_sheet->getGatingControl();

    findMaxandMin(m_output, m_maxActivation, m_minActivation);
    findMaxandMin(m_suppressive_surround, m_maxSuppression, m_minSuppression);

    for(int row = 0; row < m_output->getYSize(); row++)
    {
        for(int column = 0; column < m_output->getXSize(); column++)
        {
            float a = (*m_output)(column, row);
            float s = (*m_suppressive_surround)(column, row);
            float gc = (*m_gating_control)(column, row);

            int s_pix = mapFloatRangeto8bit(s, m_minSuppression, m_maxSuppression);
            int a_pix = mapFloatRangeto8bit(a, m_minActivation, m_maxActivation);

            //use the next line instead the conditional,
            //if gating control won't show off

            //m_img->setPixel(column, row, qRgb(act, act, act));

            //these lines if gating control shows off
            if(m_config->gui_mode == m_config->GATING_CONTROL)
            {
                if(gc == 0.0)
                    m_img->setPixel(column, row, qRgb(a_pix, a_pix, a_pix));
                else if (gc == 1.0)
                    m_img->setPixel(column, row, qRgb(0, 255, 0));
                else
                    m_img->setPixel(column, row, qRgb(255,0, 0));
            }
            else if(m_config->gui_mode == m_config->SUPPRESIVE_SURROUND)
            {
                m_img->setPixel(column, row, qRgb(0.0, s_pix,0.0));
            }
            else if (m_config->gui_mode == m_config->ACTIVATION)
            {
                m_img->setPixel(column, row, qRgb(a_pix, a_pix, a_pix));
            }
        }
    }
    QGraphicsItem::update(boundingRect());
}

QRectF SheetImage::boundingRect() const
{
    return QRectF(m_position, QSizeF(m_size, m_size));
}

void SheetImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    painter->drawImage(boundingRect(), *m_img);
}

void SheetImage::update(const QRectF &rect)
{

}

int SheetImage::mapFloatRangeto8bit(float value, float min, float max)
{
    return (value-min)*(255.0/(max-min));
}

void SheetImage::findMaxandMin(Matrix *m, float &max, float &min)
{
    max = 1.0e-10;
    min = 1.0e+10;

    for(int i = 0; i < m->getYSize(); i++)
    {
        for(int j = 0; j < m->getYSize(); j++)
        {
            float val = (*m)(i,j);
            if(val < min)
            {
                min = val;
            }
            if(val > max)
            {
                max = val;
            }
        }
    }
}

void SheetImage::updatePositionAndSize(int x, int y, int size)
{
    this->setPosition(x,y);
    this->setSize(size);
    updatePixels();
}

void SheetImage::setPosition(int x, int y)
{
    m_position = QPointF(x, y);
}

void SheetImage::setSize(int size)
{
    m_size = size;
}

Sheet* SheetImage::getSheet()
{
    return m_sheet;
}

QPointF SheetImage::getInputPoint()
{
    return QPointF(m_position.x() + m_size/2, m_position.y());
}

QPointF SheetImage::getOutputPoint()
{
    return QPointF(m_position.x()+(m_size/2), m_position.y() + m_size);
}

SheetImage::~SheetImage()
{
    delete m_sheet;
    delete m_img;
    delete m_output;
}
