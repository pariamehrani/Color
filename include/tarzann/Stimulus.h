#ifndef SHOW_STIMULI_H
#define SHOW_STIMULI_H

#include <iostream>
#include <string>

#include <tarzann/Matrix.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace tarzann
{

    class Matrix;

    class Stimulus
    {
        public:
            Stimulus(uint32_t im_width,
                     uint32_t im_height,
                     bool is_color);

            ~Stimulus();

            void loadStimulus(std::string im_name);

            Matrix* getMatrix(uint32_t index);

            uint32_t getWidth();

            uint32_t getHeight();

        private:
            void captureAndProcessInput();

            cv::Mat resizeInput(const cv::Mat input_img,
                                const uint32_t w,
                                const uint32_t h);

            void separateRGBandLuminance(const cv::Mat input_img);

        protected:
            uint32_t m_im_width;
            uint32_t m_im_height;
            bool m_is_color;
            std::string m_im_name;

            std::vector<cv::Mat> bgrl;
            Matrix* m_channels[4];
    };

}
#endif
