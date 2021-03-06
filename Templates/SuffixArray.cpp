pair<pii, int> T[100005];
int ran[100005];
int sa[100005];
int lcp[100005];

int cnt[100005]; // cnt[i] = number of occurences of i - 1 in T
int ranker[100005];
pair<pii, int> tem[100005]; // temporary array
void countingSort(int sz) {
	FOR(i, sz) {
		cnt[T[i].F.S + 1]++;
	}
	F0R(i, 1, sz + 1) {
		ranker[i] = ranker[i - 1] + cnt[i - 1];
		cnt[i - 1] = 0;
	}
	cnt[sz - 1] = 0;
	FOR(i, sz) {
		tem[ranker[T[i].F.S + 1]] = T[i];
		ranker[T[i].F.S + 1]++;
	}
	FOR(i, sz) {
		T[i] = tem[i];
	}
	ranker[0] = 0;
	FOR(i, sz) {
		cnt[T[i].F.F + 1]++;
	}
	F0R(i, 1, sz + 1) {
		ranker[i] = ranker[i - 1] + cnt[i - 1];
		cnt[i - 1] = 0;
	}
	cnt[sz - 1] = 0;
	FOR(i, sz) {
		tem[ranker[T[i].F.F + 1]] = T[i];
		ranker[T[i].F.F + 1]++;
	}
	FOR(i, sz) {
		T[i] = tem[i];
	}
	ranker[0] = 0;
}
void getSuffixArray(string& s) {
	FOR(i, s.length()) {
		T[i] = { {0,(int)s[i]}, i };
	}
	sort(T, T + s.length());
	ran[T[0].S] = 0;
	F0R(i, 1, s.length()) {
		if (i > 0 && T[i].F == T[i - 1].F) {
			ran[T[i].S] = ran[T[i - 1].S];
		}
		else {
			ran[T[i].S] = i;
		}
	}
	FOR(i, s.length()) {
		T[i].F.S = ran[T[i].S];
	}
	for (int len = 1; len <= s.length(); len *= 2) { // sort by first len characters
		FOR(i, s.length()) {
			int b = i + len < s.length() ? ran[i + len] : -1;
			T[i] = { {ran[i], b}, i };
		}
		countingSort(s.length());
		FOR(i, s.length()) {
			if (i > 0 && T[i].F == T[i - 1].F)
				ran[T[i].S] = ran[T[i - 1].S];
			else
				ran[T[i].S] = i;
			
		}
	}
	FOR(i, s.length()) {
		sa[ran[i]] = i;
	}
}
void constructLCP(string& s) {
	int sz = s.size();
	int k = 0;
	for (int i = 0; i < sz; i++, k ? k-- : 0) {
		if (ran[i] == sz - 1) {
			k = 0;
			continue;
		}
		int j = sa[ran[i] + 1];
		while (i + k < sz && j + k < sz && s[i + k] == s[j + k]) k++;
		lcp[ran[i]] = k;
	}
}
