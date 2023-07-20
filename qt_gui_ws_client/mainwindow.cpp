#include <QUrl>
#include <QDebug>

#include <QWebSocketHandshakeOptions>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TODO: разобраться что такое origin
    ws = new QWebSocket("", QWebSocketProtocol::Version13, this);

    // web sock
    {
        connect(ws, &QWebSocket::connected, []() {
            qDebug() << "QWebSocket::connected";
        });
        connect(ws, &QWebSocket::disconnected, []() {
            qDebug() << "QWebSocket::disconnected";
        });
        connect(ws, &QWebSocket::errorOccurred, [](QAbstractSocket::SocketError error) {
            qDebug() << "QWebSocket::errorOccurred" << error;
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// -----------------------------------------------------------------------

void MainWindow::on_pushBtnCon_clicked()
{
    ws->open(QUrl("ws://127.0.0.1:47777"));
}

void MainWindow::on_pushBtnSend_clicked()
{
    ws->sendTextMessage(ui->plainTextEdit->toPlainText());
}

