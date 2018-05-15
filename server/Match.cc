#include "Match.h"
#include <cassert>

namespace ConnectDots {

static inline bool operator==(LineById ln1, LineById ln2) {
    if (ln1.id[0] > ln1.id[1]) std::swap(ln1.id[0], ln1.id[1]);
    if (ln2.id[0] > ln2.id[1]) std::swap(ln2.id[0], ln2.id[1]);

    return ln1.id[0] == ln2.id[0] && ln1.id[1] == ln2.id[1];
}

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
    for (int id = 0; id < fLines.size(); ++id) {
        Line cur{fPoints[fLines[id].id[0]], fPoints[fLines[id].id[1]]};
        if (HasIntersection(ln, cur)) {
            result.line_id_out = id;
            result.status = INTERSECTION;
            return result;
        }
    }

    result.status = SUCC;
    result.line_id_out = fLines.size();
    fLines.push_back(LineById{p1, p2});

    // triangles for scores


    return result;
}
ValidLinesResult Match::ValidLines() {
    ValidLinesResult result;
    for (int p1 = 0; p1 < fPoints.size(); ++p1) {
        for (int p2 = p1 + 1; p2 < fPoints.size(); ++p2) {
            LineById lni{p1, p2};
            Line ln{fPoints[p1], fPoints[p2]};

            for (LineById curi : fLines) {
                Line cur{fPoints[curi.id[0]], fPoints[curi.id[1]]};
                if (curi == lni)
                    continue;
                if (HasIntersection(cur, ln))
                    continue;
            }

            result.lines.push_back(lni);
        }
    }
    return result;
}

}; // namespace ConnectDots
