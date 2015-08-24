#include "client.h"
#include "controller.h"
#include "server.h"

#include <QCoreApplication>
#include <QDir>

Server::Server(int port, QString folder, QObject *parent) : QTcpServer(parent)
{
    m_port = port;
    m_folder = folder;
}

void Server::startServer() {
    if(listen(QHostAddress::Any, m_port)) {
        qDebug() << "Server started on port " << QString::number(m_port);
    } else {
        qDebug() << "[Error] Server not started";
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    Controller *c = new Controller(socketDescriptor, QDir(m_folder).absolutePath());
}
