#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QString>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile file("style.qss");
    if(file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString stylesheet = stream.readAll();
        app.setStyleSheet(stylesheet);
        file.close();
    }

    MainWindow w;
    w.show();

    return app.exec();
}

