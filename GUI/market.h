#ifndef MARKET_H
#define MARKET_H

#include <QObject>
#include <QLineEdit>
#include <math.h>
#include <src/Boomer.h>
#include <ui_mainwindow.h>
#include "mainwindow.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout; using std::endl;

class Market : public QObject
{
    Q_OBJECT
public:
    Market(std::shared_ptr<IB::Boomer>);
    ~Market();

signals:
    void finished();
    void error(QString err);

    void bidSizeUpdate_0(double newValue);
    void bidPriceUpdate_0(double newValue);
    void myBidsUpdate_0(int newValue);
    void myPositionUpdate_0(int newValue);
    void bidSizeUpdate_2(double newValue);
    void bidPriceUpdate_2(double newValue);
    void myBidsUpdate_2(int newValue);
    void myPositionUpdate_2(int newValue);
    void bidSizeUpdate_4(double newValue);
    void bidPriceUpdate_4(double newValue);
    void myBidsUpdate_4(int newValue);
    void myPositionUpdate_4(int newValue);
    void bidSizeUpdate_6(double newValue);
    void bidPriceUpdate_6(double newValue);
    void myBidsUpdate_6(int newValue);
    void myPositionUpdate_6(int newValue);
    void bidSizeUpdate_8(double newValue);
    void bidPriceUpdate_8(double newValue);
    void myBidsUpdate_8(int newValue);
    void myPositionUpdate_8(int newValue);
    void bidSizeUpdate_10(double newValue);
    void bidPriceUpdate_10(double newValue);
    void myBidsUpdate_10(int newValue);
    void myPositionUpdate_10(int newValue);


    void offerPriceUpdate_1(double newValue);
    void offerSizeUpdate_1(double newValue);
    void myOffersUpdate_1(int newValue);
    void myPositionUpdate_1(int newValue);
    void offerPriceUpdate_3(double newValue);
    void offerSizeUpdate_3(double newValue);
    void myOffersUpdate_3(int newValue);
    void myPositionUpdate_3(int newValue);
    void offerPriceUpdate_5(double newValue);
    void offerSizeUpdate_5(double newValue);
    void myOffersUpdate_5(int newValue);
    void myPositionUpdate_5(int newValue);
    void offerPriceUpdate_7(double newValue);
    void offerSizeUpdate_7(double newValue);
    void myOffersUpdate_7(int newValue);
    void myPositionUpdate_7(int newValue);
    void offerPriceUpdate_9(double newValue);
    void offerSizeUpdate_9(double newValue);
    void myOffersUpdate_9(int newValue);
    void myPositionUpdate_9(int newValue);
    void offerPriceUpdate_11(double newValue);
    void offerSizeUpdate_11(double newValue);
    void myOffersUpdate_11(int newValue);
    void myPositionUpdate_11(int newValue);

    void upTickUpdate(int newValue);
    void downTickUpdate(int newValue);

    void PnLUpdate(int newValue);

    void currentPositionUpdate(int newValue);
    void bidDeadPriceUpdate(double newValue);
    void offerDeadPriceUpdate(double newValue);

public slots:
    void getMarket();

private:
    std::shared_ptr<IB::Boomer> marketClient_;
    vector<double> mkt_vec;

    double bidSize_0;
    double bidPrice_0;
    int myBids_0;
    int myPosition_0;
    double bidSize_2;
    double bidPrice_2;
    int myBids_2;
    int myPosition_2;
    double bidSize_4;
    double bidPrice_4;
    int myBids_4;
    int myPosition_4;
    double bidSize_6;
    double bidPrice_6;
    int myBids_6;
    int myPosition_6;
    double bidSize_8;
    double bidPrice_8;
    int myBids_8;
    int myPosition_8;
    double bidSize_10;
    double bidPrice_10;
    int myBids_10;
    int myPosition_10;

    double offerSize_1;
    double offerPrice_1;
    int myOffers_1;
    int myPosition_1;
    double offerSize_3;
    double offerPrice_3;
    int myOffers_3;
    int myPosition_3;
    double offerSize_5;
    double offerPrice_5;
    int myOffers_5;
    int myPosition_5;
    double offerSize_7;
    double offerPrice_7;
    int myOffers_7;
    int myPosition_7;
    double offerSize_9;
    double offerPrice_9;
    int myOffers_9;
    int myPosition_9;
    double offerSize_11;
    double offerPrice_11;
    int myOffers_11;
    int myPosition_11;

    int currentPosition;
    double bidDeadPrice;
    double offerDeadPrice;

    int upTick;
    int downTick;

    int PnL;
};

#endif // MARKET_H
