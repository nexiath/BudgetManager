#ifndef BUDGETITEM_H
#define BUDGETITEM_H


#include <QString>
#include <QDate>
#include <QPixmap>

class BudgetItem {
public:
    enum Category { Restaurant, Shopping, Transport, Loisirs, Courses, Autres };

    BudgetItem() = default;
    BudgetItem(const QString &description, double amount, const QDate &date, const Category& category, const QPixmap &image = QPixmap(), bool urgent = false)
        : m_description(description), m_amount(amount), m_date(date), m_category(category), m_image(image), m_urgent(urgent) {}

    QString description() const { return m_description; }
    double amount() const { return m_amount; }
    QDate date() const { return m_date; }
    Category category() const { return m_category; }
    QPixmap image() const { return m_image; }
    bool isUrgent() const { return m_urgent; }

    static QString categoryToString(Category category) {
        switch (category) {
        case Restaurant: return QObject::tr("Restaurant");
        case Shopping: return QObject::tr("Shopping");
        case Transport: return QObject::tr("Transport");
        case Loisirs: return QObject::tr("Loisirs");
        case Courses: return QObject::tr("Courses");
        default: return QObject::tr("Inconnu");
        }
    }

private:
    QString m_description;
    double m_amount;
    QDate m_date;
    Category m_category;
    QPixmap m_image;
    bool m_urgent;
};

#endif // BUDGETITEM_H
