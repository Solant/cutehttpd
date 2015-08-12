#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(int port, QString folder, QObject *parent = 0);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    int m_port;
    QString m_folder;
};

#endif // SERVER_H
