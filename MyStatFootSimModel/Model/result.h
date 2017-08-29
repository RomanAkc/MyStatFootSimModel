#pragma once
#include <random>
#include "matchresult.h"

class CResult
{
private:
    static std::random_device rd;
    static std::mt19937 generator;
    static std::uniform_int_distribution<> dist;

public:
    static CMatchResult getResult(int nDiffPower, bool bWithPenalty = false);
};
