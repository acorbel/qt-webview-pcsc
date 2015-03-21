#include "mainpage.h"

MainPage::MainPage(QWidget *parent): QWebPage(parent)
{
}


MainPage::~MainPage()
{

}


QString MainPage::userAgentForUrl ( const QUrl & url ) const
   {
       return "Multipass";
   }
