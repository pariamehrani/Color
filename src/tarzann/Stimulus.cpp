#include<tarzann/Stimulus.h>

using namespace cv;
using namespace std;
using namespace tarzann;

Stimulus::Stimulus(uint32_t im_width, uint32_t im_height,
                   bool is_color)
{
    m_im_width=im_width;
    m_im_height=im_height;
    m_im_name="";
    m_is_color=is_color;

    for (int i=0; i<4; i++)
    {
        m_channels[i] = new Matrix(m_im_width, m_im_height);
    }
}

void Stimulus::loadStimulus(string im_name)
{
    m_im_name = im_name;

    captureAndProcessInput();
}

void Stimulus::captureAndProcessInput()
{
    Mat input_img;
    input_img = imread(m_im_name, CV_LOAD_IMAGE_COLOR);// Read color file
    input_img.convertTo(input_img, CV_32F);
    //cv::normalize(input_img, input_img, 0.0, 100.0, cv::NORM_MINMAX);

    //Chosen size to be processed
    Mat resize_img=resizeInput(input_img,m_im_width,m_im_height);

    if(! resize_img.data )
    {
        cout <<  "Could not open or find the image" << std::endl;
    }
    else
    {
        separateRGBandLuminance(resize_img);
    }
}

Stimulus::~Stimulus()
{
    for (int i=0; i<4; i++)
    {
        delete m_channels[i];
    }
}

cv::Mat Stimulus::resizeInput(const cv::Mat input_img,
                              const uint32_t w,
                              const uint32_t h)
{
    Mat resized_im;                                       //destination image
    Size size(w,h);                                       //desired image size
    resize(input_img,resized_im,size,0,0,INTER_CUBIC);   //resize operation
    return resized_im;
}

void Stimulus::separateRGBandLuminance(const cv::Mat input_img)
{
    bgrl.clear();

    //store our RGB matrices as BGR in a vector
    bgrl.push_back( Mat(m_channels[2]->getYSize(),
                    m_channels[2]->getXSize(),
                    CV_32F,
                    m_channels[2]->getData(),
                    m_channels[2]->getStep()) );

    bgrl.push_back( Mat(m_channels[1]->getYSize(),
                    m_channels[1]->getXSize(),
                    CV_32F,
                    m_channels[1]->getData(),
                    m_channels[1]->getStep()) );

    bgrl.push_back( Mat(m_channels[0]->getYSize(),
                    m_channels[0]->getXSize(),
                    CV_32F,
                    m_channels[0]->getData(),
                    m_channels[0]->getStep()) );

    //split source
    split(input_img,bgrl);

    //luminance channel
    bgrl.push_back( Mat(m_channels[3]->getYSize(),
                    m_channels[3]->getXSize(),
                    CV_32F,
                    m_channels[3]->getData(),
                    m_channels[3]->getStep()) );

    //convert to gray
    cv::cvtColor(input_img,bgrl[3], CV_BGR2GRAY);
}

Matrix* Stimulus::getMatrix(uint32_t index)
{
    return m_channels[index];
}

uint32_t Stimulus::getWidth()
{
    return m_im_width;
}

uint32_t Stimulus::getHeight()
{
    return m_im_height;
}
