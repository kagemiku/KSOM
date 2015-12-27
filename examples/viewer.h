#pragma once

#include <string>
#include <opencv2/core/core.hpp>


namespace kg {


class Viewer {
private:
	const std::string winName_;

public:
	explicit Viewer(const std::string& winName);
    Viewer(const Viewer& rhs) = delete;
	~Viewer(void);
    auto operator=(const Viewer& rhs) -> Viewer* = delete;

	auto showMat(const cv::Mat& source, int delay=0) -> void;
};


}
