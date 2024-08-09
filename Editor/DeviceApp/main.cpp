#include <QApplication>
#include <QQmlApplicationEngine>

#include <QIcon>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QSharedMemory>
#include <QMessageBox>
#include <QStandardPaths>

#include <jconfig.h>
#include <Studio/jfreed.h>
#include <Studio/jrobot.h>
#include <Studio/jcamera.h>
#include <Studio/jfollowfocus.h>
#include <Studio/jturnplate.h>
#include <Studio/jcameradevice.h>
#include <NetWork/studioserver.h>
#include <NetWork/studioclient.h>
#include <Studio/studiocontroller.h>
#include <Studio/scriptcontroller.h>
#include <Session/jsession.h>

#include "editorqml.h"

using namespace jltmoco;

static QObject *JCameraDeviceProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JCameraDevice::getInstance();
}
QObject *EditorQmlProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return EditorQml::getInstance();
}

QObject *JFreedProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JFreed::getInstance();
}
QObject *StudioConfigProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JConfig::getInstance();
}
QObject *JRobotProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JRobot::getInstance();
}
QObject *JCameraProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JCamera::getInstance();
}
QObject *JFollowfocusProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JFollowfocus::getInstance();
}

QObject *JTurnplateProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JTurnplate::getInstance();
}

QObject *StudioControllerProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return StudioController::getInstance();
}

QObject *StudioServerProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return StudioServer::getInstance();
}

QObject *DeviceScriptProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return ScriptController::getInstance();
}

QObject *StudioClientProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return StudioClient::getInstance();
}
QObject *SessionProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return JSession::getInstance();
}

#if QT_NO_DEBUG
char *logFileName = NULL;
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    FILE *fp = NULL;
    if(fopen_s(&fp,logFileName,"a") == 0)
    {
        QByteArray localMsg = msg.toLocal8Bit();
        const char *file = context.file ? context.file : "CPP";
        const char *function = context.function ? context.function : "CPP";
        QByteArray timeMsg = QDateTime::currentDateTime().toString("hh:mm:ss.zzz").toLocal8Bit();
        fprintf(fp, "[%s,%s,%u,%s]%s \n",timeMsg.constData(),file,context.line,function,localMsg.constData());
        std::fclose(fp);
    }
}
#endif

//! [0]
int main(int argc, char *argv[])
{
    QFileInfo mExeInfo(argv[0]);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    //目录
    QString installDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/Install";
    QString logDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/Log/DeviceApp";
    QDir dir;
    if(!dir.exists(logDir)){
        dir.mkpath(logDir);
    }
    if(!dir.exists(installDir)){
        dir.mkpath(installDir);
    }

#ifndef QT_DEBUG
    //日志功能
    std::string fileStr = QString(logDir+"/"+QDateTime::currentDateTime().toString("yyyyMMdd")+".txt").toStdString();
    logFileName = new char[fileStr.length() + 1];
    strcpy_s(logFileName,fileStr.length()+1, fileStr.c_str());
    qInstallMessageHandler(myMessageOutput);

    //自动更新功能
    if(argc == 1 && mExeInfo.absoluteDir().dirName() != "Release")
    {
        //变更更新程序
        QFile file;
        if(file.exists(mExeInfo.path()+"/UpdateApp.exe.jlt"))
        {
            if(file.exists(mExeInfo.path()+"/UpdateApp.exe"))
                file.remove(mExeInfo.path()+"/UpdateApp.exe");

            file.rename(mExeInfo.path()+"/UpdateApp.exe.jlt",mExeInfo.path()+"/UpdateApp.exe");
        }
        //打开更新程序
        QFileInfo updateExeInfo(mExeInfo.path()+"/UpdateApp.exe");
        if(updateExeInfo.exists())
        {
            QProcess process;
            process.setProgram("UpdateApp.exe");
            process.setArguments(QStringList()<<mExeInfo.path()<<mExeInfo.fileName());
            process.startDetached();
            return 0;
        }
    }
#endif

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/Icon/icon_logo.png"));

    //共享内存,禁止重复打开
    QSharedMemory sharedMem(mExeInfo.baseName());
    if(sharedMem.isAttached()){
        sharedMem.detach();
    }
    if(!sharedMem.create(1)){
        QMessageBox::critical(NULL,"启动失败","[控制服务器]已启动!",QMessageBox::Ok);
        return 0;
    }

    //qmlc++注册
    qmlRegisterSingletonType<EditorQml>("CppService",1,0,"EditorQml",EditorQmlProvider);

    qmlRegisterSingletonType<JSession>("JMoco",1,0,"JSession",SessionProvider);
    qmlRegisterSingletonType<JConfig>("JMoco",1,0,"JConfig",StudioConfigProvider);
    qmlRegisterSingletonType<StudioController>("JMoco",1,0,"JStudioController",StudioControllerProvider);
    qmlRegisterSingletonType<StudioClient>("JMoco",1,0,"JStudioClient",StudioClientProvider);
    qmlRegisterSingletonType<StudioServer>("JMoco",1,0,"JServer",StudioServerProvider);
    qmlRegisterSingletonType<JRobot>("JMoco",1,0,"JRobot",JRobotProvider);
    qmlRegisterSingletonType<JCamera>("JMoco",1,0,"JCamera",JCameraProvider);
    qmlRegisterSingletonType<JCameraDevice>("JMoco", 1, 0, "JCameraDevice",JCameraDeviceProvider);
    qmlRegisterType<JCameraProperty>("JMoco",1,0,"JMoco");//注册不可实例化的类型
    qmlRegisterSingletonType<ScriptController>("JMoco",1,0,"JScript",DeviceScriptProvider);
    qmlRegisterSingletonType<JFollowfocus>("JMoco",1,0,"JFollowfocus",JFollowfocusProvider);
    qmlRegisterSingletonType<JTurnplate>("JMoco",1,0,"JTurnplate",JTurnplateProvider);
    qmlRegisterSingletonType<JFreed>("JMoco",1,0,"JFreeD",JFreedProvider);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Qml/main.qml"_qs);
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreated,
                     &app,[url](QObject *obj,const QUrl objUrl){
        if(!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },Qt::QueuedConnection);
    engine.load(url);

    //! 退出
    return app.exec();
}
//! [0]
