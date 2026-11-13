
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long cost = 0;

        // Store {value, count} in non-increasing order.
        deque<pair<int, int>> dq;

        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            int num = nums[i];
            int count = 1;

            // Merge smaller values into the current value.
            while (!dq.empty() && dq.back().first < num) {
                int nextNum = dq.back().first;
                int nextCount = dq.back().second;

                dq.pop_back();

                count += nextCount;

                cost += 1LL * (num - nextNum) * nextCount;
            }

            dq.push_back({num, count});

            // Reduce window until its cost is within k.
            while (cost > k) {
                int rightmostNum = dq.front().first;
                int rightmostCount = dq.front().second;

                dq.pop_front();

                cost -= rightmostNum - nums[j];
                j--;

                if (rightmostCount > 1) {
                    dq.push_front({
                        rightmostNum,
                        rightmostCount - 1
                    });
                }
            }

            // All subarrays [i...j], [i+1...j], ...
            ans += j - i + 1;
        }

        return ans;
    }
};
