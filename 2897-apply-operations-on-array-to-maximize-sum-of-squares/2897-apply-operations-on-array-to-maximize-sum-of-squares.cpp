class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> bitCount(30, 0);
        
        // Count set bits for each position
        for (int x : nums) {
            for (int b = 0; b < 30; ++b) {
                if ((x >> b) & 1) {
                    bitCount[b]++;
                }
            }
        }
        
        long long totalSum = 0;
        long long MOD = 1e9 + 7;
        
        // Form the k largest possible numbers
        vector<long long> topNums(k, 0);
        for (int b = 29; b >= 0; --b) {
            for (int i = 0; i < k; ++i) {
                if (bitCount[b] > 0) {
                    topNums[i] |= (1LL << b);
                    bitCount[b]--;
                }
            }
        }
        
        // Calculate the sum of squares modulo 10^9 + 7
        for (int i = 0; i < k; ++i) {
            totalSum = (totalSum + (topNums[i] * topNums[i]) % MOD) % MOD;
        }
        
        return totalSum;
    }
};