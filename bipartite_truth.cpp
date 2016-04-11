#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "bloom.h"

using namespace std;

vector < vector <int> > adj_list;
int n;

//  TODO: test this with small graphs and write bloomfilt version
bool colourify (int* colours, int v, int c) {
  colours[v-1] = c;
  int c2 = (c == 1) ? 2 : 1;
  for (int i = 0; i < adj_list[v-1].size(); i++) {
    int u = adj_list[v-1][i];
    if (u == 0)
      continue;

    int c_u = colours[u-1];
    if (c_u == c) { // neighbour has same colour
      return false;
    } else if (colourify (colours, u, c2) == false) { // recurse
      return false;
    }  
  }
  return true;
}

bool isBipartite () {
  int* colours = new int[n]();
  for (int i = 1; i <= n; i++) {
    if (colours[i-1] != 0) 
      continue;
    if (!colourify(colours, i, 1)) { // for every new component of the graph
      return false;
    } 
  }
  return true;
}

int main (int argv, char** argc) {
  
  ifstream fs;
  
  fs.open(argc[1]); // graph
  
  int m;
  
  fs >> n >> m;
  
  adj_list.resize(n, vector<int>(2*m/n)); // avg degree
  int u, v;
  //cout << "reading file" << endl;
  for (int i = 0; i < m; i++) {
    fs >> u >> v;
    adj_list[u-1].push_back(v);
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

