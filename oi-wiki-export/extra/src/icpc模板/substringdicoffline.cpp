#include <bits/stdc++.h>
struct arr {
	int fir, last, len;
	arr() : len(-1) {}
	arr(int x) : fir(x), last(x), len(0) {}
	int cnt() {
		if(!~len) return 0;
		else if(len == 0) return 1;
		else return (last - fir) / len + 1;
	}
	bool have(int x) {
		if(!~len) return 0;
		else if(len == 0) return fir == x;
		else return x >= fir && x <= last && x % len == fir % len;
	}
	friend arr operator & (arr x, arr y) {
		if(!~x.len || !~y.len) return arr();
		if(x.cnt() >y.cnt()) std::swap(x, y);
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
	arr fix(int k, int b) {
		arr ans = *this;
		ans.fir *= k, ans.last *= k;
		ans.fir += b, ans.last += b;
		if(ans.fir > ans.last) std::swap(ans.fir, ans.last);
		return ans;
	}
	friend std::ostream& operator << (std::ostream &out, arr x) {
		out << "(" << x.len << ',' << x.fir << ',' << x.last << ")";
		return out;
	}
	void emplace_back(int p) {
		if(len == -1) len = 0, fir = last = p;
		else if(len == 0) {
			last = p;
			len = last - fir;
		} else {
			last = p;
		}
	}
	void pop_front() {
		if(len == 0) len = -1;
		else {
			fir += len;
			if(fir == last) len = 0;
		}
	}
};
int main() {
	//freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::string str;
	std::cin >> str;
	int n = str.size();
	int q;
	std::cin >> q;
	std::vector<std::array<int, 3>> ans(q);
	std::vector<std::vector<std::pair<int, int>>> ql(n), qr(n);
	constexpr int inf = 1e9;
	std::vector<std::pair<int, int>> qs(q);
	for(int i = 0; i < q; i ++) {
		auto &[l, r] = qs[i];
		std::cin >> l >> r;
		ql[l].emplace_back(r, i);
		qr[r].emplace_back(l, i);
		ans[i][0] = inf;
	}
	std::vector<int> rank(n), sa(n), last_rank(n);
	auto tmp = str;
	std::sort(tmp.begin(), tmp.end());
	tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
	std::vector<int> cnt(n);
	int m = tmp.size();
	for(int i = 0; i < n; i ++) {
		cnt[rank[i] = std::lower_bound(tmp.begin(), tmp.end(), str[i]) - tmp.begin()] ++;
	}
	for(int i = 1; i < m; i ++) {
		cnt[i] += cnt[i - 1];
	}
	for(int i =  0; i < n; i ++) {
		sa[-- cnt[rank[i]]] = i;
	}
	auto solve = [&] (int D) {
		int len = 1 << D;
		std::vector<std::array<arr, 2>> seg(q);
		std::vector<arr> que(n);
		for(int i = 0; i < n; i ++) {
			que[rank[i]].emplace_back(i);
			if(i >= len) {
				que[rank[i - len]].pop_front();
			}
			if(i + len - 1 < n) {
				for(auto [l, id] : qr[i + len - 1]) {
					seg[id][0] = que[rank[l]].fix(-1, i + len);
				}
			}
			if(i - len + 1 >= 0) {
				for(auto [r, id] : ql[i - len + 1]) {
					if(r - len + 1 >= 0) {
						seg[id][1] = que[rank[r - len + 1]].fix(1, - (i - len + 1) + len);
					}
				}
			}
		}
		for(int i = 0; i < q; i ++) {
			arr cur = seg[i][0] & seg[i][1];
			if(~cur.len) {
				int len = qs[i].second - qs[i].first + 1;
				if(cur.len) {
					if(cur.last >= len) {
						cur.last -= ((cur.last - len) / cur.len + 1) * cur.len;
					}
					if(cur.fir <= cur.last) {
						ans[i][2] += (cur.last - cur.fir) / cur.len + 1;
						ans[i][0] = std::min(ans[i][0], cur.fir);
						ans[i][1] = std::max(ans[i][1], cur.last);
					}
				} else {
					if(cur.last < len) {
						ans[i][2] ++;
						ans[i][0] = std::min(ans[i][0], cur.fir);
						ans[i][1] = std::max(ans[i][1], cur.last);
					}

				}
			}
		}
	};
	solve(0);
	for(int i = 0, len = 1; len <= n; len <<= 1, i ++) {
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
			cnt[rank[i]] ++;
		}
		for(int i = 1; i < m; i ++) cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; i --) {
			sa[-- cnt[rank[ord[i]]]] = ord[i];
		}
		m = 0;
		std::swap(rank, last_rank);
		for(int i = 0; i < n; i ++) {
			if(i && last_rank[sa[i]] == last_rank[sa[i - 1]] && 
				(sa[i] + len < n ? last_rank[sa[i] + len] : -1) == (sa[i - 1] + len < n ? last_rank[sa[i - 1] + len] : -1)) {
				rank[sa[i]] = m - 1;
			} else {
				rank[sa[i]] = m ++;
			}
		}
		solve(i + 1);
		if(m == n) break;
	}
	for(int i = 0; i < q; i ++) {
		if(ans[i][2]) {
			std::cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
		} else {
			std::cout << -1 << '\n';
		}
	}
	return 0;
}