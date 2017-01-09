#include "requestresponsehelper.h"

#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QMimeDatabase>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QString RequestResponseHelper::MIME_TYPE_TEXT_HTML = "text/html";
QString RequestResponseHelper::MIME_TYPE_APPLICATION_OCTET_STREAM = "application/octet-stream";
QMimeDatabase RequestResponseHelper::m_database;

QMap<QString, QString> *RequestResponseHelper::getParameters(QString &url) {
    QMap<QString, QString> *params = new QMap<QString, QString>();

    QStringList paramsWithValues = url.split("?").last().split("&");
    for (int i = 0; i < paramsWithValues.size(); i++) {
        QStringList paramWithValue = paramsWithValues.at(i).split("=");
        params->insert(paramWithValue.first(), QUrl::fromPercentEncoding(paramWithValue.last().toUtf8()));
    }

    return params;
}

QByteArray RequestResponseHelper::createJsonHeader(int contentLength)
{
    QByteArray header;
    header.append("HTTP/1.1 200 OK\r\n");
    header.append("Content-Type: ").append("application/json").append("\r\n");
    header.append("Content-Length: ").append(QString::number(contentLength)).append("\r\n");
    header.append("\r\n");
    return header;
}

QByteArray RequestResponseHelper::composeJsonResponse(QString path, QStringList folders, QStringList files)
{
    QJsonObject json;
    json.insert("currentPath", path);
    json.insert("folders", QJsonArray::fromStringList(folders));
    json.insert("files", QJsonArray::fromStringList(files));

    QJsonDocument document(json);
    QString jsonString = document.toJson(QJsonDocument::Compact);
    return createJsonHeader(jsonString.length()).append(jsonString);
}

QString RequestResponseHelper::createHeader(QFile &file, QString mimeType, bool addContentDisposition, bool addAcceptRanges)
{
    QString header;
    header.append("HTTP/1.1 200 OK\r\n");
    if (addContentDisposition) {
        header.append("Content-Disposition: attachment; filename=\"").append(QFileInfo(file.fileName()).fileName()).append("\"\r\n");
    }
    if (addAcceptRanges) {
        //Chrome need this for setting currentTime on audio tags
        header.append("Accept-Ranges: bytes\r\n");
    }
    header.append("Content-Type: ").append(mimeType).append("\r\n");
    header.append("Content-Length: ").append(QString::number(file.size())).append("\r\n");
    header.append("\r\n");
    return header;
}

QString RequestResponseHelper::detectMimeType(QString fileName) {
    return m_database.mimeTypeForFile(fileName, QMimeDatabase::MatchExtension).name();
}
