#include "client.h"
#include "controller.h"

#include <QCoreApplication>

Controller::Controller(qintptr descr, QString absolutePath)
{
    Client *client = new Client(descr, absolutePath);
    client->moveToThread(&workerThread);
    //start
    connect(&workerThread, SIGNAL(started()), client, SLOT(handleRequest()));
    //stop
    connect(client, SIGNAL(finished()), &workerThread, SIGNAL(finished()));
    //deletion
    connect(&workerThread, SIGNAL(finished()), client, SLOT(deleteLater()));
    connect(&workerThread, SIGNAL(finished()), this, SLOT(deleteLater()));

    workerThread.start();
}

Controller::~Controller()
{
    qDebug() << "Thread closed";
    workerThread.quit();
    workerThread.wait();
}
