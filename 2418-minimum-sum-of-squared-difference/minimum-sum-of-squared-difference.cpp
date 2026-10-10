class Solution {
public:
    long long minSumSquareDiff(std::vector<int>& nums1, std::vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        int max_diff = 0;
        // Size 100001 covers differences from 0 to 100000
        std::vector<long long> count(100001, 0);

        for (int i = 0; i < n; ++i) {
            int d = std::abs(nums1[i] - nums2[i]);
            count[d]++;
            max_diff = std::max(max_diff, d);
        }

        // Greedily reduce the largest differences using available budget `k`
        for (int d = max_diff; d > 0; --d) {
            if (count[d] == 0) continue;

            long long ops = std::min(k, count[d]);
            count[d] -= ops;
            count[d - 1] += ops;
            k -= ops;

            if (k == 0) break;
        }

        // Calculate the final minimum sum of squared differences
        long long result = 0;
        for (int d = 0; d <= 100000; ++d) { // Fixed upper bound to 100000
            if (count[d] > 0) {
                result += count[d] * (long long)d * d;
            }
        }

        return result;
    }
};