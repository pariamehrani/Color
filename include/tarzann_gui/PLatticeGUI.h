#ifndef PLATTICE_GUI_H
#define PLATTICE_GUI_H

#include <thread>
#include <mutex>

#include <QCoreApplication>

namespace tarzann
{
	class PLattice;
    class PLatticeGUI;

    class PLatticeGUIThread
	{
        public:
            PLatticeGUIThread(PLattice* plattice, int argc, char **argv);
            ~PLatticeGUIThread();

        private:
            PLatticeGUI* m_plattice_gui;
            std::thread m_thread;
	};

    class PLatticeGUI
    {
        public:
            PLatticeGUI(PLattice* plattice, int argc, char **argv);

            ~PLatticeGUI();

            void run();

            void stop();

            std::thread getThread() {
                return std::thread([=] { run(); });
            }

        private:
            PLattice* m_plattice;
            std::mutex m_gui_mutex;

            bool m_running;
            int m_argc;
            char** m_argv;

            void setupComponents();
    };
}

#endif
