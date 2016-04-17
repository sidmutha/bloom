#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "bloom.h"

using namespace std;

#define NUMW 8 // width of no. in key

int edge_bfil_arr_size, edge_bfil_num_hash;
BinaryBloomFilter* edge_store_bf;

vector < vector <int> > adj_list;


int n, m;
  
vector <vector<int> >* generate_bipartite_graph(int num_edges) {
  int num_vertices = 2 * num_edges;
  vector <vector<int> > *adj_list 
		 = new vector< vector <int> > (num_vertices, vector<int>(0));
  
  int i, j;
  int nv2 = num_vertices/2;
  int count = 0;
  // TODO: seed rand
				       srand(time(0));				       
  while (count != num_edges) {
    i = rand() % nv2;
    j = nv2 + rand() % nv2;
    cout << i << " " << j << " " << count <<endl;
    if(find((*adj_list)[i].begin(), (*adj_list)[i].end(), j) == (*adj_list)[i].end()) {
      (*adj_list)[i].push_back(j);
      (*adj_list)[j].push_back(i);
      count++;
    }
  }
  return adj_list;
}

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
    if (colours[i-1] != 0) 
      continue;
    if (!colourify(colours, i, 1)) { // for every new component of the graph
      return false;
    } 
  }
  delete[] colours;
  return true;
}


int main (int argc, char** argv) {
  //cout << argc << endl;
  
  edge_bfil_arr_size = 100;
  edge_bfil_num_hash = 1;
  
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
 
  int t;

  fstream updatefs; 
  updatefs.open(argv[2]);
  while (updatefs >> n >> m >> edge_bfil_arr_size >> edge_bfil_num_hash >> t >> t >> t){
    //cout << r << " " << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << bfs_bfil_arr_size << " " << bfs_bfil_num_hash << " " << ratio2  << " "  << ratio3 << endl;  
  }; // read till end
    
  
  updatefs.close();
  
  
  /*
  edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
	//int u, v;
	
  for (int i = 1; i <= n; i++) { // m
    for (int j = 0; j < adj_list[i-1].size(); j++)
      edge_store_bf->add(i, adj_list[i-1][j-1]); // add edges to BF from adj_list
  }
  */
  
  
  bool is_bipartite, real_bipartite = false;
  
  updatefs.open(argv[2], ofstream::out | ofstream::app);

  //goto this_point;
  
  
  for(edge_bfil_arr_size = 100; edge_bfil_arr_size <= 10000; edge_bfil_arr_size += 400) {
    for(edge_bfil_num_hash = 2; edge_bfil_num_hash <= 10; edge_bfil_num_hash += 2) {
      edge_store_bf = new BinaryBloomFilter(edge_bfil_arr_size, edge_bfil_num_hash, NUMW); 
      // populate bloom filter
      for (int i = 1; i <= n; i++) { // m
	for (int j = 0; j < adj_list[i-1].size(); j++)
	  edge_store_bf->add(i, adj_list[i-1][j-1]); // add edges to BF from adj_list
	;}
	
	
      is_bipartite = isBipartite();
	
	
      updatefs << n << " " << m << " " << edge_bfil_arr_size << " " << edge_bfil_num_hash << " " << real_bipartite << " " <<  is_bipartite << " " << (real_bipartite == is_bipartite) << endl;
  
	    
	
      //break;
      delete edge_store_bf;
    this_point:;
    }
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


