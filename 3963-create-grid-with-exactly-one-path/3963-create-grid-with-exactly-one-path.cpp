#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize the grid entirely with obstacles '#'
        vector<string> grid(m, string(n, '#'));
        
        // Carve out a path along the top row
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }
        
        // Carve out a path down the rightmost column
        for (int i = 1; i < m; ++i) {
            grid[i][n - 1] = '.';
        }
        
        return grid;
    }
};