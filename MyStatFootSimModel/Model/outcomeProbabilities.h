#pragma once
#include <vector>
#include <map>

class COutcomeProbabilities
{
private:
    static const std::vector<int> m_ProbWin;
    static const std::vector<int> m_ProbDraw;
    static const std::map<int, std::vector<int>> m_ProbGoalDiff;

public:
    static int getProbWin(int nIndex);
    static int getProbDraw(int nIndex);
    static const std::map<int, std::vector<int>>& getProbGoalDiff();
};
