#include <QCoreApplication>
#include <iostream>
#include <string>

#include "Model/result.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CMatchResult res = CResult::getResult(0, false);
    std::cout<<res.getGoalsFullTime().GetGoalHome()<<" : "<<res.getGoalsFullTime().GetGoalAway();
    std::cout<<std::endl;

    std::string sTemp = "lalala";
    std::cout<<sTemp;

    return a.exec();
}
