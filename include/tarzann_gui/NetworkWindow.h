#ifndef NETWORK_WINDOW_H
#define NETWORK_WINDOW_H

#include <tarzann/PLattice.h>
#include <tarzann_gui/SheetImage.h>
#include <tarzann_gui/ConnectionGUI.h>
#include <tarzann_gui/GUI_config.h>

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QWheelEvent>

namespace tarzann
{
    class NetworkWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            NetworkWindow(PLattice* plattice);
            ~NetworkWindow();

            enum Mode {
                ACTIVATION = 0,
                SUPPRESIVE_SURROUND = 1,
            };

        private:
            PLattice* m_plattice;

            int m_windowHeight;
            int m_windowWidth;

            std::vector<SheetImage*> m_sheetImages;
            std::vector<ConnectionGUI*> m_connections;

            QGraphicsView *m_view;
            QGraphicsScene *m_scene;
            QTimer *m_timer;

            void calculateCoordinates(int defaultImgSize);
            int calculateSize(int sheetNum, int defaultSize, int xSpace);
            int calculateYSpace(int layerNum, int defaultYSpace, int defaultSize, int topOffset);

            void drawImages();
            void drawConnections();

            const int DEFAULT_IMAGE_SIZE = 50;

            GUI_config* m_config;

            float m_h11 = 1.0;
            float m_h12 = 0.0;
            float m_h21 = 1.0;
            float m_h22 = 0.0;

        protected:
            void keyPressEvent(QKeyEvent *event);
            virtual void wheelEvent(QWheelEvent* event);
            bool eventFilter(QObject* object, QEvent *event);
    };
}


#endif
