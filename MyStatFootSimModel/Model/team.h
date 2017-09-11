#pragma once
#include <string>
#include <map>
#include <list>

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

class CTeam
{
private:
    static std::list<CCountry> m_listCountries;
    static std::map<int, const CCountry*> m_mapCountryByID;
    static std::map<std::string, const CCountry*> m_mapCountryByName;
    static std::map<ERegion, const CCountry*> m_mapCountryByRegion;
    
    std::string m_sName;
    int m_nPower;
    
public:
    static int AddCountry(const std::string& sName, ERegion eRegion);
        
    static const CCountry* GetCountryByName(const std::string& sName);
    static const CCountry* GetCountryByID(int nID);
    
public:
    CTeam(const std::string& sName, int nPower);
    virtual ~CTeam();
    
    const std::string& GetName() const;
    int GetPower();
};

class CNational : public CTeam
{
private:
    ERegion m_eRegion;
    
public:
    CNational(const std::string& sName, int nPower, ERegion eRegion);
    
    ERegion getRegion() const;
};

class CClub : public CTeam
{
private:
    int m_nCountryID;
    
public:
    CClub(const std::string& sName, int nPower, int nCountryID);
    CClub(const std::string& sName, int nPower, const std::string& sCountryName, ERegion eRegion);
};
