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

CMatchResult CResult::getResult(int nDiffPower, bool bUseHomeAway /*= true*/
                                , bool bNeedWinner /*= false*/, const CMatchResult* pFirstResult /*= nullptr*/)
{
    if(!m_bResultInited)
        InitResult();
    
    auto funcCheckIsEndResult = [](const CMatchResult& result, const CMatchResult& firstResult, bool bUseAddTime)->bool
    {
        int nGoalsHome = result.getGoalsFullTime().GetGoalHome() + firstResult.getGoalsFullTime().GetGoalAway();
        int nGoalsAway = result.getGoalsFullTime().GetGoalAway() + firstResult.getGoalsFullTime().GetGoalHome();
        
        if(bUseAddTime)
        {
            nGoalsHome += result.getGoalsAddTime().GetGoalHome();
            nGoalsAway += result.getGoalsAddTime().GetGoalAway();
        }
        
        if(nGoalsHome != nGoalsAway)
            return true;
        
        if(bUseAddTime)
        {
            if(result.getGoalsFullTime().GetGoalAway() + result.getGoalsAddTime().GetGoalAway() != firstResult.getGoalsFullTime().GetGoalAway())
                return true;             
        }
        else 
        {
            if(result.getGoalsFullTime().GetGoalAway() != firstResult.getGoalsFullTime().GetGoalAway())
                return true;
        }
        
        return false;
    };
    
    CResult::EWinner winner = GetWinner(nDiffPower, bUseHomeAway);
    CMatchResult result(CResult::GetGoals(nDiffPower, winner));

    if(bNeedWinner)
    {
        if(pFirstResult)
        {
            if(funcCheckIsEndResult(result, *pFirstResult, false))
                return result;
        }
        else if(winner != CResult::DRAW)
            return result;
        
        winner = GetWinner(nDiffPower, false);
        result.setGoalsAddTime(CResult::GetGoals(nDiffPower, winner));
        
        if(pFirstResult)
        {
            if(funcCheckIsEndResult(result, *pFirstResult, true))
                return result;
        }
        else if(winner != CResult::DRAW)
            return result;
        
        result.setGoalsPenalty(CResult::GetPenalty());
    }

    return result;
}

std::pair<CMatchResult, CMatchResult> CResult::getPairResult(int nDiffPower)
{
    CMatchResult result1 = CResult::getResult(nDiffPower);
    return std::move(std::make_pair(result1, CResult::getResult(nDiffPower * (-1), true, true, &result1)));
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

CResult::EWinner CResult::GetWinner(int nDiffPower, bool bUseHomeAway)
{
    int nRandom = dist10000(generator);
    if(bUseHomeAway)
    {
        if(nDiffPower >= 0)
            nRandom -= 1500;
        else 
            nRandom += 1500;
        
        if(nRandom < 1)
            nRandom = 1;
        
        if(nRandom > 10000)
            nRandom = 10000;
    }
    
    int nProbWin = COutcomeProbabilities::getProbWin(abs(nDiffPower));
    if(nRandom <= nProbWin)
    {
        if(nDiffPower >= 0)
            return CResult::WIN_HOME;
        else 
            return CResult::WIN_AWAY;
    }

    int nProbDraw = COutcomeProbabilities::getProbDraw(abs(nDiffPower));
    if(nRandom > nProbWin + nProbDraw)
    {
        if(nDiffPower >= 0)
            return CResult::WIN_AWAY;
        else 
            return CResult::WIN_HOME;
    }

    return CResult::DRAW;
}

CGoals CResult::GetGoals(int nDiffPower, EWinner winner)
{
    nDiffPower = abs(nDiffPower);
    
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

CGoals CResult::GetPenalty()
{
    auto funcGetKickGoal = []()
    {
        int nRandom = dist10000(generator);
        if(nRandom <= 7500)
            return true;
        
        return false;
    };
    
    int nRound = 1, nGoalHome = 0, nGoalAway = 0;
    while (true) 
    {
        nGoalHome += funcGetKickGoal() ? 1 : 0;
        
        if(nRound > 2 && nRound <= 5)
        {
            if(nGoalHome - nGoalAway > 5 - nRound + 1)
                break;   
            if(nGoalAway - nGoalHome > 5 - nRound)
                break;
        }
        
        nGoalAway += funcGetKickGoal() ? 1 : 0;
        
        if(nRound > 2 && nRound <= 5)
        {
            if(abs(nGoalHome - nGoalAway) > 5 - nRound)
                break;
        }
        
        if(nRound > 5 && nGoalHome != nGoalAway)
            break;
        
        nRound++;
    }
    
    return CGoals(nGoalHome, nGoalAway);
}
