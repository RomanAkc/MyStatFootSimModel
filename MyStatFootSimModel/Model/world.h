#pragma once
#include <random>
#include <string>
#include <list>
#include <map>
#include "team.h"
#include "tournament.h"

enum ERegion
{
    EUROPE                  = 0,
    SOUTH_AMERICA           ,
    NORD_AMERICA            ,
    AFRICA                  ,
    ASIA                    ,
    OCEANIA                 ,
};

class CCountry
{
private:
    static int m_nNextID;
    int m_nID;
    std::string m_sName;
    ERegion m_eRegion;
    
public:
    CCountry(const std::string& sName, ERegion eRegion);
    CCountry(const CCountry& rhs);
    CCountry& operator=(const CCountry& rhs);
    CCountry(CCountry &&rhs);
    CCountry& operator=(CCountry&& rhs);
    
    int GetID() const;
    const std::string& GetName() const;
    ERegion getRegion() const;
};

class CWorld
{
private:    
    std::list<CCountry> m_listCountries;
    std::map<int, const CCountry*> m_mapCountryByID;
    std::map<std::string, const CCountry*> m_mapCountryByName;
    std::multimap<ERegion, const CCountry*> m_mapCountryByRegion;
    
    CWorld(const CWorld& rhs) = delete;
    void operator=(const CWorld& rhs) = delete;
    CWorld(CWorld&& rhs) = delete;
    void operator=(CWorld&& rhs) = delete;
   
public:
    CWorld();
    ~CWorld();
    
    const CCountry* AddCountry(const std::string& sName, ERegion eRegion);
    const CCountry* getCountryByID(int nID) const;
    const CCountry* getCountryByName(const std::string& sName) const;
};

