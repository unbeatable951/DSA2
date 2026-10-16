#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    static const int MOD = 1e9 + 7;
    vector<long long> sum1, sum2, lazy;

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = l + (r - l) / 2;
            apply(2 * node, l, mid, lazy[node]);
            apply(2 * node + 1, mid + 1, r, lazy[node]);
            lazy[node] = 0;
        }
    }

    void apply(int node, int l, int r, long long val) {
        long long len = (r - l + 1);
        sum2[node] = (sum2[node] + 2 * val * sum1[node] % MOD + val * val % MOD * len) % MOD;
        sum1[node] = (sum1[node] + val * len) % MOD;
        lazy[node] = (lazy[node] + val) % MOD;
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        push(node, l, r);
        int mid = l + (r - l) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        sum1[node] = (sum1[2 * node] + sum1[2 * node + 1]) % MOD;
        sum2[node] = (sum2[2 * node] + sum2[2 * node + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sum1.assign(4 * n, 0);
        sum2.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        unordered_map<int, int> last_pos;
        long long total_ans = 0;

        for (int j = 0; j < n; ++j) {
            int prev = -1;
            if (last_pos.find(nums[j]) != last_pos.end()) {
                prev = last_pos[nums[j]];
            }
            
            update(1, 0, n - 1, prev + 1, j, 1);
            last_pos[nums[j]] = j;

            total_ans = (total_ans + sum2[1]) % MOD;
        }

        return total_ans;
    }
};