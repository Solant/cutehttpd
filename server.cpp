#include "client.h"
#include "controller.h"
#include "server.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>

#ifdef Q_OS_LINUX
    #define LOCAL_IP_QUERY_COMMAND "hostname"
    #define LOCAL_IP_QUERY_ARGS "-i"
#endif
#ifdef Q_OS_WIN
    #define LOCAL_IP_QUERY_COMMAND "cmd"
    //Well, this is only way i found to run ifconfig and pipe its stdout to findstr
    #define LOCAL_IP_QUERY_ARGS "/C ipconfig | findstr IPv4"
#endif

QString parseIp(QString string) {
    QStringList tokens = string.split(QRegularExpression("[\n\r ]+"));
    QRegularExpression ipRegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    for (int i = 0; i < tokens.size(); i++) {
        if(tokens.at(i).contains(ipRegExp)) {
            return tokens[i];
        }
    }
    return "127.0.0.1";
}

Server::Server(int port, QString folder, QObject *parent) : QTcpServer(parent)
{
    m_port = port;
    m_folder = folder;
}

void Server::startServer() {
    if(listen(QHostAddress::Any, m_port)) {
        //Get
        QProcess localIpProcess;
        localIpProcess.start(LOCAL_IP_QUERY_COMMAND, QString(LOCAL_IP_QUERY_ARGS).split(" "));
        localIpProcess.waitForFinished();
        QByteArray localIp = localIpProcess.readAll();
        qDebug() << "Server address:" << parseIp(localIp) + ":" + QString::number(m_port);
    } else {
        qDebug() << "[Error] Unable to start server:" << errorString();
        exit(EXIT_FAILURE);
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    new Controller(socketDescriptor, m_folder);
}
