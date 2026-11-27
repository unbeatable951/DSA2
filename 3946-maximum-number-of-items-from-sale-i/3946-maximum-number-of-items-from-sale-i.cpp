
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;

        for (int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);
        }

        vector<int> freeItems(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    freeItems[i]++;
                }
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int weight = items[i][1];
            int value = 1 + freeItems[i];

            for (int b = budget; b >= weight; b--) {
                dp[b] = max(
                    dp[b],
                    dp[b - weight] + value
                );
            }
        }

        int ans = 0;

        for (int b = 0; b <= budget; b++) {
            int extra = (budget - b) / minPrice;
            ans = max(ans, dp[b] + extra);
        }

        return ans;
    }
};
