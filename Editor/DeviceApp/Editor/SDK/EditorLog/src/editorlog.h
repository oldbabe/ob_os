#ifndef EDITORLOG_H
#define EDITORLOG_H

#include <QObject>
#include "EditorLog_global.h"

class EDITORLOG_EXPORT EditorLog
{
public:
    static EditorLog* getInstance();

    void setup(bool enable);
    void setLogType(int type = true);
    int getLogType() const;
    void updateLogData(const QMessageLogContext &context,const QString &msg);

    enum LogLeaver
    {
        Fatal = 0,
        Critical,
        Warning,
        Info,
        Debug,
        Null,
    };

private:
    static EditorLog* handle;
    EditorLog();

    int myLogType;


};

#endif // EDITORLOG_H
