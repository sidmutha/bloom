#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "bloom.h"

using namespace std;

//vector < vector <int> > adj_list;
#define NUMW 8 // width of no. in key
int n, m; // num of vertices
int edge_bfil_arr_size, edge_bfil_num_hash;

BinaryBloomFilter* edge_store_bf;

void get_adjacent (int v, vector<int> &adj_vec) {
  //cout << n<< endl;
  int k = 0;
  for (int i = 1; i <= n; i++) { // assumption: 1 indexed node numbers
    //cout << "^";
    if (edge_store_bf->check(v, i) != -1) { // check for edge between v-i
      //cout << k++ << endl;
      adj_vec.push_back(i);
    }
  }
}


bool colourify (int* colours, int v, int c) {
  colours[v-1] = c;
  int c2 = (c == 1) ? 2 : 1;
  vector <int>  adj_vec = vector<int>();
  get_adjacent(v, adj_vec);
  for (int i = 0; i < adj_vec.size(); i++) {
    int u = adj_vec[i];
    if (u == 0)
      continue;

    int c_u = colours[u-1];
    if (c_u == c) { // neighbour has same colour
      return false;
    } else if (c_u == c2) { // already coloured (with c2)
      continue;
    } else if (colourify (colours, u, c2) == false) { // recurse
      return false;
    }  
  }
  return true;
}

bool isBipartite () {
  int* colours = new int[n]();
  for (int i = 1; i <= n; i++) {
    if (colours[i-1] != 0) // visited
      continue;
    if (!colourify(colours, i, 1)) { // for every new component of the graph
      return false;
    } 
  }
  delete[] colours;
  return true;
}

int main (int argc, char** argv) {
  
  ifstream fs;
  
  fs.open(argv[1]); // graph
  fs >> n >> m; // n is global
  //cout  << "n:" << n;
  edge_bfil_arr_size = 100;
  edge_bfil_num_hash = 3;
  edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
  int u, v;
  //cout << "reading file\n";
  for (int i = 0; i < m; i++) { // m
    fs >> u >> v; // 0 indexed vertices? : assumed 1 indexed
    edge_store_bf->add(u, v); // add edge to BF
  }
  fs.close();
  //cout << "done reading file\n";
  
  bool b = isBipartite();
  cout << b << endl;
  
  /*
  fs.open(argc[2]); // testcase file
  int t; // test node
  //cout << "testcase\n";
  /*while(fs >> t){
    cout << bfs_out[t-1] << endl;
    }
  //cout << bfs_out[233751-1];
  fs.close();
  */
  return 0;
}

