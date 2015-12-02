#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include "../KSOM.h"
#include "../Node.h"
using namespace std;


namespace {
    constexpr auto RGB_MIN = 0;
    constexpr auto RGB_MAX = 255;
}

int main()
{ 
    // create array of input vector
	constexpr auto length = 100;
	constexpr auto dimension = 3;
    vector<Node<int>> src(length);
    for ( auto& node : src ) {
		node = Node<int>(dimension);
    }

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
    vector<vector<Node<int>>> map(rows, vector<Node<int>>());
    for ( auto& row : map ) {
		row = vector<Node<int>>(cols);
    }
 
    uniform_int_distribution<> randIdx(0, length - 1);
	for ( auto& row : map ) {
		for ( auto& node : row ) {
            // set input vector at random
            int idx = randIdx(mt);
			node = src[idx];
		 }
	}
	

    // create instance of KSOM and compute
    constexpr auto maxIterate = 100;
	constexpr auto alpha0 = 0.1;
	constexpr auto sigma0 = 20.0;
	KSOM<int>* colorSOM = new KSOM<int>(src, map, maxIterate, alpha0, sigma0);
	while ( colorSOM->computeOnes() ) {
        cout << colorSOM->time() << endl;
	}


	delete colorSOM;

	return 0;
}

