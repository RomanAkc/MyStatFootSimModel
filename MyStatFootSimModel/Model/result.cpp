#include "result.h"

CResult::CResult()
    : m_gFullTime(), m_gAddTime(), m_gPenalty(), m_bPenalty(false)
    , m_bAddTime(false), m_bExistResult(false)
{
}

CResult::CResult(int nGoalHome, int nGoalAway)
    : m_gFullTime(nGoalHome, nGoalAway), m_gAddTime(), m_gPenalty(), m_bPenalty(false)
    , m_bAddTime(false), m_bExistResult(true)
{
}

CResult::CResult(CGoals gFullTime)
    : m_gFullTime(gFullTime), m_gAddTime(), m_gPenalty(), m_bPenalty(false)
    , m_bAddTime(false), m_bExistResult(true)
{
}


void CResult::setGoalsFullTime(const CGoals& gFullTime)
{
    m_gFullTime = gFullTime;
    m_bExistResult = true;
}

void CResult::setGoalsAddTime(const CGoals& gAddTime)
{
    m_gAddTime = gAddTime;
    m_bAddTime = true;
}

void CResult::setGoalsPenalty(const CGoals& gPenalty)
{
    m_gPenalty = gPenalty;
    m_bPenalty = true;
}

const CGoals& CResult::getGoalsFullTime() const
{
    return m_gFullTime;
}

const CGoals& CResult::getGoalsAddTime() const
{
    return m_gAddTime;
}

CGoals CResult::getGoalsAll() const
{
    return CGoals(m_gFullTime.GetGoalHome() + m_gAddTime.GetGoalHome(),
                  m_gFullTime.GetGoalAway() + m_gAddTime.GetGoalAway());
}

const CGoals& CResult::getGoalsPenalty() const
{
    return m_gPenalty;
}

bool CResult::GetAddTime() const
{
    return m_bAddTime;
}

bool CResult::GetPenalty() const
{
    return m_bPenalty;
}

CResult::EWinner CResult::GetWinner() const
{
    if(!m_bExistResult)
        return NO_RESULT;
    
    int nSumGoalHome = m_gFullTime.GetGoalHome() + m_gAddTime.GetGoalHome() + m_gPenalty.GetGoalHome();
    int nSumGoalAwaw = m_gFullTime.GetGoalAway() + m_gAddTime.GetGoalAway() + m_gPenalty.GetGoalAway();
    
    if(nSumGoalHome == nSumGoalAwaw)
        return DRAW;
    
    if(nSumGoalHome > nSumGoalAwaw)
        return WIN_HOME;
    
    return WIN_AWAY;
}
