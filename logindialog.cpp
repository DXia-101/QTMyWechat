#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QtXml>
#include <QtNetwork>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(54545,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginPushButton_clicked()
{
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out<<ui->usrLineEdit->text();
    out<<ui->pwdLineEdit->text();
    qDebug()<<ui->usrLineEdit->text()<<" "<<ui->pwdLineEdit->text();
    sender->writeDatagram(datagram,datagram.size(),QHostAddress::Broadcast,45454);
    connect(receiver,&QUdpSocket::readyRead,this,&LoginDialog::processPendingDatagram);
}

//void LoginDialog::showWeiChatWindow()
//{
//    QFile file("../MyChat/userlog.xml");
//    if(!file.open(QIODevice::ReadOnly)) return;
//    QString errorStr;
//    int errorLine, errorCol;
//    if(!mydoc.setContent(&file,true,&errorStr,&errorLine,&errorCol))
//    {
//        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
//        file.close();
//        return ;
//    }
//    QDomElement root = mydoc.documentElement();
//    if (root.hasChildNodes())
//        {
//            QDomNodeList userList = root.childNodes();
//            bool exist = false;
//            for (int i = 0; i < userList.count(); i++)
//            {
//                QDomNode user = userList.at(i);
//                QDomNodeList record = user.childNodes();
//                QString uname = record.at(0).toElement().text();
//                QString pword = record.at(1).toElement().text();
//                if (uname == ui->usrLineEdit->text())
//                {
//                    exist = true;
//                    if (!(pword == ui->pwdLineEdit->text()))
//                    {
//                        QMessageBox::warning(0, QObject::tr("提示"), "口令错！请重新输入。");
//                        ui->pwdLineEdit->clear();
//                        ui->pwdLineEdit->setFocus();
//                        return;
//                    }
//                }
//            }
//            if (!exist)
//            {
//                QMessageBox::warning(0, QObject::tr("提示"), "此用户不存在！请重新输入。");
//                ui->usrLineEdit->clear();
//                ui->pwdLineEdit->clear();
//                ui->usrLineEdit->setFocus();
//                return;
//            }
//            weiChatWindow = new MainWindow(0);
//            weiChatWindow->setWindowTitle(ui->usrLineEdit->text());
//            weiChatWindow->show();
//    }
//}

//接收数据
void LoginDialog::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size());
        qDebug()<<datagram;
        const QString WindowTitleName = ui->usrLineEdit->text();
        qDebug()<<WindowTitleName;
        if(datagram=="canlogin")
        {
            weiChatWindow = new MainWindow(0);
            weiChatWindow->setWindowTitle(WindowTitleName);
            weiChatWindow->setAccessibleName(WindowTitleName);
            weiChatWindow->show();
            disconnect(receiver,&QUdpSocket::readyRead,this,&LoginDialog::processPendingDatagram);
        }
        else if(datagram =="pwdfalse")
        {
            QMessageBox::warning(0, QObject::tr("提示"), "口令错！请重新输入。");
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
            return;
        }
        else{
            qDebug()<<"receive nouser"<<datagram;
            QMessageBox::warning(0, QObject::tr("提示"), "此用户不存在！请重新输入。");
            ui->usrLineEdit->clear();
            ui->pwdLineEdit->clear();
            ui->usrLineEdit->setFocus();
            return;
        }
    }
}

