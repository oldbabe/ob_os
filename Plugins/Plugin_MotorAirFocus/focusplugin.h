#ifndef FOCUSPLUGIN_H
#define FOCUSPLUGIN_H

#include "abstractfollowfocus.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace jltmoco
{
class FocusPlugin : public QObject, AbstractFllowFocus
{
    Q_OBJECT
    Q_INTERFACES(jltmoco::AbstractFllowFocus)
    Q_PLUGIN_METADATA(IID AbstractFllowFocus_iid FILE "config.json")
public:
    FocusPlugin();

    virtual void setup();
    virtual void uninstall();
    virtual bool connect(const QString &port);
    virtual bool connected() const;
    virtual void disconnect();
    virtual void calibrate();
    virtual void setFocus(int value);
    virtual void setZoom(int value);
    virtual void setIris(int value);
    virtual void setValues(int focus, int zoom, int iris);
    virtual QJsonObject getStatusData();

private:
    QSerialPort *mPort;
    QString toValue(int value);
    void controlAmotor(int value,char number);
    void writeData(const QByteArray &array);
};
}

#endif // FOCUSPLUGIN_H
