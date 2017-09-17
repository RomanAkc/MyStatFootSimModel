#include <exception>
#include "tournament.h"
#include "world.h"

const CWorld* CStage::m_pWorld = nullptr;

void CStage::SetWorld(const CWorld* pWorld)
{
    m_pWorld = pWorld;
}

CStage::CStage(EToss toss)
    : m_toss(toss)
{
}

CStage::~CStage()
{
}

void CStage::SetToss(EToss toss)
{
    m_toss = toss;
}


CRoundStage::CRoundStage(EToss toss /*= TOSS_BY_RANDOM*/
                         , const std::shared_ptr<std::vector<int>> pVecHome /*= nullptr*/
                         , const std::shared_ptr<std::vector<int>> pVecAway /*= nullptr*/)
    : CStage(toss), m_pvecHome(pVecHome), m_pvecAway(pVecAway)
{
    
}

CRoundStage::~CRoundStage()
{
}

void CRoundStage::Calculate()
{
    
}

std::vector<int> CRoundStage::GetTop(int nCount /*= 0*/) const
{
    std::vector<int> vecResult;
    vecResult.reserve(nCount);
    
    return vecResult;
}

void CRoundStage::SetToss(std::shared_ptr<std::vector<int>> pVecHome)
{
    if(m_vecTeams.size() / 2 != pVecHome->size())
        throw std::exception("VecHome size is bad");
    
    m_pvecHome = pVecHome;
}
