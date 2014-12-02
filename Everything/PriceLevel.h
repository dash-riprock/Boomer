// PriceLevel.h

#ifndef pricelevel_h
#define pricelevel_h

#include "IBString.h"
#include "CommonDefs.h"
#include <iostream>
using std::cout; using std::endl;

namespace IB {

class PriceLevel
{
public:

    PriceLevel()
        : price(0)
        , size(0)
        , desires(0)
        , fires(0)
        , side(0)
        , position(0)
        , open_orders(0)
        , filled_open(0)
        , stop_level(0)
    {
        cout << "Price Level constructor" << endl;
    }

    double price;
    int size;
    int desires;
    int fires;
    int side;   // 1 bid, 0 offer
    int position;
    int open_orders;
    int filled_open;  // filled but not closed 
    int stop_level;
    };

}   // namespace IB
#endif

