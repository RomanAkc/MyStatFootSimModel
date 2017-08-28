#include "matchresult.h"

CMatchResult::CMatchResult()
    : m_gFullTime(), m_gAddTime(), m_gPenalty()
{
}


void CMatchResult::setGoalsFullTime(const CGoals& gFullTime)
{
    m_gFullTime = gFullTime;
}

void CMatchResult::setGoalsAddTime(const CGoals& gAddTime)
{
    m_gAddTime = gAddTime;
}

void CMatchResult::setGoalsPenalty(const CGoals& gPenalty)
{
    m_gPenalty = gPenalty;
}

const CGoals& CMatchResult::getGoalsFullTime() const
{
    return m_gFullTime;
}

const CGoals& CMatchResult::getGoalsAddTime() const
{
    return m_gAddTime;
}
const CGoals& CMatchResult::getGoalsPenalty() const
{
    return m_gPenalty;
}
