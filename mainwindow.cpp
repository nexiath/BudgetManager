#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BudgetModel.h"
#include "BudgetItem.h"
#include "WalletInitDialog.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFileDialog>
#include <QPainter>
#include <QTextDocument>

void MainWindow::exportData() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter les données"), "", tr("Fichiers texte (*.txt);;Tous les fichiers (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier pour l'écriture."));
        return;
    }

    QTextStream out(&file);

    out << tr("Détails des paiements:\n");
    for (int i = 0; i < model->rowCount(); ++i) {
        QString description = model->data(model->index(i, 0), Qt::DisplayRole).toString();
        double amount = model->data(model->index(i, 1), Qt::DisplayRole).toDouble();
        QString date = model->data(model->index(i, 2), Qt::DisplayRole).toString();
        QString category = BudgetItem::categoryToString(static_cast<BudgetItem::Category>(model->data(model->index(i, 3), BudgetModel::CategoryRole).toInt()));

        out << tr("Titre: ") << description << ", ";
        out << tr("Montant: ") << amount << ", ";
        out << tr("Date: ") << date << ", ";
        out << tr("Catégorie: ") << category << "\n";
    }

    double finalAmount = walletAmount;
    out << tr("Budget final: ") << finalAmount << "\n";

    file.close();
    QMessageBox::information(this, tr("Exportation réussie"), tr("Les données ont été exportées avec succès."));
}

void MainWindow::exportPortfolio() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter le portefeuille"), "", tr("JPEG (*.jpeg);;Tous les fichiers (*)"));
    if (fileName.isEmpty()) return;

    QImage compositeImage(800, 1200, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&compositeImage);
    painter.fillRect(compositeImage.rect(), Qt::white); // Fond blanc
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap profilePic = ui->profilePictureLabel->pixmap(Qt::ReturnByValue);
    if (!profilePic.isNull()) {
        QRect profilePicRect(650, 10, 140, 140);
        painter.drawPixmap(profilePicRect, profilePic.scaled(profilePicRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    QPixmap chartPixmap = chartView->grab();
    painter.drawPixmap(QRect(0, 160, 800, 300), chartPixmap);

    QFont titleFont("Arial", 18, QFont::Bold);
    QFont subTitleFont("Arial", 14, QFont::Bold);
    QFont contentFont("Arial", 12);

    painter.setFont(titleFont);
    painter.drawText(QRect(0, 480, 800, 30), Qt::AlignCenter, tr("Dépenses et Budget"));

    int startY = 520;
    painter.setFont(subTitleFont);
    for (int i = 0; i < model->rowCount(); ++i) {
        auto index = model->index(i, 0);
        QString description = model->data(index, Qt::DisplayRole).toString();
        double amount = model->data(model->index(i, 1), Qt::DisplayRole).toDouble();
        QString date = model->data(model->index(i, 2), Qt::DisplayRole).toString();
        QString category = BudgetItem::categoryToString(static_cast<BudgetItem::Category>(model->data(model->index(i, 3), BudgetModel::CategoryRole).toInt()));

        QString expenseDetails = tr("%1 - %2: %3 €, %4").arg(date, category, QString::number(amount, 'f', 2), description);
        painter.drawText(QRect(10, startY, 780, 20), Qt::AlignLeft, expenseDetails);
        startY += 20;
    }

    painter.setFont(contentFont);
    painter.drawText(QRect(0, startY + 20, 800, 30), Qt::AlignCenter, tr("Budget final: %1 €").arg(walletAmount));

    painter.end();

    if (!fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
        fileName += ".jpeg";
    }
    compositeImage.save(fileName);
}







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), walletAmount(0.0) {
    ui->setupUi(this);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::exportData);
    connect(ui->actionNouveau_Portefeuille, &QAction::triggered, this, &MainWindow::onNouveauPortefeuilleTriggered);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exportPortfolio);



    ui->profilePictureLabel->setAcceptDrops(true);


    model = new BudgetModel(this);
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setDefaultSectionSize(32);
    ui->tableView->setSortingEnabled(true);

    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartContainer->setLayout(new QVBoxLayout());
    ui->chartContainer->layout()->addWidget(chartView);

    walletAmountLabel = findChild<QLabel*>("walletAmountLabel");
    if (!walletAmountLabel) {
        qWarning("MainWindow: QLabel for wallet amount not found!");
        return;
    }

    ui->profilePictureLabel->setAcceptDrops(true);
    ui->profilePictureLabel->setText(tr("Glissez une image ici"));

    showWalletInitDialog();

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        QString filePath = urlList.at(0).toLocalFile();
        QPixmap image(filePath);

        ui->profilePictureLabel->setPixmap(image.scaled(ui->profilePictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::updateWalletAmountDisplay() {
    walletAmountLabel->setText(tr("Montant du portefeuille : %L1 €").arg(walletAmount, 0, 'f', 2));
}

void MainWindow::showWalletInitDialog() {
    WalletInitDialog initDialog(this);
    if (initDialog.exec() == QDialog::Accepted) {
        walletAmount = initDialog.getInitialAmount();
        updateWalletAmountDisplay();
    }
}

void MainWindow::onAddButtonClicked() {
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Ajouter un élément de budget"));
    QFormLayout form(&dialog);

    QLineEdit *descriptionEdit = new QLineEdit(&dialog);
    QDoubleSpinBox *amountEdit = new QDoubleSpinBox(&dialog);
    amountEdit->setMaximum(999999.99);
    QDateEdit *dateEdit = new QDateEdit(&dialog);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDate(QDate::currentDate());
    QComboBox *categoryComboBox = new QComboBox(&dialog);
    categoryComboBox->addItem(tr("Restaurant"), QVariant(BudgetItem::Restaurant));
    categoryComboBox->addItem(tr("Shopping"), QVariant(BudgetItem::Shopping));
    categoryComboBox->addItem(tr("Transport"), QVariant(BudgetItem::Transport));
    categoryComboBox->addItem(tr("Loisirs"), QVariant(BudgetItem::Loisirs));
    categoryComboBox->addItem(tr("Courses"), QVariant(BudgetItem::Courses));

    QCheckBox *urgentCheck = new QCheckBox(tr("Urgent"), &dialog);
    QPushButton *addImageButton = new QPushButton(tr("Ajouter une image"), &dialog);
    QPixmap image;

    connect(addImageButton, &QPushButton::clicked, [&]() {
        QString filePath = QFileDialog::getOpenFileName(&dialog, tr("Sélectionner une image"), QString(), tr("Fichiers d'images (*.png *.jpg *.jpeg)"));
        if (!filePath.isEmpty()) {
            image.load(filePath);
        }
    });

    form.addRow(new QLabel(tr("Description :")), descriptionEdit);
    form.addRow(new QLabel(tr("Montant :")), amountEdit);
    form.addRow(new QLabel(tr("Date :")), dateEdit);
    form.addRow(new QLabel(tr("Catégorie :")), categoryComboBox);
    form.addRow(urgentCheck);
    form.addRow(addImageButton);

    QPushButton *addButton = new QPushButton(tr("Ajouter"), &dialog);
    form.addRow(addButton);
    connect(addButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    if (dialog.exec() == QDialog::Accepted) {
        bool urgent = urgentCheck->isChecked();
        auto category = static_cast<BudgetItem::Category>(categoryComboBox->currentData().toInt());
        BudgetItem newItem(descriptionEdit->text(), amountEdit->value(), dateEdit->date(), category, image, urgent);
        model->addBudgetItem(newItem);

        walletAmount -= amountEdit->value();
        updateWalletAmountDisplay();
        updatePieChart();
    }
}

void MainWindow::onDeleteButtonClicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, tr("Aucune sélection"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int row = currentIndex.row();
    double amount = model->data(model->index(row, 1), Qt::DisplayRole).toDouble();

    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Confirmation de suppression"), tr("Êtes-vous sûr de vouloir supprimer cet élément ?"), QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        model->removeBudgetItem(row);
        walletAmount += amount;
        updateWalletAmountDisplay();
        updatePieChart();
    }
}

void MainWindow::onNouveauPortefeuilleTriggered() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Créer un nouveau portefeuille"), tr("Êtes-vous sûr de vouloir créer un nouveau portefeuille ? Toutes les données actuelles seront perdues."), QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        model->clearBudgetItems();
        walletAmount = 0.0;
        showWalletInitDialog();
        updateWalletAmountDisplay();
        updatePieChart();

        ui->profilePictureLabel->clear();
        ui->profilePictureLabel->setText(tr("Glissez une image ici"));

        ui->profilePictureLabel->setStyleSheet("QLabel { border: 2px dashed #D2B48C; }");
    }
}

void MainWindow::setupPieChart() {
}

void MainWindow::updatePieChart() {
    chartView->chart()->removeAllSeries();
    auto *series = new QPieSeries();
    QMap<BudgetItem::Category, double> sumsByCategory;

    for (int i = 0; i < model->rowCount(); ++i) {
        auto category = static_cast<BudgetItem::Category>(model->data(model->index(i, 3), BudgetModel::CategoryRole).toInt());
        double amount = model->data(model->index(i, 1), Qt::DisplayRole).toDouble();
        sumsByCategory[category] += amount;
    }

    for (auto category : sumsByCategory.keys()) {
        QString categoryName = BudgetItem::categoryToString(category);
        double amount = sumsByCategory[category];
        qDebug() << "Adding to series:" << categoryName << amount;
        series->append(categoryName + QString(": %1 €").arg(amount, 0, 'f', 2), amount);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Dépenses par Catégorie"));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
    chartView->update();

    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
    }
}

