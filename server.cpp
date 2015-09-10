#include "client.h"
#include "controller.h"
#include "server.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>

#ifdef Q_OS_LINUX
    #define LOCAL_IP_QUERY "hostname -i"
#endif

Server::Server(int port, QString folder, QObject *parent) : QTcpServer(parent)
{
    m_port = port;
    m_folder = folder;
}

void Server::startServer() {
    if(listen(QHostAddress::Any, m_port)) {
        QProcess localIpProcess;
        localIpProcess.start(LOCAL_IP_QUERY);
        localIpProcess.waitForFinished();
        QByteArray localIp = localIpProcess.readAll();
        qDebug() << "Server can be accessed on ip:" << localIp.replace(" \n", "") + ":" + QString::number(m_port);
    } else {
        qDebug() << "[Error] Unable to start server:" << errorString();
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    new Controller(socketDescriptor, m_folder);
}
