#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		if(sets[table].parent != table)
			sets[table].parent = getParent(sets[table].parent); 
        return sets[table].parent;
	}
	/**
	 * merge two table(tree) using heuristic union by rank
	 * update rank and size
	 * calculate max_table_size for each merge step
	*/
	void merge(int destination, int source){
		int i_des = getParent(destination);
		int i_src = getParent(source);
		if (i_des != i_src) {
			if (sets[i_des].rank > sets[i_src].rank) {
				sets[i_des].size += sets[i_src].size;

				sets[i_src].parent = i_des;
				sets[i_src].size = 0;
			}
			else{
				sets[i_src].size += sets[i_des].size;

				sets[i_des].parent = i_src;
				sets[i_des].size = 0;
				if (sets[i_des].rank == sets[i_src].rank){
					sets[i_src].rank += 1;
				}
			}
		}
		max_table_size = max(max(max_table_size, sets[i_des].size), sets[i_src].size); 
	}
};

int main() {
	int n, m;
	vector<int> max_table_size_history;
	cin >> n >> m;
	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
		max_table_size_history.push_back(tables.max_table_size);
	}
	for (auto const& maxSize : max_table_size_history){
		cout << maxSize << endl;
	}

	return 0;
}