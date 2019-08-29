#ifndef SHEET_IMAGE_H
#define SHEET_IMAGE_H

#include <QGraphicsItem>
#include <QImage>
#include <QRectF>
#include <QPointF>
#include <QPixmap>
#include <QMainWindow>
#include <QObject>

#include <tarzann/Sheet.h>
#include <tarzann_gui/GUI_config.h>

using namespace tarzann;

class SheetImage : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    SheetImage(Sheet *s, QPointF pos, int sizeOfImage, QGraphicsScene *scene, QTimer *timer1, GUI_config *config);
    ~SheetImage();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void update(const QRectF &rect=QRectF());
    void updatePositionAndSize(int x, int y, int size);
    void setPosition(int x, int y);
    void setSize(int size);
    Sheet* getSheet();

    QPointF getInputPoint();
    QPointF getOutputPoint();

private:
    Sheet* m_sheet;
    QPointF m_position;
    QGraphicsScene* m_scene;
    QImage *m_img;

    GUI_config* m_config;

    Matrix *m_output;
    Matrix *m_suppressive_surround;
    Matrix *m_gating_control;

    int m_size;

    float m_minActivation;
    float m_maxActivation;
    float m_minSuppression;
    float m_maxSuppression;
    float m_minGatingControl;
    float m_maxGatingControl;

    int activationTo8Bit(float a);
    void findMaxandMin(Matrix* m, float &max, float &min);
    int mapFloatRangeto8bit(float value, float min, float max);

public slots:
    void updatePixels();
};

#endif
