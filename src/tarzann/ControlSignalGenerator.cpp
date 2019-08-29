#include <tarzann/Debug.h>
#include <tarzann/ControlSignalGenerator.h>

using namespace tarzann;
using namespace std;

ControlSignalGenerator::ControlSignalGenerator(int steps_per_attentive_cycle,
                                               TaskType task_type)
{
    m_steps_per_attentive_cycle = steps_per_attentive_cycle;
    m_task_type = task_type;

    m_clock_time = -1;
    m_cycle_counter = 0;

    //set the attentive cycle time based on the task type;
    setUpTimings();
}

void ControlSignalGenerator::setUpTimings()
{
    //cycle times
    if (m_task_type == TASK_CATEGORIZATION)
        m_attentive_cycle_time = 100.0;
    else if (m_task_type == TASK_DETECTION)
        m_attentive_cycle_time = 150.0;
    else if (m_task_type == TASK_IDENTIFICATION)
        m_attentive_cycle_time = 215.0;
    else if (m_task_type == TASK_WITHIN_CATEGORY)
        m_attentive_cycle_time = 215.0;
    else if (m_task_type == TASK_LOCALIZATION)
        m_attentive_cycle_time = 250.0;
    else if (m_task_type == TASK_GAZE_SHIFT)
        m_attentive_cycle_time = 250.0;
    else if (m_task_type == TASK_MEASURE)
        m_attentive_cycle_time = 350.0;

    //create arrays for storing sync for each attentive cycle
    m_signal_timings.m_priming = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_find_winner = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_matching = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_recurrent_localization = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_reinterpret = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_reset_blackboard = new bool[m_steps_per_attentive_cycle];
    m_signal_timings.m_next_fixation = new bool[m_steps_per_attentive_cycle];

    //set the sync flags
    setupPrimingSync();
    setupNextFixation();
    setupFindWinnerSync();
}

void ControlSignalGenerator::setupPrimingSync()
{
    for (int i=0; i<m_steps_per_attentive_cycle; i++)
    {
        m_signal_timings.m_priming[i] = false;
    }
}

void ControlSignalGenerator::setupFindWinnerSync()
{
    for (int i=0; i<m_steps_per_attentive_cycle; i++)
    {
        m_signal_timings.m_find_winner[i] = false;
    }

    int idx = (int) ((100.0/ m_attentive_cycle_time) *
                     (float) m_steps_per_attentive_cycle);

    m_signal_timings.m_find_winner[idx] = true;
}

void ControlSignalGenerator::setupNextFixation()
{
    for (int i=0; i<m_steps_per_attentive_cycle; i++)
    {
        m_signal_timings.m_next_fixation[i] = false;
    }
    m_signal_timings.m_next_fixation[0] = true;
}

ControlSignal ControlSignalGenerator::updateTimer()
{    
    m_clock_time++;

    m_cycle_counter = m_clock_time % m_steps_per_attentive_cycle;

    ControlSignal signal;

    signal.m_do_find_winner = m_signal_timings.m_find_winner[m_cycle_counter];
    signal.m_do_matching = m_signal_timings.m_matching[m_cycle_counter];
    signal.m_do_next_fixation = m_signal_timings.m_next_fixation[m_cycle_counter];
    signal.m_do_priming = m_signal_timings.m_priming[m_cycle_counter];
    signal.m_do_recurrent_localization = m_signal_timings.m_recurrent_localization[m_cycle_counter];
    signal.m_do_reinterpret = m_signal_timings.m_reinterpret[m_cycle_counter];
    signal.m_do_reset_blockboard = m_signal_timings.m_reset_blackboard[m_cycle_counter];

    return signal;
}

int ControlSignalGenerator::getTime()
{
    return m_clock_time;
}

int* ControlSignalGenerator::getTimePtr()
{
    return &m_clock_time;
}

ControlSignalGenerator::~ControlSignalGenerator()
{
    delete [] m_signal_timings.m_priming;
    delete [] m_signal_timings.m_find_winner;
    delete [] m_signal_timings.m_matching;
    delete [] m_signal_timings.m_recurrent_localization;
    delete [] m_signal_timings.m_reinterpret;
    delete [] m_signal_timings.m_reset_blackboard;
    delete [] m_signal_timings.m_next_fixation;
}

