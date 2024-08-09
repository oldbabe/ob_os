#ifndef EDITORQML_H
#define EDITORQML_H

#include <QObject>
//#include <QVideoFrame>

class EditorQml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cameraRotate READ getCameraRotate WRITE setCameraRotate NOTIFY cameraRotateChanged)
    Q_PROPERTY(int studioType READ getStudioType WRITE setStudioType NOTIFY studioTypeChanged)
    Q_PROPERTY(QString robotIp READ getRobotIp WRITE setRobotIp NOTIFY robotIpChanged)
    Q_PROPERTY(QString railIp READ getRailIp WRITE setRailIp NOTIFY railIpChanged)
    Q_PROPERTY(QString railDriveIp READ getRailDriveIp WRITE setRailDriveIp NOTIFY railDriveIpChanged)
    Q_PROPERTY(QString followFocuCom READ getFollowFocuCom WRITE setFollowFocuCom NOTIFY followFocuComChanged)
    Q_PROPERTY(QString turnplateCom READ getTurnplateCom WRITE setTurnplateCom NOTIFY turnplateComChanged)

signals:
    void studioTypeChanged();
    void cameraRotateChanged();
    void robotIpChanged();
    void railIpChanged();
    void railDriveIpChanged();
    void followFocuComChanged();
    void turnplateComChanged();

    //设备连接状态改变
    void deviceStateChanged(int deviceId,bool state);
    void cameraFrameImgUpdate(bool);
//    void openCvDetChanged(int errorVlue);

public:
    static EditorQml *getInstance();

    void setup();
    void uninstall();

    void setStudioType(const int &type);
    int getStudioType() const;
    void setCameraRotate(const QString &angle);
    QString getCameraRotate() const;
    void setRobotIp(const QString &ip);
    QString getRobotIp() const;
    void setRailIp(const QString &ip);
    QString getRailIp() const;
    void setRailDriveIp(const QString &ip);
    QString getRailDriveIp() const;
    void setFollowFocuCom(const QString &com);
    QString getFollowFocuCom() const;
    void setTurnplateCom(const QString &com);
    QString getTurnplateCom() const;

    Q_INVOKABLE QStringList ports();
    Q_INVOKABLE bool getDebugFlag() const;
    Q_INVOKABLE QString getLocalHostName();

    void setDevConnected(int deviceID,bool state);
    Q_INVOKABLE bool getRobotConnected() const;
    Q_INVOKABLE bool getCameraConnected() const;
    Q_INVOKABLE bool getFollowfocusConnected() const;
    Q_INVOKABLE bool getTurnplateConnected() const;

public slots:
    void onStudioDevicesPropertiesChanged(const QJsonObject &obj);
    void onAutoFollowStateChanged(bool);

private:
    static EditorQml *handle;
    EditorQml();

    bool debugFlag;
    int studioType;
    QString cameraRotate;
    QString robotIp;
    QString railIp;
    QString railDriveIp;
    QString followFocuCom;
    QString turnplateCom;

    bool robotConnected;
    bool cameraConnected;
    bool followfocusConnected;
    bool turnplateConnected;
    void setRobotConnected(bool);
    void setCameraConnected(bool);
    void setFollowfocusConnected(bool);
    void setTurnplateConnected(bool);

    void setConfigValue(const QString &key,const QString &value);
    void setConfigValue(const QString &key,const int &value);


};

#endif // EDIORQML_H
