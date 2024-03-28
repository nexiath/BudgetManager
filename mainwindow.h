#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QLabel>
#include "budgetmodel.h"
#include "walletinitdialog.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exportData();
    void exportPortfolio();

private slots:
    void onAddButtonClicked();
    void setupPieChart();
    void onNouveauPortefeuilleTriggered();
    void updatePieChart();


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::MainWindow *ui;
    BudgetModel *model;
    QLabel *walletAmountLabel;
    double walletAmount;
    void onDeleteButtonClicked();
    QtCharts::QChartView *chartView;

    void setupUI();
    void showWalletInitDialog();
    void updateWalletAmountDisplay();
};
#endif // MAINWINDOW_H
