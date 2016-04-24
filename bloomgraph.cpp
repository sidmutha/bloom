#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "bloom.h"

using namespace std;

#define NUMW 8

int** generate_random_graph (int num_vertices) {
  srand(time(0));				       

  int** graph = new int* [num_vertices];
  
  for (int i = 0; i < num_vertices; i++) {
    graph[i] = new int[num_vertices]();
    for (int j = 0; j < num_vertices; j++) {
      int r = rand() % 2;
      graph[i][j] = r;
      //cout << r;
    }
  }
  //cout << endl;
  return graph;
}

int main (int argc, char** argv) {
  
  
  // graph size
  int g[9] = {10, 100, 500, 1000, 5000, 10000, 100000, 500000, 1000000};

  // bbf m array
  int b[7] = {100, 500, 1000, 5000, 10000, 100000, 500000};
  
  for (int i = 0; i < 9; i++) {
    int num_vertices = g[i];
    int** graph = generate_random_graph(num_vertices);
    for (int j = 0; j < 7; j++) {
      int m = b[j];
      for (int k = 2; k <= 10; k += 2) {
	BinaryBloomFilter bbf (m, k, NUMW);
	int t = 0;
	for (int p = 0; p < num_vertices; p++) {
	  for (int q = 0; q < num_vertices; q++) {
	    if (graph[p][q] == 1) {
	      bbf.add(p, q);
	      t++;
	    }
	  }
	}
	int t1 = 0;
	for (int p = 0; p < num_vertices; p++) {
	  for (int q = 0; q < num_vertices; q++) {
	    if (bbf.check (p, q) != -1) {
	      t1++;
	    }
	  }
	}
	
	cout <<  num_vertices << " " << m << " " << k 
	     << " " << t << " " << t1 << " " << t1-t << endl;
	//return 0;
      }
    }
  }
  
  
  return 0;
}
