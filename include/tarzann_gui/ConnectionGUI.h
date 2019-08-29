 
#ifndef CONNECTION_GUI_H
#define CONNECTION_GUI_H

#include <QGraphicsPathItem>
#include <QObject>

//using namespace tarzann;

class SheetImage;

class ConnectionGUI : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    ConnectionGUI(SheetImage* outputImg, SheetImage* inputImage, QGraphicsScene* scene);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void highLightAsInput(bool val) { m_highLightedAsInput = val; }
    void highLightAsOutput(bool val) { m_highLightedAsOutput = val; }
    bool isHighlightedAsInput() { return m_highLightedAsInput; }
    bool isHighlightedAsOutput() { return m_highLightedAsOutput; }



    SheetImage* getInputImg();
    SheetImage* getOutputImg();

    void updatePath();

    ~ConnectionGUI();

private:
    QGraphicsScene* m_scene;
    QPainterPath* m_path;
    SheetImage* m_inputImg;
    SheetImage* m_outputImg;
    QPen* m_pen;
    bool m_highLightedAsInput;
    bool m_highLightedAsOutput;
};


#endif
