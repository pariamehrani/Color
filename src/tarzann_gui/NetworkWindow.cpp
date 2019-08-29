#include <iostream>
#include <vector>

#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QApplication>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QKeyEvent>
#include <QTimer>
#include <QtAlgorithms>
#include <QGraphicsRectItem>
#include <QTransform>
#include <QScrollBar>
#include <QEvent>

#include <tarzann_gui/NetworkWindow.h>
#include <tarzann/Layer.h>
#include <tarzann/PLattice.h>
#include <tarzann/Sheet.h>
#include <tarzann_gui/SheetImage.h>
#include <tarzann_gui/ConnectionGUI.h>
#include <tarzann_gui/GUI_config.h>

using namespace std;
using namespace tarzann;

NetworkWindow::NetworkWindow(PLattice *plattice) : QMainWindow() {
    m_plattice = plattice;

    QRect screenRec = QApplication::desktop()->screenGeometry();
    m_windowWidth = screenRec.width()-30;
    m_windowHeight = screenRec.height()-30;

    m_view = new QGraphicsView(this);
    setCentralWidget(m_view);

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0, 0, m_windowWidth, m_windowHeight);

    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setInteractive(true);
    m_view->setDragMode(QGraphicsView::ScrollHandDrag);
    m_view->viewport()->installEventFilter(this);

    m_config = new GUI_config();
    m_config->gui_mode = m_config->ACTIVATION;

    m_timer = new QTimer(this);

    std::vector<Layer*> layers;
    std::vector<Sheet*> sheets;

    m_plattice->getLayers(layers);

    for (uint32_t i=0; i<layers.size(); i++)
    {
        Layer* layer = (Layer*) layers[i];
        layer->getSheets(sheets);

        for (uint32_t j=0; j<sheets.size(); j++)
        {
            Sheet* sheet = (Sheet*) sheets[j];
            SheetImage *img = new SheetImage(sheet, QPointF(10,10), 20, m_scene, m_timer, m_config);
            m_sheetImages.push_back(img);
            m_scene->addItem(img);
        }
    }

    calculateCoordinates(DEFAULT_IMAGE_SIZE);
    drawImages();
    drawConnections();

    m_timer->start(50);
    m_view->setScene(m_scene);
    showMaximized();
}

void NetworkWindow::calculateCoordinates(int defaultImgSize)
{
    int x = 10;
    int y = 10;
    int xSpace = 5;
    int ySpace = 300;
    int size = defaultImgSize;

    std::vector<Layer*> layers;
    std::vector<Sheet*> sheets;
    std::vector<SheetImage*> sheetImgs;

    m_plattice->getLayers(layers);

    ySpace = calculateYSpace(layers.size(), ySpace, size, 30)+size-xSpace;
    y = (m_windowHeight - (layers.size()*size + (layers.size() - 1) * ySpace))/2 + (layers.size() - 3)*size + (layers.size()-1)*ySpace - size/2;

    uint32_t k = 0;

    for (uint32_t i=0; i<layers.size(); i++)
    {
        Layer* layer = (Layer*) layers[i];
        layer->getSheets(sheets);

        size = calculateSize(sheets.size(), size, xSpace);
        x = ((m_windowWidth - (sheets.size()*size + (sheets.size()-1)*xSpace))/2);

        for (uint32_t j=0; j<sheets.size(); j++)
        {
            Sheet* sheet = (Sheet*) sheets[j];
            SheetImage* img = (SheetImage*) m_sheetImages[k];

            img->updatePositionAndSize(x,y,size);
            k++;
            x += xSpace+size;
        }
        y-=ySpace;
    }
}

int NetworkWindow::calculateYSpace(int layerNum, int defaultYSpace, int defaultSize, int topOffset)
{
    if ((defaultSize*layerNum + (layerNum-1)*defaultYSpace) < (m_windowHeight - topOffset))
        return defaultYSpace;
    defaultYSpace -= 20;
    calculateYSpace(layerNum, defaultYSpace, defaultSize, topOffset);
}

int NetworkWindow::calculateSize(int sheetNum, int defaultSize, int xSpace)
{
    if(defaultSize*sheetNum + (sheetNum+1)*xSpace < m_windowWidth)
        return defaultSize;
    defaultSize -= 2;
    calculateSize(sheetNum, defaultSize, xSpace);
}

void NetworkWindow::drawImages()
{
    m_scene->update(0,0, m_windowWidth, m_windowHeight);
}

void NetworkWindow::drawConnections()
{
    for (int k=0; k < m_sheetImages.size(); k++)
    {
        SheetImage* img1 = m_sheetImages[k];
        for (int l = 0; l < m_sheetImages.size(); l++)
        {
            SheetImage* img2 = m_sheetImages[l];
            std::vector<Connection*> conList;

            img1->getSheet()->getInputConnections(conList);

            if(conList.size())
            {
                for (int m = 0; m < conList.size(); m++)
                {
                    Connection* con = (Connection*) conList[m];
                    if (con->getSource()->getName() == img2->getSheet()->getName())
                    {
                        ConnectionGUI *conGui = new ConnectionGUI(img1, img2, m_scene);
                        m_scene->addItem(conGui);
                        m_connections.push_back(conGui);
                    }
                }
            }
        }
    }
}

void NetworkWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_M)
    {
        if(m_config->gui_mode == m_config->ACTIVATION)
        {
            m_config->gui_mode = m_config->SUPPRESIVE_SURROUND;
        }
        else if(m_config->gui_mode == m_config->SUPPRESIVE_SURROUND)
        {
            m_config->gui_mode = m_config->GATING_CONTROL;
        }
        else if (m_config->gui_mode == m_config->GATING_CONTROL) {
            m_config->gui_mode = m_config->ACTIVATION;
        }
    }
}

bool NetworkWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_view->viewport() && event->type() == QEvent::Wheel)
    {
        QWheelEvent *q = dynamic_cast<QWheelEvent*>(event);
        cout << "scroll" << endl;
        m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        double scaleFactor = 1.15;
        if(q->delta() > 0)
        {
            m_view->scale(scaleFactor, scaleFactor);
        }
        else
        {
            m_view->scale(1 / scaleFactor, 1 / scaleFactor);
        }
        return true;
    }
    return false;
}

void NetworkWindow::wheelEvent(QWheelEvent *event) {

}

NetworkWindow::~NetworkWindow() {
    delete m_scene;
    delete m_view;
    delete m_timer;
}
