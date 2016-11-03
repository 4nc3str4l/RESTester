#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QNetworkAccessManager>
#include <QtNetwork\QNetworkRequest>
#include <QtNetwork\QNetworkReply>
#include "highlighter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString getResponeHeaders(QNetworkReply *reply)
{
    QString headers("<br><strong>Code</strong>    :   "+ reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString() +"<br>");
    foreach(const QNetworkReply::RawHeaderPair& rawHeaderPair, reply->rawHeaderPairs())
    {
        headers.append("<br><strong>"+ rawHeaderPair.first +"</strong>    :   " + rawHeaderPair.second +"<br>");
    }
    return headers;
}

void MainWindow::on_pushButton_clicked()
{
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString(ui->txtQuery->text()) ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    Highlighter *highlighter = new Highlighter(ui->txtResponseHighlight->document());

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QByteArray data = reply->readAll();
        ui->txtHeaders->appendHtml(getResponeHeaders(reply));
        ui->txtResponseRaw->appendPlainText(data);
        ui->txtResponseHighlight->setPlainText(data);
        ui->txtPreview->appendHtml(data);
        delete reply;
    }
    else
    {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}


