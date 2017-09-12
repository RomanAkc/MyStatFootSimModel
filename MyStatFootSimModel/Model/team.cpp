#include <exception>
#include "team.h"
#include "world.h"

int CTeam::m_nNextID = 1;
const CWorld* CTeam::m_pWorld = nullptr;
std::string CTeam::m_sUndefined = "Undefined";

void CTeam::SetWorld(const CWorld* pWorld)
{
    m_pWorld = pWorld;
}

CTeam::CTeam(int nPower, int nCountryID)
    : m_nID(m_nNextID++), m_nPower(nPower), m_nCountryID(nCountryID)
{
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
    if(!m_pWorld)
        return m_sUndefined;
    
    const CCountry* pCountry = m_pWorld->getCountryByID(m_nCountryID);
    if(!pCountry)
       return m_sUndefined;
   
    return pCountry->GetName();
}





CClub::CClub(const std::string& sName, int nPower, int nCountryID)
    : CTeam(nPower, nCountryID), m_sName(sName)
{
}

const std::string& CClub::GetName() const
{
    return m_sName;
}
