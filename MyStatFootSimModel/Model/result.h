#pragma once
#include <random>
#include <map>
#include "matchresult.h"

class CResult
{
private:
    static bool m_bResultInited;
    static std::map<std::pair<int, int>, int> m_mapProbGoalDiff;
    static std::map<int, int> m_mapProbGoalDraw;
    static std::map<int, int> m_mapProbGoalLoseTeam;
    static std::random_device rd;
    static std::mt19937 generator;
    static std::uniform_int_distribution<> dist10000;


    enum EWinner
    {
        WIN_HOME        = 0,
        WIN_AWAY        ,
        DRAW            ,
    };

public:
    static CMatchResult getResult(int nDiffPower, bool bUseHomeAway = true
            , bool bNeedWinner = false, const CMatchResult* pFirstResult = nullptr);
    static std::pair<CMatchResult, CMatchResult> getPairResult(int nDiffPower);

private:
    static void InitResult();
    static EWinner GetWinner(int nDiffPower, bool bUseHomeAway); //to do: переписать возвращаемое значение на std::optional
    static CGoals GetGoals(int nDiffPower, EWinner winner);
    static CGoals GetPenalty();
};
