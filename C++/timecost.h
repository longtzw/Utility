#ifndef __TIME_COST_H__
#define __TIME_COST_H__

#include <string>
#include <cinttypes>

class CTimeCost 
{
public:

    CTimeCost(const std::string &title = "cost time", uint64_t constTimeThreshold = 0);

    ~CTimeCost();

    void record(const std::string &title = "");

private:

    uint64_t getTick() const;

    uint64_t getTimeCost() const;

    uint64_t m_tick;
    uint64_t m_tickSum;
    std::string m_title;
    uint64_t m_costTimeThreshold;
};

#endif

