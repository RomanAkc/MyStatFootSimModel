#include "result.h"
#include "outcomeProbabilities.h"
#include <functional>

bool CResult::m_bResultInited = false;
std::map<std::pair<int, int>, int> CResult::m_mapProbGoalDiff;
std::map<int, int> CResult::m_mapProbGoalDraw;
std::map<int, int> CResult::m_mapProbGoalLoseTeam;
std::random_device CResult::rd;
std::mt19937 CResult::generator(rd());
std::uniform_int_distribution<> CResult::dist10000(1, 10000);

CMatchResult CResult::getResult(int nDiffPower, bool bWithPenalty /*= false*/)
{
    if(!m_bResultInited)
        InitResult();

    CResult::EWinner winner = GetWinner(nDiffPower);
    CMatchResult result(CResult::GetGoals(nDiffPower, winner));

    if(bWithPenalty && winner == CResult::DRAW)
    {
        ;
    }

    return result;
}

void CResult::InitResult()
{
    if(m_bResultInited)
        return;

    m_mapProbGoalDiff.clear();

    auto mapProbGoalDiff = COutcomeProbabilities::getProbGoalDiff();
    int nCurrDiff = -1;
    for(auto it = mapProbGoalDiff.begin(); it != mapProbGoalDiff.end(); ++it)
    {
        nCurrDiff = it->first;
        int nLast = 1;
        int nCurrDiffGoals = 1;
        int nCurrVecIndex = 0;
        int nLastSum = 0;

        for(; nCurrVecIndex < it->second.size(); ++nCurrVecIndex)
        {
            nLastSum += it->second[nCurrVecIndex];

            for(int i = nLast; i <= nLastSum; ++i)
                m_mapProbGoalDiff[std::make_pair(nCurrDiff, i)] = nCurrDiffGoals;

            nLast = nLastSum + 1;
            nCurrDiffGoals++;
        }
    }

    auto FillMap = [](const std::map<int, int>& in, std::map<int, int>& out)
    {
        out.clear();

        int nLast = 1;
        int nLastSum = 0;

        for(auto it = in.begin(); it != in.end(); ++it)
        {
            nLastSum += it->second;

            for(int i = nLast; i <= nLastSum; ++i)
                out[i] = it->first;

            nLast = nLastSum + 1;
        }
    };

    FillMap(COutcomeProbabilities::getProbGoalDraw(), m_mapProbGoalDraw);
    FillMap(COutcomeProbabilities::getProbGoalLoseTeam(), m_mapProbGoalLoseTeam);

    m_bResultInited = true;
}

CResult::EWinner CResult::GetWinner(int nDiffPower)
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

CGoals CResult::GetGoals(int nDiffPower, EWinner winner)
{
    int nRandom = dist10000(generator);

    if(winner == CResult::DRAW)
    {
        auto it_find = m_mapProbGoalDraw.find(nRandom);
        if(it_find == m_mapProbGoalDraw.end())
            return CGoals(0, 0);

        return CGoals(it_find->second, it_find->second);
    }

    auto it_find = m_mapProbGoalDiff.find(std::make_pair(nDiffPower, nRandom));
    if(it_find == m_mapProbGoalDiff.end())
    {
        if(winner == CResult::WIN_HOME)
            return CGoals(1, 0);

        return CGoals(0, 1);
    }
    int nDiffGoals = it_find->second;

    int nGoalLoseTeam = 0, nGoalWinTeam = 0;

    auto it_find_goalloseteam = m_mapProbGoalLoseTeam.find(dist10000(generator));
    if(it_find_goalloseteam == m_mapProbGoalLoseTeam.end())
    {
        nGoalLoseTeam = 0;
        nGoalWinTeam = nDiffGoals;
    }
    else
    {
        nGoalLoseTeam = it_find_goalloseteam->second;
        if(nGoalLoseTeam + nDiffGoals >= 12)
            nGoalLoseTeam = 0;

        nGoalWinTeam = nGoalLoseTeam + nDiffGoals;
    }

    if(winner == CResult::WIN_HOME)
        return CGoals(nGoalWinTeam, nGoalLoseTeam);

    return CGoals(nGoalLoseTeam, nGoalWinTeam);

}
