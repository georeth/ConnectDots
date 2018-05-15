#ifndef MATCHGENERATOR_H_QUEMVLOD
#define MATCHGENERATOR_H_QUEMVLOD

#include <random>
#include <vector>
#include <cassert>
#include "Geometry.h"

namespace ConnectDots {

typedef std::mt19937_64 RNG;
static const int MAX_RETRY = 20;

std::vector<Point> GeneratePoints(Int W, Int H, int num, RNG &rng, Int dist2, double gap) {
    assert(dist2 > 0);
    assert(gap > 0);
    assert(W > 0);
    assert(H > 0);

    std::vector<Point> res;

    std::uniform_int_distribution<Int> xdist(0, W - 1);
    std::uniform_int_distribution<Int> ydist(0, H - 1);

    for (int i = 0; i < num; ++i) {
        bool succ = false;
        int iter = 0;
        while (!succ && iter < MAX_RETRY) {
            ++iter;
            succ = true;

            Int x = xdist(rng);
            Int y = ydist(rng);

            // check |p - pi|
            Point p{x, y};
            for (Point pi : res) {
                if ((p - pi).dist2() < dist2) {
                    succ = false;
                    break;
                }
            }
            if (!succ) continue;

            // check dist(p, pi \to pj)
            for (int i = 0; i < res.size(); ++i) {
                Point pi = res[i];
                for (int j = i + 1; j < res.size(); ++j) {
                    Point pj = res[j];
                    Line ln{pi, pj};

                    if (ln.distTo(p) < gap) {
                        succ = false;
                        break;
                    }
                }
                if (!succ) break;
            }
            if (!succ) continue;

            res.push_back(p);
        }

        if (iter == MAX_RETRY) return res;
    }
    return res;
}

}; // namespace ConnectDots

#endif /* end of include guard: MATCHGENERATOR_H_QUEMVLOD */
