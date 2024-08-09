#ifndef TURNPLATEPLUGIN_H
#define TURNPLATEPLUGIN_H

#include <abstractturnplate.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QJsonArray>

namespace jltmoco
{

class TurnplatePlugin : public QObject, jltmoco::AbstractTurnplate
{
    Q_OBJECT
    Q_INTERFACES(jltmoco::AbstractTurnplate)
    Q_PLUGIN_METADATA(IID AbstractTurnplate_iid FILE "config.json")

public:
    TurnplatePlugin();

    virtual void setup();
    virtual void uninstall();
    virtual bool connect(const QString &value);
    virtual void disconnect();
    virtual bool connected() const;
    virtual QJsonObject getStatusData();
    virtual void parseUserCommand(const QJsonObject &cmd);

private slots:
    void onPortDataParse();

private:
    QSerialPort *mPort;
    QByteArray recvBuffer;
    void parseRecvBuffer();

    int8_t motorState;
    QString motorAngle;

};

}

#endif // TURNPLATEPLUGIN_H
