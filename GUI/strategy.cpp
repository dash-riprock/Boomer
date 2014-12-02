#include "strategy.h"

Strategy::Strategy(std::shared_ptr<IB::Boomer> strategyClient_ptr)
    : strategyClient_(strategyClient_ptr)
{
}

Strategy::~Strategy()
{
}

void Strategy::runStrat()
{
    strategyClient_->runBoomer();
    emit finished();
}
