// Time:  O(n * 2^p)
// Space: O(n * 2^p)

static const int MAX_NUM = 30;
vector<int> linear_sieve_of_eratosthenes(int n) {  // Time: O(n), Space: O(n)
    vector<int> spf(n + 1, -1);
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == -1) {
            spf[i] = i;
            primes.emplace_back(i);
        }
        for (const auto& p : primes) {
            if (i * p > n || p > spf[i]) {
                break;
            }
            spf[i * p] = p;
        }
    }
    return primes;
}

const auto& PRIMES = linear_sieve_of_eratosthenes(MAX_NUM);
vector<int> init_masks() {
    vector<int> masks(MAX_NUM + 1);
    for (int x = 0; x <= MAX_NUM; ++x) {
        for (int i = 0, y = x; i < size(PRIMES); ++i) {
            if (y % PRIMES[i]) {
                continue;
            }
            if (y % (PRIMES[i] * PRIMES[i]) == 0) {
                masks[x] = 0;
                break;
            }
            masks[x] |= (1 << i);
            y /= PRIMES[i];
        }
    }
    return masks;
}
const auto& MASKS = init_masks();

// number theory, combinatorics, backtracking, memoization, bitmasks
class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        unordered_map<int, int> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> arr;
        for (const auto& [k, _] : cnt) {
            if (k != 1) {
                arr.emplace_back(k);
            }
        }
        vector<vector<int>> dp(size(arr), vector<int>(1 << size(PRIMES), -1));
        const function<int(int, int)> backtracking = [&](int i, int mask) {
            if (i == size(arr)) {
                return 1;
            }
            if (dp[i][mask] == -1) {
                dp[i][mask] = backtracking(i + 1, mask);
                if (MASKS[arr[i]] && (MASKS[arr[i]] & mask) == 0) {
                    dp[i][mask] = (dp[i][mask] + static_cast<int64_t>(cnt[arr[i]]) * backtracking(i + 1, mask | MASKS[arr[i]])) % MOD;
                }
            }
            return dp[i][mask];
        };
        return cnt.count(1) ? ((backtracking(0, 0) * powmod(2, cnt[1]) - 1) + MOD) % MOD: ((backtracking(0, 0) - 1) + MOD) % MOD;
    }
};
