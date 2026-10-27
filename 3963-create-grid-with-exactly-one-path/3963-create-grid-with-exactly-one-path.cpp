#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> createGrid(int m, int n) {
        // Initialize an m x n grid filled with obstacles ('#')
        std::vector<std::string> grid(m, std::string(n, '#'));
        
        // Make the top row all free cells '.'
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }
        
        // Make the rightmost column all free cells '.'
        for (int i = 0; i < m; ++i) {
            grid[i][n - 1] = '.';
        }
        
        return grid;
    }
};