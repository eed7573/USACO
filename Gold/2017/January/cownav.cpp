#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define SQ(a) (a)*(a)

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define ROF(i,a,b) for (int i = (b)-1; i >= a; i--)
#define R0F(i,a) for (int i = (a)-1; i >= 0; i--)
#define endl "\n"
#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

#define maxN 20
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

int n;
bool arr[maxN][maxN];
int states[maxN][maxN][maxN][maxN][4][4][3]; //0=north 1=east 2=south 3=west
queue<tuple<pii, pii, pii, int>> que;
pii forPos(int firCoord, int secCoord, int direc) {
	if ((secCoord == 0 && direc == 3) || (secCoord == n - 1 && direc == 1) || (firCoord == 0 && direc == 0) || (firCoord == n - 1 && direc == 2)) {
		return MP(firCoord, secCoord);
	}
	if (direc == 0) {
		if (arr[firCoord - 1][secCoord]) {
			return MP(firCoord - 1, secCoord);
		}
	}
	if (direc == 1) {
		if (arr[firCoord][secCoord + 1]) {
			return MP(firCoord, secCoord + 1);
		}
	}
	if (direc == 2) {
		if (arr[firCoord + 1][secCoord]) {
			return MP(firCoord + 1, secCoord);
		}
	}
	if (direc == 3) {
		if (arr[firCoord][secCoord - 1]) {
			return MP(firCoord, secCoord - 1);
		}
	}
	return MP(firCoord, secCoord);
}
int main()
{
	FAST
	ofstream cout("cownav.out");
	ifstream cin("cownav.in");
	cin >> n;
	string nexts;
	for (int i = 0; i<n; i++) {
		cin >> nexts;
		for (int j = 0; j<n; j++) {
			if (nexts[j] == 'E') {
				arr[i][j] = true;
			}
			else {
				arr[i][j] = false;
			}
		}
	}
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			for (int k = 0; k<n; k++) {
				for (int l = 0; l<n; l++) {
					for (int m = 0; m<4; m++) {
						for (int o = 0; o<4; o++) {
							for (int p = 0; p < 3; p++) {
								states[i][j][k][l][m][o][p] = -1;
							}
						}
					}
				}
			}
		}
	}
	states[n-1][0][n-1][0][0][1][0] = 0;
	states[n-1][0][n-1][0][1][0][0] = 0;
	que.push(MT(MP(n - 1, 0), MP(n - 1, 0), MP(0, 1), 0));
	while (!que.empty()) {
		tuple<pii, pii, pii, int> next = que.front();
		que.pop();
		pii coords1 = get<0>(next);
		pii coords2 = get<1>(next);
		pii dir = get<2>(next);
		int which = get<3>(next);
		int moves = states[coords1.F][coords1.S][coords2.F][coords2.S][dir.F][dir.S][which];
		if (states[coords1.F][coords1.S][coords2.F][coords2.S][(dir.F + 1) % 4][(dir.S + 1) % 4][which] == -1) {
			states[coords1.F][coords1.S][coords2.F][coords2.S][(dir.F + 1) % 4][(dir.S + 1) % 4][which] = moves + 1;
			que.push(MT(coords1, coords2, MP((dir.F + 1) % 4, (dir.S + 1) % 4), which));
		}
		if (states[coords1.F][coords1.S][coords2.F][coords2.S][(dir.F + 3) % 4][(dir.S + 3) % 4][which] == -1) {
			states[coords1.F][coords1.S][coords2.F][coords2.S][(dir.F + 3) % 4][(dir.S + 3) % 4][which] = moves + 1;
			que.push(MT(coords1, coords2, MP((dir.F + 3) % 4, (dir.S + 3) % 4), which));
		}
		pii pos1 = forPos(coords1.F, coords1.S, dir.F);
		pii pos2 = forPos(coords2.F, coords2.S, dir.S);
		if (which == 0 && pos1.first == 0 && pos1.second == n - 1) which = 1;
		if (which == 0 && pos2.first == 0 && pos2.second == n - 1) which = 2;
		if (which == 1 && pos2.first == 0 && pos2.second == n - 1) {
			cout << moves + 1 << endl;
			break;
		}
		if (which == 2 && pos1.first == 0 && pos1.second == n - 1) {
			cout << moves + 1 << endl;
			break;
		}
		if (states[pos1.F][pos1.S][pos2.F][pos2.S][dir.F][dir.S][which] == -1) {
			states[pos1.F][pos1.S][pos2.F][pos2.S][dir.F][dir.S][which] = moves + 1;
			que.push(MT(pos1, pos2, dir, which));
		}
	}
	return 0;

}
