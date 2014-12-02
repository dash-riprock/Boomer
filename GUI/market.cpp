#include "market.h"
#include "mainwindow.h"

Market::Market(std::shared_ptr<IB::Boomer> marketClient_ptr)
    : marketClient_(marketClient_ptr)
{
}

Market::~Market()
{
}

void Market::getMarket()
{
    while (marketClient_->checkLife() ) {
        mkt_vec = marketClient_->returnMarket_1();

        if (mkt_vec[0] != bidSize_0) {
            bidSize_0 = mkt_vec[0];
            emit bidSizeUpdate_0(bidSize_0);
        }
        if (mkt_vec[1] != bidPrice_0) {
            bidPrice_0 = mkt_vec[1];
            emit bidPriceUpdate_0(bidPrice_0);
        }
        if (mkt_vec[2] != offerPrice_1) {
            offerPrice_1 = mkt_vec[2];
            emit offerPriceUpdate_1(offerPrice_1);
        }
        if (mkt_vec[3] != offerSize_1) {
            offerSize_1 = mkt_vec[3];
            emit offerSizeUpdate_1(offerSize_1);
        }
        if (mkt_vec[4] != currentPosition) {
            currentPosition = mkt_vec[4];
            emit currentPositionUpdate(currentPosition);
        }
        if (mkt_vec[7] != bidPrice_2) {
            bidPrice_2 = mkt_vec[7];
            emit bidPriceUpdate_2(bidPrice_2);
        }
        if (mkt_vec[8] != bidSize_2) {
            bidSize_2 = mkt_vec[8];
            emit bidSizeUpdate_2(bidSize_2);
        }
        if (mkt_vec[9] != bidPrice_4) {
            bidPrice_4 = mkt_vec[9];
            emit bidPriceUpdate_4(bidPrice_4);
        }
        if (mkt_vec[10] != bidSize_4) {
            bidSize_4 = mkt_vec[10];
            emit bidSizeUpdate_4(bidSize_4);
        }
        if (mkt_vec[15] != bidPrice_6) {
            bidPrice_6 = mkt_vec[15];
            emit bidPriceUpdate_6(bidPrice_6);
        }
        if (mkt_vec[16] != bidSize_6) {
            bidSize_6 = mkt_vec[16];
            emit bidSizeUpdate_6(bidSize_6);
        }
        if (mkt_vec[19] != bidPrice_8) {
            bidPrice_8 = mkt_vec[19];
            emit bidPriceUpdate_8(bidPrice_8);
        }
        if (mkt_vec[20] != bidSize_8) {
            bidSize_8 = mkt_vec[20];
            emit bidSizeUpdate_8(bidSize_8);
        }
        if (mkt_vec[11] != offerPrice_3) {
            offerPrice_3 = mkt_vec[11];
            emit offerPriceUpdate_3(offerPrice_3);
        }
        if (mkt_vec[12] != offerSize_3) {
            offerSize_3 = mkt_vec[12];
            emit offerSizeUpdate_3(offerSize_3);
        }
        if (mkt_vec[13] != offerPrice_5) {
            offerPrice_5 = mkt_vec[13];
            emit offerPriceUpdate_5(offerPrice_5);
        }
        if (mkt_vec[14] != offerSize_5) {
            offerSize_5 = mkt_vec[14];
            emit offerSizeUpdate_5(offerSize_5);
        }
        if (mkt_vec[17] != offerPrice_7) {
            offerPrice_7 = mkt_vec[17];
            emit offerPriceUpdate_7(offerPrice_7);
        }
        if (mkt_vec[18] != offerSize_7) {
            offerSize_7 = mkt_vec[18];
            emit offerSizeUpdate_7(offerSize_7);
        }
        if (mkt_vec[21] != offerPrice_9) {
            offerPrice_9 = mkt_vec[21];
            emit offerPriceUpdate_9(offerPrice_9);
        }
        if (mkt_vec[22] != offerSize_9) {
            offerSize_9 = mkt_vec[22];
            emit offerSizeUpdate_9(offerSize_9);
        }
        if (mkt_vec[23] != myBids_0) {
            myBids_0 = mkt_vec[23];
            emit myBidsUpdate_0(myBids_0);
        }
        if (mkt_vec[25] != myBids_2) {
            myBids_2 = mkt_vec[25];
            emit myBidsUpdate_2(myBids_2);
        }
        if (mkt_vec[27] != myBids_4) {
            myBids_4 = mkt_vec[27];
            emit myBidsUpdate_4(myBids_4);
        }
        if (mkt_vec[29] != myBids_6) {
            myBids_6 = mkt_vec[29];
            emit myBidsUpdate_6(myBids_6);
        }
        if (mkt_vec[31] != myBids_8) {
            myBids_8 = mkt_vec[31];
            emit myBidsUpdate_8(myBids_8);
        }
        if (mkt_vec[24] != myOffers_1) {
            myOffers_1 = mkt_vec[24];
            emit myOffersUpdate_1(myOffers_1);
        }
        if (mkt_vec[26] != myOffers_3) {
            myOffers_3 = mkt_vec[26];
            emit myOffersUpdate_3(myOffers_3);
        }
        if (mkt_vec[28] != myOffers_5) {
            myOffers_5 = mkt_vec[28];
            emit myOffersUpdate_5(myOffers_5);
        }
        if (mkt_vec[30] != myOffers_7) {
            myOffers_7 = mkt_vec[30];
            emit myOffersUpdate_7(myOffers_7);
        }
        if (mkt_vec[32] != myOffers_9) {
            myOffers_9 = mkt_vec[32];
            emit myOffersUpdate_9(myOffers_9);
        }
        if (mkt_vec[33] != myPosition_0) {
            myPosition_0 = mkt_vec[33];
            emit myPositionUpdate_0(myPosition_0);
        }
        if (mkt_vec[35] != myPosition_2) {
            myPosition_2 = mkt_vec[35];
            emit myPositionUpdate_2(myPosition_2);
        }
        if (mkt_vec[37] != myPosition_4) {
            myPosition_4 = mkt_vec[37];
            emit myPositionUpdate_4(myPosition_4);
        }
        if (mkt_vec[39] != myPosition_6) {
            myPosition_6 = mkt_vec[39];
            emit myPositionUpdate_6(myPosition_6);
        }
        if (mkt_vec[41] != myPosition_8) {
            myPosition_8 = mkt_vec[41];
            emit myPositionUpdate_8(myPosition_8);
        }
        if (mkt_vec[34] != myPosition_1) {
            myPosition_1 = mkt_vec[34];
            emit myPositionUpdate_1(myPosition_1);
        }
        if (mkt_vec[36] != myPosition_3) {
            myPosition_3 = mkt_vec[36];
            emit myPositionUpdate_3(myPosition_3);
        }
        if (mkt_vec[38] != myPosition_5) {
            myPosition_5 = mkt_vec[38];
            emit myPositionUpdate_5(myPosition_5);
        }
        if (mkt_vec[40] != myPosition_7) {
            myPosition_7 = mkt_vec[40];
            emit myPositionUpdate_7(myPosition_7);
        }
        if (mkt_vec[42] != myPosition_9) {
            myPosition_9 = mkt_vec[42];
            emit myPositionUpdate_9(myPosition_9);
        }
        if (mkt_vec[43] != bidDeadPrice) {
            bidDeadPrice = mkt_vec[43];
            emit bidDeadPriceUpdate(bidDeadPrice);
        }
        if (mkt_vec[44] != offerDeadPrice) {
            offerDeadPrice = mkt_vec[44];
            emit offerDeadPriceUpdate(offerDeadPrice);
        }
        if (mkt_vec[45] != downTick) {
            downTick = mkt_vec[45];
            emit downTickUpdate(downTick);
        }
        if (mkt_vec[46] != upTick) {
            upTick = mkt_vec[46];
            emit upTickUpdate(upTick);
        }
        if (mkt_vec[47] != PnL) {
            PnL = mkt_vec[47];
            emit PnLUpdate(PnL);
        }

        ///////
        if (mkt_vec[48] != bidPrice_10) {
            bidPrice_10 = mkt_vec[48];
            emit bidPriceUpdate_10(bidPrice_10);
        }
        if (mkt_vec[49] != bidSize_10) {
            bidSize_10 = mkt_vec[49];
            emit bidSizeUpdate_10(bidSize_10);
        }
        if (mkt_vec[50] != offerPrice_11) {
            offerPrice_11 = mkt_vec[50];
            emit offerPriceUpdate_11(offerPrice_11);
        }
        if (mkt_vec[51] != offerSize_11) {
            offerSize_11 = mkt_vec[51];
            emit offerSizeUpdate_11(offerSize_11);
        }
        if (mkt_vec[52] != myBids_10) {
            myBids_10 = mkt_vec[52];
            emit myBidsUpdate_10(myBids_10);
        }
        if (mkt_vec[53] != myOffers_11) {
            myOffers_11 = mkt_vec[53];
            emit myOffersUpdate_11(myOffers_11);
        }
        if (mkt_vec[54] != myPosition_10) {
            myPosition_10 = mkt_vec[54];
            emit myPositionUpdate_10(myPosition_10);
        }
        if (mkt_vec[55] != myPosition_11) {
            myPosition_11 = mkt_vec[55];
            emit myPositionUpdate_11(myPosition_11);
        }
        //////
    }
    emit finished();
}
