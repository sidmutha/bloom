all: bloomtest

bloomtest: bloomtest.o bloom.o MurmurHash2.o
	g++ -g -o bloomtest bloomtest.o bloom.o MurmurHash2

bloomtest.o: bloomtest.cpp
	g++ -g -c bloomtest.cpp

bfs: bfs.o bloom.o MurmurHash2.o
	g++ -g -o bfs bfs.o bloom.o MurmurHash2.o

bfs.o: bfs.cpp
	g++ -g -c bfs.cpp


bfs2: bfs2.o bloom.o MurmurHash2.o
	g++ -g -o bfs2 bfs2.o bloom.o MurmurHash2.o

bfs2.o: bfs2.cpp
	g++ -g -c bfs2.cpp

bfs3: bfs3.o bloom.o MurmurHash2.o
	g++ -g -o bfs3 bfs3.o bloom.o MurmurHash2.o

bfs3.o: bfs3.cpp
	g++ -g -c bfs3.cpp

bfs4: bfs4.o bloom.o MurmurHash2.o
	g++ -g -o bfs4 bfs4.o bloom.o MurmurHash2.o

bfs4.o: bfs4.cpp
	g++ -g -c bfs4.cpp

bipartite_truth: bipartite_truth.o bloom.o MurmurHash2.o
	g++ -g -o bipartite_truth bipartite_truth.o bloom.o MurmurHash2.o

bipartite_truth.o: bipartite_truth.cpp
	g++ -g -c bipartite_truth.cpp


bfs_truth: bfs_truth.o bloom.o MurmurHash2.o
	g++ -g -o bfs_truth bfs_truth.o bloom.o MurmurHash2.o

bfs_truth.o: bfs_truth.cpp
	g++ -g -c bfs_truth.cpp


bloom.o: bloom.h bloom.cpp 
	g++ -g -c bloom.cpp 

MurmurHash2.o: MurmurHash2.cpp MurmurHash2.h
	g++ -g -c MurmurHash2.cpp

clean:
	rm *.o
