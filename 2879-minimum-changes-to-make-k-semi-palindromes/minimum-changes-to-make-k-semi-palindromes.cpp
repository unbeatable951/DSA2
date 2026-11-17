
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // Stage 1: Precompute substring costs
        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;

                // Try every proper divisor
                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Process each group
                    for (int r = 0; r < d; r++) {

                        int left = r;
                        int right = len - d + r;

                        while (left < right) {

                            if (s[i + left] != s[i + right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // Stage 2: Partition DP
        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {

            for (int i = 2 * parts; i <= n; i++) {

                for (int t = 2 * (parts - 1); t <= i - 2; t++) {

                    if (dp[t][parts - 1] == INF)
                        continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[t][parts - 1] + cost[t][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
