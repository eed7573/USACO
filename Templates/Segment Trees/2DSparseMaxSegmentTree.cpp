struct maxnode {
	node segment;
	maxnode* c[2];


	void update(int x, int y, ll v, int l = 0, int r = SZ - 1) {
		if (l == x && r == x) {
			segment.update(y, v);
			return;
		}
		int mid = (l + r) / 2;
		if (x <= mid) {
			if (!c[0]) c[0] = new maxnode();
			c[0]->update(x, y, v, l, mid);
		}
		else {
			if (!c[1]) c[1] = new maxnode();
			c[1]->update(x, y, v, mid + 1, r);
		}
		segment.upd2d(y, c[0] ? &c[0]->segment : NULL, c[1] ? &c[1]->segment : NULL);
	}
	ll query(int w, int x, int y, int z, int l = 0, int r = SZ - 1) {
		if (w <= l && r <= x) return segment.query(y, z);
		if (x < l || w > r) return 0;
		int mid = (l + r) / 2;
		return max((c[0] ? c[0]->query(w, x, y, z, l, mid) : 0), (c[1] ? c[1]->query(w, x, y, z, mid + 1, r) : 0));
	}
};
