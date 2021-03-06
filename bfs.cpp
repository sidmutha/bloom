#include <iostream>
#include <vector>
#include <queue>
#include "bloom.h"

using namespace std;

vector < vector <int> > adj_list;

BloomFilter* BFS (int n) {
  int h = 0;
  queue<int> q;
  BloomFilter* bf = new BloomFilter(100, 4, 4);// 
  string key;
 
  q.push(n);
  bf->add(n, h++); // visited

  while (!q.empty()) {
    int f = q.front();
    h++;
    for (int i = 0; i < adj_list[f].size(); i++) {
      int c = adj_list[f][i];
      if (bf->check(c) == -1) {
	bf->add(c, h);
	q.push(c);
      }
      // directed / undirected?
    }
    q.pop();
  }
  
  return bf;
}

int main (int argv, char** argc) {
  int m, n;
  cin >> n >> m;
  
  adj_list.resize(n, vector<int>(2*m/n)); // avg degree
  int u, v;
  for (int i = 0; i < m; i++) {
    cin >> u >> v;
    adj_list[u].push_back(v);
  }
  return 0;
}
