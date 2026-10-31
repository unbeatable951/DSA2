
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0] = ways arriving from left
        // dp[i][j][1] = ways arriving from above
        vector<vector<vector<long long>>> dp(
            m, vector<vector<long long>>(n, vector<long long>(2, 0))
        );

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Mirror cell
                if (grid[i][j] == 1) {

                    // Entered from left: reflect DOWN
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                    }

                    // Entered from above: reflect RIGHT
                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + dp[i][j][1]) % MOD;
                    }
                }

                // Empty cell
                else {
                    long long ways;

                    // Starting position
                    if (i == 0 && j == 0) {
                        ways = 1;
                    }
                    else {
                        ways = (dp[i][j][0] + dp[i][j][1]) % MOD;
                    }

                    // Move RIGHT
                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + ways) % MOD;
                    }

                    // Move DOWN
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + ways) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};
