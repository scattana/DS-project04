#!/bin/sh

BACKENDS="
    unsorted
    sorted 
    bst 
    rbtree 
    treap
    unordered
    chained-0.500
    chained-0.750
    chained-1.000
    chained-5.000
    chained-10.00
    chained-100.0
    open-0.5
    open-0.6
    open-0.7
    open-0.8
    open-0.9
    open-1.0
"
NITEMS="1 10 100 1000 10000 100000 1000000 10000000"
TIMEOUT=60
    
echo '| BACKEND              | NITEMS     | INSERT     | SEARCH     |'
echo '|----------------------|------------|------------|------------|'

for nitem in $NITEMS; do
    for backend in $BACKENDS; do
    	if [ $backend = "unsorted" -o $backend = "sorted" ] && [ $nitem -gt 10000 ]; then
	    insert="INFINITY"
	    search="INFINITY"
	else
	    benchs=$(./timeout.py -t $TIMEOUT ./map_bench -b $backend -n $nitem)
	    if [ $? -eq 0 ]; then
		insert=$(echo $benchs | awk '/Insert/ { print $2 }')
		search=$(echo $benchs | awk '/Search/ { print $5 }')
	    else
		insert="INFINITY"
		search="INFINITY"
	    fi
	fi
	printf "| %20s | %10d | %10.4f | %10.4f |\n" $backend $nitem $insert $search
    done
done
