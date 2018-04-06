--------------------------------------------------
1. Complexity Analysis for each Backend:
--------------------------------------------------

	a. 	UNORDERED
		
		Insertion is O(1) average case and O(n) in worst case. This backend 
		uses the built-in "unordered_set" which has its own hashing function; 
		since we don't know exactly how this hashing function is implemented, 
		we're assuming is it an efficient implementation that chooses a 
		bucket in such a way that avoids collisions, to the greatest extent 
		possible. 
		
		Searching is also O(1) average case and O(n) worst case for the same 
		reasons - in the average case, there would be few/no collisions, so 
		the searching function can immediately return a unique value in 
		bucket determined by hashing the key. In the worst case, there are 
		many (up to n) collisions, and search must perform a linear search 
		(either a linear search of a list within a bucket, for a "chained" 
		implementation, or a linear search of the buckets, for an "open 
		addressing" implementation.
	
	b.	CHAINED
	
		Insertion is O(1) average case, because in the absense of collisions, 
		a key will map to a unique value, and the program won't have to 
		traverse a map within the bucket to find an empty space to insert 
		that particular element. In the worst case, insertion is O(n); this 
		occurs when all/nearly all of the elements are mapped to the same 
		bucket, in which each insertion becomes a linear search within a 
		bucket to find an empty spot.
		
		Searching is O(1) in the average case, because in the absense of 
		collisions, each key will map to one unique value. So, the program 
		can just hash the key and return the value in constant time. In the 
		worst case, searching is O(n); this also occurs when all/nearly all 
		of the values were inserted into one bucket, in which case hashing 
		returns the bucket in constant time, but then must search a bucket 
		with n values to find the correct value.
		
	c.	OPEN
	
		Inserting is O(1) average case complexity because, with few or no 
		collisions, the hashing function will simply choose a bucket based on 
		the hashed key and insert the value accordingly. In the worst case, 
		insertion is O(n); this occurs when the first (n-1) buckets are 
		already filled and the load factor is essentially one, in which case 
		searching for an open bucket becomes a linear search.
		
		Searching is O(1) average case for similar reasons; with a low load 
		factor, hashing the key should return the intended bucket without 
		searching subsequent buckets. Again, in the worst case, searching is 
		O(n), because the program would have to search all buckets in 
		linear fashion to find the "first open bucket" in which the original 
		key was placed.
		
	
-----------------------------------------------------
2. Benchmark Table for All Backends
-----------------------------------------------------

| BACKEND              | NITEMS     | INSERT     | SEARCH     |
|----------------------|------------|------------|------------|
|             unsorted |          1 |     0.0000 |     0.0000 |
|               sorted |          1 |     0.0001 |     0.0000 |
|                  bst |          1 |     0.0001 |     0.0000 |
|               rbtree |          1 |     0.0000 |     0.0000 |
|                treap |          1 |     0.0001 |     0.0000 |
|            unordered |          1 |     0.0001 |     0.0000 |
|        chained-0.500 |          1 |     0.0000 |     0.0000 |
|        chained-0.750 |          1 |     0.0001 |     0.0000 |
|        chained-1.000 |          1 |     0.0001 |     0.0000 |
|        chained-5.000 |          1 |     0.0000 |     0.0000 |
|        chained-10.00 |          1 |     0.0001 |     0.0000 |
|        chained-100.0 |          1 |     0.0001 |     0.0000 |
|             open-0.5 |          1 |     0.0001 |     0.0000 |
|             open-0.6 |          1 |     0.0001 |     0.0000 |
|             open-0.7 |          1 |     0.0001 |     0.0000 |
|             open-0.8 |          1 |     0.0000 |     0.0000 |
|             open-0.9 |          1 |     0.0001 |     0.0000 |
|             open-1.0 |          1 |     0.0001 |     0.0000 |
|             unsorted |         10 |     0.0001 |     0.0000 |
|               sorted |         10 |     0.0001 |     0.0000 |
|                  bst |         10 |     0.0001 |     0.0000 |
|               rbtree |         10 |     0.0001 |     0.0000 |
|                treap |         10 |     0.0002 |     0.0000 |
|            unordered |         10 |     0.0001 |     0.0000 |
|        chained-0.500 |         10 |     0.0001 |     0.0000 |
|        chained-0.750 |         10 |     0.0001 |     0.0000 |
|        chained-1.000 |         10 |     0.0001 |     0.0000 |
|        chained-5.000 |         10 |     0.0001 |     0.0000 |
|        chained-10.00 |         10 |     0.0001 |     0.0000 |
|        chained-100.0 |         10 |     0.0001 |     0.0000 |
|             open-0.5 |         10 |     0.0000 |     0.0000 |
|             open-0.6 |         10 |     0.0001 |     0.0000 |
|             open-0.7 |         10 |     0.0001 |     0.0000 |
|             open-0.8 |         10 |     0.0000 |     0.0000 |
|             open-0.9 |         10 |     0.0001 |     0.0000 |
|             open-1.0 |         10 |     0.0001 |     0.0000 |
|             unsorted |        100 |     0.0005 |     0.0004 |
|               sorted |        100 |     0.0011 |     0.0002 |
|                  bst |        100 |     0.0003 |     0.0002 |
|               rbtree |        100 |     0.0004 |     0.0002 |
|                treap |        100 |     0.0002 |     0.0001 |
|            unordered |        100 |     0.0004 |     0.0002 |
|        chained-0.500 |        100 |     0.0003 |     0.0002 |
|        chained-0.750 |        100 |     0.0002 |     0.0001 |
|        chained-1.000 |        100 |     0.0003 |     0.0002 |
|        chained-5.000 |        100 |     0.0003 |     0.0002 |
|        chained-10.00 |        100 |     0.0002 |     0.0001 |
|        chained-100.0 |        100 |     0.0002 |     0.0001 |
|             open-0.5 |        100 |     0.0002 |     0.0001 |
|             open-0.6 |        100 |     0.0002 |     0.0001 |
|             open-0.7 |        100 |     0.0002 |     0.0001 |
|             open-0.8 |        100 |     0.0001 |     0.0001 |
|             open-0.9 |        100 |     0.0002 |     0.0001 |
|             open-1.0 |        100 |     0.0002 |     0.0001 |
|             unsorted |       1000 |     0.0375 |     0.0382 |
|               sorted |       1000 |     0.0573 |     0.0016 |
|                  bst |       1000 |     0.0026 |     0.0013 |
|               rbtree |       1000 |     0.0038 |     0.0022 |
|                treap |       1000 |     0.0033 |     0.0023 |
|            unordered |       1000 |     0.0028 |     0.0014 |
|        chained-0.500 |       1000 |     0.0029 |     0.0008 |
|        chained-0.750 |       1000 |     0.0050 |     0.0008 |
|        chained-1.000 |       1000 |     0.0017 |     0.0010 |
|        chained-5.000 |       1000 |     0.0026 |     0.0008 |
|        chained-10.00 |       1000 |     0.0027 |     0.0016 |
|        chained-100.0 |       1000 |     0.0026 |     0.0016 |
|             open-0.5 |       1000 |     0.0030 |     0.0013 |
|             open-0.6 |       1000 |     0.0016 |     0.0007 |
|             open-0.7 |       1000 |     0.0032 |     0.0013 |
|             open-0.8 |       1000 |     0.0033 |     0.0013 |
|             open-0.9 |       1000 |     0.0040 |     0.0013 |
|             open-1.0 |       1000 |     0.0037 |     0.0033 |
|             unsorted |      10000 |     3.4942 |     3.4656 |
|               sorted |      10000 |     4.5896 |     0.0195 |
|                  bst |      10000 |     0.0305 |     0.0273 |
|               rbtree |      10000 |     0.0425 |     0.0178 |
|                treap |      10000 |     0.0361 |     0.0164 |
|            unordered |      10000 |     0.0248 |     0.0150 |
|        chained-0.500 |      10000 |     0.0475 |     0.0101 |
|        chained-0.750 |      10000 |     0.0324 |     0.0104 |
|        chained-1.000 |      10000 |     0.0390 |     0.0102 |
|        chained-5.000 |      10000 |     0.0277 |     0.0104 |
|        chained-10.00 |      10000 |     0.0212 |     0.0111 |
|        chained-100.0 |      10000 |     0.0169 |     0.0115 |
|             open-0.5 |      10000 |     0.0292 |     0.0092 |
|             open-0.6 |      10000 |     0.0211 |     0.0090 |
|             open-0.7 |      10000 |     0.0166 |     0.0077 |
|             open-0.8 |      10000 |     0.0217 |     0.0090 |
|             open-0.9 |      10000 |     0.0230 |     0.0071 |
|             open-1.0 |      10000 |     0.0180 |     0.0068 |
|             unsorted |     100000 |        inf |        inf |
|               sorted |     100000 |        inf |        inf |
|                  bst |     100000 |     0.2617 |     0.1776 |
|               rbtree |     100000 |     0.3192 |     0.1756 |
|                treap |     100000 |     0.2618 |     0.2073 |
|            unordered |     100000 |     0.1718 |     0.1032 |
|        chained-0.500 |     100000 |     0.4186 |     0.1086 |
|        chained-0.750 |     100000 |     0.4935 |     0.1096 |
|        chained-1.000 |     100000 |     0.3705 |     0.1125 |
|        chained-5.000 |     100000 |     0.4027 |     0.1243 |
|        chained-10.00 |     100000 |     0.4334 |     0.1367 |
|        chained-100.0 |     100000 |     0.2837 |     0.1581 |
|             open-0.5 |     100000 |     0.2050 |     0.0773 |
|             open-0.6 |     100000 |     0.2168 |     0.0764 |
|             open-0.7 |     100000 |     0.2346 |     0.0810 |
|             open-0.8 |     100000 |     0.1711 |     0.0848 |
|             open-0.9 |     100000 |     0.1865 |     0.0861 |
|             open-1.0 |     100000 |     0.1871 |     0.0852 |
|             unsorted |    1000000 |        inf |        inf |
|               sorted |    1000000 |        inf |        inf |
|                  bst |    1000000 |     2.9176 |     2.1091 |
|               rbtree |    1000000 |     3.6699 |     1.9990 |
|                treap |    1000000 |     3.1111 |     2.7278 |
|            unordered |    1000000 |     1.7647 |     1.1171 |
|        chained-0.500 |    1000000 |     3.7381 |     1.1379 |
|        chained-0.750 |    1000000 |     4.6102 |     1.1839 |
|        chained-1.000 |    1000000 |     3.4071 |     1.1750 |
|        chained-5.000 |    1000000 |     3.9201 |     1.4538 |
|        chained-10.00 |    1000000 |     4.2742 |     1.6159 |
|        chained-100.0 |    1000000 |     6.7299 |     2.4246 |
|             open-0.5 |    1000000 |     1.9631 |     0.8441 |
|             open-0.6 |    1000000 |     2.0634 |     0.8930 |
|             open-0.7 |    1000000 |     2.2051 |     0.8475 |
|             open-0.8 |    1000000 |     2.2724 |     0.8240 |
|             open-0.9 |    1000000 |     2.5146 |     0.9189 |
|             open-1.0 |    1000000 |     1.7977 |     0.9236 |
|             unsorted |   10000000 |        inf |        inf |
|               sorted |   10000000 |        inf |        inf |
|                  bst |   10000000 |    32.2460 |    24.9630 |
|               rbtree |   10000000 |        inf |        inf |
|                treap |   10000000 |        inf |        inf |
|            unordered |   10000000 |    20.9750 |    11.6350 |
|        chained-0.500 |   10000000 |        inf |        inf |
|        chained-0.750 |   10000000 |        inf |        inf |
|        chained-1.000 |   10000000 |        inf |        inf |
|        chained-5.000 |   10000000 |    38.2480 |    16.5690 |
|        chained-10.00 |   10000000 |        inf |        inf |
|        chained-100.0 |   10000000 |        inf |        inf |
|             open-0.5 |   10000000 |    27.5000 |     8.6212 |
|             open-0.6 |   10000000 |    19.2470 |     8.7811 |
|             open-0.7 |   10000000 |    20.7640 |     8.9038 |
|             open-0.8 |   10000000 |    21.7040 |     8.8540 |
|             open-0.9 |   10000000 |    22.6570 |     8.6762 |
|             open-1.0 |   10000000 |    24.1260 |     9.2204 |



------------------------------------------------
3. Frequencies word count benchmarking:
------------------------------------------------

| Backend     | Text                      | File Size | Elasped Time  | Memory     |
|-------------|---------------------------|-----------|---------------|------------|
| Unsorted    | Alice in Wonderland (11)  | 173595    | 4.297s        | 2,727,454  |
| Sorted      | Alice in Wonderland (11)  | 173595    | 4.705s        | 2,727,454  |
| BST         | Alice in Wonderland (11)  | 173595    | 0.110s        | 2,706,070  |
| RBTree      | Alice in Wonderland (11)  | 173595    | 0.129s        | 2,754,262  |
| Treap       | Alice in Wonderland (11)  | 173595    | 0.130s        | 2,706,670  |
| Unordered   | Alice in Wonderland (11)  | 173595    | 0.098s        | 2,774,814  |
| Chained     | Alice in Wonderland (11)  | 173595    | 0.140s        | 9,544,142  |
| Open        | Alice in Wonderland (11)  | 173595    | 0.100s        | 5,559,283  |
| Unsorted    | A Tale of Two Cities (98) | 804335    | 54.935s       | inf        |
| Sorted      | A Tale of Two Cities (98) | 804335    | 1m34.313s     | inf        |
| BST         | A Tale of Two Cities (98) | 804335    | 0.547s        | 11,291,582 |
| RBTree      | A Tale of Two Cities (98) | 804335    | 0.669s        | 11,448,950 |
| Treap       | A Tale of Two Cities (98) | 804335    | 0.597s        | 11,292,182 |
| Unordered   | A Tale of Two Cities (98) | 804335    | 0.408s        | 11,618,350 |
| Chained     | A Tale of Two Cities (98) | 804335    | 0.610s        | 38,414,206 |
| Open        | A Tale of Two Cities (98) | 804335    | 0.433s        | 25,849,497 |
| Unsorted    | Les Mis\303\251rables (135)       | 3324334   | inf           | inf        |
| Sorted      | Les Mis\303\251rables (135)      | 3324334   | inf           | inf        |
| BST         | Les Mis\303\251rables (135)      | 3324334   | 2.662s        | 41,425,210 |
| RBTree      | Les Mis\303\251rables (135)      | 3324334   | 3.172s        | 41,855,162 |
| Treap       | Les Mis\303\251rables (135)      | 3324334   | 2.604s        | 41,425,810 |
| Unordered   | Les Mis\303\251rables (135)      | 3324334   | 1.674s        | 41,977,258 |
| Chained     | Les Mis\303\251rables (135)      | 3324334   | 2.142s        | 147,918,818|
| Open        | Les Mis\303\251rables (135)      | 3324334   | 1.857s        | 102,051,131|




------------------------------------------------------------
4. Analysis and Discussion
------------------------------------------------------------


