#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWebView>

class MainWindow : public QWebView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void addJSObject();
    void rebootCommand();
    void appExit();
    void sendUid(QString);
};

#endif // MAINWINDOW_H
