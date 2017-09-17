#include "world.h"

int CCountry::m_nNextID = 1;

CCountry::CCountry(const std::string& sName, ERegion eRegion)
    : m_nID(m_nNextID++), m_sName(sName), m_eRegion(eRegion) 
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




CWorld::CWorld()
{
    CTeam::SetWorld(this);
    CStage::SetWorld(this);
}

CWorld::~CWorld()
{
}

const CCountry* CWorld::AddCountry(const std::string& sName, ERegion eRegion)
{
    m_listCountries.emplace_back(CCountry(sName, eRegion));
    
    const CCountry* pCountry = &(*m_listCountries.rbegin());
    
    m_mapCountryByID[pCountry->GetID()] = pCountry;
    m_mapCountryByName[pCountry->GetName()] = pCountry;
    m_mapCountryByRegion.insert ( std::make_pair(pCountry->getRegion(), pCountry) );
    
    return pCountry;
}

const CCountry* CWorld::getCountryByID(int nID) const
{
    auto it_find = m_mapCountryByID.find(nID);
    if(it_find == m_mapCountryByID.end())
        return nullptr;
    
    return it_find->second;
}

const CCountry* CWorld::getCountryByName(const std::string& sName) const
{
    auto it_find = m_mapCountryByName.find(sName);
    if(it_find == m_mapCountryByName.end())
        return nullptr;
    
    return it_find->second; 
}


