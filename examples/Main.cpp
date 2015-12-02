#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv_lib.hpp"
#include "Viewer.h"
#include "../KSOM.h"
#include "../Node.h"
using namespace std;


namespace {
    constexpr auto RGB_MIN          = 0;
    constexpr auto RGB_MAX          = 255;
    constexpr auto RED_IDX          = 2;
    constexpr auto GREEN_IDX        = 1;
    constexpr auto BLUE_IDX         = 0;
    constexpr auto VIEWER_WIDTH     = 800;
    constexpr auto VIEWER_HEIGHT    = 800;
}

template <typename T>
void createMapMat(const vector<vector<Node<T>>>& map, int rows, int cols, cv::Mat& image)
{
    const auto blockWidth= VIEWER_WIDTH/cols;
    const auto blockHeight  = VIEWER_HEIGHT/rows;

    for ( auto r = 0; r < rows; r++ ) {
        for ( auto c = 0; c < cols; c++ ) {
            cv::Point rectPos1(c * blockWidth, r * blockHeight);
            cv::Point rectPos2((c + 1) * blockWidth, (r + 1) * blockHeight);
            cv::Scalar rectColor(map[r][c][BLUE_IDX], map[r][c][GREEN_IDX], map[r][c][RED_IDX]);
            cv::rectangle(image, rectPos1, rectPos2, rectColor, -1);
        }
    }
} 

int main()
{ 
    // create array of input vector
    constexpr auto length = 10000;
    constexpr auto dimension = 3;
    vector<Node<int>> src(length, Node<int>(dimension));

    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randRGB(RGB_MIN, RGB_MAX);
    for ( auto& node : src ) {
        for ( auto i = 0; i < dimension; i++ ) {
            node[i] = randRGB(mt);
        }
    }
    
    // create matrix of model vector
    constexpr auto rows = 40, cols = 40;
    vector<vector<Node<int>>> map(rows, vector<Node<int>>(cols));
 
    uniform_int_distribution<> randIdx(0, length - 1);
    for ( auto& row : map ) {
        for ( auto& node : row ) {
            // set input vector at random
            int idx = randIdx(mt);
            node = src[idx];
         }
    }
    
    // create instance of KSOM and compute
    constexpr auto maxIterate = 1000;
    constexpr auto alpha0 = 0.1;
    constexpr auto sigma0 = 20.0;
    auto colorSOM = make_unique<KSOM<int>>(src, map, maxIterate, alpha0, sigma0);
    auto viewer = make_unique<Viewer>(std::string("ColorMap"));
    auto mapMat    = cv::Mat(cv::Size(VIEWER_WIDTH, VIEWER_HEIGHT), CV_8UC3, cv::Scalar::all(255));
    while ( colorSOM->computeOnes() ) {
        cout << colorSOM->time() << endl;
        createMapMat<int>(colorSOM->map(), rows, cols, mapMat);
        viewer->showImage(mapMat, 1);                
    }
    cv::waitKey(0);
 
    return 0;
}
