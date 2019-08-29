#include <iostream>
#include <unistd.h>

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>

#include <tarzann/PLattice.h>
#include <tarzann_gui/PLatticeGUI.h>
#include <tarzann_gui/NetworkWindow.h>

using namespace tarzann;
using namespace std;

PLatticeGUIThread::PLatticeGUIThread(PLattice* plattice, int argc, char **argv)
{
    m_plattice_gui = new PLatticeGUI(plattice, argc, argv);

    m_thread = m_plattice_gui->getThread();

    m_thread.detach();
}

PLatticeGUIThread::~PLatticeGUIThread()
{
    m_plattice_gui->stop();
    delete m_plattice_gui;
}

PLatticeGUI::PLatticeGUI(PLattice* plattice, int argc, char **argv)
{
    m_plattice = plattice;
    m_running = true;
    m_argc = argc;
    m_argv = argv;
}

PLatticeGUI::~PLatticeGUI()
{

}

void PLatticeGUI::stop()
{
    m_gui_mutex.lock();
    m_running = false;
    m_gui_mutex.unlock();
}

void PLatticeGUI::setupComponents()
{

}

void PLatticeGUI::run()
{
    setupComponents();

    QApplication app(m_argc,m_argv);
    NetworkWindow *w = new NetworkWindow(m_plattice);
    app.exec();
}
