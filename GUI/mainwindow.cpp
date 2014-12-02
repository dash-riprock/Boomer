#include "mainwindow.h"
#include "strategy.h"
#include "market.h"
#include "doubleclickbutton.h"
#include <QObject>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QThread>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <iostream>
using std::cout; using std::endl;

MainWindow::MainWindow(std::shared_ptr<IB::Boomer> client_ptr)
    : client_(client_ptr)
    , host_("")
    , port_(7496)
    , clientId_(3)
    , insideSize_(0)
    , outsideSize_(0)
    , buffer_(1.0)
    , depth_(0)
    , profit_(1.0)
    , stop_(1.0)
    , support_(0)
    , rows_(3)
{
    widget.setupUi(this);

    QDoubleClickButton* cancelButton = new QDoubleClickButton(this);
    connect(cancelButton, SIGNAL(doubleClicked()), this, SLOT(on_doubleClicked()));
    QFont font;
    font.setPointSize(7);
    cancelButton->setFont(font);
    cancelButton->setText("Cancel");
    QGridLayout *codeLayout = new QGridLayout;
    codeLayout->addWidget(cancelButton,10,15,4,4);


    // Buttons
    QObject::connect(widget.connectButton, SIGNAL(clicked()), this, SLOT(connectClicked()));
    QObject::connect(widget.disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectClicked()));
    QObject::connect(widget.boomerButton, SIGNAL(clicked()), this, SLOT(boomerClicked()));
    QObject::connect(widget.updateButton, SIGNAL(clicked()), this, SLOT(updateClicked()));
    QObject::connect(widget.marketButton, SIGNAL(clicked()), this, SLOT(marketClicked()));
    QObject::connect(widget.resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
    QObject::connect(widget.stopButton, SIGNAL(clicked()), this, SLOT(stopClicked()));
    QObject::connect(widget.startButton, SIGNAL(clicked()), this, SLOT(startClicked()));

    // Debug
    QObject::connect(widget.debugCheckBox, SIGNAL(toggled(bool)), this, SLOT(debugChecked(bool)));


    // Spin Boxes
    QObject::connect(widget.profitDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_profitDoubleSpinBoxChange(double)));
    QObject::connect(widget.stopDoubleSpinBox, SIGNAL(valueChanged(double)),this, SLOT(on_stopDoubleSpinBoxChange(double)));
    QObject::connect(widget.insideSizeSpinBox, SIGNAL(valueChanged(int)),this, SLOT(on_insideSizeSpinBoxChange(int)));
    QObject::connect(widget.outsideSizeSpinBox, SIGNAL(valueChanged(int)),this, SLOT(on_outsideSizeSpinBoxChange(int)));
    QObject::connect(widget.depthSpinBox, SIGNAL(valueChanged(int)),this, SLOT(on_depthSpinBoxChange(int)));
    QObject::connect(widget.bufferDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_bufferDoubleSpinBoxChange(double)));
    QObject::connect(widget.supportSpinBox, SIGNAL(valueChanged(int)),this, SLOT(on_supportSpinBoxChange(int)));
    QObject::connect(widget.rowSpinBox, SIGNAL(valueChanged(int)),this, SLOT(on_rowSpinBoxChange(int)));



    cout << "Main Window object constructor" << endl;
}

MainWindow::~MainWindow()
{
    cout << "Closing GUI" << endl;
}

// BIDS
void MainWindow::myPositionSet_0(int dubs){ widget.myPositionLineEdit_0->setText(QString::number(dubs));}
void MainWindow::myBidsSet_0(int dubs){ widget.myBidsLineEdit_0->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_0(double dubs){ widget.bidSizeLineEdit_0->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_0(double dubs){ widget.bidPriceLineEdit_0->setText(QString::number(dubs, 'f', 1));}
void MainWindow::bidPriceSet_0(double dubs){ widget.bidPriceLineEdit_0->setText(QString::number(dubs));}
void MainWindow::myPositionSet_2(int dubs){ widget.myPositionLineEdit_2->setText(QString::number(dubs));}
void MainWindow::myBidsSet_2(int dubs){ widget.myBidsLineEdit_2->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_2(double dubs){ widget.bidSizeLineEdit_2->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_2(double dubs){ widget.bidPriceLineEdit_2->setText(QString::number(dubs, 'f', 2));}
void MainWindow::bidPriceSet_2(double dubs){ widget.bidPriceLineEdit_2->setText(QString::number(dubs));}
void MainWindow::myPositionSet_4(int dubs){ widget.myPositionLineEdit_4->setText(QString::number(dubs));}
void MainWindow::myBidsSet_4(int dubs){ widget.myBidsLineEdit_4->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_4(double dubs){ widget.bidSizeLineEdit_4->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_4(double dubs){ widget.bidPriceLineEdit_4->setText(QString::number(dubs, 'f', 3));}
void MainWindow::bidPriceSet_4(double dubs){ widget.bidPriceLineEdit_4->setText(QString::number(dubs));}
void MainWindow::myPositionSet_6(int dubs){ widget.myPositionLineEdit_6->setText(QString::number(dubs));}
void MainWindow::myBidsSet_6(int dubs){ widget.myBidsLineEdit_6->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_6(double dubs){ widget.bidSizeLineEdit_6->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_6(double dubs){ widget.bidPriceLineEdit_6->setText(QString::number(dubs, 'f', 4));}
void MainWindow::bidPriceSet_6(double dubs){ widget.bidPriceLineEdit_6->setText(QString::number(dubs));}
void MainWindow::myPositionSet_8(int dubs){ widget.myPositionLineEdit_8->setText(QString::number(dubs));}
void MainWindow::myBidsSet_8(int dubs){ widget.myBidsLineEdit_8->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_8(double dubs){ widget.bidSizeLineEdit_8->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_8(double dubs){ widget.bidPriceLineEdit_8->setText(QString::number(dubs, 'f', 5));}
void MainWindow::bidPriceSet_8(double dubs){ widget.bidPriceLineEdit_8->setText(QString::number(dubs));}
void MainWindow::myPositionSet_10(int dubs){ widget.myPositionLineEdit_10->setText(QString::number(dubs));}
void MainWindow::myBidsSet_10(int dubs){ widget.myBidsLineEdit_10->setText(QString::number(dubs));}
void MainWindow::bidSizeSet_10(double dubs){ widget.bidSizeLineEdit_10->setText(QString::number(dubs));}
//void MainWindow::bidPriceSet_10(double dubs){ widget.bidPriceLineEdit_10->setText(QString::number(dubs, 'f', 6));}
void MainWindow::bidPriceSet_10(double dubs){ widget.bidPriceLineEdit_10->setText(QString::number(dubs));}

// Offers
void MainWindow::myPositionSet_1(int dubs){ widget.myPositionLineEdit_1->setText(QString::number(dubs));}
void MainWindow::myOffersSet_1(int dubs){ widget.myOffersLineEdit_1->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_1(double dubs){ widget.offerSizeLineEdit_1->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_1(double dubs){ widget.offerPriceLineEdit_1->setText(QString::number(dubs, 'f', 1));}
void MainWindow::offerPriceSet_1(double dubs){ widget.offerPriceLineEdit_1->setText(QString::number(dubs));}
void MainWindow::myPositionSet_3(int dubs){ widget.myPositionLineEdit_3->setText(QString::number(dubs));}
void MainWindow::myOffersSet_3(int dubs){ widget.myOffersLineEdit_3->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_3(double dubs){ widget.offerSizeLineEdit_3->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_3(double dubs){ widget.offerPriceLineEdit_3->setText(QString::number(dubs, 'f', 2));}
void MainWindow::offerPriceSet_3(double dubs){ widget.offerPriceLineEdit_3->setText(QString::number(dubs));}
void MainWindow::myPositionSet_5(int dubs){ widget.myPositionLineEdit_5->setText(QString::number(dubs));}
void MainWindow::myOffersSet_5(int dubs){ widget.myOffersLineEdit_5->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_5(double dubs){ widget.offerSizeLineEdit_5->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_5(double dubs){ widget.offerPriceLineEdit_5->setText(QString::number(dubs, 'f', 3));}
void MainWindow::offerPriceSet_5(double dubs){ widget.offerPriceLineEdit_5->setText(QString::number(dubs));}
void MainWindow::myPositionSet_7(int dubs){ widget.myPositionLineEdit_7->setText(QString::number(dubs));}
void MainWindow::myOffersSet_7(int dubs){ widget.myOffersLineEdit_7->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_7(double dubs){ widget.offerSizeLineEdit_7->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_7(double dubs){ widget.offerPriceLineEdit_7->setText(QString::number(dubs, 'f', 4));}
void MainWindow::offerPriceSet_7(double dubs){ widget.offerPriceLineEdit_7->setText(QString::number(dubs));}
void MainWindow::myPositionSet_9(int dubs){ widget.myPositionLineEdit_9->setText(QString::number(dubs));}
void MainWindow::myOffersSet_9(int dubs){ widget.myOffersLineEdit_9->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_9(double dubs){ widget.offerSizeLineEdit_9->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_9(double dubs){ widget.offerPriceLineEdit_9->setText(QString::number(dubs, 'f', 5));}
void MainWindow::offerPriceSet_9(double dubs){ widget.offerPriceLineEdit_9->setText(QString::number(dubs));}
void MainWindow::myPositionSet_11(int dubs){ widget.myPositionLineEdit_11->setText(QString::number(dubs));}
void MainWindow::myOffersSet_11(int dubs){ widget.myOffersLineEdit_11->setText(QString::number(dubs));}
void MainWindow::offerSizeSet_11(double dubs){ widget.offerSizeLineEdit_11->setText(QString::number(dubs));}
//void MainWindow::offerPriceSet_11(double dubs){ widget.offerPriceLineEdit_11->setText(QString::number(dubs, 'f', 6));}
void MainWindow::offerPriceSet_11(double dubs){ widget.offerPriceLineEdit_11->setText(QString::number(dubs));}

// current position
void MainWindow::currentPositionSet(int dubs){ widget.currentPositionLineEdit->setText(QString::number(dubs));}

// ticks
void MainWindow::upTickSet(int dubs){ widget.upTickLineEdit->setText(QString::number(dubs));}
void MainWindow::downTickSet(int dubs){ widget.downTickLineEdit->setText(QString::number(dubs));}

// PnL
void MainWindow::PnLSet(int dubs){ widget.PnLLineEdit->setText(QString::number(dubs));}

// deadPrices
void MainWindow::bidDeadPriceSet(double dubs){ widget.bidDeadPriceLineEdit->setText(QString::number(dubs));}
void MainWindow::offerDeadPriceSet(double dubs){ widget.offerDeadPriceLineEdit->setText(QString::number(dubs));}
//void MainWindow::bidDeadPriceSet(double dubs){ widget.bidDeadPriceLineEdit->setText(QString::number(dubs, 'f', 5));}
//void MainWindow::offerDeadPriceSet(double dubs){ widget.offerDeadPriceLineEdit->setText(QString::number(dubs, 'f', 5));}


void MainWindow::boomerClicked()
{
    QThread* strategyThread = new QThread;
    Strategy* strategy = new Strategy(client_);
    strategy->moveToThread(strategyThread);
    connect(strategyThread, SIGNAL(started()), strategy, SLOT(runStrat()));
    connect(strategy, SIGNAL(finished()), strategyThread, SLOT(quit()));
    connect(strategy, SIGNAL(finished()), strategy, SLOT(deleteLater()));
    connect(strategyThread, SIGNAL(finished()), strategyThread, SLOT(deleteLater()));
    strategyThread->start();
}

void MainWindow::marketClicked()
{
    // Thread 1
    QThread* marketThread = new QThread;
    Market* market = new Market(client_);

    connect(market, SIGNAL(bidSizeUpdate_0(double)), this, SLOT(bidSizeSet_0(double)));
    connect(market, SIGNAL(bidPriceUpdate_0(double)), this, SLOT(bidPriceSet_0(double)));
    connect(market, SIGNAL(myBidsUpdate_0(int)), this, SLOT(myBidsSet_0(int)));
    connect(market, SIGNAL(myPositionUpdate_0(int)), this, SLOT(myPositionSet_0(int)));
    connect(market, SIGNAL(bidSizeUpdate_2(double)), this, SLOT(bidSizeSet_2(double)));
    connect(market, SIGNAL(bidPriceUpdate_2(double)), this, SLOT(bidPriceSet_2(double)));
    connect(market, SIGNAL(myBidsUpdate_2(int)), this, SLOT(myBidsSet_2(int)));
    connect(market, SIGNAL(myPositionUpdate_2(int)), this, SLOT(myPositionSet_2(int)));
    connect(market, SIGNAL(bidSizeUpdate_4(double)), this, SLOT(bidSizeSet_4(double)));
    connect(market, SIGNAL(bidPriceUpdate_4(double)), this, SLOT(bidPriceSet_4(double)));
    connect(market, SIGNAL(myBidsUpdate_4(int)), this, SLOT(myBidsSet_4(int)));
    connect(market, SIGNAL(myPositionUpdate_4(int)), this, SLOT(myPositionSet_4(int)));
    connect(market, SIGNAL(bidSizeUpdate_6(double)), this, SLOT(bidSizeSet_6(double)));
    connect(market, SIGNAL(bidPriceUpdate_6(double)), this, SLOT(bidPriceSet_6(double)));
    connect(market, SIGNAL(myBidsUpdate_6(int)), this, SLOT(myBidsSet_6(int)));
    connect(market, SIGNAL(myPositionUpdate_6(int)), this, SLOT(myPositionSet_6(int)));
    connect(market, SIGNAL(bidSizeUpdate_8(double)), this, SLOT(bidSizeSet_8(double)));
    connect(market, SIGNAL(bidPriceUpdate_8(double)), this, SLOT(bidPriceSet_8(double)));
    connect(market, SIGNAL(myBidsUpdate_8(int)), this, SLOT(myBidsSet_8(int)));
    connect(market, SIGNAL(myPositionUpdate_8(int)), this, SLOT(myPositionSet_8(int)));
    connect(market, SIGNAL(bidSizeUpdate_10(double)), this, SLOT(bidSizeSet_10(double)));
    connect(market, SIGNAL(bidPriceUpdate_10(double)), this, SLOT(bidPriceSet_10(double)));
    connect(market, SIGNAL(myBidsUpdate_10(int)), this, SLOT(myBidsSet_10(int)));
    connect(market, SIGNAL(myPositionUpdate_10(int)), this, SLOT(myPositionSet_10(int)));

    connect(market, SIGNAL(offerPriceUpdate_1(double)), this, SLOT(offerPriceSet_1(double)));
    connect(market, SIGNAL(offerSizeUpdate_1(double)), this, SLOT(offerSizeSet_1(double)));
    connect(market, SIGNAL(myOffersUpdate_1(int)), this, SLOT(myOffersSet_1(int)));
    connect(market, SIGNAL(myPositionUpdate_1(int)), this, SLOT(myPositionSet_1(int)));
    connect(market, SIGNAL(offerPriceUpdate_3(double)), this, SLOT(offerPriceSet_3(double)));
    connect(market, SIGNAL(offerSizeUpdate_3(double)), this, SLOT(offerSizeSet_3(double)));
    connect(market, SIGNAL(myOffersUpdate_3(int)), this, SLOT(myOffersSet_3(int)));
    connect(market, SIGNAL(myPositionUpdate_3(int)), this, SLOT(myPositionSet_3(int)));
    connect(market, SIGNAL(offerPriceUpdate_5(double)), this, SLOT(offerPriceSet_5(double)));
    connect(market, SIGNAL(offerSizeUpdate_5(double)), this, SLOT(offerSizeSet_5(double)));
    connect(market, SIGNAL(myOffersUpdate_5(int)), this, SLOT(myOffersSet_5(int)));
    connect(market, SIGNAL(myPositionUpdate_5(int)), this, SLOT(myPositionSet_5(int)));
    connect(market, SIGNAL(offerPriceUpdate_7(double)), this, SLOT(offerPriceSet_7(double)));
    connect(market, SIGNAL(offerSizeUpdate_7(double)), this, SLOT(offerSizeSet_7(double)));
    connect(market, SIGNAL(myOffersUpdate_7(int)), this, SLOT(myOffersSet_7(int)));
    connect(market, SIGNAL(myPositionUpdate_7(int)), this, SLOT(myPositionSet_7(int)));
    connect(market, SIGNAL(offerPriceUpdate_9(double)), this, SLOT(offerPriceSet_9(double)));
    connect(market, SIGNAL(offerSizeUpdate_9(double)), this, SLOT(offerSizeSet_9(double)));
    connect(market, SIGNAL(myOffersUpdate_9(int)), this, SLOT(myOffersSet_9(int)));
    connect(market, SIGNAL(myPositionUpdate_9(int)), this, SLOT(myPositionSet_9(int)));
    connect(market, SIGNAL(offerPriceUpdate_11(double)), this, SLOT(offerPriceSet_11(double)));
    connect(market, SIGNAL(offerSizeUpdate_11(double)), this, SLOT(offerSizeSet_11(double)));
    connect(market, SIGNAL(myOffersUpdate_11(int)), this, SLOT(myOffersSet_11(int)));
    connect(market, SIGNAL(myPositionUpdate_11(int)), this, SLOT(myPositionSet_11(int)));


    connect(market, SIGNAL(currentPositionUpdate(int)), this, SLOT(currentPositionSet(int)));
    connect(market, SIGNAL(PnLUpdate(int)), this, SLOT(PnLSet(int)));

    connect(market, SIGNAL(upTickUpdate(int)), this, SLOT(upTickSet(int)));
    connect(market, SIGNAL(downTickUpdate(int)), this, SLOT(downTickSet(int)));

    connect(market, SIGNAL(bidDeadPriceUpdate(double)), this, SLOT(bidDeadPriceSet(double)));
    connect(market, SIGNAL(offerDeadPriceUpdate(double)), this, SLOT(offerDeadPriceSet(double)));


    market->moveToThread(marketThread);
    connect(marketThread, SIGNAL(started()), market, SLOT(getMarket()));
    connect(market, SIGNAL(finished()), marketThread, SLOT(quit()));
    connect(market, SIGNAL(finished()), market, SLOT(deleteLater()));
    connect(marketThread, SIGNAL(finished()), marketThread, SLOT(deleteLater()));
    marketThread->start();
}

void MainWindow::startClicked()
{
    client_->start();
}

void MainWindow::resetClicked()
{
    client_->resetShit();
}

void MainWindow::stopClicked()
{
    client_->endLife();
}

void MainWindow::connectClicked()
{
    if (!client_->isConnected()) {
        cout << "\nconnectClicked()" << endl;
        cout << "clientId_: " << clientId_ << endl;
        client_->connect(host_, port_, clientId_);}
}

void MainWindow::disconnectClicked()
{
    if (client_->isConnected()) {
        client_->disconnect();}
    if (client_->isConnected()) {
        cout << "Still connected bro." << endl;}
    if (!client_->isConnected()) {
        cout << "Successfully disconnected." << endl;}
}

void MainWindow::updateClicked()
{
    client_->updateAttributes(insideSize_, outsideSize_, buffer_, depth_, profit_, stop_, support_, rows_);
}

void MainWindow::on_doubleClicked()
{
    cout << "CANCEL EVERYTHING" << endl;
    client_->cancelAll();
}

void MainWindow::debugChecked(bool mode)
{
    if (mode) {
        cout << "Debug checked." << endl;
        client_->enableDebug(1);}
    else {
        cout << "Unchecked debug." << endl;
        client_->enableDebug(-1); }
}

void MainWindow::on_bufferDoubleSpinBoxChange(double b) { buffer_ = b; }
void MainWindow::on_profitDoubleSpinBoxChange(double p) { profit_ = p; }
void MainWindow::on_stopDoubleSpinBoxChange(double l) { stop_ = l; }
void MainWindow::on_insideSizeSpinBoxChange(int s) { insideSize_ = s; }
void MainWindow::on_outsideSizeSpinBoxChange(int o) { outsideSize_ = o; }
void MainWindow::on_depthSpinBoxChange(int d) { depth_ = d; }
void MainWindow::on_supportSpinBoxChange(int x) { support_ = x; }
void MainWindow::on_rowSpinBoxChange(int r) { rows_ = r; }

