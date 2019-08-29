#ifndef GUI_CONFIG_H
#define GUI_CONFIG_H

class GUI_config {
public:
    GUI_config(){
        gui_mode = ACTIVATION;
    }

    int gui_mode;
    enum Mode {
        ACTIVATION = 0,
        SUPPRESIVE_SURROUND = 1,
        GATING_CONTROL = 2
    };
};

#endif // GUI_CONFIG_H
