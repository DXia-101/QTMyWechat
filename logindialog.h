#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QFile>
#include "qdom.h"

namespace Ui {
class LoginDialog;
}

class QUdpSocket;
//登录界面
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginPushButton_clicked();
//    void showWeiChatWindow();
    void processPendingDatagram();

private:
    Ui::LoginDialog *ui;
    MainWindow * weiChatWindow;
    QDomDocument mydoc;
    QUdpSocket *sender;
    QUdpSocket *receiver;
};

#endif // LOGINDIALOG_H
