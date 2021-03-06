#include "bloom.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

#define NUMW 8

string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

int main (int argc, char** argv) {
  int m = atoi(argv[1]);
  int k = atoi(argv[2]);
  
  BloomFilter bf (m, k, NUMW);
  
  srand(time(NULL));
  map<string, int> kvalues = map<string, int> ();
  int l = atoi(argv[3]);
  int r = rand();
  string s;
  for(int i = 0; i < l; i++) {
    s = randomStrGen(5);
    while (r <= 0)
      r = rand();
    kvalues[s]= r;
    bf.add(s, r);
    //cout << s << ": " << r << endl;
    r = 0;
  }
  int v;
  for (map<string, int>::iterator it = kvalues.begin(); it != kvalues.end(); ++it) {
    v = bf.check(it->first);
    if (v != it->second)
      cout << it->first << " " << it->second << " " << v << " " << endl;
  }
  
  
}
