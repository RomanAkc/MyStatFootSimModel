#pragma once
#include <vector>
#include <exception>

class COutcomeProbabilities
{
private:
    std::vector<int> m_ProbWin;
    std::vector<int> m_ProbDraw;

public:
    COutcomeProbabilities();

//For get data
    int getProbWin(int nIndex) const;
    int getProbDraw(int nIndex) const;
};
