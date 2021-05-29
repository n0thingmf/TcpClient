#include "tcpclient.h"
#include "ui_tcpclient.h"

tcpclient::tcpclient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tcpclient)
{
    ui->setupUi(this);
    qTcpSocket = new QTcpSocket(this);
    in.setDevice(qTcpSocket);
    //conect push buton to quit
    connect(ui->btn_salir, &QAbstractButton::clicked, this, &QWidget::close);
    //conect request message
    connect(ui->btn_solicitar,&QAbstractButton::clicked, this, &tcpclient::requestMessage);
    //conect read message
    connect(qTcpSocket,&QIODevice::readyRead, this,&tcpclient::readMessage);
    //conect show error
    connect(qTcpSocket,&QAbstractSocket::errorOccurred, this,&tcpclient::showError);
}

tcpclient::~tcpclient()
{
    delete ui;
}

void tcpclient::requestMessage(){
    qInfo() << "request message";
    QString ipAddress=ui->lineEdit->text();
    QString port= ui->lineEdit_2->text();
    qTcpSocket->connectToHost(ipAddress,port.toInt());
    qInfo() << "ip: "+ipAddress+", port:"+port;

}
void tcpclient::readMessage(){
    qInfo() << "read message";
    in.startTransaction();
    QString message;
    in>>message;
    if(!in.commitTransaction()){
        qInfo()<<"error in datastream";
        return;
    }
    ui->lbl_messaje->setText(message);
}
void tcpclient::showError(QAbstractSocket::SocketError socketError){
    qInfo() << "show Error";
    switch(socketError){
        case 0:
            qInfo()<<"Conexion rechazada";
            break;
        case 1:
            qInfo()<<"El servidor cerro la conexion";
            break;
        default:
            qInfo()<<"Error no detectado";
    }
}
