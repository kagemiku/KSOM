#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include "../sources/evaluator.h"
#include "../sources/ksom.h"
#include "../sources/node.h"
using namespace std;


namespace {
    constexpr auto RGB_MIN = 0;
    constexpr auto RGB_MAX = 255;
    constexpr auto EPS = 10e-6;
}


template <typename T>
auto evaluateAlpha0(const vector<kg::Node<T>>& source, const vector<vector<kg::Node<T>>>& map) -> void
{
    constexpr auto maxIterate = 10000;
    constexpr auto maxAlpha0 = 1.0f;
    constexpr auto diffAlpha0 = 0.1f;
    constexpr auto sigma0 = 20.0;
    constexpr auto repeat = 20;
    
    for ( auto alpha0 = diffAlpha0; alpha0 <= maxAlpha0 + EPS; alpha0 += diffAlpha0 ) {
        auto totalTime = 0;
        auto totalEvaluateValue = 0.0f;
        for ( auto n = 0; n < repeat; n++ ) {
            // create instance of KSOM and compute
            auto colorSOM = make_unique<kg::KSOM<T>>(source, map, maxIterate, alpha0, sigma0);
            auto start = chrono::system_clock::now();
            colorSOM->compute();
            auto end = chrono::system_clock::now();
            auto diff = end - start;
            totalTime += chrono::duration_cast<chrono::milliseconds>(diff).count();

            // evaluate map created by KSOM
            auto evaluator = make_unique<kg::Evaluator<T>>(colorSOM->map());
            auto evaluateValue = evaluator->evaluateMap();
            cout << n << ": " << evaluateValue << endl;
            totalEvaluateValue += evaluateValue;
        }

        auto meanTime = static_cast<double>(totalTime)/static_cast<double>(repeat);
        auto meanEvaluateValue = static_cast<double>(totalEvaluateValue)/static_cast<double>(repeat);
        cout << "alpha0: " << alpha0 << " ..." << meanTime << "[ms]" << endl;
        cout << "evaluate value: " << meanEvaluateValue << endl; 
        cout << endl;
    }
}


template <typename T>
auto evaluateSigma0(const vector<kg::Node<T>>& source, const vector<vector<kg::Node<T>>>& map, int size) -> void
{
    constexpr auto maxIterate = 10000;
    constexpr auto alpha0 = 0.8f;
    constexpr auto diffSigma0 = 5.0f;
    constexpr auto repeat = 1;
    
    for ( auto sigma0 = static_cast<double>(size); sigma0 >= 0.0f - EPS; sigma0 -= diffSigma0 ) {
        auto totalTime = 0;
        auto totalEvaluateValue = 0.0f;
        for ( auto n = 0; n < repeat; n++ ) {
            // create instance of KSOM and compute
            auto colorSOM = make_unique<kg::KSOM<T>>(source, map, maxIterate, alpha0, sigma0);
            auto start = chrono::system_clock::now();
            colorSOM->compute();
            auto end = chrono::system_clock::now();
            auto diff = end - start;
            totalTime += chrono::duration_cast<chrono::milliseconds>(diff).count();

            // evaluate map created by KSOM
            auto evaluator = make_unique<kg::Evaluator<T>>(colorSOM->map());
            auto evaluateValue = evaluator->evaluateMap();
            cout << n << ": " << evaluateValue << endl;
            totalEvaluateValue += evaluateValue;
        }

        auto meanTime = static_cast<double>(totalTime)/static_cast<double>(repeat);
        auto meanEvaluateValue = static_cast<double>(totalEvaluateValue)/static_cast<double>(repeat);
        cout << "sigma0: " << sigma0 << " ..." << meanTime << "[ms]" << endl;
        cout << "evaluate value: " << meanEvaluateValue << endl; 
        cout << endl;
    }
}


int main()
{ 
    // create array of input vector
    constexpr auto length = 1600;
    constexpr auto dimension = 3;
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
    constexpr auto rows = 40, cols = 40;
    vector<vector<kg::Node<int>>> map(rows, vector<kg::Node<int>>(cols));
 
    uniform_int_distribution<> randIdx(0, length - 1);
    for ( auto& row : map ) {
        for ( auto& node : row ) {
            // set input vector at random
            int idx = randIdx(mt);
            node = src[idx];
         }
    }
    

    // finding best alpha0
    //evaluateAlpha0(src, map);

    // finding best sigma0
    evaluateSigma0(src, map, rows);

    return 0;
}
