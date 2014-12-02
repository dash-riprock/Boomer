// Pending.h

#ifndef pending_h
#define pending_h

#include "IBString.h"
#include "CommonDefs.h"

#include <ctime>
#include <time.h>
#include <iostream>
using std::cout; using std::endl;

namespace IB {
    
class Pending
{
public:

    Pending()
        : order_Id(0)
        , buy_sell(0)  
        , order_size(0)
        , fire_price(0.0)
        , float_price(0.0)
        , cover_price(0.0)
        , stop_price(0.0)
        , executed_quant(0)
        , executed_quant_last(0)
        , executed_delta(0)
        , fully_filled(0)   
        , partial_fully_filled(0)   // order fully filled after partial fills 
        , partial_fill(0)
        , cover(0)  
        , cover_for_Id(0)
        , sent_cancel(0)
        , sent_stop(0)
        , cancelled(0)
        , cancelled_update(0)
        , pending_update(0)
        , place_update(0)
        , placed_update(0)
        , pendex_update(0)  // for orders that go from Pending to Filled
        , executed_update(0)
        , start_t(0)
    {
        start_t = std::clock();
    }

    OrderId order_Id;
    double buy_sell;
    int order_size;
    double fire_price;
    double float_price;
    double cover_price;
    double stop_price;
    int executed_quant;
    int executed_quant_last;
    int executed_delta;
    int fully_filled;
    int partial_fully_filled;
    int partial_fill;
    int remaining;  // used to ensure order fully filled
    int cover;      // prevent searchDestroy for cancelling order
    int cover_for_Id;  // order Id this order is cover for 
    int sent_cancel;    // so you don't spam TWS with canceOrder 
    int sent_stop;      // so you don't double sent stop order
    int cancelled;
    int cancelled_update;
    int pending_update;
    int place_update;
    int placed_update;
    int pendex_update;
    int executed_update;
    std::clock_t start_t;

    // not initialized
    long conId;
    IBString exchange;
    IBString action;
    IBString order_type;

    std::clock_t cancelled_order_t;
    std::clock_t pending_order_t;
    std::clock_t place_order_t;
    std::clock_t placed_order_t;
    std::clock_t executed_order_t;
    };

} // namespace IB
#endif
