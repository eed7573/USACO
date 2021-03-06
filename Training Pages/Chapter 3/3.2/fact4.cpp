/*
ID: eed7573
TASK: fact4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define SQ(a) (a)*(a)

#define F0R(i, a, b) for (int i=(a); i<(b); i++)
#define FOR(i, a) for (int i=0; i<(a); i++)
#define F0Rd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define FORd(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

int n;
int ans = 1;
int main() {
	FAST
	freopen("fact4.in", "r", stdin);
	freopen("fact4.out", "w", stdout);
	cin >> n;
	int num0 = 0;
	for (int i = n/5; i > 0; i /= 5) {
		num0 += i;
	}
	F0R(i, 1, n + 1) {
		int j = i;
		while (j % 5 == 0) {
			j /= 5;
		}
		while (num0 > 0 && j % 2 == 0) {
			j /= 2;
			num0--;
		}
		ans = (ans*j) % 10;
	}
	cout << ans << "\n";
	return 0;
}
