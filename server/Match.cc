#include "Match.h"
#include <cassert>

namespace ConnectDots {

void Match::Init(const std::vector<Point> &points, bool speedy_mode) {
    fPoints = points;
    assert(fPoints.size() >= 2);

    fStep = 0;
    fCurrentPlayer = 0;
    fSpeedy = speedy_mode;
}

MatchStatus Match::GetStatus() {
    ValidLinesResult result = ValidLines();
    if (result.lines.size() > 0)
        return RUNNING;
    return FINISHED;
}
int Match::CurrentPlayer() {
    return fCurrentPlayer;
}

void Match::GetTriangles(LineById ln, std::vector<TriangleById> &triangles, std::vector<Int> &scores) {
    for (int p = 0; p < fPoints.size(); ++p) {
        if (p == ln.p1 || p == ln.p2) continue;
        if (fLinesSet.count(LineById(p, ln.p1)) && fLinesSet.count(LineById(p, ln.p2))) {
            bool succ = true;

            if (!fSpeedy) {
                for (int q = 0; q < fPoints.size(); ++q) {
                    if (Inside(fPoints[p], fPoints[ln.p1], fPoints[ln.p2], fPoints[q])) {
                        succ = false;
                        break;
                    }
                }
            }

            if (succ) {
                triangles.emplace_back(p, ln.p1, ln.p2);
                scores.push_back(abs(Triangle{fPoints[p], fPoints[ln.p1], fPoints[ln.p2]}.Area()));
            }
        }
    }
}

DrawLineResult Match::DrawLine(int p1, int p2) {
    DrawLineResult result;
    if (p1 < 0 || p1 >= fPoints.size() || p2 < 0 || p2 >= fPoints.size()) {
        result.status = OUT_OF_BOUND;
        return result;
    }
    if (p1 == p2) {
        result.status = SAME_POINT;
        return result;
    }

    Line ln{fPoints[p1], fPoints[p2]};
    LineById lni{p1, p2};
    for (int id = 0; id < fLines.size(); ++id) {
        Line cur{fPoints[fLines[id].p1], fPoints[fLines[id].p2]};
        if (HasIntersection(ln, cur)) {
            result.line_id_out = id;
            result.status = INTERSECTION;
            return result;
        }
    }

    result.status = SUCC;
    result.line_id_out = fLines.size();
    fLines.emplace_back(lni);
    fLinesSet.emplace(lni);
    GetTriangles(lni, result.triangles, result.scores);

    for (TriangleById tri : result.triangles) {
        fTriangles.push_back(tri);
        fOwner.push_back(fCurrentPlayer);
    }
    fCurrentPlayer = 1 - fCurrentPlayer;
    return result;
}

ValidLinesResult Match::ValidLines() {
    ValidLinesResult result;
    for (int p1 = 0; p1 < fPoints.size(); ++p1) {
        for (int p2 = p1 + 1; p2 < fPoints.size(); ++p2) {
            LineById lni{p1, p2};
            Line ln{fPoints[p1], fPoints[p2]};

            for (LineById curi : fLines) {
                Line cur{fPoints[curi.p1], fPoints[curi.p2]};
                if (curi == lni)
                    continue;
                if (HasIntersection(cur, ln))
                    continue;
            }

            result.lines.push_back(lni);

            std::vector<TriangleById> triangles;
            std::vector<Int> score;
            GetTriangles(lni, triangles, score);

            result.triangles.push_back(triangles);
            result.scores.push_back(score);
        }
    }

    return result;
}

}; // namespace ConnectDots
