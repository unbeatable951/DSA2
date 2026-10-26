class Solution {
private:
    long long dfs(vector<vector<int>>& grid, int i, int j) {
        int n = grid.size();
        int m = grid[0].size();

        // Base case: out of bounds or water (0)
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0) {
            return 0;
        }

        // Save the value of the current cell before sinking it
        long long current_val = grid[i][j];
        
        // Sink the cell so we don't visit it again (acts as our visited tracker)
        grid[i][j] = 0;

        // Accumulate the current cell's value plus all its connected 4-directional neighbors
        return current_val + dfs(grid, i + 1, j)
                           + dfs(grid, i - 1, j)
                           + dfs(grid, i, j + 1)
                           + dfs(grid, i, j - 1);
    }

public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        int valid_islands_count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // If we find land, compute its total value sum using DFS
                if (grid[i][j] > 0) {
                    long long island_sum = dfs(grid, i, j);

                    // Check if the total sum is divisible by k
                    if (island_sum % k == 0) {
                        valid_islands_count++;
                    }
                }
            }
        }

        return valid_islands_count;
    }
};