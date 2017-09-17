#pragma once
#include <random>
#include <vector>
#include <map>
#include <memory>
#include "team.h"
#include "result.h"

extern std::mt19937 generator;

class CWorld;

class CRound
{
private:
    std::map<std::pair<int, int>, CResult> m_mapResults;
    
public:
    CRound();
};

enum EToss
{
    TOSS_BY_RANDOM          = 0,
    TOSS_BY_ORDER           ,
};

class CStage
{
protected:
    static const CWorld* m_pWorld;
    EToss m_toss;
    std::vector<int> m_vecTeams;
    std::vector<CRound> m_vecRounds;
    
public:
    CStage(EToss toss);
    virtual ~CStage();
    static void SetWorld(const CWorld* pWorld);
    
    virtual void Calculate() = 0;
    virtual std::vector<int> GetTop(int nCount = 0) const = 0;
    
     void SetToss(EToss toss);
};

class CRoundStage : public CStage
{
private:
    std::shared_ptr<std::vector<int>> m_pvecHome;
    std::shared_ptr<std::vector<int>> m_pvecAway;
    
public:
    CRoundStage(EToss toss = TOSS_BY_RANDOM
            , const std::shared_ptr<std::vector<int>> pVecHome = nullptr
            , const std::shared_ptr<std::vector<int>> pVecAway = nullptr
            );
    virtual ~CRoundStage();
    
    virtual void Calculate() override;
    virtual std::vector<int> GetTop(int nCount = 0) const override;
    
    void SetToss(std::shared_ptr<std::vector<int>> pVecHome);
};
