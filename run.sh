#! /bin/bash
echo "sss"
for es in `seq 100 50 10000`;
do
    for eh in `seq 1 2 10`;
    do
	for bs in `seq 100 50 10000`;
	do
	    for bh in `seq 1 2 10`;
	    do
		echo "$es $eh $bs $bh ">> ../data/web-Stanford/outv_1_run_100_1_100_1 
		./bfs2 ../data/web-Stanford/web-Stanford.txt ../data/web-Stanford/testcase10 $es $eh $bs $bh >> ../data/web-Stanford/outv_1_run_100_1_100_1
		echo >> ../data/web-Stanford/outv_1_run_100_1_100_1
	    done
	done
    done
done
