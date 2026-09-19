class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        // Find the closest x-coordinate on rectangle
        int closestX = max(x1, min(xCenter, x2));

        // Find the closest y-coordinate on rectangle
        int closestY = max(y1, min(yCenter, y2));

        // Distance between circle center and closest rectangle point
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;

        // Compare squared distance with squared radius
        return dx * dx + dy * dy <= radius * radius;
    }
};