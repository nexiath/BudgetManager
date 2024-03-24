#ifndef BUDGETMODEL_H
#define BUDGETMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "BudgetItem.h"
#include <QString>
#include <QObject>

class BudgetModel : public QAbstractTableModel {
    Q_OBJECT

public:
    void removeBudgetItem(int row);
    void clearBudgetItems();

    explicit BudgetModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    void addBudgetItem(const BudgetItem &item);

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    enum Role {
        DescriptionRole = Qt::UserRole + 1,
        AmountRole,
        DateRole,
        UrgentRole,
        CategoryRole
    };




private:
    QList<BudgetItem> m_items;
};

#endif // BUDGETMODEL_H
