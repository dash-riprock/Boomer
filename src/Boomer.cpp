#include "Boomer.h"

#include <Everything/EPosixClientSocket.h>
#include <Everything/EPosixClientSocketPlatform.h>

#include "Contract.h"
#include "Order.h"
#include "Pending.h"
#include "PriceLevel.h"

#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <iomanip>
#include <iostream>
using std::cout; using std::endl;

namespace IB {

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds
const int SLEEP_BETWEEN_REQUEST = 5; // seconds
const int NUMBER_OF_PRODUCTS = 2;

//////////////  target product  /////////////////
//long CON_ID_TARGET = 134798470;
//const double TICK_SIZE_TARGET = 0.25;
//const IBString EXCHANGE_TARGET = "GLOBEX";
//////////////////////////////////////////////////
  
//////////////  NKD /////////////////////
//long CON_ID_PROD1 = 139904963;
//const double TICK_SIZE_PROD1 = 5;
//const IBString EXCHANGE_PROD1 = "GLOBEX";
 
//////////////  DAX     /////////////////////
//long CON_ID_PROD1 = 146612295;
//const double TICK_SIZE_PROD1 = 0.5;
//const IBString EXCHANGE_PROD1 = "DTB";
 
//////////////  AUS S&P200  /////////////////////
//long CON_ID_PROD1 = 129473019;
//const double TICK_SIZE_PROD1 = 1; 
//const IBString EXCHANGE_PROD1 = "SNFE";

//////////////  ZN /////////////////////////////
//long CON_ID_PROD1 = 134631629;
//const double TICK_SIZE_PROD1 = 0.015625;
//const IBString EXCHANGE_PROD1 = "ECBOT";

//////////////  ZF /////////////////////////////
long CON_ID_PROD1 = 141238147;
const double TICK_SIZE_PROD1 = 0.0078125;
const IBString EXCHANGE_PROD1 = "ECBOT";

/////// SPOOS /////////////////////////////////
//long CON_ID_PROD1 = 134798470;
//const double TICK_SIZE_PROD1 = 0.25;
//const IBString EXCHANGE_PROD1 = "GLOBEX";
//////////////////////////////////////////////////
// member funcs
Boomer::Boomer()
	: m_pClient(new EPosixClientSocket(this))
    , m_depthRequest(0)
    , m_life(1)
    , m_PnL(0)
    , m_debug(0)
    , m_bookCreated(0)
    , m_bidUpdateLevelCounter(0)
    , m_offerUpdateLevelCounter(0)
    , m_pending(0)
    , m_living(0)
    , m_buySell(0)
    , m_stopLoss(1.0)
    , m_profit(1.0)
    , m_insideSize(0)
    , m_outsideSize(0)
    , m_buffer(1.0)
    , m_support(0)
    , m_depth(0)
    , m_rows(3)
    , m_absPosition(0)
    , m_currentPosition(0)
    , m_deltaPosition(0)
    , m_thisPosition(0)
    , m_filPosition(0)
    , m_thatPosition(0)
    , m_firstFill(0)
    , m_deadPrice(0.0)
    , m_bidDeadPrice(0.0)
    , m_offerDeadPrice(0.0)
    , m_lifePrice(0.0)
    , m_lean(0)
    , m_stoppedOut(0)
    , m_upTick(0)
    , m_downTick(0)
    , m_firstBid(0.0)
    , m_firstOffer(0.0)
    , m_dunPosition(0)
	, m_state(ST_REQ_MKT_DEPTH_PROD1)
    , m_tickerId(1)
	, m_orderId(0)
    , m_requestId(1)
	, m_sleepDeadline(0)
    , m_requestDelay(0)
    , m_start(0)
    , m_bidSize(0)
    , m_offerSize(0)
    , m_existsFound(0)
    , m_open(0)
    , m_filledOpen(0)
    , m_fireSize(0)
    , tickerId_PROD1(0)
    , tickerIdDepth_PROD1(0)
    , m_bidDesires0(0)
    , m_bidDesires1(0)
    , m_bidDesires2(0)
    , m_bidDesires3(0)
    , m_bidDesires4(0)
    , m_bidDesires5(0)
    , m_offerDesires0(0)
    , m_offerDesires1(0)
    , m_offerDesires2(0)
    , m_offerDesires3(0)
    , m_offerDesires4(0)
    , m_offerDesires5(0)
    , m_insertBid0(0)
    , m_insertBid1(0)
    , m_insertBid2(0)
    , m_insertBid3(0)
    , m_insertBid4(0)
    , m_insertBid5(0)
    , m_insertOffer0(0)
    , m_insertOffer1(0)
    , m_insertOffer2(0)
    , m_insertOffer3(0)
    , m_insertOffer4(0)
    , m_insertOffer5(0)
{
}

Boomer::~Boomer()
{
}

void Boomer::enableDebug(int check)
{
    if (check == 1) {
        m_debug = 1;
        cout << "\nenabled\n";
    }
    else {
        m_debug = 0;
        cout << "\ndis-abled\n";
    }
}

void Boomer::runBoomer()
{
    while (m_life == 1)
        processMessages();
}

int Boomer::checkLife()
{
    if (m_life == 1)
        return 1; 
    else 
        return 0;
}

vector<double> Boomer::returnMarket_1() 
{ 
    return PROD1_market; 
}

void Boomer::resetShit()
{
    m_life = 1;
    // reset market_start
}

void Boomer::updateAttributes(int _insideSize, int _outsideSize, double _buffer,
        int _depth, double _profit, double _stop, int _support, int _rows)
{
    cout << "fuckboy attributes" << endl;
    cout << "inside: " << _insideSize << "  outside: " << _outsideSize << "  buffer: " 
         << _buffer << "  depth: " << _depth << " support: " << _support 
         << " stop: " << _stop << " profit: " << _profit << " rows: " << _rows << endl;
    m_insideSize = _insideSize;
    m_insideSizeBid = _insideSize;
    m_insideSizeOffer = _insideSize;
    m_outsideSize = _outsideSize;
    m_outsideSizeBid = _outsideSize;
    m_outsideSizeOffer = _outsideSize;
    m_stopLoss = _stop;
    m_profit = _profit;
    m_depth = _depth;
    m_buffer = _buffer;
    m_support = _support;
    m_rows = _rows;
}

bool Boomer::connect(const char *host, unsigned int port, int clientId)
{
    cout << "Connecting to host: " << host << " port: " << port << " clientId: " << clientId << endl;
	bool bRes = m_pClient->eConnect2( host, port, clientId);

	if (bRes) { cout << "Connected." << endl; }
	else { cout << "Can not connect." << endl; }
	return bRes;
}

void Boomer::disconnect() const { m_pClient->eDisconnect(); }
bool Boomer::isConnected() const { return m_pClient->isConnected(); }

void Boomer::processMessages()
{
	fd_set readSet, writeSet;
	struct timeval tval;
	tval.tv_usec = 0;
	tval.tv_sec = 0;

	time_t now = time(NULL);

	switch (m_state) {

        case ST_REQ_MKT_DEPTH_PROD1:
            reqMktDepth_PROD1(m_rows);
            break;
        case ST_REQ_MKT_DEPTH_ACK_PROD1:
            reqMktDepthAck_PROD1();
            break;

		case ST_IDLE:
			break;
	}

	if( m_sleepDeadline > 0) { tval.tv_sec = m_sleepDeadline - now; }

	if( m_pClient->fd() >= 0 ) {
		FD_ZERO( &readSet);
		writeSet = readSet;
		FD_SET( m_pClient->fd(), &readSet);

		if( !m_pClient->isOutBufferEmpty())
			FD_SET( m_pClient->fd(), &writeSet);

		int ret = select( m_pClient->fd() + 1, &readSet, &writeSet, NULL, &tval);

        // timeout
		if( ret == 0) { return; }

		if( ret < 0) {	// error
  			disconnect();
			return; }

        // socket ready for writing
		if( FD_ISSET( m_pClient->fd(), &writeSet)) { m_pClient->onSend(); }

		if( m_pClient->fd() < 0) { return; }

        // socket is ready for reading
		if( FD_ISSET( m_pClient->fd(), &readSet)) { m_pClient->onReceive(); }
	}
}
  
//////////////////////////////////////////////////////
//                                                  //
//            Request Data Methods                  //
//                                                  //
//////////////////////////////////////////////////////

void Boomer::reqMktDepth_PROD1(int rows)
{
    Contract contract_PROD1;

    contract_PROD1.conId = CON_ID_PROD1;
    contract_PROD1.exchange = EXCHANGE_PROD1;
    tickerIdDepth_PROD1 = m_tickerId;

    cout << "Market Depth Request\n";

    m_pClient->reqMktDepth( m_tickerId, contract_PROD1, rows);
    m_tickerId++;
    m_state = ST_REQ_MKT_DEPTH_ACK_PROD1;
}

void Boomer::reqMktDepthAck_PROD1()
{
    time_t now = ::time(NULL);
    m_requestDelay = now + SLEEP_BETWEEN_REQUEST;
    m_state = ST_IDLE;
}

void Boomer::reqCurrentTime()
{
	m_sleepDeadline = time( NULL) + PING_DEADLINE;
	m_pClient->reqCurrentTime();
}

void Boomer::start()
{
    cout << "*****************************************\n";
    cout << "**                                     **\n";
    cout << "**              START                  **\n";
    cout << "**                                     **\n";
    cout << "*****************************************\n";

    m_start = 1;
}

//////////////////////////////////////////////////////
//                                                  //
//            Place Order Methods                   //
//                                                  //
//////////////////////////////////////////////////////
void Boomer::placeOrder(long conId, const IBString &exchange, const IBString &action,
        const IBString &oType, int floatQuant, double floatPrice, double buySell,
        int cover, int coverFor)
{
    Contract contract;
    Order order;
    contract.conId = conId;
    contract.exchange = exchange;
    order.totalQuantity = floatQuant;
    order.lmtPrice = (floatPrice * TICK_SIZE_PROD1);
    order.orderType = oType;
    order.action = action;

    Pending frendo;
    frendo.order_Id = m_orderId;
    frendo.conId = conId;
    frendo.buy_sell = buySell;      
    frendo.order_size = floatQuant;
    frendo.float_price = floatPrice;
    frendo.exchange = exchange;
    frendo.order_type = order.orderType;
    frendo.action = order.action;
    frendo.cover = cover;
    frendo.cover_for_Id = coverFor;
    
    cout << "Place Order  : Frendo\t\tPrice: " << floatPrice << "\tOrder Id: " << m_orderId 
         << "\tCover: " << frendo.cover << "\tAction: " << frendo.action << "\toType: " 
         << oType << "\tCover For: " << frendo.cover_for_Id << endl;


    m_orderMapPending.insert(OrderMapPending::value_type(frendo.order_Id, frendo));
    cout << "Order Map Pnd: Insert" << "\t\tPrice: " << frendo.float_price << "\tOrder Id: "
         << frendo.order_Id << "\tSize: " << m_orderMapPending.size() << endl;

    m_pClient->placeOrder( frendo.order_Id, contract, order);
    m_orderId++;
    m_state = ST_IDLE;
}

//////////////////////////////////
//      get PnL()               //
//////////////////////////////////
void Boomer::getPnL()
{
    int sells, buys;
    int sell_quant, buy_quant;

    for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++)
    {
        Pending& getter = m_fil->second;
        if (getter.buy_sell == 1) 
            buy_quant = buy_quant + (getter.order_size);
            buys = buys + (getter.order_size * getter.float_price);
        if (getter.buy_sell == -1)
            sell_quant = sell_quant + (getter.order_size);
            sells = sells + (getter.order_size * getter.float_price);
    }

    if (sell_quant == buy_quant)
        m_PnL = (sells - buys) * TICK_SIZE_PROD1;



//    PROD1_market[47] = m_PnL;
}

//////////////////////////////////
//      search Destroy()        //
//////////////////////////////////
void Boomer::searchDestroy(double die)   // if desires at price "die" are 0, cancel all orders at that price
{
    for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++)
    {
        Pending& death = m_got->second;
        if ( (death.float_price == die) && (death.cover == 0) && (death.sent_cancel == 0) ) {    // will not cancel if cover = 1
        //    death.sent_cancel = 1;
            cout << "Cancel Order :      \t\tPrice: " << death.float_price << "\tOrder Id: " 
                 << death.order_Id << "\toType: " << death.order_type << endl;
            m_pClient->cancelOrder( death.order_Id);
            death.sent_cancel = 1;
        }
    }
}

//////////////////////////////////
//      search Rescue()         //
//////////////////////////////////
int Boomer::searchRescue(double live)    // returns num orders open at price level "live"
{
    // count any fired orders created but pending
    m_pending = 0;
    for (m_pend = m_orderMapPending.begin(); m_pend != m_orderMapPending.end(); m_pend++)
    {
        Pending& pendo = m_pend->second;
        if ( (pendo.float_price == live) && (pendo.fully_filled == 0) )
            m_pending = m_pending + pendo.order_size;
    }

    // count any open orders on the level
    m_living = 0;
    for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++)
    {
        Pending& life = m_got->second;
        if ( (life.float_price == live) && (life.fully_filled == 0) )
            m_living = m_living + life.order_size;
    }
    return (m_pending + m_living);
}

//////////////////////////////////
//      search Filled()         //
//////////////////////////////////
int Boomer::searchFilled(double fillPrice)    // returns num orders open at price level "live"
{
    // count any executed orders not yet closed out
    m_filled = 0;
    for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++)
    {
        Pending& filler = m_fil->second;
        if ( (filler.float_price == fillPrice) && (filler.cover == 0) )
            m_filled = m_filled + filler.order_size;
    }
    return m_filled;
}

//////////////////////////////////
//      searchStop(price)       //
//////////////////////////////////
void Boomer::searchStop(double stopPrice, int lean, int position)
{
    int fired = 0;
    // close long position
    if (lean == 1)
    {
        if ( (stopPrice == m_deadPrice) && (fired == 0) ) {
            if(m_debug)
                cout << "\tFIRE SELL AT BID BRO, Selling " << position << " at " << m_deadPrice << endl;
            placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, "SELL", "MKT", position, m_deadPrice, -1, 1, 0);
            fired = 1;
            m_stoppedOut = 1;
        }
    }
    // close short position
    if (lean == -1)
    {
        if ( (stopPrice == m_deadPrice) && (fired == 0) ) {
            if(m_debug)
                cout << "\tFIRE BUY AT OFFER BRO, Buying " << position << " at " << m_deadPrice << endl;
            placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, "BUY", "MKT", position, m_deadPrice, 1, 1, 0);
            fired = 1;
            m_stoppedOut = 1;
        }
    }
}

//////////////////////////////////
//     strategyReset()          //
//////////////////////////////////
void Boomer::strategyReset()
{
    cout << "\n\n\n\t\t\t\t\t $$$$$$$$$$$$$ RESET, SON! $$$$$$$$$$\n\n\n";

    m_lean = 0;
    m_firstFill = 0;
    m_deadPrice = 0;
    m_bidDeadPrice = 0;
    m_offerDeadPrice = 0;
    m_lifePrice = 0;
    m_stoppedOut = 0;
    m_lastPosition = 0;

    PROD1_market[43] = m_bidDeadPrice;
    PROD1_market[44] = m_offerDeadPrice;


    for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++)
    {
        Pending& clear = m_fil->second;
        if (clear.cover == 0)
            clear.cover = 1;    // remove them all from GUI count
    }

    for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++)
    {
        Pending& undoCover = m_got->second;
        if (undoCover.cover == 1)
            undoCover.cover = 0;    // reset any orders tagged cover
    }

    cout << "lean: " << m_lean << " firstfil: " << m_firstFill << " bidDeadP: " << m_bidDeadPrice
         << " ofrDeadP: " << m_offerDeadPrice << " lifeP: " << m_lifePrice << " so:" << m_stoppedOut << endl;
}

//////////////////////////////////
//      Cancel all orders       //
//////////////////////////////////
void Boomer::cancelAll()
{
    cout << "cancel all" << endl;
    int cancelCount = 0;

    for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++)
    {
        Pending& destroyer = m_got->second;
        if (destroyer.sent_cancel == 0) {
            destroyer.sent_cancel = 1;
            m_pClient->cancelOrder( destroyer.order_Id);
            cancelCount++;
        }
    }
    cout << "Cancelled a total of " << cancelCount << " orders brah." << endl;
}

void Boomer::endLife()
{
    cout << "****" << endl;
    cout << "stop" << endl;
    cout << "****" << endl;
    m_life = 0;
}

//////////////////////////////////////////////////////
//                                                  //
//        Order Status Callback Handler             //
//                                                  //
//////////////////////////////////////////////////////
void Boomer::orderStatus( OrderId orderId, const IBString &status, int filled,
	   int remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const IBString& whyHeld)
{
    if (clientId == 3) {

        m_priceOrder = (lastFillPrice / TICK_SIZE_PROD1);

        //////////////////////////////////////////////
        //          Order Map Pending               //
        //////////////////////////////////////////////
        m_pend = m_orderMapPending.find(orderId);
        if (m_pend != m_orderMapPending.end()) {
            if(m_debug)
                cout << "\t### OrderID: " << orderId << " status: " << status 
                     << " in Pending Map\tSize: " << m_orderMapPending.size() << endl << endl;
            Pending& pender = m_orderMapPending.find(orderId)->second;

            ////////////// PENDING SUBMIT ////////////////
            if ((pender.pending_update == 0) && (status == "PendingSubmit")) {
                pender.pending_update = 1;
                cout << "Order Status : " << status << "\tPrice: " << pender.float_price << "\tOrder Id: " 
                     << pender.order_Id << "\tQuant: " << pender.order_size << endl;
            }

            ////////////// PRE-SUBMITTED ////////////////
            if ((pender.place_update == 0) && (status == "PreSubmitted")) {
                pender.place_update = 1;
                cout << "Order Status : " << status << "\tPrice: " << pender.float_price << "\tOrder Id: " 
                     << pender.order_Id << "\tQuant: " << pender.order_size << endl;
            }

            ////////////// SUBMITTED /////////////////////
            if ( (pender.placed_update == 0) && (status == "Submitted") ) {
                pender.placed_update = 1;

                cout << "Order Status : " << status << "\tPrice: " << pender.float_price << "\tOrder Id: " 
                     << pender.order_Id << "\tQuant: " << pender.order_size << endl;

                // Move order from Pending Map to Map 
                m_orderMap.insert(OrderMap::value_type(pender.order_Id, pender));
                cout << "Order Map    : Insert" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                     << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;

                // Erase order from Map 
                m_orderMapPending.erase(pender.order_Id);
                cout << "Order Map Pnd: Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                     << pender.order_Id << "\tSize: " << m_orderMapPending.size() << endl;
            }
            ////////////// FILLED /////////////////////     (order status goes pending directly to filled)
            if ( (pender.pendex_update == 0) && (status == "Filled") ) {
                pender.pendex_update = 1;

                cout << "Order Status : " << status << "\t\tPrice: " << pender.float_price << "\tOrder Id: " 
                     << pender.order_Id << "\tQuant: " << filled << endl;

                // Move order from Pending Map to Map       (let orderMap sort out Filled order)
                m_orderMap.insert(OrderMap::value_type(pender.order_Id, pender));
                cout << "Order Map    : Insert" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                     << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;

                // Erase order from Pending Map 
                m_orderMapPending.erase(pender.order_Id);
                cout << "Order Map Pnd: Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                     << pender.order_Id << "\tSize: " << m_orderMapPending.size() << endl;
            }
        }
        //////////////////////////////////////////////
        //            Order Map Dunzo               //
        //////////////////////////////////////////////
        m_dun = m_orderMapDunzo.find(orderId);
        if (m_dun != m_orderMapDunzo.end()) {
            if(m_debug)
                cout << "\t### OrderID: " << orderId << " status: " << status 
                     << " in Dunzo Map\tSize: " << m_orderMapDunzo.size() << endl << endl;
            Pending& pender = m_orderMapDunzo.find(orderId)->second; }

        //////////////////////////////////////////////
        //            Order Map Filled              //
        //////////////////////////////////////////////
        m_fil = m_orderMapFilled.find(orderId);
        if (m_fil != m_orderMapFilled.end()) {
            cout << "\t### OrderID: " << orderId << " status: " << status 
                 << " in Filled Map\tSize: " << m_orderMapFilled.size() << endl << endl;
            Pending& pender = m_orderMapFilled.find(orderId)->second; }

        //////////////////////////////////////////////
        //              Order Map                   //
        //////////////////////////////////////////////
        m_got = m_orderMap.find(orderId);
        if (m_got != m_orderMap.end()) {
            if(m_debug)
                cout << "\t### OrderID: " << orderId << " status: " << status 
                     << " in Map\tSize: " << m_orderMap.size() << endl << endl;
            Pending& pender = m_orderMap.find(orderId)->second;

            if (pender.fully_filled != 1) {

                ////////////// CANCELLED  ////////////////
                if ((pender.cancelled == 0) && (status == "Cancelled")) {
                    pender.cancelled = 1;
                    cout << "Order Status : " << status << "\tPrice: " << pender.float_price << "\tOrder Id: " 
                         << pender.order_Id << "\tQuant: " << pender.order_size << endl;

                    // erase order from Map 
                    m_orderMap.erase(pender.order_Id);
                    cout << "Order Map    : Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                         << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;
                }

                //////////////  FILLED  /////////////////////
                if (status == "Filled") {
                    cout << "Order Status : " << status << "\t\tPrice: " << pender.float_price << "\tOrder Id: " 
                         << pender.order_Id << "\tQuant: " << filled << endl;

                    pender.remaining = remaining;   // will be zero if order is dunzo

                    ///////////////////// set initial mop level strat attributes /////////////////////////////////////////////////////
                    if ( (m_firstFill == 0) && (pender.executed_update == 0) ) {
                        if (m_debug) {
                            cout << "FIRST FILL EQUALS ZERO" << endl;
                            cout << "ExUp: " << pender.executed_update << endl;
                            cout << "Bumass order setting Fill is Id: " << pender.order_Id << endl; }

                        m_firstFill = 1;

//                        m_deadPrice = lastFillPrice + (m_stopLoss * TICK_SIZE_PROD1 * pender.buy_sell * -1);                        
//                        m_lifePrice = lastFillPrice + (m_profit * TICK_SIZE_PROD1 * pender.buy_sell);                               

                        m_deadPrice = m_priceOrder + (m_stopLoss * pender.buy_sell * -1);                        
                        m_lifePrice = m_priceOrder + (m_profit * pender.buy_sell);                               

                        if (pender.buy_sell == 1)  {
                            m_lean = 1;           
                            m_bidDeadPrice = m_deadPrice;
                            m_offerDeadPrice = m_lifePrice; }
                        else  {
                            m_lean = -1;        
                            m_offerDeadPrice = m_deadPrice;
                            m_bidDeadPrice = m_lifePrice; }

//                        PROD1_market[43] = m_bidDeadPrice / TICK_SIZE_PROD1;;
//                        PROD1_market[44] = m_offerDeadPrice / TICK_SIZE_PROD1;;

                        PROD1_market[43] = m_bidDeadPrice;
                        PROD1_market[44] = m_offerDeadPrice;


                        if (m_debug)
                            cout << "\n\t$$$$ First Fill Shit: DeadPrice: " << m_deadPrice << " lifePrice: " << m_lifePrice << endl << endl;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    if ( (pender.order_type == "MKT") && (pender.executed_update == 0) )
                    {
                        // insert filled order into Filled Map
                        m_orderMapFilled.insert(OrderMapFilled::value_type(pender.order_Id, pender));
                        cout << "Order Map F0 : Insert" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                             << pender.order_Id << "\tSize: " << m_orderMapFilled.size() << endl;

                        // erase filled order from Map if it exists there
                        m_got = m_orderMap.find(orderId);
                        if (m_got != m_orderMap.end()) {
                            m_orderMap.erase(pender.order_Id);
                            cout << "Order Map    : Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                                 << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;
                        }

                        // erase filled order from Pending Map if it exists there
                        m_pend = m_orderMapPending.find(orderId);
                        if (m_pend != m_orderMapPending.end()) {
                            m_orderMapPending.erase(pender.order_Id);
                            cout << "Order Map    : Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                                 << pender.order_Id << "\tSize: " << m_orderMapPending.size() << endl;
                        }

                        if (pender.remaining == 0)
                            pender.fully_filled = 1;
                        pender.executed_update = 1;

                        // calculate position
                        m_filPosition = 0;
                        for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++) {
                            Pending& filled = m_fil->second;
                            m_thisPosition = filled.order_size * filled.buy_sell;
                            m_filPosition = m_filPosition + m_thisPosition;
                        }

                        m_dunPosition = 0;
                        for (m_dun = m_orderMapDunzo.begin(); m_dun != m_orderMapDunzo.end(); m_dun++) {
                            Pending& done = m_dun->second;
                            m_thatPosition = done.order_size * done.buy_sell;
                            m_dunPosition = m_dunPosition + m_thatPosition;
                        }

                        m_price1 = lastFillPrice;
                        m_hold = lastFillPrice - m_price1;
                        m_hold = m_hold * 32;
                        m_price2 = m_hold;
                        m_hold = m_hold - m_price2;
                        if ( (m_hold >= 0) && (m_hold <= 0.2) )
                            m_price3 = 0;
                        if ( (m_hold >= 0.2) && (m_hold <= 0.4) )
                            m_price3 = 2;
                        if ( (m_hold >= 0.4) && (m_hold <= 0.6) )
                            m_price3 = 5;
                        if ( (m_hold >= 0.6) && (m_hold <= 0.9) )
                            m_price3 = 7;


                        // execution report
                        cout << "\n********** Execution Report *********\n";
                        cout << "Price   :\t" << (lastFillPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "IB Price:\t" << m_price1 << "'" << m_price2 << "" << m_price3 << "\t\t   *\n";
                        cout << "OrderId :\t" << pender.order_Id << "\t\t   *\n";
                        cout << "Executed:\t" << filled << "\t\t   *\n";
                        cout << "Cvr(y/n):\t" << pender.cover << "\t\t   *\n";
                        cout << "Buy/Sell:\t" << pender.buy_sell << "\t\t   *\n";
                        cout << "Action  :\t" << pender.action << "\t\t\t\t\t\t***********************************************************************\n";
                        cout << "Type    :\t" << pender.order_type << "\t\t   *\n";
                        cout << "oSize   :\t" << pender.order_size << "\t\t   *\n";
//                        cout << "Dead P  :\t" << (m_deadPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
//                        cout << "Life  P :\t" << (m_lifePrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "Dead P  :\t" << m_deadPrice << "\t\t   *\n";
                        cout << "Life  P :\t" << m_lifePrice << "\t\t   *\n";
                        cout << "Cover 4 :\t" << pender.cover_for_Id << "\t\t   *\n";
                        const time_t ctt = time(0);
                        cout << "Time    :\t" << asctime(localtime(&ctt)) << endl;
                        cout << "*************************************\n\n";


                        m_currentPosition = (m_dunPosition + m_filPosition);
                        m_absPosition = (abs(m_currentPosition));
                        cout << "POSITION: " << m_currentPosition << endl;
                        PROD1_market[4] = m_currentPosition;
                    }


                    // passive entry order fill
                    if ( (pender.cover == 0) && (pender.executed_update == 0) && (pender.order_type == "LMT") )
                    {
                        // insert filled order into Filled Map
                        m_orderMapFilled.insert(OrderMapFilled::value_type(pender.order_Id, pender));
                        cout << "Order Map F1 : Insert" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                             << pender.order_Id << "\tSize: " << m_orderMapFilled.size() << endl;
                        // erase filled order from Map 
                        m_orderMap.erase(pender.order_Id);
                        cout << "Order Map    : Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                             << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;

                        if (pender.remaining == 0)
                            pender.fully_filled = 1;
                        pender.executed_update = 1;

                        m_price1 = lastFillPrice;
                        m_hold = lastFillPrice - m_price1;
                        m_hold = m_hold * 32;
                        m_price2 = m_hold;
                        m_hold = m_hold - m_price2;
                        if ( (m_hold >= 0) && (m_hold <= 0.2) )
                            m_price3 = 0;
                        if ( (m_hold >= 0.2) && (m_hold <= 0.4) )
                            m_price3 = 2;
                        if ( (m_hold >= 0.4) && (m_hold <= 0.6) )
                            m_price3 = 5;
                        if ( (m_hold >= 0.6) && (m_hold <= 0.9) )
                            m_price3 = 7;


                        // execution report
                        cout << "\n********** Exe Float Report *********\n";
                        cout << "Price   :\t" << (lastFillPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "IB Price:\t" << m_price1 << "'" << m_price2 << "" << m_price3 << "\t\t   *\n";
                        cout << "OrderId :\t" << pender.order_Id << "\t\t   *\n";
                        cout << "Executed:\t" << filled << "\t\t   *\n";
                        cout << "Cvr(y/n):\t" << pender.cover << "\t\t   *\n";
                        cout << "Buy/Sell:\t" << pender.buy_sell << "\t\t   *\n";
                        cout << "Action  :\t" << pender.action << "\t\t\t\t\t\t***********************************************************************\n";
                        cout << "Type    :\t" << pender.order_type << "\t\t   *\n";
                        cout << "oSize   :\t" << pender.order_size << "\t\t   *\n";
//                        cout << "Dead P  :\t" << (m_deadPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
//                        cout << "Life  P :\t" << (m_lifePrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "Dead P  :\t" << m_deadPrice << "\t\t   *\n";
                        cout << "Life  P :\t" << m_lifePrice << "\t\t   *\n";
                        cout << "Cover 4 :\t" << pender.cover_for_Id << "\t\t   *\n";
                        const time_t ctt = time(0);
                        cout << "Time    :\t" << asctime(localtime(&ctt)) << endl;
                        cout << "*************************************\n\n";

                        // calculate position 
                        m_filPosition = 0;
                        for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++) {
                            Pending& filled = m_fil->second;
                            m_thisPosition = filled.order_size * filled.buy_sell;
                            m_filPosition = m_filPosition + m_thisPosition;
                        }
                        m_dunPosition = 0;
                        for (m_dun = m_orderMapDunzo.begin(); m_dun != m_orderMapDunzo.end(); m_dun++) {
                            Pending& done = m_dun->second;
                            m_thatPosition = done.order_size * done.buy_sell;
                            m_dunPosition = m_dunPosition + m_thatPosition;
                        }

                        m_currentPosition = (m_dunPosition + m_filPosition);
                        m_absPosition = (abs(m_currentPosition));
                        m_deltaPosition = m_absPosition - m_lastPosition;
                        m_lastPosition = m_absPosition;
                        cout << "POSITION: " << m_currentPosition << endl;
                        cout << "DELTA POSITION: " << m_deltaPosition << endl;
                        PROD1_market[4] = m_currentPosition;

                        // search for existing floats and tag them covers
                        m_existsFound = 0;

                        ////// first look in pending map for orders sent but not ack'd that will serve as covers
                        for (m_pend = m_orderMapPending.begin(); m_pend != m_orderMapPending.end(); m_pend++) {
                            Pending& pexists = m_pend->second;
                            if ( (pexists.float_price == m_lifePrice) && (pexists.cover == 0) ) {

                                if (pexists.order_size == m_deltaPosition) { // perfect match
                                    pexists.cover = 1;
                                    pexists.cover_for_Id = pender.order_Id;
                                    m_existsFound = 1;
                                    cout << "PEXISTS I     : Tagging\t\tPrice: " << pexists.float_price << "\tOrder Id: " << pexists.order_Id 
                                         << "\tTo Filled: " << pender.order_Id << endl;
                                    break; }

                                if (m_deltaPosition > pexists.order_size) {  // gotta float more
                                    pexists.cover = 1;
                                    m_existsFound = 1;
                                    floatSize = (m_deltaPosition) - (pexists.order_size);

                                    if (m_currentPosition < 0) {   // position is short so float BUY
                                        actionB = "BUY";
                                        byeCell = 1; }
                                    else {
                                        actionB = "SELL";
                                        byeCell = -1; }

                                    cout << "PEXISTS II:\t\t" << actionB << " " << floatSize << " at: " << m_lifePrice << endl;
                                    placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionB, "LMT", floatSize, m_lifePrice, byeCell, 1, pender.order_Id);
                                    break; }

                                if (pexists.order_size > m_deltaPosition) {  // float is larger, gotta float new order
                                    m_existsFound = 1;
                                    if (m_currentPosition < 0) { 
                                        actionB = "BUY";
                                        byeCell = 1; }
                                    else {
                                        actionB = "SELL";
                                        byeCell = -1; }
                                    floatSize = m_deltaPosition;
                                    cout << "PEXISTS III\t\t: " << actionB << " " << floatSize << " at: " << m_lifePrice << endl;
                                    placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionB, "LMT", floatSize, m_lifePrice, byeCell, 1, pender.order_Id);
                                    break; }
                            }
                        }
                        ///// did not find any suitable covers in pending map, check order map
                        if (m_existsFound != 1) {

                            for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++) {
                                Pending& exists = m_got->second;

                                if ( (exists.float_price == m_lifePrice) && (exists.cover == 0) ) {

                                    if (exists.order_size == m_deltaPosition) { // perfect match
                                        exists.cover = 1;
                                        exists.cover_for_Id = pender.order_Id;
                                        m_existsFound = 1;
                                        cout << "EXISTS I     : Tagging\t\tPrice: " << exists.float_price << "\tOrder Id: " << exists.order_Id 
                                             << "\tTo Filled: " << pender.order_Id << endl;
                                        break; }

                                    if (m_deltaPosition > exists.order_size) {  // gotta float more
                                        exists.cover = 1;
                                        m_existsFound = 1;
                                        floatSize = (m_deltaPosition) - (exists.order_size);

                                        if (m_currentPosition < 0) {   // position is short so float BUY
                                            actionB = "BUY";
                                            byeCell = 1; }
                                        else {
                                            actionB = "SELL";
                                            byeCell = -1; }

                                        cout << "EXISTS II:\t\t" << actionB << " " << floatSize << " at: " << m_lifePrice << endl;
                                        placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionB, "LMT", floatSize, m_lifePrice, byeCell, 1, pender.order_Id);
                                        break; }

                                    if (exists.order_size > m_deltaPosition) {  // float is larger, gotta float new order
                                        m_existsFound = 1;
                                        if (m_currentPosition < 0) { 
                                            actionB = "BUY";
                                            byeCell = 1; }
                                        else {
                                            actionB = "SELL";
                                            byeCell = -1; }
                                        floatSize = m_deltaPosition;
                                        cout << "EXISTS III\t\t: " << actionB << " " << floatSize << " at: " << m_lifePrice << endl;
                                        placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionB, "LMT", floatSize, m_lifePrice, byeCell, 1, pender.order_Id);
                                        break; }
                                }
                            }
                        }
                        // for loop ended and no existing cover found for executed entry order, fire cover
                        if ( (pender.cover == 0) && (m_existsFound == 0) && (pender.order_type == "LMT") ) {
                            if (m_currentPosition < 0) {
                                actionB = "BUY";
                                byeCell = 1;
                                floatSize = m_deltaPosition;}
                            else {
                                actionB = "SELL";
                                byeCell = -1;
                                floatSize = m_deltaPosition;}
                            m_existsFound = 1;  // tag order
                            cout << "EXISTS IV\t\t: " << actionB << " " << floatSize << " at: " << m_lifePrice << " pender.buy_sell: " << pender.buy_sell << endl;
                            placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionB, "LMT", floatSize, m_lifePrice, byeCell, 1, pender.order_Id);
                        }
                    }   // pender.cover = 0

                    ///////// COVER ORDER FILLED ////////////////
                    if ( (pender.cover == 1) && (pender.executed_update == 0) && (pender.remaining == 0) ) {
                        pender.executed_update = 1;
                        pender.fully_filled = 1;

                        // insert filled order into Filled Map
                        m_orderMapFilled.insert(OrderMapFilled::value_type(pender.order_Id, pender));
                        cout << "Order Map F2 : Insert" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                             << pender.order_Id << "\tExUpdate: " << pender.executed_update << endl;
                        // erase filled order from Map 
                        m_orderMap.erase(pender.order_Id);
                        cout << "Order Map    : Erased" << "\t\tPrice: " << pender.float_price << "\tOrder Id: "
                             << pender.order_Id << "\tSize: " << m_orderMap.size() << endl;

                        // tag entry order as covered 
                        m_fil = m_orderMapFilled.find(pender.cover_for_Id);
                        if (m_fil != m_orderMapFilled.end()) {
                            Pending& Tagged = m_fil->second;
                            Tagged.cover = 1;
                            cout << "Order Tagged : " << Tagged.order_Id << "\t\tPrice: " << Tagged.float_price << "\tCover: " << Tagged.cover << endl;
                        }

                        m_price1 = lastFillPrice;
                        m_hold = lastFillPrice - m_price1;
                        m_hold = m_hold * 32;
                        m_price2 = m_hold;
                        m_hold = m_hold - m_price2;
                        if ( (m_hold >= 0) && (m_hold <= 0.2) )
                            m_price3 = 0;
                        if ( (m_hold >= 0.2) && (m_hold <= 0.4) )
                            m_price3 = 2;
                        if ( (m_hold >= 0.4) && (m_hold <= 0.6) )
                            m_price3 = 5;
                        if ( (m_hold >= 0.6) && (m_hold <= 0.9) )
                            m_price3 = 7;

                        // execution report
                        cout << "\n********** Exe Cover Report *********\n";
                        cout << "Price   :\t" << (lastFillPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "IB Price:\t" << m_price1 << "'" << m_price2 << "" << m_price3 << "\t\t   *\n";
                        cout << "OrderId :\t" << pender.order_Id << "\t\t   *\n";
                        cout << "Executed:\t" << filled << "\t\t   *\n";
                        cout << "Cvr(y/n):\t" << pender.cover << "\t\t   *\n";
                        cout << "Buy/Sell:\t" << pender.buy_sell << "\t\t   *\n";
                        cout << "Action  :\t" << pender.action << "\t\t\t\t\t\t***********************************************************************\n";
                        cout << "Type    :\t" << pender.order_type << "\t\t   *\n";
                        cout << "oSize   :\t" << pender.order_size << "\t\t   *\n";
//                        cout << "Dead P  :\t" << (m_deadPrice / TICK_SIZE_PROD1) << "\t\t   *\n";
//                        cout << "Life  P :\t" << (m_lifePrice / TICK_SIZE_PROD1) << "\t\t   *\n";
                        cout << "Dead P  :\t" << m_deadPrice << "\t\t   *\n";
                        cout << "Life  P :\t" << m_lifePrice << "\t\t   *\n";
                        cout << "Cover 4 :\t" << pender.cover_for_Id << "\t\t   *\n";
                        const time_t ctt = time(0);
                        cout << "Time    :\t" << asctime(localtime(&ctt)) << endl;
                        cout << "*************************************\n\n";

                       // calculate position homes
                        m_filPosition = 0;
                        for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++) {
                            Pending& filled = m_fil->second;
                            m_thisPosition = filled.order_size * filled.buy_sell;
                            m_filPosition = m_filPosition + m_thisPosition;
                        }
                        m_dunPosition = 0;
                        for (m_dun = m_orderMapDunzo.begin(); m_dun != m_orderMapDunzo.end(); m_dun++) {
                            Pending& done = m_dun->second;
                            m_thatPosition = done.order_size * done.buy_sell;
                            m_dunPosition = m_dunPosition + m_thatPosition;
                        }

                        m_currentPosition = (m_dunPosition + m_filPosition);
                        m_absPosition = (abs(m_currentPosition));
                        m_deltaPosition = m_absPosition - m_lastPosition;
                        m_lastPosition = m_absPosition;
                        cout << "POSITION: " << m_currentPosition << endl;
                        PROD1_market[4] = m_currentPosition;

                    }
                }   // status = filled END
            }   // pender.fully_filled != 1
        }   // orderMap

        // update open orders on GUI
        for (int i = 0; i < (m_rows * 2); i++) 
        {
            m_iter = m_priceMap.find(i);
            PriceLevel& pos = m_iter->second;
            double thePrice = pos.price;
            findOrders(thePrice, i);
        }
        // update filled orders on GUI
        for (int i = 0; i < (m_rows * 2); i++) 
        {
            m_iter = m_priceMap.find(i);
            PriceLevel& posfil = m_iter->second;
            double thePrice = posfil.price;
            findOpenOrders(thePrice, i);
        }
        if ( (m_firstFill == 1) && (m_currentPosition == 0) )
            strategyReset();

//        getPnL();
    }
}
  
// udpate myBids and myOffers in GUI for pending orders
void Boomer::findOrders(double price, int i)
{
    int orderCount = 0;

    for (m_got = m_orderMap.begin(); m_got != m_orderMap.end(); m_got++) {
        Pending& mine = m_got->second;
        if( (mine.float_price == price) && (mine.cancelled == 0) )
            orderCount = orderCount + mine.order_size;}

    if (i == 0)
        PROD1_market[23] = orderCount;
    if (i == 1)
        PROD1_market[24] = orderCount;
    if (i == 2)
        PROD1_market[25] = orderCount;
    if (i == 3)
        PROD1_market[26] = orderCount;
    if (i == 4)
        PROD1_market[27] = orderCount;
    if (i == 5)
        PROD1_market[28] = orderCount;
    if (i == 6)
        PROD1_market[29] = orderCount;
    if (i == 7)
        PROD1_market[30] = orderCount;
    if (i == 8)
        PROD1_market[31] = orderCount;
    if (i == 9)
        PROD1_market[32] = orderCount;
    if (i == 10)
        PROD1_market[52] = orderCount;
    if (i == 11)
        PROD1_market[53] = orderCount;
}

// udpate filled open orders 
void Boomer::findOpenOrders(double price, int i)
{
    int openOrderCount = 0;

    for (m_fil = m_orderMapFilled.begin(); m_fil != m_orderMapFilled.end(); m_fil++) {
        Pending& mine = m_fil->second;
        if ( (mine.float_price == price) && (mine.cover == 0) )
            openOrderCount = openOrderCount + (mine.order_size * mine.buy_sell);}

    if (i == 0)
        PROD1_market[33] = openOrderCount;
    if (i == 1)
        PROD1_market[34] = openOrderCount;
    if (i == 2)
        PROD1_market[35] = openOrderCount;
    if (i == 3)
        PROD1_market[36] = openOrderCount;
    if (i == 4)
        PROD1_market[37] = openOrderCount;
    if (i == 5)
        PROD1_market[38] = openOrderCount;
    if (i == 6)
        PROD1_market[39] = openOrderCount;
    if (i == 7)
        PROD1_market[40] = openOrderCount;
    if (i == 8)
        PROD1_market[41] = openOrderCount;
    if (i == 9)
        PROD1_market[42] = openOrderCount;
    if (i == 10)
        PROD1_market[54] = openOrderCount;
    if (i == 11)
        PROD1_market[55] = openOrderCount;
}

void Boomer::nextValidId( OrderId orderId)
{
    cout << "nextValidId: " << orderId << endl;
	m_orderId = orderId;
    m_state = ST_REQ_MKT_DEPTH_PROD1;
}

//////////////////////////////////////////////////////
//                                                  //
//              Desire Book Update                  //
//                                                  //
//////////////////////////////////////////////////////
// will only be called when new level, aka operation = 0
//void Boomer::desireBookUpdate(int side, int position, double price, int size)
void Boomer::desireBookUpdate()
{
    // enable desires
    if (m_start == 1) {

        if (m_lean == 0) {
            m_insideSizeBid = m_insideSize;
            m_insideSizeOffer = m_insideSize;
            m_outsideSizeBid = m_outsideSize;
            m_outsideSizeOffer = m_outsideSize;
        }
        else {
            if (m_lean == 1) {
                m_insideSizeOffer = 0;
                m_outsideSizeOffer = 0;
                m_insideSizeBid = m_insideSize;
                m_outsideSizeBid = m_outsideSize;
            }
            if (m_lean == -1) {
                m_insideSizeBid = 0;
                m_outsideSizeBid = 0;
                m_insideSizeOffer = m_insideSize;
                m_outsideSizeOffer = m_outsideSize;
            }
        }

        m_bidDesires0 = m_insideSizeBid;
        m_offerDesires0 = m_insideSizeOffer;

        if (m_depth == 0) {
                m_bidDesires1 = 0;
                m_bidDesires2 = 0; 
                m_bidDesires3 = 0;
                m_bidDesires4 = 0;
                m_bidDesires5 = 0;
                m_offerDesires1 = 0;
                m_offerDesires2 = 0;
                m_offerDesires3 = 0; 
                m_offerDesires4 = 0; 
                m_offerDesires5 = 0; 
        }
        else {
            if (m_buffer == 1 ) { 
                if (m_depth == 1) {
                    m_bidDesires1 = m_outsideSizeBid;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = 0;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = m_outsideSizeOffer;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = 0; 
                    m_offerDesires4 = 0; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 2) {
                    m_bidDesires1 = m_outsideSizeBid;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = 0;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = m_outsideSizeOffer;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = 0; 
                    m_offerDesires4 = 0; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 3) {
                    m_bidDesires1 = m_outsideSizeBid;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = m_outsideSizeOffer;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = 0; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 4) {
                    m_bidDesires1 = m_outsideSizeBid;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = m_outsideSizeOffer;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 5) {
                    m_bidDesires1 = m_outsideSizeBid;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = m_outsideSizeBid;
                    m_offerDesires1 = m_outsideSizeOffer;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer; 
                    m_offerDesires5 = m_outsideSizeOffer; 
                }
            }
            if (m_buffer == 2 ) {
                if (m_depth == 1) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = 0;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = 0; 
                    m_offerDesires4 = 0; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 2) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = 0;
                    m_offerDesires5 = 0;
                }
                if (m_depth == 3) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer;
                    m_offerDesires5 = 0;
                }
                if ( (m_depth == 4) || (m_depth == 5) )  {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = m_outsideSizeBid; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = m_outsideSizeBid;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = m_outsideSizeOffer;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer;
                    m_offerDesires5 = m_outsideSizeOffer;
                }
            }
            if (m_buffer == 3 ) {
                if (m_depth == 1) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = 0;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = 0; 
                    m_offerDesires5 = 0; 
                }
                if (m_depth == 2) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer;
                    m_offerDesires5 = 0; 
                }
                if ( (m_depth == 3) || (m_depth == 4) || (m_depth == 5) ) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = m_outsideSizeBid;
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = m_outsideSizeBid;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = m_outsideSizeOffer; 
                    m_offerDesires4 = m_outsideSizeOffer;
                    m_offerDesires5 = m_outsideSizeOffer; 
                }
            }

            if (m_buffer == 4 ) {
                if (m_depth == 1) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = 0; 
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = 0;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = 0; 
                    m_offerDesires4 = m_outsideSizeOffer; 
                    m_offerDesires5 = 0; 
                }
                if ( (m_depth == 2) || (m_depth == 3) || (m_depth == 4) || (m_depth == 5) ) {
                    m_bidDesires1 = 0;
                    m_bidDesires2 = 0; 
                    m_bidDesires3 = 0; 
                    m_bidDesires4 = m_outsideSizeBid;
                    m_bidDesires5 = m_outsideSizeBid;
                    m_offerDesires1 = 0;
                    m_offerDesires2 = 0;
                    m_offerDesires3 = 0; 
                    m_offerDesires4 = m_outsideSizeOffer; 
                    m_offerDesires5 = m_outsideSizeOffer; 
                }
            }
            if (m_buffer == 5 ) {
                m_bidDesires1 = 0;
                m_bidDesires2 = 0; 
                m_bidDesires3 = 0;
                m_bidDesires4 = 0;
                m_bidDesires5 = 0;
                m_offerDesires1 = 0;
                m_offerDesires2 = 0;
                m_offerDesires3 = 0; 
                m_offerDesires4 = 0; 
                m_offerDesires5 = 0; 
            }
        }
    }

    for (int i = 0; i < (m_rows * 2); i++)
    {
        // best bid
        if (key0 == i) {
            if (m_lean == 1) {
                if (m_debug)
                    cout << "bidPrice0 = " << m_bidPrice0 << " and deadPrice = " << m_deadPrice << endl;
                if (m_stoppedOut == 0)
                    searchStop(m_bidPrice0, m_lean, m_absPosition); // something something);
            }
            m_iter = m_priceMap.find(key0);
            if (m_iter == m_priceMap.end() ) { cout << "Can't find PriceLevel bid0" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key0)->second;
                holder.price = m_bidPrice0;
                holder.fires = 0;
                if (m_bidPrice0 == m_deadPrice)
                    holder.desires = 0;
                else {
                    if (m_bidSize0 >= m_support)
                        holder.desires = m_bidDesires0;
                    else
                        holder.desires = 0;
                }
                b0 = holder.desires;
            }
        }
        // best offer
        if (key1 == i) {
            if (m_lean == -1) {
                if (m_debug)
                    cout << "offerPrice0 = " << m_offerPrice0 << " and deadPrice = " << m_deadPrice << endl;
                if (m_stoppedOut == 0)
                    searchStop(m_offerPrice0, m_lean, m_absPosition);
            }
            m_iter = m_priceMap.find(key1);
            if (m_iter == m_priceMap.end() )  { cout << "Can'e find PriceLevel offer0" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key1)->second;
                holder.price = m_offerPrice0;
                holder.fires = 0;
                if (m_offerPrice0 == m_deadPrice)
                    holder.desires = 0;
                else {
                    if (m_offerSize0 >= m_support)
                        holder.desires = m_offerDesires0;
                    else
                        holder.desires = 0;
                }
                o0 = holder.desires;
            }
        }
        // bid 1st seed 
        if (key2 == i) {
            m_iter = m_priceMap.find(key2);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel bid1" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key2)->second;
                holder.price = m_bidPrice1;
                holder.fires = 0;
                if (m_bidPrice1 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_bidDesires1;

                b1 = holder.desires;
            }
        }
        // offer 1st seed 
        if (key3 == i) {
            m_iter = m_priceMap.find(key3);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel offer1" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key3)->second;
                holder.price = m_offerPrice1;
                holder.fires = 0;
                if (m_offerPrice1 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_offerDesires1;

                o1 = holder.desires;
            }
        }
        // bid 2nd seed 
        if (key4 == i) {
            m_iter = m_priceMap.find(key4);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel bid2" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key4)->second;
                holder.price = m_bidPrice2;
                holder.fires = 0;
                if (m_bidPrice2 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_bidDesires2;

                b2 = holder.desires;
            }
        }
        // offer 2nd seed 
        if (key5 == i) {
            m_iter = m_priceMap.find(key5);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel offer2" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key5)->second;
                holder.price = m_offerPrice2;
                holder.fires = 0;
                if (m_offerPrice2 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_offerDesires2;

                o2 = holder.desires;
            }
        }
        // bid 3rd seed
        if (key6 == i) {
            m_iter = m_priceMap.find(key6);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel bid3" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key6)->second;
                holder.price = m_bidPrice3;
                holder.fires = 0;
                if (m_bidPrice3 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_bidDesires3;
                
                b3 = holder.desires;
            }
        }
        // offer 3rd seed 
        if (key7 == i) {
            m_iter = m_priceMap.find(key7);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel offer3" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key7)->second;
                holder.price = m_offerPrice3;
                holder.fires = 0;
                if (m_offerPrice3 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_offerDesires3;

                o3 = holder.desires;
            }
        }
        // bid 4th seed
        if (key8 == i) {
            m_iter = m_priceMap.find(key8);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel bid4" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key8)->second;
                holder.price = m_bidPrice4;
                holder.fires = 0;
                if (m_bidPrice4 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_bidDesires4;
                b4 = holder.desires;
            }
        }
        // offer 4th seed 
        if (key9 == i) {
            m_iter = m_priceMap.find(key9);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel offer4" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key9)->second;
                holder.price = m_offerPrice4;
                holder.fires = 0;
                if (m_offerPrice4 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_offerDesires4;
                o4 = holder.desires;
            }
        }
        // bid 5th seed
        if (key10 == i) {
            m_iter = m_priceMap.find(key10);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel bid5" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key10)->second;
                holder.price = m_bidPrice5;
                holder.fires = 0;
                if (m_bidPrice5 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_bidDesires5;
                b5 = holder.desires;
            }
        }
        // offer 5th seed 
        if (key11 == i) {
            m_iter = m_priceMap.find(key11);
            if (m_iter == m_priceMap.end() ) { cout << "Can'e find PriceLevel offer5" << endl; }
            else {
                PriceLevel& holder = m_priceMap.find(key11)->second;
                holder.price = m_offerPrice5;
                holder.fires = 0;
                if (m_offerPrice5 == m_deadPrice)
                    holder.desires = 0;
                else
                    holder.desires = m_offerDesires5;
                o5 = holder.desires;
            }
        }




    }   // end for loop

    for (m_iter = m_priceMap.begin(); m_iter != m_priceMap.end(); m_iter++)
    {
        PriceLevel& check = m_iter->second;
        if (check.desires == 0) { 
            searchDestroy(check.price); 
        }
        else {
            m_open = searchRescue(check.price);   // returns num orders at this price
            m_filledOpen = searchFilled(check.price);
            check.open_orders = m_open;
            check.filled_open = m_filledOpen;

            if ( check.desires > (check.open_orders + check.filled_open) ) {
                m_fireSize = check.desires - (check.open_orders + check.filled_open);

                if (check.desires != check.fires) {
                    if (check.position % 2 == 0) {
                        actionJackson = "BUY";
                        buyerSeller = 1;
                    }
                    else {
                        actionJackson = "SELL";
                        buyerSeller = -1;
                    }
                    check.fires = m_open + m_filledOpen + m_fireSize;
                    cout << "Order Book   : Fire\t\tPrice: " << check.price << "\tAction:   " << actionJackson << "\tQuant: " << m_fireSize << endl;
                    placeOrder(CON_ID_PROD1, EXCHANGE_PROD1, actionJackson, "LMT", m_fireSize, check.price, buyerSeller, 0, 0); 
                }
            }
        }
    }
    cout << "\n*** Wait for Check ***\n";
    cout << b0 << " " << m_bidPrice0 << "  ||  " << m_offerPrice0 << " " << o0 << endl;
    cout << b1 << " " << m_bidPrice1 << "  ||  " << m_offerPrice1 << " " << o1 << endl;
    cout << b2 << " " << m_bidPrice2 << "  ||  " << m_offerPrice2 << " " << o2 << endl;
    cout << b3 << " " << m_bidPrice3 << "  ||  " << m_offerPrice3 << " " << o3 << endl;
    cout << b4 << " " << m_bidPrice4 << "  ||  " << m_offerPrice4 << " " << o4 << endl;
    cout << b5 << " " << m_bidPrice5 << "  ||  " << m_offerPrice5 << " " << o5 << endl;
    cout << "**********************\n";
}


//////////////////////////////////////////////////////
//                                                  //
//            Market Depth Callback                 //
//                                                  //
//////////////////////////////////////////////////////
void Boomer::updateMktDepth( TickerId tickerId, int position, int operation, int side, double price, int size)
{
    if (tickerIdDepth_PROD1 == tickerId) 
    {
        m_priceDepth = (price / TICK_SIZE_PROD1);

        // side: 0=offer, 1=bid ----  position: row ---- price: price on that row

        if (position == 0) {

            if (side == 1) {  
                m_bidUpdateLevelCounter = 1;
                m_offerUpdateLevelCounter = 0;
                m_bidPrice0 = m_priceDepth;
                m_bidSize0 = size;
                m_downTick = (m_priceDepth - m_firstBid);
                if (m_downTick < 0)
                    PROD1_market[45] = m_downTick;
                else
                    PROD1_market[45] = 0;
                PROD1_market[1] = m_priceDepth;
                PROD1_market[0] = size;
                if (m_insertBid0 != 1) {
                    m_firstBid = m_priceDepth;
                    createBid0(m_priceDepth, size);
                    m_insertBid0 = 1;
                }
            }
            else {
                m_offerUpdateLevelCounter = 1;
                m_bidUpdateLevelCounter = 0;
                m_offerPrice0 = m_priceDepth;
                m_offerSize0 = size;
                m_upTick = (m_priceDepth - m_firstOffer);
                if (m_upTick > 0)
                    PROD1_market[46] = m_upTick;
                else
                    PROD1_market[46] = 0;
                PROD1_market[2] = m_priceDepth;
                PROD1_market[3] = size;
                if (m_insertOffer0 != 1) {
                    m_firstOffer = m_priceDepth;
                    createOffer0(m_priceDepth, size);
                    m_insertOffer0 = 1;
                }
            }
        }

        if (position == 1) {
            if (side == 1) {
                m_bidUpdateLevelCounter++;
                m_bidPrice1 = m_priceDepth;
                m_bidSize1 = size;
                PROD1_market[7] = m_priceDepth;
                PROD1_market[8] = size;
                if (m_insertBid1 != 1) {
                    createBid1(m_priceDepth, size);
                    m_insertBid1 = 1;
                }
            }
            else {
                m_offerUpdateLevelCounter++;
                m_offerPrice1 = m_priceDepth;
                m_offerSize1 = size;
                PROD1_market[11] = m_priceDepth;
                PROD1_market[12] = size;
                if (m_insertOffer1 != 1) {
                    createOffer1(m_priceDepth, size);
                    m_insertOffer1 = 1;
                }
            }
        }

        if (position == 2) {
            if (side == 1) {
                m_bidUpdateLevelCounter++;
                m_bidPrice2 = m_priceDepth;
                m_bidSize2 = size;
                PROD1_market[9] = m_priceDepth;
                PROD1_market[10] = size;
                if (m_insertBid2 != 1) {
                    createBid2(m_priceDepth, size);
                    m_insertBid2 = 1;
                }
            }
            else {         
                m_offerUpdateLevelCounter++;
                m_offerPrice2 = m_priceDepth;
                m_offerSize2 = size;
                PROD1_market[13] = m_priceDepth;
                PROD1_market[14] = size;
                if (m_insertOffer2 != 1) {
                    createOffer2(m_priceDepth, size);
                    m_insertOffer2 = 1;
                }
            }
        }

        if (position == 3) {
            if (side == 1) {
                m_bidUpdateLevelCounter++;
                m_bidPrice3 = m_priceDepth;
                m_bidSize3 = size;
                PROD1_market[15] = m_priceDepth;
                PROD1_market[16] = size;
                if (m_insertBid3 != 1) {
                    createBid3(m_priceDepth, size);
                    m_insertBid3 = 1;
                }
            }

            else {         
                m_offerUpdateLevelCounter++;
                m_offerPrice3 = m_priceDepth;
                m_offerSize3 = size;
                PROD1_market[17] = m_priceDepth;
                PROD1_market[18] = size;
                if (m_insertOffer3 != 1) {
                    createOffer3(m_priceDepth, size);
                    m_insertOffer3 = 1;
                }
            }
        }
        if (position == 4) {
            if (side == 1) {
                m_bidUpdateLevelCounter++;
                m_bidPrice4 = m_priceDepth;
                m_bidSize4 = size;
                PROD1_market[19] = m_priceDepth;
                PROD1_market[20] = size;
                if (m_insertBid4 != 1) {
                    createBid4(m_priceDepth, size);
                    m_insertBid4 = 1;
                }
            }

            else {         
                m_offerUpdateLevelCounter++;
                m_offerPrice4 = m_priceDepth;
                m_offerSize4 = size;
                PROD1_market[21] = m_priceDepth;
                PROD1_market[22] = size;
                if (m_insertOffer4 != 1) {
                    createOffer4(m_priceDepth, size);
                    m_insertOffer4 = 1;
                }
            }
        }
        if (position == 5) {
            if (side == 1) {
                m_bidUpdateLevelCounter++;
                m_bidPrice5 = m_priceDepth;
                m_bidSize5 = size;
                PROD1_market[48] = m_priceDepth;
                PROD1_market[49] = size;
                if (m_insertBid5 != 1) {
                    createBid5(m_priceDepth, size);
                    m_insertBid5 = 1;
                }
            }
            else {         
                m_offerUpdateLevelCounter++;
                m_offerPrice5 = m_priceDepth;
                m_offerSize5 = size;
                PROD1_market[50] = m_priceDepth;
                PROD1_market[51] = size;
                if (m_insertOffer5 != 1) {
                    createOffer5(m_priceDepth, size);
                    m_insertOffer5 = 1;
                }
            }
        }

        if (m_bookCreated == 1) {
            if ( (m_bidUpdateLevelCounter == m_rows) || (m_offerUpdateLevelCounter == m_rows) ) {
                    desireBookUpdate();
            }
        }
        else {
            if (m_insertBid0 && m_insertOffer0 && m_insertBid1 && m_insertOffer1
                    && m_insertBid2 && m_insertOffer2 && m_insertBid3 && m_insertOffer3 
                    && m_insertBid4 && m_insertOffer4 && m_insertBid5 && m_insertOffer5) {
                m_bookCreated = 1;
                cout << "\nAll PriceLevel Objects Instantiated\n\n";
            }
        }
    }
}

//////////////////////////////////////////////////////
//                                                  //
//            Create Order Books                    //
//                                                  //
//////////////////////////////////////////////////////
void Boomer::createBid0(double price, int size)
{
    key0 = 0;

    PriceLevel Bid0;
    Bid0.price = price;
    Bid0.size = size;
    Bid0.position = 0;
    m_priceMap.insert(PriceMap::value_type(key0, Bid0));
}
void Boomer::createBid1(double price, int size)
{
    key2 = 2;

    PriceLevel Bid1;
    Bid1.price = price;
    Bid1.size = size;
    Bid1.position = 2;
    m_priceMap.insert(PriceMap::value_type(key2, Bid1));
}
void Boomer::createBid2(double price, int size)
{
    key4 = 4;

    PriceLevel Bid2;
    Bid2.price = price;
    Bid2.size = size;
    Bid2.position = 4;
    m_priceMap.insert(PriceMap::value_type(key4, Bid2));
}
void Boomer::createBid3(double price, int size)
{
    key6 = 6;

    PriceLevel Bid3;
    Bid3.price = price;
    Bid3.size = size;
    Bid3.position = 6;
    m_priceMap.insert(PriceMap::value_type(key6, Bid3));
}
void Boomer::createBid4(double price, int size)
{
    key8 = 8;

    PriceLevel Bid4;
    Bid4.price = price;
    Bid4.size = size;
    Bid4.position = 8;
    m_priceMap.insert(PriceMap::value_type(key8, Bid4));
}
void Boomer::createBid5(double price, int size)
{
    key10 = 10;

    PriceLevel Bid5;
    Bid5.price = price;
    Bid5.size = size;
    Bid5.position = 10;
    m_priceMap.insert(PriceMap::value_type(key10, Bid5));
}
void Boomer::createOffer0(double price, int size)
{
    key1 = 1;

    PriceLevel Offer0;
    Offer0.price = price;
    Offer0.size = size;
    Offer0.position = 1;
    m_priceMap.insert(PriceMap::value_type(key1, Offer0));
}
void Boomer::createOffer1(double price, int size)
{
    key3 = 3;

    PriceLevel Offer1;
    Offer1.price = price;
    Offer1.size = size;
    Offer1.position = 3;
    m_priceMap.insert(PriceMap::value_type(key3, Offer1));
}
void Boomer::createOffer2(double price, int size)
{
    key5 = 5;

    PriceLevel Offer2;
    Offer2.price = price;
    Offer2.size = size;
    Offer2.position = 5;
    m_priceMap.insert(PriceMap::value_type(key5, Offer2));
}
void Boomer::createOffer3(double price, int size)
{
    key7 = 7;

    PriceLevel Offer3;
    Offer3.price = price;
    Offer3.size = size;
    Offer3.position = 7;
    m_priceMap.insert(PriceMap::value_type(key7, Offer3));
}
void Boomer::createOffer4(double price, int size)
{
    key9 = 9;

    PriceLevel Offer4;
    Offer4.price = price;
    Offer4.size = size;
    Offer4.position = 9;
    m_priceMap.insert(PriceMap::value_type(key9, Offer4));
}
void Boomer::createOffer5(double price, int size)
{
    key11 = 11;

    PriceLevel Offer5;
    Offer5.price = price;
    Offer5.size = size;
    Offer5.position = 9;
    m_priceMap.insert(PriceMap::value_type(key11, Offer5));
}
void Boomer::error(const int id, const int errorCode, const IBString errorString)
{
    if ( (errorCode != 202) ) //&& (errorCode != 161) && (errorCode != 135) )
	    printf( "Error id=%d, errorCode=%d, msg=%s\n", id, errorCode, errorString.c_str());
	if( id == -1 && errorCode == 1100) {
        cout << "\n\t *!#*!#*!#*!# LOST CONNECTION TO IB *!#*!#*!#*!#\n";
		disconnect();
    }
}

void Boomer::currentTime( long time)
{
	if ( m_state == ST_IDLE) {

		time_t now = ::time(NULL);
		m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;

		m_state = ST_IDLE;
	}
}

void Boomer::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
void Boomer::tickSize( TickerId tickerId, TickType field, int size) {}
void Boomer::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
											 double optPrice, double pvDividend,
											 double gamma, double vega, double theta, double undPrice) {}
void Boomer::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void Boomer::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void Boomer::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
							   double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void Boomer::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
void Boomer::openOrderEnd() {}
void Boomer::winError( const IBString &str, int lastError) {}
void Boomer::connectionClosed() {}
void Boomer::updateAccountValue(const IBString& key, const IBString& val,
										  const IBString& currency, const IBString& accountName) {}
void Boomer::updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName){}
void Boomer::updateAccountTime(const IBString& timeStamp) {}
void Boomer::accountDownloadEnd(const IBString& accountName) {}
void Boomer::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void Boomer::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void Boomer::contractDetailsEnd( int reqId) {}
void Boomer::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void Boomer::execDetailsEnd( int reqId) {}

//void Boomer::updateMktDepth(TickerId id, int position, int operation, int side,
//									  double price, int size) {}
void Boomer::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
										int side, double price, int size) {}
void Boomer::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void Boomer::managedAccounts( const IBString& accountsList) {}
void Boomer::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void Boomer::historicalData(TickerId reqId, const IBString& date, double open, double high,
									  double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void Boomer::scannerParameters(const IBString &xml) {}
void Boomer::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
	   const IBString &distance, const IBString &benchmark, const IBString &projection,
	   const IBString &legsStr) {}
void Boomer::scannerDataEnd(int reqId) {}
void Boomer::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
								   long volume, double wap, int count) {}
void Boomer::fundamentalData(TickerId reqId, const IBString& data) {}
void Boomer::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void Boomer::tickSnapshotEnd(int reqId) {}
void Boomer::marketDataType(TickerId reqId, int marketDataType) {}
void Boomer::commissionReport( const CommissionReport& commissionReport) {}
void Boomer::position( const IBString& account, const Contract& contract, int position, double avgCost) {}
void Boomer::positionEnd() {}
void Boomer::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
void Boomer::accountSummaryEnd( int reqId) {}

}

