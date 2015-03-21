#include "control.h"
#include "mainwindow.h"
#include <QDebug>
#include "reader.h"
#include "winscard.h"
#include "wintypes.h"

QString callback, threadNb;

SCARDCONTEXT hContext;
SCARDHANDLE hCard;
DWORD dwActiveProtocol;
DWORD dwState, dwProtocol, dwAtrLen, dwReaderLen, dwReaders, dwSendLength, dwRecvLength;
SCARD_IO_REQUEST pioRecvPci;
BYTE pbRecvBuffer[16];
BYTE pbSendBuffer[] = { 0xFF, 0xCA, 0x00, 0x00, 0x00 };
LPSTR mszReaders;
BYTE *pbAtr = NULL;
char *pcReader = NULL;
LONG rv;
bool contextG, onRun;
QString uid;
int i;
MainWindow* mainWin;

Control::Control(MainWindow *parent): QThread()
{
    qDebug() << "Etablissement du contexte ..."<<endl;
    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
    if(rv == 0) contextG = true;
    onRun = false;
    mainWin = parent;
}

void Control::run(){
    for(;;)
    {
        if(contextG == true && onRun == true) {
            rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
            mszReaders = (LPSTR)malloc(sizeof(char)*dwReaders);
            rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);
            if(rv == 0){
                qDebug() << "Décodeur : " << mszReaders;
                rv = SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0, &hCard, &dwActiveProtocol);
                if(rv == 0){
                    qDebug() << "Carte présente";

                    dwSendLength = sizeof(pbSendBuffer);
                    dwRecvLength = sizeof(pbRecvBuffer);
                    rv = SCardTransmit(hCard, SCARD_PCI_T0, pbSendBuffer, dwSendLength, &pioRecvPci, pbRecvBuffer, &dwRecvLength);
                    uid = "";

                    for(i=0; i<dwRecvLength; i++)
                    {
                        if(QString::number(pbRecvBuffer[i], 16).length() < 2) uid += "0";
                        uid += QString::number(pbRecvBuffer[i], 16).toUpper();
                    }

                    qDebug() << "UID : " << uid << endl;
                    if(onRun == true) emit(sendUid(callback + "(\"" + uid + "\","+ threadNb + ")"));
                    stopRead();

                } else qDebug() << "!!! Pas de carte présente !!!" << endl;
            } else qDebug() << "!!! Connexion au décodeur impossible !!!" <<endl;
        } else {
            if(contextG != true) qDebug() << "!!! Le contexte n'a pas été établi !!!" << endl;
        }

        msleep(250);
    }
}

void Control::startRead(QString dataCallback, QString dataThread)
{
    if(onRun == false){
        qDebug() << "Read started" << endl;
        callback = dataCallback;
        threadNb = dataThread;
        onRun = true;
    } else {
        qDebug() << "Read already started" << endl;
    }
}

void Control::stopRead()
{
    qDebug() << "Read stoped" << endl;
    onRun = false;
}
