#include "mainwindow.h"
#include <QWebFrame>
#include "control.h"
#include <QDebug>
#include "mainpage.h"

Control* control;
QUrl startURL;
QString fullCb;
MainPage* mainpage;
MainWindow::MainWindow(QWidget *parent): QWebView(parent)
{

    control = new Control();
    control->start();
    MainPage *mainpage = new MainPage(this);
    this->setPage(mainpage);
    startURL = QUrl("http://192.168.50.2/back");
    setUrl(startURL);


    connect(page()->mainFrame(), SIGNAL(loadFinished(bool)),this, SLOT(addJSObject()));
    connect(control, SIGNAL(rebootCommand()),this, SLOT(rebootCommand()));
    connect(control, SIGNAL(quitApp()),this, SLOT(appExit()));
    connect(control, SIGNAL(sendUid(QString)),this, SLOT(sendUid(QString)));


}

MainWindow::~MainWindow()
{

}
void MainWindow::addJSObject() {
    control->stopRead();
    page()->mainFrame()->addToJavaScriptWindowObject(QString("multipass"), control);
    page()->mainFrame()->evaluateJavaScript("initMultipass()");
    qDebug() << "Multipass initialized" << endl;
}


void MainWindow::rebootCommand() {
    QWebSettings::clearMemoryCaches();
    setUrl(startURL);

}


void MainWindow::appExit() {
    exit(515);
}

void MainWindow::sendUid(QString fullCb)
{
    qDebug() << fullCb;
    page()->mainFrame()->evaluateJavaScript(fullCb);
}
