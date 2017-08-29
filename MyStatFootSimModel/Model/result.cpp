#include "result.h"
#include "outcomeProbabilities.h"

std::random_device CResult::rd;
std::mt19937 CResult::generator(rd());
std::uniform_int_distribution<> CResult::dist(1, 10000);

CMatchResult CResult::getResult(int nDiffPower, bool bWithPenalty /*= false*/)
{
    int res1 = dist(generator);
    int res2 = dist(generator);
    return CMatchResult(res1, res2);
}
