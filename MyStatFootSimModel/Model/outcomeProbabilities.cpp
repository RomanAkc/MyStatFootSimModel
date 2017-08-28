#include "outcomeProbabilities.h"

COutcomeProbabilities::COutcomeProbabilities()
{
	int vecWin[31] = {3200, 5000, 5550, 6000, 6500, 6700, 6850, 
	7000, 7150, 7300, 7650, 7900, 8000, 8100, 8400, 8500, 8550,
	8800, 9000, 9200, 9375, 9525, 9600, 9850, 9925, 9950, 9960,
	9965, 9970, 9973, 9998};

	int vecDraw[31] = {3600, 2700, 2300, 2000, 1600, 1500, 1450, 
	1400, 1350, 1300, 1250, 1200, 1150, 1100, 1050, 1000, 950,
	900, 850, 700, 550, 400, 350, 100, 50, 25, 15, 10, 5, 2, 1};

    m_ProbWin.assign(vecWin, vecWin + 31);
    m_ProbDraw.assign(vecDraw, vecDraw + 31);
}

int COutcomeProbabilities::getProbWin(int nIndex) const
{
    if((nIndex < 0))
        return m_ProbWin[0];

    return m_ProbWin[nIndex > 30 ? 30 : nIndex];
}

int COutcomeProbabilities::getProbDraw(int nIndex) const
{
    if((nIndex < 0))
        return m_ProbWin[0];

    return m_ProbDraw[nIndex > 30 ? 30 : nIndex];
}
