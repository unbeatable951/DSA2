class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;
        // Max possible g * l when nums[i] <= 10 is 10 * 2520 = 25200
        long long MAX_VAL = 1e9; 

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; j++) {
                // Stop before prod overflows or exceeds any possible g * l
                if (prod > MAX_VAL / nums[j]) break;
                
                prod *= nums[j];
                g = gcd(g, (long long)nums[j]);
                l = (l / gcd(l, (long long)nums[j])) * nums[j];

                if (prod == g * l) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};