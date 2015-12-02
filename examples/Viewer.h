#pragma once

#include <string>
#include <opencv2/core/core.hpp>
#include "opencv_lib.hpp"


class Viewer {
private:
	const std::string winName_;

private:
	Viewer(const Viewer& rhs);

public:
	explicit Viewer(const std::string& winName);
	~Viewer(void);

	auto showMat(const cv::Mat& source, int delay=0) -> void;
}; 
