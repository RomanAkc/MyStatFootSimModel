#include <QCoreApplication>
#include <iostream>
#include <string>
#include <windows.h>

#include "Model/result.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 
    
    /*for(int i = 0; i < 50; ++i)
    {
        CMatchResult res = CResult::getResult(-10, false);
        std::cout<<res.getGoalsFullTime().GetGoalHome()<<" : "<<res.getGoalsFullTime().GetGoalAway();
        std::cout<<std::endl;
    }*/
    
    /*for(int i = 0; i < 50; ++i)
    {
        CMatchResult res = CResult::getResult(10, false, true);
        std::cout<<res.getGoalsFullTime().GetGoalHome()<<" : "<<res.getGoalsFullTime().GetGoalAway();
        if(res.getGoalsFullTime().GetGoalHome() == res.getGoalsFullTime().GetGoalAway())
        {
            std::cout<<" add "<<res.getGoalsAddTime().GetGoalHome()<<" : "<<res.getGoalsAddTime().GetGoalAway();
            if(res.getGoalsAddTime().GetGoalHome() == res.getGoalsAddTime().GetGoalAway())
                std::cout<<" pen "<<res.getGoalsPenalty().GetGoalHome()<<" : "<<res.getGoalsPenalty().GetGoalAway();
        }
        std::cout<<std::endl;
    }*/
    
    /*for(int i = 0; i < 100; ++i)
    {
        auto res = CResult::getPairResult(0);
        std::cout<<"Inter-Juve "<<res.first.getGoalsFullTime().GetGoalHome()<<" : "<<res.first.getGoalsFullTime().GetGoalAway();
        std::cout<<" Juve-Inter "<<res.second.getGoalsFullTime().GetGoalHome()<<" : "<<res.second.getGoalsFullTime().GetGoalAway();
        if(
                res.second.getGoalsFullTime().GetGoalHome() + res.first.getGoalsFullTime().GetGoalAway() 
                == res.second.getGoalsFullTime().GetGoalAway() + res.first.getGoalsFullTime().GetGoalHome()
                && res.first.getGoalsFullTime().GetGoalAway() == res.second.getGoalsFullTime().GetGoalAway()
                )
        {
            std::cout<<" add "<<res.second.getGoalsAddTime().GetGoalHome()<<" : "<<res.second.getGoalsAddTime().GetGoalAway();
            if(res.second.getGoalsAddTime().GetGoalHome() == 0 
                    && res.second.getGoalsAddTime().GetGoalAway() == 0)
                std::cout<<" pen "<<res.second.getGoalsPenalty().GetGoalHome()<<" : "<<res.second.getGoalsPenalty().GetGoalAway();
        }
        std::cout<<std::endl;
    }*/

    /*for(int i = 0; i < 200; ++i)
    {
        auto res = CResult::getPairResult(10);
        std::cout<<"Inter-Juve "<<res.first.getGoalsAll().GetGoalHome()<<" : "<<res.first.getGoalsAll().GetGoalAway();
        std::cout<<" Juve-Inter "<<res.second.getGoalsAll().GetGoalHome()<<" : "<<res.second.getGoalsAll().GetGoalAway();
        if(res.second.GetPenalty())
            std::cout<<" pen "<<res.second.getGoalsPenalty().GetGoalHome()<<" : "<<res.second.getGoalsPenalty().GetGoalAway();
        std::cout<<std::endl;
    }*/
    
    for(int i = 0; i < 200; ++i)
    {
        auto res = CResult::getPairResult(10);
        std::cout<<"Inter-Juve "<<res.first.getGoalsAll().GetGoalHome()<<" : "<<res.first.getGoalsAll().GetGoalAway();
        std::cout<<" "<<res.second.getGoalsAll().GetGoalAway()<<" : "<<res.second.getGoalsAll().GetGoalHome();
        if(res.second.GetPenalty())
            std::cout<<" pen "<<res.second.getGoalsPenalty().GetGoalAway()<<" : "<<res.second.getGoalsPenalty().GetGoalHome();
        std::cout<<std::endl;
    }
    
    

    return a.exec();
}
