#pragma once
#include "goals.h"

class CMatchResult
{
private:
    CGoals m_gFullTime;
    CGoals m_gAddTime;
    CGoals m_gPenalty;

public:
    CMatchResult();

    void setGoalsFullTime(const CGoals& gFullTime);
    void setGoalsAddTime(const CGoals& gAddTime);
    void setGoalsPenalty(const CGoals& gPenalty);

    const CGoals& getGoalsFullTime() const;
    const CGoals& getGoalsAddTime() const;
    const CGoals& getGoalsPenalty() const;
};

