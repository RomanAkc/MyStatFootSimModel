#include "matchresult.h"

CMatchResult::CMatchResult()
    : m_gFullTime(), m_gAddTime(), m_gPenalty(), m_bPenalty(false)
{
}

CMatchResult::CMatchResult(int nGoalHome, int nGoalAway)
    : m_gFullTime(nGoalHome, nGoalAway), m_gAddTime(), m_gPenalty(), m_bPenalty(false)
{

}


void CMatchResult::setGoalsFullTime(const CGoals& gFullTime)
{
    m_gFullTime = gFullTime;
}

void CMatchResult::setGoalsAddTime(const CGoals& gAddTime)
{
    m_gAddTime = gAddTime;
    m_bPenalty = true;
}

void CMatchResult::setGoalsPenalty(const CGoals& gPenalty)
{
    m_gPenalty = gPenalty;
    m_bPenalty = true;
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

bool CMatchResult::GetPenalty() const
{
    return m_bPenalty;
}
