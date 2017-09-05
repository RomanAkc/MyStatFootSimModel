#pragma once
#include "goals.h"

class CResult
{
private:
    CGoals m_gFullTime;
    CGoals m_gAddTime;
    CGoals m_gPenalty;
    bool m_bExistResult;
    bool m_bAddTime;
    bool m_bPenalty;

public:
    enum EWinner
    {
        WIN_HOME        = 0,
        WIN_AWAY        ,
        DRAW            ,
        NO_RESULT       ,
    };
    
    CResult();
    CResult(int nGoalHome, int nGoalAway);
    CResult(CGoals gFullTime);

    void setGoalsFullTime(const CGoals& gFullTime);
    void setGoalsAddTime(const CGoals& gAddTime);
    void setGoalsPenalty(const CGoals& gPenalty);

    const CGoals& getGoalsFullTime() const;
    const CGoals& getGoalsAddTime() const;
    CGoals getGoalsAll() const;
    const CGoals& getGoalsPenalty() const;
    bool GetAddTime() const;
    bool GetPenalty() const;
    EWinner GetWinner() const;
};
