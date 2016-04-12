#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "bloom.h"

using namespace std;

#define NUMW 8 // width of no. in key

int bfs_bfil_arr_size, bfs_bfil_num_hash;
int edge_bfil_arr_size, edge_bfil_num_hash;


vector < vector <int> > adj_list;
vector<int> nodes = vector<int>();
vector<int> dists = vector<int>();


int n, m;

int* BFS0 (int v) {
  int h = 1;
  queue<int> q;
  int* visited = new int[n]();
  string key;
  
  q.push(v);
  //bf->add(v, h++); // visited
  //cout << v << " " << h << endl;
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
	//cout << c << " " << h << endl;
	nodes.push_back(c);
	dists.push_back(h);
      }
      // directed / undirected?
    }
    q.pop();
  }
  
  return visited;
}

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

BloomFilter* BFS3 (int n) {
  int h = 1;
  queue<int> q;
  BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
 
  q.push(n);
  bf->add(n, h); // visited

  while (!q.empty()) {
    int f = q.front();
    h++;
    for (int i = 0; i < adj_list[f].size(); i++) {
      int c = adj_list[f][i];
      if (bf->check(c) == -1) { // not visited
	bf->add(c, h);
	q.push(c);
      }
      // directed / undirected?
    }
    q.pop();
  }
  //cout << "#" << h << endl;
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


vector<int> * generate_random_num_list(int len) {
  vector<int>* rand_list = new vector<int> ();
  int r;
  while (rand_list->size() != len) {
    r = 1 + rand() % n;
    if (find(rand_list->begin(), rand_list->end(), r) == rand_list->end()) {
      //cout << "#r: " << r << endl;
      rand_list->push_back(r);
    }
  }
  return rand_list;
}  

int main (int argc, char** argv) {
  //cout << argc << endl;
  nodes = vector<int>();
  dists = vector<int>();
 
  ifstream fs;
  
  fs.open(argv[1]); // graph
  fs >> n >> m; // n, m are global
  adj_list.resize(n, vector<int>(2*m/n)); // avg degree
  //cout << "reading file" << endl;
  int u, v;
  for (int i = 0; i < m; i++) {
    fs >> u >> v;
    adj_list[u-1].push_back(v);
  }
  fs.close();
  //cout << "done reading file\n";
  
  
  vector<int> rand_list = *generate_random_num_list(10);
  for (vector<int>::iterator it = rand_list.begin(); it != rand_list.end(); it++) {
    int r = *it;
    //cout << "r: " << r << endl;
    int* bfs_out_0 = BFS0(r);
    for(edge_bfil_arr_size = 100; edge_bfil_arr_size <= 10000; edge_bfil_arr_size += 400) {
      for(edge_bfil_num_hash = 1; edge_bfil_num_hash <= 10; edge_bfil_num_hash += 2) {
	//fs.open(argv[1]); // graph
	//int m;
	//fs >> n >> m; // n is global
	//cout  << "n:" << n;
	BinaryBloomFilter* edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
	//int u, v;
	
	for (int i = 1; i <= n; i++) { // m
	  for (int j = 0; j < adj_list[i-1].size(); j++)
	    edge_store_bf->add(i, adj_list[i-1][j-1]); // add edges to BF from adj_list
	}
	//fs.close();
	//cout << "done reading file\nrunning bfs\n";
     
	for(bfs_bfil_arr_size = 100; bfs_bfil_arr_size <= 10000; bfs_bfil_arr_size += 200) {
	  for(bfs_bfil_num_hash = 1; bfs_bfil_num_hash <= 10; bfs_bfil_num_hash += 2) {
	    
	    // bfs result in bloomfilter
	    
	    BloomFilter* bfs_out_3 = BFS3(r);
	    BloomFilter* bfs_out_2 = BFS2(edge_store_bf, r); 
	    //cout << "done bfs\n";
	    
	    //fs.open(argv[2]); // testcase file
	    //int t, h; // test node, real h
	    int b2, p2 = 0, q2 = 0; // b: bfs out; p: correct result; q: total
	    int b3, p3 = 0, q3 = 0; // b: bfs out; p: correct result; q: total
	    
	    //while (fs >> t >> h) {
	    int l = nodes.size();
	    for(int i = 0; i < l; i++) {
	      q2++; q3++;
	      b2 = bfs_out_2->check(nodes[i]);
	      b3 = bfs_out_3->check(nodes[i]);
	      if (b2 == dists[i]) 
		p2++;
	      if (b3 == dists[i]) 
		p3++;
	      //cout << nodes[i] << " " << b << " " << dists[i] << endl;
	    }
	    float ratio2 = p2/(float)q2;
	    float ratio3 = p3/(float)q3;
	    //cout << "total: " << q << "; correct: " << p << " ; ratio: " << ratio << endl;
	    cout << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << bfs_bfil_arr_size << " " << bfs_bfil_num_hash << " " << ratio2  << " "  << ratio3 << endl;
	    //fs.close();
	    
	    
	    delete bfs_out_2;
	    delete bfs_out_3;
	    //break;
	  }
	}
	delete edge_store_bf;
	//break;
      }
    }
    
    nodes.clear();
    dists.clear();
  }
  return 0;
    
}
