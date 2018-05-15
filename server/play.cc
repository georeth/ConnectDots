#include "Geometry.h"
#include "Match.h"
#include "GeneratePoints.h"
#include <cstdio>

using namespace std;
using namespace ConnectDots;

int main() {
    RNG rng;

    vector<Point> pts = GeneratePoints(20, 20, 10, rng, 3, 0.5);
    for (Point p : pts) {
        printf("%d %d\n", (int)p.x, (int)p.y);
    }
}
