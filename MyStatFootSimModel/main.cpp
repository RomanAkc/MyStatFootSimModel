#include <QCoreApplication>
#include <iostream>
#include <string>

#include "Model/result.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    for(int i = 0; i < 50; ++i)
    {
        CMatchResult res = CResult::getResult(-10, false);
        std::cout<<res.getGoalsFullTime().GetGoalHome()<<" : "<<res.getGoalsFullTime().GetGoalAway();
        std::cout<<std::endl;
    }
    
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
    
   /* for(int i = 0; i < 50; ++i)
    {
        getPairResult
    }*/
    
    

    return a.exec();
}
