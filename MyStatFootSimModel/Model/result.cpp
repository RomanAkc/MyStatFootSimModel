#include "result.h"
#include "outcomeProbabilities.h"

bool CResult::m_bResultInited = false;
std::map<std::pair<int, int>, int> CResult::m_mapProbGoalDiff;
std::random_device CResult::rd;
std::mt19937 CResult::generator(rd());
std::uniform_int_distribution<> CResult::dist10000(1, 10000);

CMatchResult CResult::getResult(int nDiffPower, bool bWithPenalty /*= false*/)
{
    InitResult();

    CResult::EWinner winner = GetWinnerHome(nDiffPower);

    if(winner != CResult::DRAW)
    {
        ;
    }

    int res1 = dist10000(generator);
    int res2 = dist10000(generator);
    return CMatchResult(res1, res2);
}

void CResult::InitResult()
{
    if(m_bResultInited)
        return;

    m_mapProbGoalDiff.clear();
    auto map = COutcomeProbabilities::getProbGoalDiff();

    int nCurrDiff = -1;
    int nLast = 1;
    int nCurrDiffGoals = 1;
    int nLastSum = 1;
    int nCurrVecIndex = 0;
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        if(it->first != nCurrDiff)
        {
            nCurrDiff = it->first;
            nLast = 1;
            nCurrDiffGoals = 1;
            nCurrVecIndex = 0;
            nLastSum = it->second[nCurrVecIndex];
        }
        else
        {
            nCurrVecIndex++;
            nLastSum += it->second[nCurrVecIndex];
        }

        for(int i = nLast; i <= nLastSum; ++i)
            m_mapProbGoalDiff[std::make_pair(nCurrDiff, i)] = nCurrDiffGoals;

        nLast = nLastSum + 1;
        nCurrDiffGoals++;
    }

    m_bResultInited = true;
}

CResult::EWinner CResult::GetWinnerHome(int nDiffPower)
{
    int nRandom = dist10000(generator);
    int nProbWin = COutcomeProbabilities::getProbWin(nDiffPower);
    if(nRandom <= nProbWin)
        return CResult::WIN_HOME;

    int nProbDraw = COutcomeProbabilities::getProbDraw(nDiffPower);
    if(nRandom > nProbWin + nProbDraw)
        return CResult::WIN_AWAY;

    return CResult::DRAW;
}
