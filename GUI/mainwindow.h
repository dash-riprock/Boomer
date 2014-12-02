#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "doubleclickbutton.h"
#include <ui_mainwindow.h>
#include <src/Boomer.h>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<IB::Boomer>);
    ~MainWindow();

public slots:
    void connectClicked();
    void disconnectClicked();
    void boomerClicked();
    void updateClicked();
    void marketClicked();
    void resetClicked();
    void stopClicked();
    void startClicked();
    void debugChecked(bool mode);

    void on_doubleClicked();

    // only one set of these
    void on_profitDoubleSpinBoxChange(double p);
    void on_stopDoubleSpinBoxChange(double l);
    void on_insideSizeSpinBoxChange(int s);
    void on_outsideSizeSpinBoxChange(int o);
    void on_depthSpinBoxChange(int d);
    void on_bufferDoubleSpinBoxChange(double b);
    void on_supportSpinBoxChange(int x);
    void on_rowSpinBoxChange(int r);

    void bidSizeSet_0(double newValue);
    void bidPriceSet_0(double newValue);
    void myBidsSet_0(int newValue);
    void myPositionSet_0(int newValue);
    void bidSizeSet_2(double newValue);
    void bidPriceSet_2(double newValue);
    void myBidsSet_2(int newValue);
    void myPositionSet_2(int newValue);
    void bidSizeSet_4(double newValue);
    void bidPriceSet_4(double newValue);
    void myBidsSet_4(int newValue);
    void myPositionSet_4(int newValue);
    void bidSizeSet_6(double newValue);
    void bidPriceSet_6(double newValue);
    void myBidsSet_6(int newValue);
    void myPositionSet_6(int newValue);
    void bidSizeSet_8(double newValue);
    void bidPriceSet_8(double newValue);
    void myBidsSet_8(int newValue);
    void myPositionSet_8(int newValue);
    void bidSizeSet_10(double newValue);
    void bidPriceSet_10(double newValue);
    void myBidsSet_10(int newValue);
    void myPositionSet_10(int newValue);

    void offerPriceSet_1(double newValue);
    void offerSizeSet_1(double newValue);
    void myOffersSet_1(int newValue);
    void myPositionSet_1(int newValue);
    void offerPriceSet_3(double newValue);
    void offerSizeSet_3(double newValue);
    void myOffersSet_3(int newValue);
    void myPositionSet_3(int newValue);
    void offerPriceSet_5(double newValue);
    void offerSizeSet_5(double newValue);
    void myOffersSet_5(int newValue);
    void myPositionSet_5(int newValue);
    void offerPriceSet_7(double newValue);
    void offerSizeSet_7(double newValue);
    void myOffersSet_7(int newValue);
    void myPositionSet_7(int newValue);
    void offerPriceSet_9(double newValue);
    void offerSizeSet_9(double newValue);
    void myOffersSet_9(int newValue);
    void myPositionSet_9(int newValue);
    void offerPriceSet_11(double newValue);
    void offerSizeSet_11(double newValue);
    void myOffersSet_11(int newValue);
    void myPositionSet_11(int newValue);

    void currentPositionSet(int newValue);
    void bidDeadPriceSet(double newValue);
    void offerDeadPriceSet(double newValue);

    void upTickSet(int newValue);
    void downTickSet(int newValue);

    void PnLSet(int newValue);

private:

    QDoubleClickButton* cancelButton;

    QSpinBox* insideSizeSpinBox;
    QSpinBox* outsideSizeSpinBox;
    QSpinBox* depthSpinBox;
    QSpinBox* supportSpinBox;
    QSpinBox* rowSpinBox;


    QDoubleSpinBox* bufferDoubleSpinBox;
    QDoubleSpinBox* profitDoubleSpinBox;
    QDoubleSpinBox* stopDoubleSpinBox;

    QLineEdit* bidSizeLineEdit_0;
    QLineEdit* bidPriceLineEdit_0;
    QLineEdit* myBidsLineEdit_0;
    QLineEdit* myPositionLineEdit_0;
    QLineEdit* bidSizeLineEdit_2;
    QLineEdit* bidPriceLineEdit_2;
    QLineEdit* myBidsLineEdit_2;
    QLineEdit* myPositionLineEdit_2;
    QLineEdit* bidSizeLineEdit_4;
    QLineEdit* bidPriceLineEdit_4;
    QLineEdit* myBidsLineEdit_4;
    QLineEdit* myPositionLineEdit_4;
    QLineEdit* bidSizeLineEdit_6;
    QLineEdit* bidPriceLineEdit_6;
    QLineEdit* myBidsLineEdit_6;
    QLineEdit* myPositionLineEdit_6;
    QLineEdit* bidSizeLineEdit_8;
    QLineEdit* bidPriceLineEdit_8;
    QLineEdit* myBidsLineEdit_8;
    QLineEdit* myPositionLineEdit_8;
    QLineEdit* bidSizeLineEdit_10;
    QLineEdit* bidPriceLineEdit_10;
    QLineEdit* myBidsLineEdit_10;
    QLineEdit* myPositionLineEdit_10;

    QLineEdit* offerPriceLineEdit_1;
    QLineEdit* offerSizeLineEdit_1;
    QLineEdit* myOffersLineEdit_1;
    QLineEdit* myPositionLineEdit_1;
    QLineEdit* offerPriceLineEdit_3;
    QLineEdit* offerSizeLineEdit_3;
    QLineEdit* myOffersLineEdit_3;
    QLineEdit* myPositionLineEdit_3;
    QLineEdit* offerPriceLineEdit_5;
    QLineEdit* offerSizeLineEdit_5;
    QLineEdit* myOffersLineEdit_5;
    QLineEdit* myPositionLineEdit_5;
    QLineEdit* offerPriceLineEdit_7;
    QLineEdit* offerSizeLineEdit_7;
    QLineEdit* myOffersLineEdit_7;
    QLineEdit* myPositionLineEdit_7;
    QLineEdit* offerPriceLineEdit_9;
    QLineEdit* offerSizeLineEdit_9;
    QLineEdit* myOffersLineEdit_9;
    QLineEdit* myPositionLineEdit_9;
    QLineEdit* offerPriceLineEdit_11;
    QLineEdit* offerSizeLineEdit_11;
    QLineEdit* myOffersLineEdit_11;
    QLineEdit* myPositionLineEdit_11;

    QLineEdit* currentPositionLineEdit;
    QLineEdit* bidDeadPriceLineEdit;
    QLineEdit* offerDeadPriceLineEdit;

    QLineEdit* upTickLineEdit;
    QLineEdit* downTickLineEdit;

    QLineEdit* PnLLineEdit;

    QCheckBox* debugCheckBox;

    Ui::MainWindow widget;
    std::shared_ptr<IB::Boomer> client_;
    const char* host_;
    unsigned int port_;
    int clientId_;
    int insideSize_;
    int outsideSize_;
    double buffer_;
    int depth_;
    double profit_;
    double stop_;
    int support_;
    int rows_;
};

#endif // MAINWINDOW_H
