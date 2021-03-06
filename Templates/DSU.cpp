template<int sz> struct DSU {
	int parent[sz];
	int numNodes[sz];
	int rank[sz];

	DSU() {
		for (int i = 0; i < sz; i++) {
			parent[i] = i;
			numNodes[i] = 1;
			rank[i] = 0;
		}
	}

	int getSize(int n) {
		return numNodes[find(n)];
	}
	bool connected(int n1, int n2) {
		return find(n1) == find(n2);
	}
	int find(int n) {
		if (parent[n] != n) parent[n] = find(parent[n]);
		return parent[n];
	}
	void unite(int n1, int n2) {
		int p1 = find(n1);
		int p2 = find(n2);
		if (p1 == p2) return;
		if (rank[p1] == rank[p2]) {
			parent[p1] = p2;
			numNodes[p2] = numNodes[p1] + numNodes[p2];
			rank[p2]++;
		}
		else if (rank[p1] < rank[p2]) {
			parent[p1] = p2;
			numNodes[p2] = numNodes[p1] + numNodes[p2];
		}
		else {
			parent[p2] = p1;
			numNodes[p1] = numNodes[p1] + numNodes[p2];
		}
	}
};
