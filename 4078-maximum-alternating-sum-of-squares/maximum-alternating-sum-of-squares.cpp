class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squared(n);
        
        for (int i = 0; i < n; i++) {
            long long val = nums[i];
            squared[i] = val * val;
        }
        
        sort(squared.begin(), squared.end());
        
        long long score = 0;
        int mid = n / 2;
        
        // Subtract the smaller half (odd indices)
        for (int i = 0; i < mid; i++) {
            score -= squared[i];
        }
        
        // Add the larger half (even indices)
        for (int i = mid; i < n; i++) {
            score += squared[i];
        }
        
        return score;
    }
};