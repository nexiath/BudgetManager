#ifndef WALLETINITDIALOG_H
#define WALLETINITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class WalletInitDialog : public QDialog {
    Q_OBJECT
public:
    explicit WalletInitDialog(QWidget *parent = nullptr);

    double getInitialAmount() const;

private:
    QLineEdit *amountEdit;
};

#endif // WALLETINITDIALOG_H
