#include <QCoreApplication>
#include <iostream>
#include <string>

#include "Model/goals.h"
#include "Model/matchresult.h"
#include "Model/outcomeProbabilities.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CGoals goal;
    CMatchResult mr;
    COutcomeProbabilities op;

    mr.setGoalsAddTime(goal);
    int nProbDraw = op.getProbDraw(1);

    std::cout<<nProbDraw<<std::endl;

    std::string sTemp = "lalala";
    std::cout<<sTemp;

    return a.exec();
}
