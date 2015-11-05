#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include "../KSOM.h"
#include "../Node.h"
using namespace std;


namespace {
    const int RGB_MIN = 0;
    const int RGB_MAX = 255;
}

int main()
{ 
    // create array of input vector
	const int length = 100;
	const int dimension = 3;
	Node<int>* src = new Node<int>[length];
	for (int i = 0; i < length; i++ ) {
		src[i] = Node<int>(dimension);
	}

    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randRGB(RGB_MIN, RGB_MAX);
    for ( int i = 0; i < length; i++ ) {
		for ( int j = 0; j < dimension; j++ ) {
			src[i][j] = randRGB(mt);
		}
	}
	
    // create matrix of model vector
	const int rows = 40, cols = 40;
	Node<int>** map = new Node<int>*[rows];
	for ( int i = 0; i < rows; i++ ) {
		map[i] = new Node<int>[cols];
		for ( int j = 0; j < cols; j++ ) {
			map[i][j] = Node<int>(dimension);
		}
	}
 
    uniform_int_distribution<> randIdx(0, length - 1);
	for ( int i = 0; i < rows; i++ ) {
		for ( int j = 0; j < cols; j++ ) {
            // set input vector at random
            int idx = randIdx(mt);
			map[i][j] = src[idx]; 
		 }
	}
	

    // create instance of KSOM and compute
	const double alpha0 = 0.1;
	const double sigma0 = 20.0;
	KSOM<int>* colorSOM = new KSOM<int>(src, length, map, rows, cols, length, alpha0, sigma0); 
	while ( colorSOM->calcIterate() ) {
        cout << colorSOM->time() << endl;
	}


	delete[] src;
	for ( int i = 0; i < rows; i++ ) {
		delete[] map[i];
	}
	delete[] map; 
	delete colorSOM;

	return 0;
}

