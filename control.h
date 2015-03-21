#ifndef CONTROL_H
#define CONTROL_H
#include "QThread"
#include "mainwindow.h"

class Control : public QThread
{
    Q_OBJECT

public:
    Control(MainWindow *parent = 0);

public slots:
    void startRead(QString, QString);
    void stopRead();


private:
       void run();

protected slots:

signals:
    void quitApp();
    void rebootCommand();
    void sendUid(QString);
};

#endif // CONTROL_H
