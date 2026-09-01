#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int, int>> litter;

        // Find S and all L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        // No litter to collect
        if (k == 0) return 0;

        // Give every litter cell a bit
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            auto [r, c] = litter[i];
            litterId[r][c] = i;
        }

        int totalMasks = 1 << k;

        /*
            best[pos][mask] = maximum remaining energy
            with which we have reached this position
            having collected exactly 'mask'.
            
            If we reach the same (pos, mask) with
            <= best[pos][mask], that state is dominated.
        */
        vector<vector<int>> best(m * n,
                                 vector<int>(totalMasks, -1));

        struct State {
            int r;
            int c;
            int mask;
            int en;
        };

        queue<State> q;

        int startPos = sr * n + sc;
        best[startPos][0] = energy;

        q.push({sr, sc, 0, energy});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            // Process one BFS level = same number of moves
            while (sz--) {
                State cur = q.front();
                q.pop();

                int r = cur.r;
                int c = cur.c;
                int mask = cur.mask;
                int en = cur.en;

                // All litter collected
                if (mask == totalMasks - 1) {
                    return moves;
                }

                // If energy is 0, we cannot make another move.
                // The only way to continue is to already be on R,
                // but R resets immediately when entered, so a valid
                // state on R should already have energy == 'energy'.
                if (en == 0) continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = en - 1;

                    int newMask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int id = litterId[nr][nc];
                        newMask |= (1 << id);
                    }

                    // Reset energy on R
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    int pos = nr * n + nc;

                    /*
                        Dominance pruning:
                        If we have already reached this same
                        position with the same collected litter
                        and >= energy, this new state can never
                        be better.
                    */
                    if (newEnergy <= best[pos][newMask])
                        continue;

                    best[pos][newMask] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};