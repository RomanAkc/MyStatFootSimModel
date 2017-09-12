#include <QCoreApplication>
#include <iostream>
#include <string>

#include "Model/calcresult.h"
#include "Model/team.h"
#include "Model/world.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CWorld world;
    
    const CCountry* pC1 = world.AddCountry("Italy  ", EUROPE);
    CNational club1(30, pC1->GetID());
    
    const CCountry* pC2 = world.AddCountry("Germany", EUROPE);
    CNational club2(30, pC2->GetID());
    
    for(int i = 0; i < 200; ++i)
    {
        auto res = CCalcResult::getPairResult(club1.GetPower() - club2.GetPower());
        std::cout<<club1.GetName()<<" - "<<club2.GetName()<<" ";
        std::cout<<res.first.getGoalsAll().GetGoalHome()<<" : "<<res.first.getGoalsAll().GetGoalAway();
        std::cout<<" "<<res.second.getGoalsAll().GetGoalAway()<<" : "<<res.second.getGoalsAll().GetGoalHome();
        if(res.second.GetPenalty())
            std::cout<<" pen "<<res.second.getGoalsPenalty().GetGoalAway()<<" : "<<res.second.getGoalsPenalty().GetGoalHome();
        std::cout<<" [Winner ";
        if(CCalcResult::getWinner(res) == CResult::WIN_HOME)
            std::cout<<club1.GetName();
        else 
            std::cout<<club2.GetName();
        std::cout<<"]";
        std::cout<<std::endl;
    }
    

    
    
    
    

    return a.exec();
}
