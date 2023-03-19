#ifndef FILESRVDLG_H
#define FILESRVDLG_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QElapsedTimer>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class FileSrvDlg;
}

class QFile;
class QTcpServer;
class QTcpSocket;

class FileSrvDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FileSrvDlg(QWidget *parent = nullptr);
    ~FileSrvDlg();
    void cntRefused();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void sndChatMsg();
    void refreshProgress(qint64 bynum);

    void on_openFilePushButton_clicked();

    void on_sendFilePushButton_clicked();

    void on_srvClosePushButton_clicked();

private:
    Ui::FileSrvDlg *ui;
    QTcpServer *myTcpSrv;
    QTcpSocket *mySrvSocket;
    qint16 mySrvPort;

    QFile *myLocPathFile;
    QString myPathFile;
    QString myFileName;

    qint64 myTotalBytes;
    qint64 mySendBytes;
    qint64 myBytesTobeSend;
    qint64 myPayloadSize;
    QByteArray myOutputBlock;
    QElapsedTimer mytime;

signals:
    void sendFileName(QString name);



};

#endif // FILESRVDLG_H
