
class Solution {
    using ll = long long;

    static const ll MOD1 = 1000000007;
    static const ll MOD2 = 1000000009;
    static const ll BASE = 911382323;

    struct Hash {
        ll h1, h2;

        bool operator==(const Hash& other) const {
            return h1 == other.h1 && h2 == other.h2;
        }
    };

    struct HashFunc {
        size_t operator()(const Hash& h) const {
            return h.h1 ^ (h.h2 << 1);
        }
    };

    vector<ll> p1, p2, pref1, pref2;

    bool check(int k) {
        int n = pref1.size() - 1;

        unordered_map<Hash, int, HashFunc> freq;

        int uniqueCount = 0;

        for (int i = 0; i + k <= n; i++) {

            ll h1 = (pref1[i + k] -
                     pref1[i] * p1[k] % MOD1 + MOD1) % MOD1;

            ll h2 = (pref2[i + k] -
                     pref2[i] * p2[k] % MOD2 + MOD2) % MOD2;

            Hash key = {h1, h2};

            int &count = freq[key];

            if (count == 0) {
                uniqueCount++;
            }
            else if (count == 1) {
                uniqueCount--;
            }

            count++;

        }

        return uniqueCount > 0;
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {

        int n = nums.size();

        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);

        pref1.resize(n + 1, 0);
        pref2.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {

            ll x = ((ll)nums[i] % MOD1 + MOD1) % MOD1;
            ll y = ((ll)nums[i] % MOD2 + MOD2) % MOD2;

            x++;
            y++;

            p1[i + 1] = p1[i] * BASE % MOD1;
            p2[i + 1] = p2[i] * BASE % MOD2;

            pref1[i + 1] = (pref1[i] * BASE + x) % MOD1;
            pref2[i + 1] = (pref2[i] * BASE + y) % MOD2;
        }

        int low = 1;
        int high = n;
        int ans = n;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
