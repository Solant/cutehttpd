#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(qintptr descr,QString absolutePath, QObject *parent = 0);
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void handleRequest();
signals:
    void finished();
private:
    QTcpSocket *socket;
    QString m_rootFolder;
    qintptr m_descr;
};

#endif // CLIENT_H
