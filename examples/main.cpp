#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../sources/ksom.hpp"
#include "../sources/node.hpp"
#include "../sources/evaluator.hpp"
#include "viewer.h"

#ifdef _MSC_VER
#include "opencv_lib.hpp"
#endif

using namespace std;


namespace {
    constexpr auto EPS              = 10e-6;
    constexpr auto RGB_MIN          = 0;
    constexpr auto RGB_MAX          = 255;
    constexpr auto RED_IDX          = 2;
    constexpr auto GREEN_IDX        = 1;
    constexpr auto BLUE_IDX         = 0;

    constexpr auto length           = 1024;
    constexpr auto dimension        = 3;
    constexpr auto rows             = 32;
    constexpr auto cols             = 32;
    constexpr auto matWidth         = 800;
    constexpr auto matHeight        = 800;
}


enum class SavingType : int {
    ORIGINAL    = 1,
    RESULT      = 2,
};


template <typename T>
void createMapMat(const vector<vector<kg::Node<T>>>& map, int rows, int cols, cv::Mat& image)
{
    const auto blockWidth   = matWidth/cols;
    const auto blockHeight  = matHeight/rows;

    for ( auto r = 0; r < rows; r++ ) {
        for ( auto c = 0; c < cols; c++ ) {
            cv::Point rectPos1(c * blockWidth, r * blockHeight);
            cv::Point rectPos2((c + 1) * blockWidth, (r + 1) * blockHeight);
            cv::Scalar rectColor(map[r][c][BLUE_IDX], map[r][c][GREEN_IDX], map[r][c][RED_IDX]);
            cv::rectangle(image, rectPos1, rectPos2, rectColor, -1);
        }
    }
}


auto fileNameOfMat(SavingType type, const string& suffixNumStr) -> string
{
    string fileName("result/");
    switch ( type ) {
        case SavingType::ORIGINAL:
            fileName += string("original");
            break;

        case SavingType::RESULT:
            fileName += string("result");
            break;
    }
    fileName += string("_");

    string suffix(suffixNumStr);
    replace(begin(suffix), end(suffix), '.', '_');
    fileName += suffix;
    fileName += string(".png");

    return fileName;
}


template <typename T>
auto evaluateAlpha0(const vector<kg::Node<T>>& source, const kg::Matrix<kg::Node<T>>& map) -> void
{
    const auto maxIterate       = 500*source.size();
    constexpr auto maxAlpha0    = 1.0;
    constexpr auto diffAlpha0   = 0.1;
    constexpr auto sigma0       = 16;
    constexpr auto repeat       = 1;


    for ( auto alpha0 = diffAlpha0; alpha0 <= maxAlpha0 + EPS; alpha0 += diffAlpha0 ) {
        auto totalTime              = 0;
        auto totalEvaluationValue   = 0.0;
        for ( auto n = 0; n < repeat; n++ ) {
            // create instance of KSOM and compute
            auto colorSOM       = make_unique<kg::KSOM<T>>(source, map, maxIterate, alpha0, sigma0);
            auto originalMat    = cv::Mat(cv::Size(matWidth, matHeight), CV_8UC3, cv::Scalar::all(0));
            createMapMat(colorSOM->map(), rows, cols, originalMat);
            cv::imwrite(fileNameOfMat(SavingType::ORIGINAL, to_string(alpha0)), originalMat);

            auto start      = chrono::system_clock::now();
            colorSOM->compute();
            auto end        = chrono::system_clock::now();
            auto diff       = end - start;
            totalTime += chrono::duration_cast<chrono::milliseconds>(diff).count();

            auto resultMat  = originalMat.clone();
            createMapMat(colorSOM->map(), rows, cols, resultMat);
            cv::imwrite(fileNameOfMat(SavingType::RESULT, to_string(alpha0)), resultMat);

            // evaluate map created by KSOM
            auto resultMap          = colorSOM->map();
            auto evaluationValue    = kg::Evaluator<T>::evaluateMap(source, resultMap);
            // cout << n << ": " << evaluationValue << endl;
            totalEvaluationValue += evaluationValue;
        }

        auto meanTime               = static_cast<double>(totalTime)/static_cast<double>(repeat);
        auto meanEvaluationValue    = static_cast<double>(totalEvaluationValue)/static_cast<double>(repeat);
        cout << "alpha0: " << alpha0 << " ..." << meanTime << "[ms]" << endl;
        cout << "evaluation value: " << meanEvaluationValue << endl;
        cout << endl;
    }
}


template <typename T>
auto evaluateSigma0(const vector<kg::Node<T>>& source, const kg::Matrix<kg::Node<T>>& map, int size) -> void
{
    constexpr auto maxIterate   = 10000;
    constexpr auto alpha0       = 0.8;
    constexpr auto diffSigma0   = 5.0;
    constexpr auto repeat       = 1;

    for ( auto sigma0 = static_cast<double>(size); sigma0 >= 0.0 - EPS; sigma0 -= diffSigma0 ) {
        auto totalTime = 0;
        auto totalEvaluationValue = 0.0;
        for ( auto n = 0; n < repeat; n++ ) {
            // create instance of KSOM and compute
            auto colorSOM   = make_unique<kg::KSOM<T>>(source, map, maxIterate, alpha0, sigma0);
            auto start      = chrono::system_clock::now();
            colorSOM->compute();
            auto end        = chrono::system_clock::now();
            auto diff       = end - start;
            totalTime += chrono::duration_cast<chrono::milliseconds>(diff).count();

            // evaluate map created by KSOM
            auto resultMap          = colorSOM->map();
            auto evaluationValue    = kg::Evaluator<T>::evaluateMap(source, resultMap);
            cout << n << ": " << evaluationValue << endl;
            totalEvaluationValue += evaluationValue;
        }

        auto meanTime               = static_cast<double>(totalTime)/static_cast<double>(repeat);
        auto meanEvaluationValue    = static_cast<double>(totalEvaluationValue)/static_cast<double>(repeat);
        cout << "sigma0: " << sigma0 << " ..." << meanTime << "[ms]" << endl;
        cout << "evaluation value: " << meanEvaluationValue << endl;
        cout << endl;
    }
}


int main()
{
    // create array of input vector
    vector<kg::Node<int>> src(length, kg::Node<int>(dimension));

    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randRGB(RGB_MIN, RGB_MAX);
    for ( auto& node : src ) {
        for ( auto i = 0; i < dimension; i++ ) {
            node[i] = randRGB(mt);
        }
    }

    // create matrix of model vector
    kg::Matrix<kg::Node<int>> map(rows, vector<kg::Node<int>>(cols));

    uniform_int_distribution<> randIdx(0, length - 1);
    for ( auto& row : map ) {
        for ( auto& node : row ) {
            // set input vector at random
            int idx = randIdx(mt);
            node = src[idx];
         }
    }

    // finding best alpha0
    evaluateAlpha0(src, map);

    // finding best sigma0
    //evaluateSigma0(src, map, rows);

    return 0;
}
