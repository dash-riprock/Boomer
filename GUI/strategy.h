#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
#include <src/Boomer.h>
#include <iostream>
using std::cout; using std::endl;

class Strategy : public QObject
{
    Q_OBJECT
public:
    Strategy(std::shared_ptr<IB::Boomer>);
    ~Strategy();

signals:
    void finished();
    void error(QString err);

public slots:
    void runStrat();

private:
    std::shared_ptr<IB::Boomer> strategyClient_;
};

#endif // STRATEGY_H
