#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include "../KSOM.h"
#include "../Node.h"
using namespace std;

void testNode();

namespace {
	const int VIEWER_WIDTH	= 800;
	const int VIEWER_HEIGHT	= 800;
	const int RED_IDX	= 0;
	const int GREEN_IDX = 1;
	const int BLUE_IDX	= 2; 
};


int main()
{ 
	const int length = 100;
	const int dimension = 3;
	Node<int>* src = new Node<int>[length];
	for (int i = 0; i < length; i++ ) {
		src[i] = Node<int>(dimension);
	}

    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randRGB(0, 255);
    for ( int i = 0; i < length; i++ ) {
		for ( int j = 0; j < dimension; j++ ) {
			src[i][j] = randRGB(mt);
		}
	}
	
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
            int idx = randIdx(mt);
			map[i][j] = src[idx]; 
		 }
	}
	

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


template <typename T>
void show(const Node<T>& node)
{
	for ( int i = 0; i < node.size(); i++ ) {
		cout << node.elem(i) << ", ";
	}
	cout << endl;
}


void testNode()
{
	const int size = 3;
	Node<int> node(size);
	for ( int i = 0; i < node.size(); i++ ) {
		node.setElem(i, i);
	}
	// show(node);
	cout << "+node: ";
	show(+node);
	cout << "-node: ";
	show(-node);

	Node<int> node2(size);
	for ( int i = 0; i < node.size(); i++ ) {
		node2.setElem(i + 1, i);
	}
	// show(node2);

	
	Node<int> node3(size);
	node3 = node + node2;
	cout << "operator+: ";
	show(node3);

	Node<int> node4(size);
	node4 = node - node2;
	cout << "operator-: ";
	show(node4);
	
	Node<int> node5 = node;
	node5 += node2;
	cout << "operator+=: ";
	show(node5);
	
	Node<int> node6 = node;
	node6 -= node2;
	cout << "operator-=: ";
	show(node6);

	Node<int> node7(size);
	node7 = node + 2;
	cout << "operator+(val): ";
	show(node7);

	Node<int> node8(size);
	node8 = node - 2;
	cout << "operator-(val): ";
	show(node8);

	Node<int> node9(node);
	node9 += 2;
	cout << "operator+=(val): ";
	show(node9);

	Node<int> node10(node);
	node10 -= 2;
	cout << "operator-=(val): ";
	show(node10);

	cout << "node[0]: " << node10[0] << endl;
	cout << "node[1]: " << node10[1] << endl;
	cout << "node[2]: " << node10[2] << endl;
	try {
		cout << "node[3]: " << node10[3] << endl;
	} catch ( const std::string& msg ) {
		cerr << msg << endl;
		exit(1);
	}
}

