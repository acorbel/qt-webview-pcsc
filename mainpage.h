#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWebPage>
class MainPage : public QWebPage
{
public:
    MainPage(QWidget *parent = 0);
    ~MainPage();

protected:
    QString userAgentForUrl ( const QUrl & url ) const;


};

#endif // MAINPAGE_H
