#pragma once
#include <vector>
#include <map>

class COutcomeProbabilities
{
private:
    static const std::vector<int> m_ProbWin;
    static const std::vector<int> m_ProbDraw;
    static const std::map<int, std::vector<int>> m_ProbGoalDiff;
    static const std::map<int, int> m_ProbGoalDraw;
    static const std::map<int, int> m_ProbGoalLoseTeam;

public:
    static int getProbWin(int nIndex);
    static int getProbDraw(int nIndex);
    static const std::map<int, std::vector<int>> getProbGoalDiff();
    static const std::map<int, int>& getProbGoalDraw();
    static const std::map<int, int>& getProbGoalLoseTeam();
};
