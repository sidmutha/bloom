//#include "bloom.h"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char** argv) {
  //BloomFilter B(100, 4, 4);
  //B.add(10, 12, 3);
  //B.add(10, 13, 5);
  //cout << B.check(10, 12);
  vector <vector <int> > v; //(10, vector <int> (10));
  v.resize(10, vector <int> (5));
  v[0][0] = 4;
  cout << v[0][0];
  return 0;
}
