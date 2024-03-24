#include "WalletInitDialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

WalletInitDialog::WalletInitDialog(QWidget *parent) : QDialog(parent), amountEdit(new QLineEdit(this)) {
    amountEdit->setPlaceholderText("Enter initial wallet amount");
    amountEdit->setStyleSheet("QLineEdit {"
                              "border: 2px solid #D2B48C;"
                              "border-radius: 5px;"
                              "padding: 5px;"
                              "background-color: #f5f5dc;"
                              "color: #8B4513;"
                              "}");

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    confirmButton->setStyleSheet("QPushButton {"
                                 "background-color: #D2B48C;"
                                 "border-radius: 5px;"
                                 "padding: 5px;"
                                 "color: white;"
                                 "font-weight: bold;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #A0522D;"
                                 "}");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(amountEdit);
    layout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &WalletInitDialog::accept);
}

double WalletInitDialog::getInitialAmount() const {
    return amountEdit->text().toDouble();
}
