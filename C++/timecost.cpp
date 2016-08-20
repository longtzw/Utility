//#include <ctime>
#include <time.h>
#include <cstdio>
#include "timecost.h"

namespace {

const uint32_t msecond_per_second = 1000;
const uint32_t nsecond_per_msecond = 1000000;

}

CTimeCost::CTimeCost(const std::string &title, uint64_t costTimeThreshold)
    : m_tick(0),
      m_tickSum(0),
      m_title(title),
      m_costTimeThreshold(costTimeThreshold)
{
    m_tick = getTick();  
}

CTimeCost::~CTimeCost()
{
    m_tickSum += getTimeCost();
    if (m_tickSum >= m_costTimeThreshold)
    {
        printf("[%s], total time cost %" PRIu64 " ms, stop\n", m_title.c_str(), m_tickSum);
    }
}

void CTimeCost::record(const std::string &title)
{
    uint64_t timeCost = getTimeCost();
    if (timeCost >= m_costTimeThreshold)
    {
        if (title == "")
        {
            printf("[%s], total time cost %" PRIu64 " ms\n", m_title.c_str(), timeCost);
        }
        else
        {
            printf("[%s], total time cost %" PRIu64 " ms\n", title.c_str(), timeCost);
        }
    }

    m_tickSum += timeCost;
    m_tick = getTick();
}

uint64_t CTimeCost::getTick() const
{
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);
    
    return tp.tv_sec * msecond_per_second + tp.tv_nsec / nsecond_per_msecond;
}

uint64_t CTimeCost::getTimeCost() const
{
    return getTick() - m_tick;
}

