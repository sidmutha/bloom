#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <cmath>
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

// graph in adj-matrix and result in array 
// pretty similar to BFS0 
int* BFS3_2 (int s, int **adj_mat) {
  cout << "running bfs3_2\n";
  int h = 1;
  queue<int> q;
  //BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
  int* visited = new int[n]();
  q.push(s);
  visited[s-1] = h;

  while (!q.empty()) {
    int f = q.front();
    h++;
    for (int i = 0; i < n; i++) {
      int c = adj_mat[f][i];
      if (c != 0) {
	if (visited[c-1] == 0) { // not visited
	  visited[c-1] = h;
	  q.push(c);
	}
      }
      // directed / undirected?
    }
    q.pop();
  }
  cout << "done\n";
  //cout << "#" << h << endl;
  return visited;
}


// graph in BF, result in array
int* BFS2_2 (BinaryBloomFilter* edge_store_bbf, int v) {
  vector<int> adj_vec = vector<int>();
  
  int h = 1;
  queue<int> q;
  //BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
  int* visited = new int[n];
  q.push(v);
  visited[v-1] = h; // visited
  
  while (!q.empty()) {
    int f = q.front();
    h++;
    get_adjacent(f, edge_store_bbf, adj_vec);
    //cout << "#" << h << endl;
    //cout << "v:" << adj_vec.size();
    for (int i = 0; i < adj_vec.size(); i++) {
      int c = adj_vec[i];
      //cout << c << endl;
      if (visited[c-1] == 0) { // not visited
	//cout << "ee\n";
	visited[c-1] = h;
	q.push(c);
      }
      // directed/undirected?
    }
    adj_vec.clear();
    q.pop();
  }
  
  return visited;
}



// simple BFS on edges stored in bf, result in BF
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


// graph in adj_list; result in BF
BloomFilter* BFS3 (int n, vector < vector <int> >& adj_list) {
  //cout << "running bfs3\n";
  int h = 1;
  queue<int> q;
  BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
 
  q.push(n);
  bf->add(n, h); // visited

  while (!q.empty()) {
    int f = q.front();
    h++;
    for (int i = 0; i < adj_list[f-1].size(); i++) {
      int c = adj_list[f-1][i];
      if (bf->check(c) == -1) { // not visited
	bf->add(c, h);
	q.push(c);
      }
      // directed / undirected?
    }
    q.pop();
  }
  //cout << "done\7\n";
  //cout << "#" << h << endl;
  return bf;
}

// graph in adj_mat; result in BF
BloomFilter* BFS3_3 (int s, int **adj_mat) {
  //cout << "running bfs3_3\n";
  int h = 1;
  queue<int> q;
  BloomFilter* bf = new BloomFilter(bfs_bfil_arr_size, bfs_bfil_num_hash, NUMW); // stores output of bfs
 
  q.push(s);
  bf->add(s, h); // visited

  while (!q.empty()) {
    int f = q.front();
    h++;
    for (int i = 0; i < n; i++) {
      int c = adj_mat[f-1][i];
      if (c != 0) {
	if (bf->check(i+1) == -1) { // not visited
	  bf->add(i+1, h);
	  q.push(i+1);
	}
      }
      // directed / undirected?
    }
    q.pop();
  }
  //cout << "done\7\n";
  //cout << "#" << h << endl;
  return bf;
}


void get_bf_graph_adjacency_list (BinaryBloomFilter* bf, vector < vector <int> > bf_adj_list) {
  cout << "populating bf_adj_list\7\n";
  //cout << n<< endl;
  for(int v = 1; v <= n; v++) {
    for (int i = 1; i <= n; i++) { // assumption: 1 indexed node numbers
      //cout << "^";
      if (bf->check(v, i) != -1) { // check for edge between v-i
	//cout << k++ << endl;
	bf_adj_list[v-1].push_back(i);
      }
    }
  }
  cout << "done\7\n";
}


void get_bf_graph_adjacency_matrix (BinaryBloomFilter* bf, int** adj_mat) {
  cout << "populating bf_adj_mat\7\n";
  //cout << n<< endl;
  for(int v = 1; v <= n; v++) {
    for (int i = 1; i <= n; i++) { // assumption: 1 indexed node numbers
      //cout << "^";
      //cout << k++ << endl;
      adj_mat[v-1][i-1] = bf->check(v, i) != -1;
    }
  }
  cout << "done\7\n";
}


vector<int> * generate_random_num_list (int len) {
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
  fs.open(argv[2]); // random numbers list
  int r2;
  vector<int> rand_list = vector<int> ();
  while(fs >> r2) {
    rand_list.push_back(r2);
    cout << r2 << endl;
  }
  fs.close();
  
  // read graph
  fs.open(argv[1]); // graph
  fs >> n >> m; // n, m are global
  
  //adj_list.resize(n, vector<int>(2*m/n)); // avg degree
  adj_list.resize(n, vector<int>()); // avg degree
  cout << "reading file" << endl;
  int u, v;
  for (int i = 0; i < m; i++) {
    fs >> u >> v;
    adj_list[u-1].push_back(v);
  }
  fs.close();
  cout << "done reading file\n";
  

  fstream updatefs; 
  updatefs.open(argv[3]);
  float ratio2;
  float ratio3;
  int r;
  edge_bfil_arr_size = 100;
  edge_bfil_num_hash = 2;
  bfs_bfil_arr_size = 100;
  bfs_bfil_num_hash = 2;

  while (updatefs >> r >> edge_bfil_arr_size >> edge_bfil_num_hash >> bfs_bfil_arr_size >> bfs_bfil_num_hash >> ratio2 >> ratio3) {
    //cout << r << " " << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << bfs_bfil_arr_size << " " << bfs_bfil_num_hash << " " << ratio2  << " "  << ratio3 << endl;  
  }; // read till end
    
  
  updatefs.close();
  
  

  BinaryBloomFilter* edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
  //int u, v;
  cout << sizeof(int*) << endl;
  cout << "adding to edge bf\n";
  for (int i = 0; i < n; i++) { // m
    for (int j = 0; j < adj_list[i].size(); j++)
      edge_store_bf->add(i+1, adj_list[i][j]); // add edges to BF from adj_list
  }
  cout << "done adding to edge bf\n";
  // adj list for graph from edge_store_bf
  //vector < vector <int> > bf_adj_list;
  //bf_adj_list.resize(n, vector<int>(2*m/n)); // avg degree
  cout << "creating matrix of size " << n << "\n";
  int** bf_adj_mat = new int*[n];
  for (int i = 0; i < n; i++) {
    bf_adj_mat[i] = new int[n]();
    //cout << i << endl;
  }
  cout << "done creating matrix\n";
  //return 0;
  get_bf_graph_adjacency_matrix(edge_store_bf, bf_adj_mat);
  //return 0;
  
  
  
  vector<int>::iterator it = find(rand_list.begin(), rand_list.end(), r);
  if (it == rand_list.end()) 
    it = rand_list.begin();
  
  // vector<int>::iterator it = rand_list.begin();
  r = *it;
  cout << r << endl;
  //vector<int> rand_list = *generate_random_num_list(10);
  int l;
  float p2_2 = 0, q2_2 = 0; // b: bfs out; p: correct result; q: total
  int b3, b3_3, b2_2;
  float p3 = 0, q3 = 0; // b: bfs out; p: correct result; q: total
  float p3_3 = 0, q3_3 = 0; // b: bfs out; p: correct result; q: total

  int* bfs_out_0 = BFS0(r);
  int* bfs_out_2_2 = BFS2_2(edge_store_bf, r);
  
 
  
  BloomFilter* bfs_out_3;
  //BloomFilter* bfs_out_2; 
  BloomFilter* bfs_out_3_3; 
  
  updatefs.open(argv[3], ofstream::out | ofstream::app);
  
  goto this_point;
  
  for (; it != rand_list.end(); it++) {
    r = *it;
   
    cout << "r: " << r << endl;
    bfs_out_0 = BFS0(r);
    for(edge_bfil_arr_size = 100; edge_bfil_arr_size <= 10000; edge_bfil_arr_size += 1000) {
      for(edge_bfil_num_hash = 2; edge_bfil_num_hash <= 10; edge_bfil_num_hash += 2) {
	//fs.open(argv[1]); // graph
	//int m;
	//fs >> n >> m; // n is global
	//cout  << "n:" << n;
	edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
	// populating edge store bf
	for (int i = 0; i < n; i++) { // m
	  for (int j = 0; j < adj_list[i].size(); j++)
	    edge_store_bf->add(i+1, adj_list[i][j]); // add edges to BF from adj_list
	}


	//for (int i = 0; i < bf_adj_list.size(); i++) 
	//  bf_adj_list[i].clear();
	get_bf_graph_adjacency_matrix(edge_store_bf, bf_adj_mat);

	bfs_out_2_2 = BFS2_2(edge_store_bf, r); // bf-arr
	
	for (bfs_bfil_arr_size = 100; bfs_bfil_arr_size <= 10000; bfs_bfil_arr_size += 500) {
	  for (bfs_bfil_num_hash = 2; bfs_bfil_num_hash <= 10; bfs_bfil_num_hash += 2) {
	    
	    // bfs result in bloomfilter
	    
	    bfs_out_3 = BFS3(r, adj_list); // adj_list-bf
	    //bfs_out_2 = BFS2(edge_store_bf, r); // bf-bf
	    bfs_out_3_3 = BFS3_3(r, bf_adj_mat); // (bf)matrix-bf
	    //bfs_out_2_2 = BFS2_2(edge_store_bf, r); // bf-arr

	    b2_2 = 0; p2_2 = 0; q2_2 = 0; // b: bfs out; p: correct result; q: total
	    b3 = 0; p3 = 0, q3 = 0; // b: bfs out; p: correct result; q: total
	    b3_3 = 0; p3_3 = 0, q3_3 = 0; // b: bfs out; p: correct result; q: total
	    
	    
	    l = nodes.size();
	    for (int i = 0; i < l; i++) {
	      int ni = nodes[i];
	      int di = dists[i];
	      
	      b3_3 = bfs_out_3_3->check(ni);
	      b3   = bfs_out_3->check(ni);
	      b2_2 = bfs_out_2_2[ni-1];
	      
	      //cout << ni << " " << di << " " << b3 << endl;
	      
	      b3_3 = b3_3 != -1 ? b3_3 : di;
	      b3   = b3   != -1 ? b3   : di;
	      b2_2 = b2_2 !=  0 ? b2_2 : di;

	      p3_3 += fabs(b3_3 - di);
	      p3   += fabs(b3 - di);
	      p2_2 += fabs(b2_2 - di);
	      
	      //cout << " " << p3_3 << endl;
	      //cout << nodes[i] << " " << b << " " << dists[i] << endl;
	    }
	    //cout << l << endl;
	    p3_3 /= l;
	    p3   /= l;
	    p2_2 /= l;
	      
	    //ratio2_2 = p2_2/(float)l;
	    //ratio3 = p3/(float)l;
	    //ratio3_3 = p3_3/(float)l;
	    //cout << "total: " << q << "; correct: " << p << " ; ratio: " << ratio << endl;
	    updatefs << r 
		     << " " << edge_bfil_arr_size 
		     << " " << edge_bfil_num_hash 
		     << " " << bfs_bfil_arr_size 
		     << " " << bfs_bfil_num_hash 
		     << " " << l
		     << " " << p3_3  << " "  << p3 << " " << p2_2 
		     << endl;
	    
	    cout     << r 
		     << " " << edge_bfil_arr_size 
		     << " " << edge_bfil_num_hash 
		     << " " << bfs_bfil_arr_size 
		     << " " << bfs_bfil_num_hash 
		     << " " << l
		     << " " << p3_3  << " "  << p3 << " " << p2_2 
		     << endl;
	    
	    
	    
	    //cout << r << " " << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << bfs_bfil_arr_size << " " << bfs_bfil_num_hash << " " << ratio2  << " "  << ratio3 << endl;  
	    

	    delete bfs_out_3;
	    //break;
	  this_point:;
	  }
	}
	delete bfs_out_2_2;
	delete edge_store_bf;
	//break;
      }
    }
    nodes.clear();
    dists.clear();
  }
  updatefs.close();
  return 0;
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

