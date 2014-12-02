#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <src/Boomer.cpp>
#include <src/Boomer.h>
#include <Everything/EClient.h>
#include <Everything/EClientSocketBase.cpp>
#include <Everything/EClientSocketBase.h>
#include <Everything/EClientSocketBaseImpl.h>
#include <Everything/EWrapper.h>
#include <Everything/IBString.h>
#include <Everything/Pending.h>
#include <Everything/PriceLevel.h>
#include <Everything/EPosixClientSocket.cpp>
#include <Everything/EPosixClientSocket.h>
#include <Everything/EPosixClientSocketPlatform.h>
#include <Everything/shared_ptr.h>
#include <Everything/Execution.h>
#include <Everything/Order.h>
#include <Everything/ScannerSubscription.h>
#include <Everything/TagValue.h>
#include <Everything/TwsSocketClientErrors.h>
#include <QDebug>

std::shared_ptr<IB::Boomer> client;

int main(int argc, char *argv[])
{
    client.reset(new IB::Boomer()); // calls class function

    QApplication a(argc, argv);

    MainWindow w(client);
    w.show();

    return a.exec();
}
