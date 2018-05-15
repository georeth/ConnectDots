#ifndef MATCH_H_SBIQ58CN
#define MATCH_H_SBIQ58CN

#include <vector>
#include <set>
#include <utility>
#include "Geometry.h"

namespace ConnectDots {

enum MatchStatus { RUNNING, FINISHED };

struct LineById {
    int p1, p2;
    LineById(int p1, int p2) : p1(p1), p2(p2) {
        if (p1 > p2) std::swap(p1, p2);
    }
    bool operator==(LineById that) const {
        return std::make_pair(p1, p2) == std::make_pair(that.p1, that.p2);
    }
    bool operator<(LineById that) const {
        return std::make_pair(p1, p2) < std::make_pair(that.p1, that.p2);
    }
};
struct TriangleById {
    int p1, p2, p3; 
    TriangleById(int p1, int p2, int p3) : p1(p1), p2(p2), p3(p3) { }
};

enum DrawLineStatus { SUCC, OUT_OF_BOUND, SAME_POINT, INTERSECTION };
struct DrawLineResult {
    DrawLineStatus status;
    int line_id_out;
    std::vector<TriangleById> triangles;
    std::vector<Int> scores;
};

struct ValidLinesResult {
    std::vector<LineById> lines;
    std::vector<std::vector<TriangleById>> triangles;
    std::vector<std::vector<Int>> scores;
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
    void GetTriangles(LineById ln, std::vector<TriangleById> &triangles, std::vector<Int> &scores);

    int fCurrentPlayer;
    int fStep;
    bool fSpeedy;
    std::vector<Point> fPoints;
    std::vector<LineById> fLines;
    std::set<LineById> fLinesSet;

    std::vector<TriangleById> fTriangles;
    std::vector<int> fOwner;
};

}

#endif /* end of include guard: MATCH_H_SBIQ58CN */
