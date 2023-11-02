
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  *s = '\0';
  return s;
}
int rdmod() {
  long long ret = 0;
  long long mod = 1004535809;
  while (*o && *o <= 32) ++o;
  while (*o >= '0' && *o <= '9')
    ret = (ret << 3) + (ret << 1) + (*o++ - '0'), ret %= mod;
  return ret;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
// #define MULTI
const int N = 1 << 19;
const i64 p = 998244353;
i64 gp[N], iv[N];

i64 q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}

inline int wrap(int x) { return (x == (x & -x)) ? x : 1u << (32 - __builtin_clz(x)); };
inline void red(i64 &x) { if (x >= p) x -= p; }

u32 bit_inv[N];

i64 _c[N], A[N], B[N];
i64 _h[N], _f[N];
i64 *a;

void dft(i64 *a, int len) {
  for (int i = 1; i < len; ++i) {
    bit_inv[i] = bit_inv[i>>1]>>1;
    if (i & 1) bit_inv[i] |= len >> 1;
    if (bit_inv[i] > i) swap(a[i], a[bit_inv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    i64 wn = gp[N/i/2];
    for (int j = 0; j < len; j += i << 1) {
      i64 w = 1;
      for (int k = j; k < j + i; ++k) {
        i64 x = a[k], y = a[k + i] * w % p;
        red(a[k] = x + y);
        red(a[k + i] = x + p - y);
        w = w * wn % p;
      }
    }
  }
}

void idft(i64 *a, int len) {
  dft(a, len);
  reverse(a + 1, a + len);
  i64 t = q_pow(len, p - 2);
  FOR(i, 0, len) a[i] = a[i] * t % p;
}

void mul(i64 *a, i64 *b, int len) { // A, B
  FOR(i, 0, len) A[i] = a[i], B[i] = b[i];
  int lim = wrap(len);
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = A[i] * A[i] % p;
  idft(A, lim);
  FOR(i, 0, len) a[i] = A[i];
  FOR(i, 0, lim) A[i] = B[i] = 0;
}

void cdq(int l, int r) { // _c A B
  if (r == l + 1) {
    if (l) _c[l] = _c[l] * iv[l] % p;
    return;
  }
  int mid = (l + r) >> 1;
  cdq(l, mid);
  FOR(i, l, mid) A[i-l] = _c[i];
  FOR(i, 0, r-l) B[i] = a[i];
  int lim = wrap(mid + r - 2 * l);
  dft(A, lim);
  dft(B, lim);
  FOR(i, 0, lim) A[i] = A[i] * B[i] % p;
  idft(A, lim);
  FOR(i, mid, r) red(_c[i] += A[i-l]);
  FOR(i, 0, lim) A[i] = B[i] = 0;
  cdq(mid, r);
}

void exp(i64 *a, int len) { // |_c A B| _c, A, B
  _c[0] = 1;
  for (int i = 0; i < len; ++i) {
    a[i] = i * a[i] % p;
  }
  ::a = a;
  cdq(0, len);
  for (int i = 0; i < len; ++i) {
    a[i] = _c[i];
    _c[i] = 0;
  }
}

void inv(i64 *a, int len) { // _c A B
  _c[0] = q_pow(a[0], p - 2);
  int lm = wrap(len);
  for (int n = 1; n < len; n <<= 1) {
    int lim = n << 2;
    FOR(i, 0, n) A[i] = _c[i];
    FOR(i, 0, n << 1) B[i] = a[i];
    dft(A, lim);
    dft(B, lim);
    FOR(i, 0, lim) A[i] = (A[i] * 2 + p - A[i] * A[i] % p * B[i] % p) % p;
    idft(A, lim);
    FOR(i, 0, n << 1) _c[i] = A[i];
    FOR(i, 0, lim) A[i] = B[i] = 0;
  }
  for (int i = 0; i < len; ++i) a[i] = _c[i];
  for (int i = 0; i < lm; ++i) _c[i] = 0;
}

void sqrt(i64 *a, int len) { // (_c A B) _h _f A B
  _h[0] = 1;
  int lm = wrap(len);
  for (int n = 1; n < len; n <<= 1) {
    int lim = n << 2;
    FOR(i, 0, n) _f[i] = _h[i];
    inv(_f, n << 1);
    FOR(i, 0, n << 1) B[i] = a[i];
    dft(_f, lim);
    dft(B, lim);
    FOR(i, 0, lim) A[i] = (_f[i] * B[i]) % p;
    idft(A, lim);
    FOR(i, 0, n << 1) _h[i] = (A[i] + _h[i]) * iv[2] % p;
    FOR(i, 0, lim) _f[i] = A[i] = B[i] = 0;
  }
  for (int i = 0; i < len; ++i) a[i] = _h[i];
  for (int i = 0; i < lm; ++i) _h[i] = 0;
}

void ln(i64 *a, int len) { // |_c A B| _f A B
  FOR(i, 0, len) {
    _f[i] = a[i];
    a[i] = (i + 1) * a[i + 1] % p;
  }
  inv(_f, len);
  mul(a, _f, len << 1);
  ROF(i, 1, len) a[i] = a[i-1] * iv[i] % p;
  a[0] = 0;
  FOR(i, 0, len) _f[i] = 0;
}

inline void MSET(i64 *a, int len) { // [[_c A B] _c A B] _f
  FOR(i, 1, len) {
    for (int j = 1; j * i < len; ++j) {
      red(_f[i * j] += a[i] * iv[j] % p);
    }
  }
  exp(_f, len);
  FOR(i, 0, len) a[i] = _f[i], _f[i] = 0;
}

inline void PSET(i64 *a, int len) { // [[_c A B] _c A B] _f
  FOR(i, 1, len) {
    for (int j = 1; j * i < len; ++j) {
      if (j & 1) red(_f[i * j] += a[i] * iv[j] % p);
      else red(_f[i * j] += p - a[i] * iv[j] % p);
    }
  }
  exp(_f, len);
  FOR(i, 0, len) a[i] = _f[i], _f[i] = 0;
}

i64 g[N], h[N];

void init() {
  i64 w = q_pow(3, (p-1)/N);
  gp[0] = 1;
  FOR(i, 1, N) gp[i] = gp[i-1] * w % p;
  iv[1] = 1;
  FOR(i, 2, N) iv[i] = (p - p / i) * iv[p % i] % p;
}

void solve() {
  init();
  int n = rd() + 1;
  FOR(i, 0, n) h[i] = 1;
  MSET(h, n);
  FOR(i, 1, n) cout << h[i] << '\n';
}

int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}

