#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define ff first
#define ss second
#define all(c)	c.begin(), c.end()
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define trace(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {cerr << "\n";}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << " : " << a << " | "; err(++it, args...);}

typedef long long int lli;
typedef pair<lli, lli> plli;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pair<lli, lli> > vplli;
typedef vector<lli> vlli;
typedef vector<vlli> vvlli;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define PI 3.141592653589793
#define mod (lli)(1000*1000*1000+7)
template<typename T> T gcd(T a, T b) { if (a == 0) return b; return gcd(b % a, a); }
template<typename T> T pow(T a, T b, lli m) {T ans = 1; while (b > 0) { if (b % 2 == 1) ans = ((ans % m) * (a % m)) % m; b /= 2; a = ((a % m) * (a % m)) % m; } return ans % m; }
const int N = 100010;

class BOARD {
public:
	vvi brd;
	int SIZE;

	BOARD(vvi& x) {
		srand(time(NULL));
		brd = x;
		SIZE = 4;
	}

	BOARD(int SZ = 4) {
		srand(time(NULL));

		SIZE = SZ;

		brd.clear();	brd.resize(SIZE, vi(SIZE, 0));
		int i = rand() % (SIZE * SIZE), ni = i;
		brd[i / SIZE][i % SIZE] = 2;
		do {ni = rand() % (SIZE * SIZE);} while (ni == i);
		brd[ni / SIZE][ni % SIZE] = 2;
	}

	void fillATile() {
		int as = 0;
		for (int i = 0; i < brd.size(); i++) {
			for (int j = 0; j < brd[i].size(); j++) {
				as += (brd[i][j] == 0);
			}
		}
		assert(as != 0);
		int kk = 1 + (rand() % as);
		as = 0;
		for (int i = 0; i < brd.size(); i++) {
			for (int j = 0; j < brd.size(); j++) {
				if (brd[i][j] == 0) {
					as++;
					if (as == kk) {
						brd[i][j] = 2;
						return;
					}
				}
			}
		}
	}

	void set(int i, int j, int v = 2) {
		brd[i][j] = v;
	}

	void fillRandom() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				brd[i][j] = 1 << (1 + rand() % 2);
			}
		}
	}
	void print() {
		for (int i = 0; i < brd.size(); i++) {
			for (int j = 0; j < brd.size(); j++) {
				cout << brd[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "-----------\n";
	}

	bool valid(int i, int j) {
		if (i < 0 || i >= SIZE || j < 0 || j >= SIZE)	return false;
		return true;
	}

	void move(char c) {
		if (c == 'U')
			move_up();
		else if (c == 'L')
			move_left();
		else if (c == 'R')
			move_right();
		else if (c == 'D')
			move_down();
	}
	void move_up() {
		for (int j = 0; j < SIZE; j++) {
			vi nZ;
			for (int i = 0; i < SIZE; i++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
			for (int i = 0; i < nZ.size(); i++) {brd[i][j] = nZ[i];}
			for (int i = nZ.size(); i < SIZE; i++) {brd[i][j] = 0;}
		}
		for (int j = 0; j < SIZE; j++) {
			for (int i = 0; i < SIZE; i++) {
				if (valid(i + 1, j) && brd[i][j] != 0 && brd[i][j] == brd[i + 1][j]) {
					brd[i][j] *= 2;
					brd[i + 1][j] = 0;
				}
			}
		}

		for (int j = 0; j < SIZE; j++) {
			vi nZ;
			for (int i = 0; i < SIZE; i++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
			for (int i = 0; i < nZ.size(); i++) {brd[i][j] = nZ[i];}
			for (int i = nZ.size(); i < SIZE; i++) {brd[i][j] = 0;}
		}
	}

	void move_down() {
		for (int i = 0; i < brd.size() / 2; i++) {
			for (int j = 0; j < brd.size(); j++) {
				swap(brd[i][j], brd[SIZE - 1 - i][j]);
			}
		}

		move_up();

		for (int i = 0; i < brd.size() / 2; i++) {
			for (int j = 0; j < brd.size(); j++) {
				swap(brd[i][j], brd[SIZE - 1 - i][j]);
			}
		}
	}

	void move_left() {
		for (int i = 0; i < SIZE; i++) {
			vi nZ;
			for (int j = 0; j < SIZE; j++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
			for (int j = 0; j < nZ.size(); j++) {brd[i][j] = nZ[j];}
			for (int j = nZ.size(); j < SIZE; j++) {brd[i][j] = 0;}
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (valid(i, j + 1) && brd[i][j] != 0 && brd[i][j] == brd[i][j + 1]) {
					brd[i][j] *= 2;
					brd[i][j + 1] = 0;
				}
			}
		}
		for (int i = 0; i < SIZE; i++) {
			vi nZ;
			for (int j = 0; j < SIZE; j++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
			for (int j = 0; j < nZ.size(); j++) {brd[i][j] = nZ[j];}
			for (int j = nZ.size(); j < SIZE; j++) {brd[i][j] = 0;}
		}
	}

	void move_right() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE / 2; j++) {
				swap(brd[i][j], brd[i][SIZE - 1 - j]);
			}
		}
		move_left();
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE / 2; j++) {
				swap(brd[i][j], brd[i][SIZE - 1 - j]);
			}
		}
	}
	void clear() {
		brd.clear();
		brd.resize(SIZE, vi(SIZE, 0));
	}

	int value() {
		vector<vector<int>> table = {{12, 13, 14, 15}, {11, 10, 9, 8}, {4, 5, 6, 7}, {3, 2, 1, 0}};
		int sc = 0, pen = 0;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				sc += (table[i][j] * brd[i][j]);
			}
		}
		return sc;
	}
};

void print(vvi& x) {
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x[i].size(); j++) {
			cout << x[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "---------\n";
}

int MAXDEPTH = 0;

char choice = '$';
int MAX_DEPTH;

int mainMethod(BOARD& brd, int depth, int player) {
//    cout<<depth<<" "<<player<<"\n";
	if (depth == 0)return brd.value();
	if (player == 0) {
		int sc = 0, v;
		BOARD temp;

		temp = brd;
		temp.move_up();
		v = mainMethod(temp, depth - 1, 1 - player);
		if (v > sc) {
			sc = v;
			if (depth == MAX_DEPTH)
				choice = 'U';
		}

		temp = brd;
		temp.move_down();
		v = mainMethod(temp, depth - 1, 1 - player);
		if (v > sc) {
			sc = v;
			if (depth == MAX_DEPTH)
				choice = 'D';
		}


		temp = brd;
		temp.move_left();
		v = mainMethod(temp, depth - 1, 1 - player);
		if (v > sc) {
			sc = v;
			if (depth == MAX_DEPTH)
				choice = 'L';
		}

		temp = brd;
		temp.move_right();
		v = mainMethod(temp, depth - 1, 1 - player);
		if (v > sc) {
			sc = v;
			if (depth == MAX_DEPTH)
				choice = 'R';
		}
		return sc;
	} else {
		//BOARD is playing
		int sc = 0, empties = 0;
		vvi& grid = brd.brd;
		for (int i = 0; i < brd.SIZE; i++) {
			for (int j = 0; j < brd.SIZE; j++) {
				if (grid[i][j] != 0)    continue;
				empties++;
				grid[i][j] = 2;
				sc += 0.9 * (mainMethod(brd, depth - 1, 1 - player) * 1.0);
				grid[i][j] = 4;
				sc += 0.1 * (mainMethod(brd, depth - 1, 1 - player) * 1.0);
				grid[i][j] = 0;
			}
		}
		if (empties == 0)return -10;
		// trace(sc, empties);
		return sc / empties;
	}
}


bool best_move(BOARD& myBoard) {
	MAX_DEPTH = 5;
	choice = '$';
	int v = mainMethod(myBoard, MAX_DEPTH, 0);
	if (choice == '$') {
		cout << v << " " << choice << "\n";
	}
	myBoard.move(choice);
}
int main() {
	// fio;
	srand(time(NULL));
	MAXDEPTH = 4;
	BOARD brd;
	while (true) {
		// brd.print();
		// brd.value();
		best_move(brd);
		brd.fillATile();
		brd.print();
		// cin >> x;
	}
}