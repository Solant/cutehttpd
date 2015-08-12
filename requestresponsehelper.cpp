#include "requestresponsehelper.h"

#include <QFile>
#include <QUrl>

QString RequestResponseHelper::MIME_TYPE_IMAGE_PNG = "image/png";
QString RequestResponseHelper::MIME_TYPE_TEXT_CSS = "text/css";
QString RequestResponseHelper::MIME_TYPE_TEXT_HTML = "text/html";
QString RequestResponseHelper::MIME_TYPE_APPLICATION_OCTET_STREAM = "application/octet-stream";

RequestResponseHelper::RequestResponseHelper()
{

}

QMap<QString, QString> *RequestResponseHelper::getPostParams(QString &request)
{
    QMap<QString, QString> *params = new QMap<QString, QString>();
    QStringList list = request.split("\r\n");
    if (list.last().startsWith("Accept-Language")) {
        return params;
    }

    QStringList paramsWithValues = list.last().split("&");
    for (int i = 0; i < paramsWithValues.size(); i++) {
        QStringList paramWithValue = paramsWithValues.at(i).split("=");
        params->insert(paramWithValue.first(), QUrl::fromPercentEncoding(paramWithValue.last().toUtf8()));
    }

    return params;
}

QString RequestResponseHelper::composeJsonResponse(QString path, QStringList folders, QStringList files)
{
    QString response = "{";

    response.append("\"currentPath\": \"" + path + "\"" + ",");

    response.append("\"folders\": [");
    for (int i = 0; i < folders.size(); i++) {
        response.append("\"" + folders.at(i) + "\"");
        if (i != folders.size()-1) {
            response.append(",");
        }
    }
    response.append("],");

    response.append("\"files\": [");
    for (int i = 0; i < files.size(); i++) {
        response.append("\"" + files.at(i) + "\"");
        if (i != files.size()-1) {
            response.append(",");
        }
    }
    response.append("]");

    response.append("}");
    return response;
}

QString RequestResponseHelper::createHeader(QFile &file, QString &mimeType)
{
    QString header;
    header.append("HTTP/1.1 200 OK\r\n");
    header.append("Content-Type: ").append(mimeType).append("\r\n");
    header.append("Content-Length: ").append(QString::number(file.size())).append("\r\n");
    header.append("\r\n");
    return header;
}
