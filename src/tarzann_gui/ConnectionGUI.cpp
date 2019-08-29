#include <tarzann_gui/ConnectionGUI.h>
#include <tarzann_gui/SheetImage.h>

#include <QPointF>
#include <QPainterPath>
#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include <QtGui>
#include <QTimer>
#include <QStyleOptionGraphicsItem>

ConnectionGUI::ConnectionGUI(SheetImage *outputImg, SheetImage *inputImage, QGraphicsScene *scene) : QGraphicsPathItem()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);

    m_outputImg = outputImg;
    m_inputImg = inputImage;
    m_scene = scene;

    m_pen = new QPen(QColor(255,0,0));

    updatePath();
}

void ConnectionGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(option->state.testFlag(QStyle::State_MouseOver))
    {
        QColor tempColor = QColor(0,255,0);
        tempColor.setAlpha(255);
        QPen tempPen(tempColor);
        tempPen.setWidth(3);
        painter->setPen(tempPen);
    }
    else
    {
        painter->setPen(*m_pen);
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(*m_path);
}

void ConnectionGUI::updatePath()
{
    QPointF outputPoint(m_outputImg->getOutputPoint());
    m_path = new QPainterPath(outputPoint);
    float c1x = m_outputImg->getOutputPoint().x() + (m_inputImg->getInputPoint().x() - m_outputImg->getOutputPoint().x())/4;
    float c1y = m_inputImg->getInputPoint().y() - (m_inputImg->getInputPoint().y() - m_outputImg->getOutputPoint().y())/4;
    float c2x = m_inputImg->getInputPoint().x() - (m_inputImg->getInputPoint().x() - m_outputImg->getOutputPoint().x())/4;
    float c2y = m_outputImg->getOutputPoint().y() + (m_inputImg->getInputPoint().y() - m_inputImg->getInputPoint().y())/4;
    m_path->cubicTo(c1x,c1y,c2x,c2y,m_inputImg->getInputPoint().x(), m_inputImg->getInputPoint().y());
    setPath(*m_path);
}

ConnectionGUI::~ConnectionGUI()
{
    delete m_path;
    delete m_pen;
}
