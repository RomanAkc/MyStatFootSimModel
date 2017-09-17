#include <exception>
#include "team.h"
#include "world.h"

int CTeam::m_nNextID = 1;
const CWorld* CTeam::m_pWorld = nullptr;

void CTeam::SetWorld(const CWorld* pWorld)
{
    m_pWorld = pWorld;
}

CTeam::CTeam(int nPower, int nCountryID)
    : m_nID(m_nNextID++), m_nPower(nPower), m_nCountryID(nCountryID)
{
    if(!m_pWorld)
        throw std::exception("m_pWorld is undefined");
}

CTeam::~CTeam()
{    
}

int CTeam::GetPower() const
{
    return m_nPower;   
}




CNational::CNational(int nPower, int nCountryID)
    : CTeam(nPower, nCountryID)
{ 
}

const std::string& CNational::GetName() const
{       
    return m_pWorld->getCountryByID(m_nCountryID)->GetName();
}





CClub::CClub(const std::string& sName, int nPower, int nCountryID)
    : CTeam(nPower, nCountryID), m_sName(sName)
{
}

const std::string& CClub::GetName() const
{
    return m_sName;
}
