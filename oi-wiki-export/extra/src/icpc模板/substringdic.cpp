#include <bits/stdc++.h>
constexpr int inf = 1e9;
using i64 = long long;
int ceil(int a, int b){
	assert(a >= 0 && b >= 1);
	a = (a + b - 1) / b;
	return a * b;
}
struct arr {
	int fir, last, len;
	arr() : len(0), last(0), fir(0) {}
	arr(int x) : fir(x), last(x), len(-1) {}
	arr(int fir, int last, int len) : fir(fir), last(last), len(fir < last ? len : (fir == last ? -1 : 0)) {}
	int cnt() {
		if(!len) return 0;
		else return (last - fir) / len + 1;
	}
	bool have(int x) {
		if(!len) return 0;
		else return x >= fir && x <= last && x % len == fir % len;
	}
	friend arr operator & (arr x, arr y) {
		if(!x.len || !y.len) return arr();
		if(x.cnt() > y.cnt()) std::swap(x, y);
		if(x.cnt() <= 2) {
			if(x.fir != x.last) {
				int o1 =  y.have(x.fir), o2 = y.have(x.last);
				if(o1 && o2) return x;
				else if(o1) return arr(x.fir);
				else if(o2) return arr(x.last);
				else return arr();
			} else {
				return y.have(x.fir) ? x : arr();
			}
		} else {
			if(x.fir % x.len != y.fir % y.len) return arr();
			else {
				arr ans;
				ans.fir = std::max(x.fir, y.fir);
				ans.last = std::min(x.last, y.last);
				ans.len = x.len;
				if(ans.fir <= ans.last) return ans;
				else return arr();
			}
		}
	}
	friend arr operator + (arr x, arr y) {
		if(!x.len) return y;
		if(!y.len) return x;
		if(~x.len) assert(y.fir - x.last == x.len);
		if(~y.len) assert(y.fir - x.last == y.len);
		return arr(x.fir, y.last, y.fir - x.last);
		
	}
	arr fix(int k, int b) {
		arr ans = *this;
		ans.fir *= k, ans.last *= k;
		ans.fir += b, ans.last += b;
		if(ans.fir > ans.last) std::swap(ans.fir, ans.last);
		return ans;
	}
	arr cut(int l, int r) {
		if(!len) return arr();
		else if(!~len) {
			if(fir >= l && fir <= r) return arr(fir);
			else return arr();
		} else {
			if(fir < l) fir += ceil(l - fir, len);
			if(r < last) last -= ceil(last - r, len);
			return arr(fir, last, len);
		}
	}
	void emplace_back(int p) {
		if(!len) len = -1, fir = last = p;
		else if(!~len) {
			last = p;
			len = last - fir;
		} else {
			last = p;
		}
	}
	int kth(int k) {
		assert(k <= cnt());
		return last - (k - 1) * len;
	}
	friend std::ostream& operator << (std::ostream &out, arr x) {
		out << "(" << x.len << ',' << x.fir << ',' << x.last << ")";
		return out;
	}
};
constexpr int hashmod = 5e7 + 7, B = 1234567;
struct hash_table {
	std::vector<std::array<int, 3>> sta;
	std::vector<arr> seg;
	std::vector<int> head, nxt;
	hash_table(int limit) : head(hashmod, -1) {
		seg.reserve(limit);
		nxt.reserve(limit);
		sta.reserve(limit);
	}
	int calc(auto &x) {
		int sum = 0;
		for(int i = 0; i < 3; i ++) {
			sum = (1ll * sum * B + x[i] + 1) % hashmod;
		}
		return sum;
	}
	void insert(auto x, auto y) {
		int u = calc(x);
		int id = sta.size();
		sta.emplace_back(x);
		nxt.emplace_back(head[u]);
		head[u] = id;
		seg.emplace_back(y);
	}
	arr find(std::array<int, 3> x) {
		int u = calc(x);
		for(int i = head[u]; ~i; i = nxt[i]) if(sta[i] == x) {
			return seg[i];
		}
		return arr();
	}
};
struct dictionary {
	int n, k, m;
	std::vector<std::vector<int>> rank, st;
	std::vector<int> rk, sa;
	hash_table mp;
	dictionary(std::string str) : mp(str.size() * std::__lg(str.size())) {
		n = str.size(), k = std::__lg(n) + 1;
		std::vector<int> last_rk(n);
		std::vector<int> cnt(n);
		rk.resize(n), sa.resize(n);
		rank = st = std::vector<std::vector<int>> (k + 1, std::vector<int> (n));
		auto tmp = str;
		std::sort(tmp.begin(), tmp.end());
		tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
		int m = tmp.size();
		for(int i = 0; i < n; i ++) {
			cnt[rk[i] = std::lower_bound(tmp.begin(), tmp.end(), str[i]) - tmp.begin()] ++;
		}
		for(int i = 1; i < n; i ++) {
			cnt[i] += cnt[i - 1];
		}
		for(int i =  0; i < n; i ++) {
			sa[-- cnt[rk[i]]] = i;
		}
		std::vector<int> use(n);
		std::vector<arr> seg(n);
		for(int i = 0, len = 1; ; len <<= 1, i ++) {
			rank[i] = rk;
			for(int l = 0, r; l < n; l = r + 1) {
				r = std::min(n - 1, l + len - 1);
				for(int i = l; i <= r; i ++) {
					use[rk[i]] = 1;
					seg[rk[i]].emplace_back(i);
				}
				for(int j = l; j <= r; j ++) {
					if(use[rk[j]]) {
						mp.insert(std::array<int, 3> {i, l / len, rk[j]}, seg[rk[j]]);
						use[rk[j]] = 0;
						seg[rk[j]] = arr();
					}
				}
			}
			if(i == k) break;
			std::vector<int> ord;
			ord.reserve(n);
			for(int i = n - len; i < n; i ++) {
				ord.emplace_back(i);
			}
			for(int i = 0; i < n; i ++) if(sa[i] >= len) {
				ord.emplace_back(sa[i] - len);
			}
			assert(ord.size() == n);
			fill(cnt.begin(), cnt.begin() + m, 0);
			for(int i = 0; i < n; i ++) {
				cnt[rk[i]] ++;
			}
			for(int i = 1; i < m; i ++) cnt[i] += cnt[i - 1];
			for(int i = n - 1; i >= 0; i --) {
				sa[-- cnt[rk[ord[i]]]] = ord[i];
			}
			m = 0;
			std::swap(rk, last_rk);
			for(int i = 0; i < n; i ++) {
				if(i && last_rk[sa[i]] == last_rk[sa[i - 1]] && 
					(sa[i] + len < n ? last_rk[sa[i] + len] : -1) == (sa[i - 1] + len < n ? last_rk[sa[i - 1] + len] : -1)) {
					rk[sa[i]] = m - 1;
				} else {
					rk[sa[i]] = m ++;
				}
			}
		}
	}
	std::vector<arr> query(int l, int r) {
		std::vector<arr> ans;
		for(int i = 0, len = 1; i <= k; i ++, len <<= 1) {
			auto ask = [&] (int l, int r, int id) {
				int fir = inf, last = -1, cnt = 0;
				l = std::max(l, 0);
				arr seg1 = mp.find(std::array<int, 3>{i, l / len, id}).cut(l, r);
				arr seg2 = mp.find(std::array<int, 3>{i, l  / len + 1, id}).cut(l, r);
				return seg1 + seg2;
			};
			if(l + len - 1 >= n || r - len + 1 < 0) {
				break;
			}
			int lid = rank[i][l];
			int rid = rank[i][r - len + 1];
			arr seg1 = ask(r - 2 * len + 2, r - len + 1, lid).fix(-1, r + 1);
			arr seg2 = ask(l, l + len - 1, rid).fix(1, -l + len);
			arr seg3 = seg1 & seg2;
			if(seg3.len) {
				ans.emplace_back(seg3);
			}
		}
		return ans;
	}
};
int main() {
//	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::string str;
	std::cin >> str;
	int n = str.size(), q;
	std::cin >> q;
	dictionary dic(str);
	for(int i = 0; i < q; i ++) {
		int l, r;
		std::cin >> l >> r;
		auto range = dic.query(l, r);
		if(range.empty()){
			std::cout << -1 << '\n';
		} else {
			int sum = 0, min = 1e9, max = 0;
			for(auto seg : range) {
				seg = seg.cut(1, r - l);
				if(seg.len) {
					sum += seg.cnt();
					min = std::min(min, seg.fir);
					max = std::max(max, seg.last);
				}
			}
			if(!sum) std::cout << -1 << '\n';
			else std::cout << min << ' ' << max << ' ' << sum << '\n';
		}
	}
	return 0;
}