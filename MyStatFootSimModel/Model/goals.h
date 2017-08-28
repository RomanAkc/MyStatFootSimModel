#pragma once

class CGoals
{
private:
    int m_nGoalHome;
    int m_nGoalAway;

public:
    CGoals()
    {
        m_nGoalHome = 0;
        m_nGoalAway = 0;
    }

    CGoals(int nGoalHome, int nGoalAway)
        : m_nGoalHome(nGoalHome), m_nGoalAway(nGoalAway)
    {
    }

    int GetGoalHome() const { return m_nGoalHome; }
    int GetGoalAway() const { return m_nGoalAway; }
};
