
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = find(nums.begin(), nums.end(), 0) - nums.begin();

        // Check whether values increase from 0
        // while moving around the array.
        auto check = [&](int step) {
            for (int i = 0; i < n; i++) {
                int idx = (zero + i * step + n) % n;

                if (nums[idx] != i)
                    return false;
            }
            return true;
        };

        int ans = INT_MAX;

        if (check(1)) {
            ans = min(ans, zero);
            ans = min(ans, n - zero + 2);
        }

        if (check(-1)) {
            ans = min(ans, zero + 2);
            ans = min(ans, n - zero);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
