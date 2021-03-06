/*
EULER TOTIENT FUNCTION
Alice is given the task of finding totient φ of a positive integer n (the number of positive integers less than or equal to n that are co-prime to n). As Alice is going on a date, he asks you to write a program for this.

Input Format:
First line of input of consists of an integer 't' denoting the number of test cases. Then 't' lines follow each containing integer values 'n' to calculate totient.

Constraints:
1<=t<=50000 1<=n<=10^6

Output Format
Print 't' lines

Sample Input
2
2
3

Sample Output
1
2
 */
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <numeric>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

/* ------------------------- HELPERS DEFINE -------------------------- */
template <typename T>
ostream &operator<<(ostream &o, pair<const T, T> &pair) // To print map in PRINT
{
    o << pair.first << " " << pair.second << endl;
    return o;
}

#define DEBUG(X) cout << #X << " = " << X << endl;
#define PRINT(C)                           \
    do                                     \
    {                                      \
        cout << setw(10) << #C << " : \n"; \
        for (auto &&i : C)                 \
        {                                  \
            cout << i << " ";              \
        }                                  \
        cout << endl;                      \
    } while (0);
#define ALL(C) (C).begin(), (C).end()
#define PRESENT(C, X) ((C).find(X) != (C).end())
#define BENCHMARK(f)         \
    do                       \
    {                        \
        cout << #f << " = "; \
        benchmark(f);        \
    } while (0);

const auto benchmark = [](function<void(void)> f) {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    f();
    cout << chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count() << " microseconds\n";
};

using ll = unsigned long long;

ll get_no_of_query();

template <typename T>
vector<T> get_array(T Q);

/* ----------------------------- MAIN CODE ----------------------------- */
vector<ll> smallest_prime_factor;
ll primes_upto = 1000000;

/*
index: 0  | 1  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15
prime: -1 | -1 | 2 | 3 | 2 | 5 | 2 | 7 | 2 | 3 | 2  | 11 | 2  | 13 | 2  | 3
Note: Could multiple as well
 */
template <typename T>
vector<T> precomp_small_primes_upto(T n)
{
    vector<T> prime_list((n + 1), numeric_limits<T>::max());

    for (T d = 2; d <= n; d++)
    {
        prime_list[d] = min(d, prime_list[d]); // self divisible

        for (T i = (d * d); i <= n; i += d)
        {
            prime_list[i] = min(d, prime_list[i]);
        }
    }

    return prime_list;
}

template <typename T>
map<T, T> smallest_prime_factors_of(T n)
{
    map<T, T> prime_factors;

    while (n > 1)
    {
        prime_factors[smallest_prime_factor[n]]++;
        n /= smallest_prime_factor[n];
    }

    return prime_factors;
}

ll euler_totient_function(ll N) // also called `phi`
{
    ll res = N;
    map<ll, ll> prime_factors_N = smallest_prime_factors_of(N);

    for (auto &&factor : prime_factors_N)
    {
        res = (res - (res / factor.first));
    }
    return res;
}

int main()
{
    auto Q = get_no_of_query();
    smallest_prime_factor = precomp_small_primes_upto(primes_upto);

    for (ll i = 0; i < Q; i++)
    {
        ll n;
        cin >> n;
        cout << euler_totient_function(n) << endl;
    }

    return 0;
}

/* -------------------- HELPERS IMPLEMENTATION ------------------------ */
ll get_no_of_query()
{
    ll Q;
    cin >> Q;
    return Q;
}

template <typename T>
vector<T> get_array(T Q)
{
    vector<T> res(Q);

    for (T i = 0; i < Q; i++)
    {
        T temp;
        cin >> temp;
        res[i] = temp;
    }

    return res;
}
