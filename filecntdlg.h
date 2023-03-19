#ifndef FILECNTDLG_H
#define FILECNTDLG_H

#include <QDialog>
#include <QFile>
#include <QElapsedTimer>
#include <QTcpSocket>
#include <QHostAddress>

class QTcpSocket;

namespace Ui {
class FileCntDlg;
}

class FileCntDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileCntDlg(QWidget *parent = nullptr);
    ~FileCntDlg();
    void getSrvAddr(QHostAddress saddr);
    void getLocPath(QString lpath);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void createConnToSrv(); //连接到服务器
    void readChatMsg(); //读取服务器发来的文件数据

    void on_cntClosePushButton_clicked();

private:
    Ui::FileCntDlg *ui;
    QTcpSocket *myCntSocket;
    QHostAddress mySrvAddr;
    qint16 mySrvPort;

    qint64 myTotalBytes;
    qint64 myRcvedBytes;
    QByteArray myInputBlock;
    quint16 myBlockSize;

    QFile *myLocPathFile;
    QString myFileName;
    qint64 myFileNameSize;

    QElapsedTimer mytime;
};

#endif // FILECNTDLG_H
