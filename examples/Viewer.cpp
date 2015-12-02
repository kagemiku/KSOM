#include "Viewer.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>


Viewer::Viewer(const std::string& winName)
	:winName_(winName)
{
	cv::namedWindow(winName_, cv::WINDOW_AUTOSIZE);
}


Viewer::Viewer(const Viewer& rhs)
{
}


Viewer::~Viewer(void)
{
} 


auto Viewer::showMat(const cv::Mat& source, int delay) -> void
{
	cv::imshow(winName_, source);
	cv::waitKey(delay);
}