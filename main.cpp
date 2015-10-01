#include "server.h"

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("cutehttpd");
    QCoreApplication::setApplicationVersion("0.3");

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt-based HTTP server for file sharing.");
    parser.
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portOption(QStringList() << "p" << "port", "Port number, default 4242", "number");
    portOption.setDefaultValue(QString::number(4242));
    parser.addOption(portOption);
    parser.process(a);

    //Folder is args.at(0)
    QStringList args = parser.positionalArguments();

    int portNumber = parser.value(portOption).toInt();
    QDir folder = args.size() ? QDir(args.at(0)) : QDir::currentPath();
    if (!folder.exists()) {
        qDebug() << "[Error] Folder" << folder.absolutePath() << "not found";
        exit(EXIT_FAILURE);
    }
    qDebug() << "Shared folder: " << folder.absolutePath();
    Server server(portNumber, folder.absolutePath());
    server.startServer();
    return a.exec();
}
