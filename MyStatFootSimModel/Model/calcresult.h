#pragma once
#include <random>
#include <map>
#include "result.h"

extern std::mt19937 generator;

typedef std::pair<CResult, CResult> CPairResult;

class CCalcResult
{
private:
    static bool m_bResultInited;
    static std::map<std::pair<int, int>, int> m_mapProbGoalDiff;
    static std::map<int, int> m_mapProbGoalDraw;
    static std::map<int, int> m_mapProbGoalLoseTeam;
    static std::uniform_int_distribution<> dist10000;

public:    
    static CResult getResult(int nDiffPower, bool bUseHomeAway = true
            , bool bNeedWinner = false, const CResult* pFirstResult = nullptr);
    static CPairResult getPairResult(int nDiffPower);
    static CResult::EWinner getWinner(const CResult& result);
    static CResult::EWinner getWinner(const CPairResult& result);

private:
    static void InitResult();
    static CResult::EWinner GetWinner(int nDiffPower, bool bUseHomeAway); //to do: переписать возвращаемое значение на std::optional
    static CGoals GetGoals(int nDiffPower, CResult::EWinner winner);
    static CGoals GetPenalty();
};

