#include "server.h"

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("cutehttpd");
    QCoreApplication::setApplicationVersion("0.1a");

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt based http server for file sharing");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portOption(QStringList() << "p" << "port", "Port number, default 4242", "number");
    portOption.setDefaultValue(QString::number(4242));
    parser.addOption(portOption);
    parser.process(a);

    //Folder is args.at(0)
    QStringList args = parser.positionalArguments();

    int portNumber = parser.value(portOption).toInt();
    QString folder;
    if (!args.size()) {
        folder = QDir::currentPath();
    } else {
        if (QDir::isAbsolutePath(args.at(0))) {
            if (!QDir(args.at(0)).exists()) {
                qDebug() << "[Error] Folder not found";
                exit(EXIT_FAILURE);
            }
            folder = args.at(0);
        } else {
            folder = QDir::currentPath() + QDir::separator() + args.at(0);
            if (!QDir(folder).exists()) {
                qDebug() << "[Error] Folder " << folder << " not found";
                exit(EXIT_FAILURE);
            }
        }
    }
    qDebug() << "Shared folder: " << folder;
    Server server(portNumber, folder);
    server.startServer();
    return a.exec();
}
