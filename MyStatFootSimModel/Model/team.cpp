#include "team.h"

int CCountry::m_nNextID = 1;

CCountry::CCountry(const std::string& sName, ERegion eRegion)
    : m_sName(sName), m_eRegion(eRegion), m_nID(m_nNextID++)
{
}

CCountry::CCountry(const CCountry& rhs)
    : m_sName(rhs.m_sName), m_eRegion(rhs.m_eRegion), m_nID(rhs.m_nID)
{
    
}

CCountry& CCountry::operator=(const CCountry& rhs)
{
    if(this == &rhs)
        return *this;
    
    m_sName = rhs.m_sName;
    m_eRegion = rhs.m_eRegion;
    m_nID = rhs.m_nID;
    
    return *this;
}

CCountry::CCountry(CCountry&& rhs)
    : m_sName(std::move(rhs.m_sName)), m_eRegion(rhs.m_eRegion), m_nID(rhs.m_nID)
{
}

CCountry& CCountry::operator=(CCountry&& rhs)
{
    if(this == &rhs)
        return *this;
    
    m_sName = std::move(rhs.m_sName);
    m_eRegion = rhs.m_eRegion;
    m_nID = rhs.m_nID;
    
    return *this;
}

int CCountry::GetID() const
{
    return m_nID;
}

const std::string& CCountry::GetName() const
{
    return m_sName;
}

ERegion CCountry::getRegion() const
{
    return m_eRegion;
}



std::list<CCountry> CTeam::m_listCountries;
std::map<int, const CCountry*> CTeam::m_mapCountryByID;
std::map<std::string, const CCountry*> CTeam::m_mapCountryByName;
std::map<ERegion, const CCountry*> CTeam::m_mapCountryByRegion;

int CTeam::AddCountry(const std::string& sName, ERegion eRegion)
{
    m_listCountries.emplace_back(CCountry(sName, eRegion));
    const CCountry* p = &(*m_listCountries.rbegin());
    
    m_mapCountryByID[p->GetID()] = p;
    m_mapCountryByName[p->GetName()] = p;
    m_mapCountryByRegion[p->getRegion()] = p;
    
    return p->GetID();
}

const CCountry* CTeam::GetCountryByName(const std::string& sName)
{
    auto it_find = m_mapCountryByName.find(sName);
    if(it_find == m_mapCountryByName.end())
        return nullptr;
    
    return it_find->second;
}

const CCountry* CTeam::GetCountryByID(int nID)
{
    auto it_find = m_mapCountryByID.find(nID);
    if(it_find == m_mapCountryByID.end())
        return nullptr;
    
    return it_find->second;
}


CTeam::CTeam(const std::string& sName, int nPower)
    : m_sName(sName), m_nPower(nPower)
{
}

CTeam::~CTeam()
{    
}

const std::string& CTeam::GetName() const
{
    return m_sName;
}

int CTeam::GetPower()
{
    return m_nPower;   
}


CNational::CNational(const std::string& sName, int nPower, ERegion eRegion)
    : CTeam(sName, nPower), m_eRegion(eRegion)
{ 
}

ERegion CNational::getRegion() const
{
    return m_eRegion;
}


CClub::CClub(const std::string& sName, int nPower, int nCountryID)
    : CTeam(sName, nPower), m_nCountryID(nCountryID)
{
}

CClub::CClub(const std::string& sName, int nPower, const std::string& sCountryName, ERegion eRegion)
    : CTeam(sName, nPower)
{
    const CCountry* pCountry = CTeam::GetCountryByName(sCountryName);
    if(pCountry)
        m_nCountryID = pCountry->GetID();
    else 
        m_nCountryID = CTeam::AddCountry(sCountryName, eRegion);
}
