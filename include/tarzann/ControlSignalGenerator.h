/**
 * @author  Asheer Bachoo, abachoo@gmail.com
 * @date    May 12, 2016
 */

#ifndef CONTROLSIGNAL_H
#define CONTROLSIGNAL_H

#include <stdint.h>
#include <iostream>

namespace tarzann
{
    enum TaskType
    {
        TASK_CATEGORIZATION,
        TASK_DETECTION,
        TASK_IDENTIFICATION,
        TASK_WITHIN_CATEGORY,
        TASK_LOCALIZATION,
        TASK_GAZE_SHIFT,
        TASK_MEASURE
    };

    struct ControlSignalTimings
    {
        bool* m_priming;
        bool* m_find_winner;
        bool* m_matching;
        bool* m_recurrent_localization;
        bool* m_reinterpret;
        bool* m_reset_blackboard;
        bool* m_next_fixation;

        int num_steps;
    };

    struct ControlSignal
    {
        bool m_do_priming;
        bool m_do_find_winner;
        bool m_do_matching;
        bool m_do_recurrent_localization;
        bool m_do_reinterpret;
        bool m_do_reset_blockboard;
        bool m_do_next_fixation;

        void print()
        {
            //std::cout << "Priming: " << m_do_priming << std::endl;
            std::cout << "Find Winner: " << m_do_find_winner << std::endl;
            //std::cout << "Matching: " << m_do_matching << std::endl;
            //std::cout << "Recurrent Loc: " << m_do_recurrent_localization << std::endl;
            //std::cout << "Reinterpret: " << m_do_reinterpret << std::endl;
            //std::cout << "Reset BlackBoard: " << m_do_reset_blockboard << std::endl;
            std::cout << "Next Fixation: " << m_do_next_fixation << std::endl;
        }
    };

    class ControlSignalGenerator
    {
        public:
            ControlSignalGenerator(int steps_per_attentive_cycle,
                                   TaskType task_type);

            ControlSignal updateTimer();

            int getTime();

            int* getTimePtr();

            ~ControlSignalGenerator();

        private:
            void setupPrimingSync();
            void setupFindWinnerSync();
            void setupMatchingSync();
            void setupRecurrentLocalizationSync();
            void setupReinterpretSync();
            void setupResetBlackBoard();
            void setupNextFixation();

            void setUpTimings();

            int m_clock_time;
            int m_cycle_counter;            
            int m_steps_per_attentive_cycle;

            float m_attentive_cycle_time;
            float m_integr_step;


            ControlSignalTimings m_signal_timings;

            TaskType m_task_type;
    };
}

#endif // GATINGSIGNAL_H
