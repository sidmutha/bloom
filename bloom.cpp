#include "bloom.h"
#include "MurmurHash2.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
using namespace std;
void dbg(string s){
  cout << "D: " << s << endl;
}

// common functions:

int min (int* arr, int len) {
  int m = arr[0];
  for(int i = 0; i < len; i++) {
    m = arr[i] < m ? arr[i] : m;
  }
  return m;
}

int max (int* arr, int len) {
  int m = arr[0];
  for(int i = 0; i < len; i++) {
    m = arr[i] > m ? arr[i] : m;
  }
  return m;
}

string intToStr (int v, int len) {
  stringstream ss;
  ss << setw(len) << setfill('0') << v;
  string out;
  ss >> out;
  return out;
}



/**************************BloomFilter*******************************/

BloomFilter::BloomFilter (int m, int k, int numw) {
  this->m = m; 
  this->k = k;
  this->numw = numw;
  mArray = new int[m]();
  hArray = new int[k]();
  // TODO: intiatilize hash functions?
}

BloomFilter::~BloomFilter () {
  //cout << "bf destructor called\n";
  delete[] hArray;
  delete[] mArray;
}

void BloomFilter::add (int u, int v, int w) {
  int* hashes = get_hashes(u, v);
  int *hw;
  for (int i = 0; i < k; i++) {
    hw = &mArray[hashes[i]];
    *hw = *hw < w ? w : *hw; // set the max val 
    //dbg(string(hashes[i]));
  }
  //delete[] hashes;
}

void BloomFilter::add (string key, int w) {
  int* hashes = get_hashes(key);
  int *hw;
  for (int i = 0; i < k; i++) {
    hw = &mArray[hashes[i]];
    *hw = *hw < w ? w : *hw; // set the max val 
    //dbg(string(hashes[i]));
  } 
  //delete[] hashes;
}

void BloomFilter::add (int u, int w) {
  string key = intToStr(u, numw);
  int* hashes = get_hashes(key);
  int *hw;
  for (int i = 0; i < k; i++) {
    hw = &mArray[hashes[i]];
    *hw = *hw < w ? w : *hw; // set the max val 
    //dbg(string(hashes[i]));
  } 
  //delete[] hashes;
}


int BloomFilter::check (int u, int v) {
  int* hashes = get_hashes(u, v);
  //int* hash_ws = new int[k];
  int m = mArray[hashes[0]]; // for min
  int p;
  for (int i = 0; i < k; i++) {
    p = mArray[hashes[i]];
    if (!p)
      return -1; 
    else if (p < m)
      m = p; 
  }
  
  //int m = min(hash_ws, k); // embed in above loop?
  //delete[] hashes;
  return m;
}

int BloomFilter::check (string key) {
  int* hashes = get_hashes(key);
  //int* hash_ws = new int[k];
  int m = mArray[hashes[0]]; // for min
  int p;
  for (int i = 0; i < k; i++) {
    p = mArray[hashes[i]];
    if (!p)
      return -1; 
    else if (p < m)
      m = p; 
  }
  //int m = min(hash_ws, k); // embed in above loop?
  //delete[] hashes;
  return m;
}

int BloomFilter::check (int u) {
  string key = intToStr(u, numw);
  int* hashes = get_hashes(key);
  //int* hash_ws = new int[k];
  int m = mArray[hashes[0]]; // for min
  int p;
  for (int i = 0; i < k; i++) {
    p = mArray[hashes[i]];
    if (!p)
      return -1; 
    else if (p < m)
      m = p; 
  }
  //int m = min(hash_ws, k); // embed in above loop?
  //delete[] hashes;
  return m;
}


int* BloomFilter::get_hashes (int u, int v) {
  //int* hashes = new int[k];
  string key = intToStr(u, numw) + intToStr(v, numw);
  return get_hashes(key);
  /*
  cout << "key: " + key << endl;
  int l = m/k;
  for (int i = 0; i < k; i++) {
    hashes[i] = l*i + MurmurHash2(key.c_str(), key.length(), i) % l; // seed = i
    cout << hashes[i] << endl;
  }
  return hashes;
  */
}

int* BloomFilter::get_hashes (string key) {
  //int* hashes = new int[k];
  //string key = intToStr(u, numw);
  //cout << "key: " + key << endl;
  int l = m/k;
  for (int i = 0; i < k; i++) {
    hArray[i] = l*i + MurmurHash2(key.c_str(), key.length(), i) % l; // seed = i
    //cout << hashes[i] << endl;
  }
  return hArray;
}



/*****************************BinaryBloomFilter**************************************/

BinaryBloomFilter::BinaryBloomFilter (int m, int k, int numw) {
  this->m = m; 
  this->k = k;
  this->numw = numw;
  mArray = new int[m]();
  hArray = new int[k]();
  // TODO: intiatilize hash functions?
}

BinaryBloomFilter::~BinaryBloomFilter () {
  delete[] hArray;
  delete[] mArray;
}


void BinaryBloomFilter::add (int u, int v) {
  int* hashes = get_hashes(u, v);
  for (int i = 0; i < k; i++) {
    mArray[hashes[i]] = 1;
  }  
  //delete[] hashes;
}

void BinaryBloomFilter::add (string key) {
  int* hashes = get_hashes(key);
  for (int i = 0; i < k; i++) {
    mArray[hashes[i]] = 1;
  }  
  //delete[] hashes;
}

void BinaryBloomFilter::add (int u) {
  string key = intToStr(u, numw);
  add(key);
}




int BinaryBloomFilter::check (int u, int v) {
  int* hashes = get_hashes(u, v);
  for (int i = 0; i < k; i++) {
    if (!mArray[hashes[i]])
      return -1; 
  }
  //delete[] hashes;
  return 1; // embed in above loop?
}

int BinaryBloomFilter::check (string key) {
  int* hashes = get_hashes(key);
  for (int i = 0; i < k; i++) {
    if (!mArray[hashes[i]])
      return -1; 
  }
  //delete[] hashes;
  return 1; // embed in above loop?
}

int BinaryBloomFilter::check (int u) {
  string key = intToStr(u, numw);
  int* hashes = get_hashes(key);
  for (int i = 0; i < k; i++) {
    if (!mArray[hashes[i]])
      return -1; 
  }
  //delete[] hashes;
  return 1; // embed in above loop?
}




int* BinaryBloomFilter::get_hashes (int u, int v) {
  //int* hashes = new int[k];
  string key = intToStr(u, numw) + intToStr(v, numw);
  return get_hashes(key);
  /*
  cout << "key: " + key << endl;
  int l = m/k;
  for (int i = 0; i < k; i++) {
    hashes[i] = l*i + MurmurHash2(key.c_str(), key.length(), i) % l; // seed = i
    cout << hashes[i] << endl;
  }
  return hashes;
  */
}

int* BinaryBloomFilter::get_hashes (string key) {
  //int* hashes = new int[k];
  //string key = intToStr(u, numw);
  //cout << "key: " + key << endl;
  int l = m/k;
  for (int i = 0; i < k; i++) {
    hArray[i] = l*i + MurmurHash2(key.c_str(), key.length(), i) % l; // seed = i
    //cout << hashes[i] << endl;
  }
  return hArray;
}




/**********************************************************************************

NbrBloom::NbrBloom (int m, int k, int numw) {
  this->m = m; 
  this->k = k;
  this->numw = numw;
  mArray.resize(m, vector<int>());
  // TODO: intiatilize hash functions?
}

void NbrBloom::add (int u, int v, int w) {
  int* hashes = get_hashes(u, v);
  int *hw;
  for (int i = 0; i < k; i++) {
    hw = &mArray[hashes[i]];
    *hw = *hw < w ? w : *hw; // set the max val 
    //dbg(string(hashes[i]));
  }  
}

int NbrBloom::check (int u, int v) {
  int* hashes = get_hashes(u, v);
  int* hash_ws = new int[k];
  for (int i = 0; i < k; i++) {
    if (!mArray[hashes[i]])
      return -1; 
    else
      hash_ws[i] = mArray[hashes[i]]; 
  }
  return min(hash_ws, k); // embed in above loop?
}

string NbrBloom::intToStr (int v, int len) {
  stringstream ss;
  ss << setw(len) << setfill('0') << v;
  string out;
  ss >> out;
  return out;
}

int* NbrBloom::get_hashes (int u, int v) {
  int* hashes = new int[k];
  string key = intToStr(u, numw) + intToStr(v, numw);
  cout << "key: " + key << endl;
  int l = m/k;
  for (int i = 0; i < k; i++) {
    hashes[i] = l*i + MurmurHash2(key.c_str(), key.length(), i) % l; // seed = i
    cout << hashes[i] << endl;
  }
  return hashes;
}

*/
