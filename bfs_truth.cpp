#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include "bloom.h"

using namespace std;

vector < vector <int> > adj_list;
int n;

int* BFS (int v) {
  int h = 1;
  queue<int> q;
  int* visited = new int[n]();
  string key;
  
  q.push(v);
  //bf->add(v, h++); // visited
  cout << v << " " << h << endl;
  visited[v-1] = h;
  
  while (!q.empty()) {
    int f = q.front();
    //cout << f << " " << adj_list[f-1].size() << endl;
    h++;
    for (int i = 0; i < adj_list[f-1].size(); i++) {
      int c = adj_list[f-1][i];
      
      if (c == 0)
	continue;
      //else 
      //cout << c << endl;
      if (visited[c-1] == 0) {
	visited[c-1] = h;
	q.push(c);
	cout << c << " " << h << endl;
      }
      // directed / undirected?
    }
    q.pop();
  }
  
  
  return visited;
}

int main (int argc, char** argv) {
  
  ifstream fs;
  
  fs.open(argv[1]); // graph
  
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
  
  int* bfs_out = BFS(atoi(argv[2]));
  
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
