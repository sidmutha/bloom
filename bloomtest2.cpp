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
  
  srand(time(NULL));
  int m;
  //int m = atoi(argv[1]);
  map<string, int> kvalues = map<string, int> ();
  //int k = atoi(argv[2]);
  //int l = atoi(argv[3]);
  // size of array 
  int a[7] = {100, 500, 1000, 5000, 10000, 100000, 500000};
  int b[9] = {10, 100, 500, 1000, 5000, 10000, 100000, 500000, 1000000};
  for (int j = 0; j < 7; j++) {
    m = a[j];
    for (int t = 0; t < 9; t++) {
      for (int k = 2; k <= 10; k += 2) {
	BloomFilter bf (m, k, NUMW);
	int l = b[t];
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
	int w = 0;
	for (map<string, int>::iterator it = kvalues.begin(); it != kvalues.end(); ++it) {
	  v = bf.check(it->first);
	  if (v != it->second) {
	    w++;
	    //cout << it->first << " " << it->second << " " << v << " " << endl;
	  }
	}
	
	cout << m << " " << l << " " << k << " " << w << endl;
	kvalues.clear();
      }
    }
    
  }
  
  
  
  
 
  
  
  
  
    
}
