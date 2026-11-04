
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<long long> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto rebalance = [&]() {
            while (low.size() > high.size() + 1) {
                long long val = *prev(low.end());
                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while (low.size() < high.size()) {
                long long val = *high.begin();
                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        auto add = [&](long long val) {
            if (low.empty() || val <= *prev(low.end())) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            rebalance();
        };

        auto remove = [&](long long val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            rebalance();
        };

        vector<long long> cost(n - x + 1);

        // Calculate cost of every window of size x.
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                long long median = *prev(low.end());

                cost[i - x + 1] =
                    median * (long long)low.size() - sumLow
                    + sumHigh - median * (long long)high.size();
            }
        }

        // DP: minimum cost to select j windows
        // using the first i elements.
        const long long INF = LLONG_MAX / 4;

        vector<long long> prevDP(n + 1, 0);
        vector<long long> currDP(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(currDP.begin(), currDP.end(), INF);

            for (int i = 1; i <= n; i++) {
                // Skip element i-1.
                currDP[i] = currDP[i - 1];

                // Select window ending at i-1.
                if (i >= x && prevDP[i - x] != INF) {
                    currDP[i] = min(
                        currDP[i],
                        prevDP[i - x] + cost[i - x]
                    );
                }
            }

            swap(prevDP, currDP);
        }

        return prevDP[n];
    }
};
