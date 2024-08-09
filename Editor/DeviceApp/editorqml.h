#ifndef EDITORQML_H
#define EDITORQML_H

#include <QObject>

class EditorQml : public QObject
{
    Q_OBJECT
signals:
    //设备连接状态改变
    void deviceStateChanged(int deviceId,bool state);

public:
    static EditorQml *getInstance();

    Q_INVOKABLE bool showDialog(const QString &title,const QString &content);

private:
    static EditorQml *handle;
    EditorQml();

};

#endif // EDIORQML_H
