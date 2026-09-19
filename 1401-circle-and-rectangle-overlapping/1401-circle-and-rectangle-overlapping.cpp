class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {
        
        // Circle ke center ke closest rectangle point ko find karo
        int closestX = max(x1, min(xCenter, x2));
        int closestY = max(y1, min(yCenter, y2));

        // Distance squared
        int dx = closestX - xCenter;
        int dy = closestY - yCenter;

        // sqrt lene ki zarurat nahi
        return dx * dx + dy * dy <= radius * radius;
    }
};