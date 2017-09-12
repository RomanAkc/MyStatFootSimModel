#pragma once
#include <string>

class CWorld;

class CTeam
{
private:
    static int m_nNextID;
    
protected:
    static const CWorld* m_pWorld;
    static std::string m_sUndefined;
    
    int m_nID;
    int m_nPower;
    int m_nCountryID;
    
public:
    CTeam(int nPower, int nCountryID);
    virtual ~CTeam();
    static void SetWorld(const CWorld* pWorld);
    
    int GetPower() const;
    virtual const std::string& GetName() const = 0;
};

class CNational : public CTeam
{
private:
    
public:
    CNational(int nPower, int nCountryID);
    
    virtual const std::string& GetName() const override;
};

class CClub : public CTeam
{
private:
    std::string m_sName;
    
public:
    CClub(const std::string& sName, int nPower, int nCountryID);
    
    virtual const std::string& GetName() const override;
};
