#ifndef boomer_h__INCLUDED
#define boomer_h__INCLUDED

#include "EWrapper.h"
#include "Pending.h"
#include "PriceLevel.h"

#include <ctime>
#include <memory>
#include <unordered_map>
#include <map>
#include <utility>
#include <list>
using std::list;
#include <vector>
using std::vector;
#include <stdio.h> //printf()

namespace IB {

class EPosixClientSocket;

enum State {

    ST_REQ_MKT_DEPTH_PROD1,
    ST_REQ_MKT_DEPTH_ACK_PROD1,
	ST_IDLE
};

class Boomer : public EWrapper
{
public:
	Boomer();
	~Boomer();

	void processMessages();
    void runBoomer();
    void updateAttributes(int _insideSize, int _outsideSize, double _buffer, 
            int _depth, double _profit, double _stop, int _support, int _rows);
	void reqCurrentTime();
    void resetShit();

    void start();   // begin placing orders brah

    int checkLife();
    void endLife();
    void getPnL();
    void enableDebug(int check);

    // sends data to GUI
    vector<double> returnMarket_1();

	bool connect(const char * host, unsigned int port, int clientId);
	void disconnect() const;
	bool isConnected() const;

	std::shared_ptr<EPosixClientSocket> m_pClient;

    // unordered map containing pending order objects created in placeOrder fcn
    typedef std::unordered_map<OrderId, Pending> OrderMapPending;
    OrderMapPending m_orderMapPending;
    std::unordered_map<OrderId, Pending>::iterator m_pend;

    // unordered map containing order objects
    typedef std::unordered_map<OrderId, Pending> OrderMap;
    OrderMap m_orderMap;
    std::unordered_map<OrderId, Pending>::iterator m_got;

    // unordered map containing Filled Orders 
    typedef std::unordered_map<OrderId, Pending> OrderMapFilled;
    OrderMapFilled m_orderMapFilled;
    std::unordered_map<OrderId, Pending>::iterator m_fil;

    // unordered map closed out orders 
    typedef std::unordered_map<OrderId, Pending> OrderMapDunzo;
    OrderMapDunzo m_orderMapDunzo;
    std::unordered_map<OrderId, Pending>::iterator m_dun;

    // unordered map containing PriceLevel objects
    typedef std::unordered_map<PriceKey, PriceLevel> PriceMap;
    PriceMap m_priceMap;
    std::unordered_map<PriceKey, PriceLevel>::iterator m_iter;

    void placeOrder(long conId, const IBString &exchange, const IBString &action, 
            const IBString &oType, int oSize, double firePrice, double buySell,
            int cover, int coveredFor);

    int searchRescue(double live);  // return number of live orders at price "live"
    int searchFilled(double fillPrice); // returns number of open fills at price "fillPrice"
    void findOrders(double price, int i);   // find orders and corr levels
    void findOpenOrders(double price, int i);   // orders not closed/stopped out 
    void searchDestroy(double die);

    void searchStop(double stopPrice, int lean, int position);
    void strategyReset();

    void cancelAll();

//    void desireBookUpdate(int side, int position, double price, int size);
    void desireBookUpdate();
    void orderBookUpdate();

private:
    int m_depthRequest;
    double m_priceOrder;     // conversion for orderStatus callback 
    double m_priceDepth;    // conversion for updateMktDepth callback

    int m_price1, m_price2, m_price3;   // reverse convert
    double m_hold;

    ///////////////////
    int m_life;
    int m_PnL;
    bool m_debug;
    int m_bookCreated;

    int m_bidUpdateLevelCounter;
    int m_offerUpdateLevelCounter;

    int m_pending;
    int m_living;
    int m_filled;

    int m_buySell;
      
    //// attributes set in GUI /////
    double m_stopLoss;
    double m_profit;
    int m_insideSize;
    int m_insideSizeBid;
    int m_insideSizeOffer;
    int m_outsideSize;
    int m_outsideSizeBid;
    int m_outsideSizeOffer;
    double m_buffer;
    int m_support;
    int m_depth;
    int m_rows;

    /// position management data members
    int m_absPosition;
    int m_currentPosition;
    int m_lastPosition;
    int m_deltaPosition;

    int m_thisPosition;
    int m_filPosition;

    int m_thatPosition;
    int m_dunPosition;

    int m_firstFill;

    double m_deadPrice;
    double m_bidDeadPrice;
    double m_offerDeadPrice;
    double m_lifePrice;
    int m_lean;
    int m_stoppedOut;

    int m_upTick, m_downTick;
    double m_firstBid, m_firstOffer;

	State m_state;
    TickerId m_tickerId;
	OrderId m_orderId;
    int m_requestId;

	time_t m_sleepDeadline;
	time_t m_requestDelay;

    int m_start;

    int m_bidSize, m_offerSize; 

    int m_existsFound;
    int m_open;         // floating orders
    int m_filledOpen;   // filled but not closed
    int m_fireSize;
    int m_fireBuySell;  // -1 is cancel, +1 is place more

    double buyerSeller;
    double byeCell;     // for float after fill
    int floatSize;      // for float after fill

    IBString genericTicks;
    IBString actionJackson;
    IBString actionB;

    void reqMktDepth_PROD1(int rows);
    void reqMktDepthAck_PROD1();
    TickerId tickerId_PROD1;
    TickerId tickerIdDepth_PROD1;
    vector<double> PROD1_market {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};

    /// data members store incomming order book data
    double m_bidPrice0;
    double m_bidPrice1;
    double m_bidPrice2;
    double m_bidPrice3;
    double m_bidPrice4;
    double m_bidPrice5;
    int m_bidSize0;
    int m_bidSize1;
    int m_bidSize2;
    int m_bidSize3;
    int m_bidSize4;
    int m_bidSize5;
    int m_bidDesires0;
    int m_bidDesires1;
    int m_bidDesires2;
    int m_bidDesires3;
    int m_bidDesires4;
    int m_bidDesires5;

    double m_offerPrice0; 
    double m_offerPrice1; 
    double m_offerPrice2; 
    double m_offerPrice3; 
    double m_offerPrice4; 
    double m_offerPrice5; 
    int m_offerSize0;
    int m_offerSize1;
    int m_offerSize2;
    int m_offerSize3;
    int m_offerSize4;
    int m_offerSize5;
    int m_offerDesires0;
    int m_offerDesires1;
    int m_offerDesires2;
    int m_offerDesires3;
    int m_offerDesires4;
    int m_offerDesires5;

    double m_bestBid;
    double m_bestOffer;

    PriceKey key0;
    PriceKey key1;
    PriceKey key2;
    PriceKey key3;
    PriceKey key4;
    PriceKey key5;
    PriceKey key6;
    PriceKey key7;
    PriceKey key8;
    PriceKey key9;
    PriceKey key10;
    PriceKey key11;

    void createBid0(double price, int size);
    void createBid1(double price, int size);
    void createBid2(double price, int size);
    void createBid3(double price, int size);
    void createBid4(double price, int size);
    void createBid5(double price, int size);

    void createOffer0(double price, int size);
    void createOffer1(double price, int size);
    void createOffer2(double price, int size);
    void createOffer3(double price, int size);
    void createOffer4(double price, int size);
    void createOffer5(double price, int size);

    int m_insertBid0;
    int m_insertBid1;
    int m_insertBid2;
    int m_insertBid3;
    int m_insertBid4;
    int m_insertBid5;
    int m_insertOffer0;
    int m_insertOffer1;
    int m_insertOffer2;
    int m_insertOffer3;
    int m_insertOffer4;
    int m_insertOffer5;

    ///////////// for mkt check print /////////////////
    int b0, b1, b2, b3, b4, b5;
    int o0, o1, o2, o3, o4, o5;

public:
	// events
	void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	void tickSize(TickerId tickerId, TickType field, int size);
	void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
		double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
	void tickGeneric(TickerId tickerId, TickType tickType, double value);
	void tickString(TickerId tickerId, TickType tickType, const IBString& value);
	void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry);
	void orderStatus(OrderId orderId, const IBString &status, int filled,
		int remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const IBString& whyHeld);
	void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
	void openOrderEnd();
	void winError(const IBString &str, int lastError);
	void connectionClosed();
	void updateAccountValue(const IBString& key, const IBString& val,
		const IBString& currency, const IBString& accountName);
	void updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName);
	void updateAccountTime(const IBString& timeStamp);
	void accountDownloadEnd(const IBString& accountName);
	void nextValidId(OrderId orderId);
	void contractDetails(int reqId, const ContractDetails& contractDetails);
	void bondContractDetails(int reqId, const ContractDetails& contractDetails);
	void contractDetailsEnd(int reqId);
	void execDetails(int reqId, const Contract& contract, const Execution& execution);
	void execDetailsEnd(int reqId);
	void error(const int id, const int errorCode, const IBString errorString);
	void updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size);
	void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
		int side, double price, int size);
	void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch);
	void managedAccounts(const IBString& accountsList);
	void receiveFA(faDataType pFaDataType, const IBString& cxml);
	void historicalData(TickerId reqId, const IBString& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps);
	void scannerParameters(const IBString &xml);
	void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
		const IBString &distance, const IBString &benchmark, const IBString &projection,
		const IBString &legsStr);
	void scannerDataEnd(int reqId);
	void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count);
	void currentTime(long time);
	void fundamentalData(TickerId reqId, const IBString& data);
	void deltaNeutralValidation(int reqId, const UnderComp& underComp);
	void tickSnapshotEnd(int reqId);
	void marketDataType(TickerId reqId, int marketDataType);
	void commissionReport( const CommissionReport& commissionReport);
	void position( const IBString& account, const Contract& contract, int position, double avgCost);
	void positionEnd();
	void accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency);
	void accountSummaryEnd( int reqId);

};

}
#endif
