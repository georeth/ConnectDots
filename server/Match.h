#ifndef MATCH_H_SBIQ58CN
#define MATCH_H_SBIQ58CN

#include <vector>
#include <utility>
#include "Geometry.h"

namespace ConnectDots {

enum MatchStatus { RUNNING, FINISHED };

struct LineById { int id[2]; };
struct TriangleById { int id[3]; };

enum DrawLineStatus { SUCC, OUT_OF_BOUND, SAME_POINT, INTERSECTION };
struct DrawLineResult {
    DrawLineStatus status;
    int line_id_out;
    std::vector<TriangleById> triangles;
    std::vector<Int> scores;
};

struct ValidLinesResult {
    std::vector<LineById> lines;
    // std::vector<std::vector<TriangleById>> triangles;
    // std::vector<std::vector<Int>> scores;
};

class Match {
public:
    // Core API
    void Init(const std::vector<Point> &points, bool speedy_mode);
    MatchStatus GetStatus();
    int CurrentPlayer();
    DrawLineResult DrawLine(int p1, int p2);

    // Auxiliary
    ValidLinesResult ValidLines();

private:
    int fCurrentPlayer;
    int fStep;
    bool fSpeedy;
    std::vector<Point> fPoints;
    std::vector<LineById> fLines;
    std::vector<TriangleById> fTriangles;
    std::vector<int> fOwner;
};

}

#endif /* end of include guard: MATCH_H_SBIQ58CN */
