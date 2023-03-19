#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include "qdom.h"

enum ChatMsgType{ChatMsg,OnLine,OffLine,SfileName,RefFile};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileSrvDlg;

//聊天界面
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //初始化界面
    void initMainWindow();
    void onLine(QString name,QString time);
    void offLine(QString name,QString time);
    void sendChatMsg(ChatMsgType msgType,QString rmtName = "");
    QString getLocHostIp();
    QString getLocChatMsg();
    void recvFileName(QString name,QString hostip,QString rmtname,QString filename);

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void recvAndProcessChatMsg();
    void getSfileName(QString);

    void on_sendPushButton_clicked();

    void on_transPushButton_clicked();

    void on_loginPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString myname = "";
    QUdpSocket *myUdpSocket;
    qint16 myUdpPort;
    QDomDocument myDoc;
    QString myFileName;
    FileSrvDlg *myfsrv;
};
#endif // MAINWINDOW_H
