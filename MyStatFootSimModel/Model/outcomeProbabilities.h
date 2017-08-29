#pragma once
#include <vector>
#include <exception>

class COutcomeProbabilities
{
private:
    static std::vector<int> m_ProbWin;
    static std::vector<int> m_ProbDraw;

public:
    static int getProbWin(int nIndex);
    static int getProbDraw(int nIndex);
};
