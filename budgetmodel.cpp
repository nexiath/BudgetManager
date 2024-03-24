#include "BudgetModel.h"
#include <QBrush>
#include <QColor>
#include <algorithm>

BudgetModel::BudgetModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

int BudgetModel::rowCount(const QModelIndex & /* parent */) const {
    return m_items.count();
}

int BudgetModel::columnCount(const QModelIndex & /* parent */) const {
    return 4;
}

QVariant BudgetModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    const BudgetItem &item = m_items.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return item.description();
        case 1: return QString::number(item.amount(), 'f', 2);
        case 2: return item.date().toString("yyyy-MM-dd");
        case 3: return BudgetItem::categoryToString(item.category());
        }
        break;
    case CategoryRole:
        if (index.column() == 3) {
            return item.category();
        }
        break;
    case Qt::ForegroundRole:
        if (item.isUrgent()) {
            return QBrush(QColor("#D2691E"));
        } else {
            return QBrush(QColor("#8B4513"));
        }
        break;
    case Qt::DecorationRole:
        if (index.column() == 0) {
            return item.image().scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        break;
    }

    return QVariant();
}




QVariant BudgetModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
    case 0: return QStringLiteral("Titre");
    case 1: return QStringLiteral("Montant");
    case 2: return QStringLiteral("Date");
    case 3: return QStringLiteral("Categorie");
    default: return QVariant();
    }
}

void BudgetModel::sort(int column, Qt::SortOrder order) {
    beginResetModel();
    if (column == 0) {
        std::sort(m_items.begin(), m_items.end(), [order](const BudgetItem &a, const BudgetItem &b) {
            if (order == Qt::AscendingOrder) {
                return a.description() < b.description();
            } else {
                return a.description() > b.description();
            }
        });
    }
    endResetModel();
}

void BudgetModel::addBudgetItem(const BudgetItem &item) {
    int insertPosition = m_items.size();
    if (item.isUrgent()) {
        insertPosition = 0;
    }
    beginInsertRows(QModelIndex(), insertPosition, insertPosition);
    m_items.insert(insertPosition, item);
    endInsertRows();
}

void BudgetModel::removeBudgetItem(int row) {
    if (row < 0 || row >= m_items.size()) return;

    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeAt(row);
    endRemoveRows();
}
void BudgetModel::clearBudgetItems() {
    beginResetModel();
    m_items.clear();
    endResetModel();
}



