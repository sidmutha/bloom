#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include "bloom.h"

using namespace std;

#define NUMW 8 // width of no. in key

int n; // num of vertices
int bfs_bfil_arr_size, bfs_bfil_num_hash;
int edge_bfil_arr_size, edge_bfil_num_hash;


/*
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
      if (bf->check(c) != -1) {
	bf->add(c, h);
	q.push(c);
      }
      // directed / undirected?
    }
    q.pop();
  }
  
  
  return bf;
}
*/

void get_adjacent (int v, BinaryBloomFilter* bf, vector<int> &adj_vec) {
  //cout << n<< endl;
  int k = 0;
  for (int i = 1; i <= n; i++) { // assumption: 1 indexed node numbers
    //cout << "^";
    if (bf->check(v, i) != -1) { // check for edge between v-i
      //cout << k++ << endl;
      adj_vec.push_back(i);
    }
  }
}


// simple BFS on edges stored in bf
BloomFilter* BFS2 (BinaryBloomFilter* edge_store_bbf, int v) {
  vector<int> adj_vec = vector<int>();
  
  int h = 1;
  queue<int> q;
  BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
  
  q.push(v);
  bf->add(v, h); // visited
  
  while (!q.empty()) {
    int f = q.front();
    h++;
    get_adjacent(f, edge_store_bbf, adj_vec);
    //cout << "#" << h << endl;
    //cout << "v:" << adj_vec.size();
    for (int i = 0; i < adj_vec.size(); i++) {
      int c = adj_vec[i];
      //cout << c << endl;
      if (bf->check(c) == -1) { // not visited
	//cout << "ee\n";
	bf->add(c, h);
	q.push(c);
      }
      // directed/undirected?
    }
    adj_vec.clear();
    q.pop();
  }
  
  return bf;
}

/*
int main (int argc, char** argv) {
  cout << argc << endl;
  if (argc != 7) {
    cout << "run as: <executable> <graph file> <testcase file> <edge_bfil_arr_size> <edge_bfil_num_hash> <bfs_bfil_arr_size> <bfs_bfil_num_hash>" << endl;
    exit(1);
  }
    
  edge_bfil_arr_size = atoi(argv[3]);
  edge_bfil_num_hash = atoi(argv[4]);
  
  bfs_bfil_arr_size = atoi(argv[5]);
  bfs_bfil_num_hash = atoi(argv[6]);
  
  
  ifstream fs;
  fs.open(argv[1]); // graph
  
  int m;
  fs >> n >> m;
  //cout  << "n:" << n;
  BinaryBloomFilter* edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
  int j = 0;
  int u, v;
  //cout << "reading file\n";
  for (int i = 0; i < m; i++) { // m
    fs >> u >> v; // 0 indexed vertices? : assumed 1 indexed
    edge_store_bf->add(u, v); // add edge to BF
  }
  fs.close();
  //cout << "done reading file\nrunning bfs\n";
  //cout << BFS2 (bf, 1); // start BFS on 1
  
  
  // bfs result in bloomfilter
  
  BloomFilter* bfs_out = BFS2(edge_store_bf, 1); // start node = 1
  //cout << "done bfs\n";
  
  fs.open(argv[2]); // testcase file
  int t, h; // test node, real h
  int b, p = 0, q = 0;
  while(fs >> t >> h){
    q++;
    b = bfs_out->check(t);
    if (b == h) 
      p++;
    cout << t << " " << b << " " << h << endl;
  }
  float ratio = p/(float)q;
  //cout << "total: " << q << "; correct: " << p << " ; ratio: " << ratio << endl;
  cout << ratio << endl;
  fs.close();
  
  delete edge_store_bf;
  delete bfs_out;
  
  return 0;
}
*/


int main (int argc, char** argv) {
  //cout << argc << endl;
  
    
  //edge_bfil_arr_size = atoi(argv[3]);
  //edge_bfil_num_hash = atoi(argv[4]);
  
  //bfs_bfil_arr_size = atoi(argv[5]);
  //bfs_bfil_num_hash = atoi(argv[6]);
  
  
  ifstream fs;
  
  fs.open(argv[2]); // testcase file
  vector<int> nodes = vector<int>();
  vector<int> dists = vector<int>();
  
  int t, h; // test node, real h
  
  while (fs >> t >> h) {
    nodes.push_back(t);
    dists.push_back(h);
  }
  
  
  fs.close();
  
  for(edge_bfil_arr_size = 100; edge_bfil_arr_size <= 10000; edge_bfil_arr_size += 400) {
    for(edge_bfil_num_hash = 1; edge_bfil_num_hash <= 10; edge_bfil_num_hash += 2) {
      fs.open(argv[1]); // graph
      int m;
      fs >> n >> m; // n is global
      //cout  << "n:" << n;
      BinaryBloomFilter* edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
      int u, v;
      //cout << "reading file\n";
      for (int i = 0; i < m; i++) { // m
	fs >> u >> v; // 0 indexed vertices? : assumed 1 indexed
	edge_store_bf->add(u, v); // add edge to BF
      }
      fs.close();
      //cout << "done reading file\nrunning bfs\n";
     
      for(bfs_bfil_arr_size = 100; bfs_bfil_arr_size <= 10000; bfs_bfil_arr_size += 200) {
	for(bfs_bfil_num_hash = 1; bfs_bfil_num_hash <= 10; bfs_bfil_num_hash += 2) {
	 
	  // bfs result in bloomfilter
	 
	  BloomFilter* bfs_out = BFS2(edge_store_bf, 1); // start node = 1
	  //cout << "done bfs\n";
	 
	  //fs.open(argv[2]); // testcase file
	  //int t, h; // test node, real h
	  int b, p = 0, q = 0; // b: bfs out; p: correct result; q: total
	  
	  //while (fs >> t >> h) {
	  int l = nodes.size();
	  for(int i = 0; i < l; i++) {
	    q++;
	    b = bfs_out->check(nodes[i]);
	    if (b == dists[i]) 
	      p++;
	    //cout << nodes[i] << " " << b << " " << dists[i] << endl;
	  }
	  float ratio = p/(float)q;
	  //cout << "total: " << q << "; correct: " << p << " ; ratio: " << ratio << endl;
	  cout << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << bfs_bfil_arr_size << " " << bfs_bfil_num_hash << " " << ratio << endl;
	  //fs.close();
	 
	 
	  delete bfs_out;
	  //break;
	}
      }
      delete edge_store_bf;
      //break;
    }
  }
  return 0;
}

