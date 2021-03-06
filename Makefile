all: bloomtest

bloomtest: bloomtest.o bloom.o MurmurHash2.o
	g++ -g -o bloomtest bloomtest.o bloom.o MurmurHash2.o

bloomtest.o: bloomtest.cpp
	g++ -g -c bloomtest.ocpp

bloomtest2: bloomtest2.o bloom.o MurmurHash2.o
	g++ -g -o bloomtest2 bloomtest2.o bloom.o MurmurHash2.o

bloomtest2.o: bloomtest2.cpp
	g++ -g -c bloomtest2.cpp


bloomgraph: bloomgraph.o bloom.o MurmurHash2.o
	g++ -g -o bloomgraph bloomgraph.o bloom.o MurmurHash2.o

bloomgraph.o: bloomgraph.cpp
	g++ -g -c bloomgraph.cpp

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


bfs5: bfs5.o bloom.o MurmurHash2.o
	g++ -g -o bfs5 bfs5.o bloom.o MurmurHash2.o

bfs5.o: bfs5.cpp
	g++ -g -c bfs5.cpp

bfs2_auto: bfs2_auto.o bloom.o MurmurHash2.o
	g++ -g -o bfs2_auto bfs2_auto.o bloom.o MurmurHash2.o

bfs2_auto.o: bfs2_auto.cpp
	g++ -g -c bfs2_auto.cpp

bfs4_auto: bfs4_auto.o bloom.o MurmurHash2.o
	g++ -g -o bfs4_auto bfs4_auto.o bloom.o MurmurHash2.o

bfs4_auto.o: bfs4_auto.cpp
	g++ -g -c bfs4_auto.cpp


bipartite_truth: bipartite_truth.o bloom.o MurmurHash2.o
	g++ -g -o bipartite_truth bipartite_truth.o bloom.o MurmurHash2.o

bipartite_truth.o: bipartite_truth.cpp
	g++ -g -c bipartite_truth.cpp

bipartite: bipartite.o bloom.o MurmurHash2.o
	g++ -g -o bipartite bipartite.o bloom.o MurmurHash2.o

bipartite.o: bipartite.cpp
	g++ -g -c bipartite.cpp

bipartite_auto: bipartite_auto.o bloom.o MurmurHash2.o
	g++ -g -o bipartite_auto bipartite_auto.o bloom.o MurmurHash2.o

bipartite_auto.o: bipartite_auto.cpp
	g++ -g -c bipartite_auto.cpp



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
