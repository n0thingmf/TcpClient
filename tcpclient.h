#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class tcpclient; }
QT_END_NAMESPACE

class tcpclient : public QDialog
{
    Q_OBJECT

public:
    tcpclient(QWidget *parent = nullptr);
    ~tcpclient();
private slots:
    void requestMessage();
    void readMessage();
    void showError(QAbstractSocket::SocketError socketError);

private:
    Ui::tcpclient *ui;
    QTcpSocket *qTcpSocket = nullptr;
    QDataStream in;
    QString receivedMessage;
};
#endif // TCPCLIENT_H
