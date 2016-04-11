#ifndef _BLOOM_H
#define _BLOOM_H
#include <string>
#include <vector>

using namespace std;

string intToStr(int v, int len);
int min (int* arr, int len);
int max (int* arr, int len);

class BloomFilter {
 public:
  // m = size of array; k = no. of hash functions; numw = width of a no. in key
  BloomFilter (int m, int k, int numw);
  ~BloomFilter();
  void add (int u, int v, int w); // (u, v) -> edge; w -> weight
  int check (int u, int v);
  
  void add (string key, int w);
  int check (string key);
  
  void add (int u, int w);
  int check (int u);
  
 private:
  int m, k, numw; // m = size of array; k = no. of hash functions; numw = width of num
  int* get_hashes (int u, int v);
  int* get_hashes (string key);
  //int* get_hashes (int u);
  int* mArray;
  int* hArray;
  //string intToStr(int v, int len);
};


class BinaryBloomFilter {
 public:
  // m = size of array; k = no. of hash functions; numw = width of num
  BinaryBloomFilter (int m, int k, int numw);
  ~BinaryBloomFilter();
  void add (int u, int v); // (u, v) -> edge; 
  int check (int u, int v);
  
  void add (string key);
  int check (string key);

  void add (int u);
  int check (int u);
  
 private:
  int m, k, numw; // m = size of array; k = no. of hash functions; numw = width of num
  int* get_hashes (int u, int v);
  int* get_hashes (string key);
  //int* get_hashes (int u);
  int* mArray;
  int* hArray;
  //string intToStr(int v, int len);
};

class NbrBloom{
  NbrBloom (int n, int k, int numw);
  void add (int u, int v, int w); // (u, v) -> edge; w -> weight
  int check (int u, int v);

 private:
  int m, k, numw; // m = size of array; k = no. of hash functions; numw = width of num
  int* get_hashes (int u, int v);
  vector<vector<int> > mArray;
  //string intToStr(int v, int len);
};
#endif
