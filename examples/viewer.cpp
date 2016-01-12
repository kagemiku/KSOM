#include "viewer.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>


namespace kg {


Viewer::Viewer(const std::string& winName)
	:winName_(winName)
{
	cv::namedWindow(winName_, cv::WINDOW_AUTOSIZE);
}


Viewer::~Viewer(void)
{
    cv::destroyWindow(winName_);
}


auto Viewer::showMat(const cv::Mat& source, int delay) -> void
{
	cv::imshow(winName_, source);
	cv::waitKey(delay);
}


}
