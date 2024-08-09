#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QSharedMemory>
#include <QMessageBox>
#include <QQuickWindow>
#include <QStandardPaths>

#include "jltscriptscene.h"
#include "jltscriptdrop.h"
#include "jltscriptshape.h"
#include "jltscriptnode.h"
#include "jltscriptconnector.h"

#include <Session/jsession.h>
#include <Session/jscript.h>
#include <Session/jnoderobot.h>
#include <Session/jnodefollowfocus.h>
#include <Session/jnodeturnplate.h>

#include <Remote/jfollowfocusremote.h>
#include <Remote/jgamepad.h>

#include <NetWork/studioclient.h>
#include <Studio/scriptcontroller.h>
#include <Studio/studiocontroller.h>
#include <Studio/jrobot.h>
#include <Studio/jcamera.h>
#include <Studio/jcamerainstall.h>
#include <Studio/jcameradevice.h>
#include <Studio/jfollowfocus.h>
#include <Studio/jturnplate.h>
#include <Studio/jglobalremoteparam.h>

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
void JMocoRegister();

int main(int argc, char *argv[])
{
    QFileInfo mExeInfo(argv[0]);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    //目录
    QString installDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/Install";
    QString logDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/Log/Designer";
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
    app.setWindowIcon(QIcon(":/Image/icon_logo.png"));

    //共享内存,禁止重复打开
    QSharedMemory sharedMem(mExeInfo.baseName());
    if(sharedMem.isAttached()){
        sharedMem.detach();
    }
    if(!sharedMem.create(1)){
        QMessageBox::critical(NULL,"启动失败","[设计端]已启动!",QMessageBox::Ok);
        return 0;
    }

    JMocoRegister();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

/**
 * @brief JSession 实例化
 */
static QObject *JSessionProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JSession::getInstance();
}

/**
 * @brief JSession 实例化
 */
static QObject *JStudioClientProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::StudioClient::getInstance();
}

/**
 * @brief JSession 实例化
 */
static QObject *JFollowfocusRemoteProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JFollowfocusRemote::getInstance();
}
/**
 * @brief JGamepad 实例化
 */
static QObject *JGamepadProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JGamepad::getInstance();
}

static QObject *JRobotProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JRobot::getInstance();
}

static QObject *JCameraProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JCamera::getInstance();
}

static QObject *JTurnplateProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JTurnplate::getInstance();
}

static QObject *JFollowfocusProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JFollowfocus::getInstance();
}

static QObject *ScriptControllerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::ScriptController::getInstance();
}
static QObject *JStudioControllerProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::StudioController::getInstance();
}
static QObject *JCameraInstallProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JCameraInstall::getInstance();
}
static QObject *JCameraDeviceProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JCameraDevice::getInstance();
}
static QObject *JGlobalRemoteParamProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return jltmoco::JGlobalRemoteParam::getInstance();
}

/**
 * @brief JMoco 对象注册
 */
void JMocoRegister()
{
//    qmlRegisterUncreatableMetaObject(JMOCO::staticMetaObject, "JMoco", 1, 0, "JDefined", "JMoco namespace register failed");
    qmlRegisterType<JltScriptScene>("JltView",1,0,"JltScriptScene");
    qmlRegisterType<JltScriptShape>("JltView",1,0,"JltScriptShape");
    qmlRegisterType<JltScriptDrop>("JltView",1,0,"JltScriptDrop");
    qmlRegisterType<JltScriptNode>("JltView",1,0,"JltScriptNode");
    qmlRegisterType<JltScriptConnector>("JltView",1,0,"JltScriptConnector");

    qmlRegisterSingletonType<jltmoco::JSession>("JMoco", 1, 0, "JSession",JSessionProvider);
    qmlRegisterUncreatableType<jltmoco::JRobotArray>("JMoco", 1, 0, "JRobotArray","qmlRegisterUncreatableType JRobotArray failed!");
    qmlRegisterUncreatableType<jltmoco::JScript>("JMoco", 1, 0, "JScript","qmlRegisterUncreatableType JScript failed!");
    qmlRegisterUncreatableType<jltmoco::JScriptScene>("JMoco", 1, 0, "JScriptScene","qmlRegisterUncreatableType JScriptScene failed!");
    qmlRegisterUncreatableType<jltmoco::JScriptRobot>("JMoco", 1, 0, "JScriptRobot","qmlRegisterUncreatableType JScriptRobot failed!");
    qmlRegisterUncreatableType<jltmoco::JScriptCamera>("JMoco", 1, 0, "JScriptCamera","qmlRegisterUncreatableType JScriptCamera failed!");
    qmlRegisterUncreatableType<jltmoco::JScriptTurnplate>("JMoco", 1, 0, "JScriptTurnplate","qmlRegisterUncreatableType JScriptTurnplate failed!");
    qmlRegisterUncreatableType<jltmoco::JScriptFollowFocus>("JMoco", 1, 0, "JScriptFollowFocus","qmlRegisterUncreatableType JScriptFollowFocus failed!");
    qmlRegisterUncreatableType<jltmoco::JNode>("JMoco", 1, 0, "JNode","qmlRegisterUncreatableType JNode failed!");
    qmlRegisterUncreatableType<jltmoco::JNodeRobot>("JMoco", 1, 0, "JNodeRobot","qmlRegisterUncreatableType JNodeRobot failed!");
    qmlRegisterUncreatableType<jltmoco::JNodeCamera>("JMoco", 1, 0, "JNodeCamera","qmlRegisterUncreatableType JNodeCamera failed!");
    qmlRegisterUncreatableType<jltmoco::JNodeFollowFocus>("JMoco", 1, 0, "JNodeFollowFocus","qmlRegisterUncreatableType JNodeFollowFocus failed!");
    qmlRegisterUncreatableType<jltmoco::JNodeTurnplate>("JMoco", 1, 0, "JNodeTurnplate","qmlRegisterUncreatableType JNodeTurnplate failed!");

    qmlRegisterSingletonType<jltmoco::JFollowfocusRemote>("JMoco", 1, 0, "JFollowfocusRemote",JFollowfocusRemoteProvider);
    qmlRegisterSingletonType<jltmoco::JGamepad>("JMoco", 1, 0, "JGamepad",JGamepadProvider);

    qmlRegisterUncreatableType<jltmoco::JRobotInstall>("JMoco", 1, 0, "JRobotInstall","qmlRegisterUncreatableType JRobotInstall failed!");
    qmlRegisterUncreatableType<jltmoco::CartesianTran>("JMoco", 1, 0, "CartesianTran","qmlRegisterUncreatableType JCartesianTran failed!");
    qmlRegisterUncreatableType<jltmoco::Rpy>("JMoco", 1, 0, "Rpy","qmlRegisterUncreatableType Rpy failed!");
    qmlRegisterUncreatableType<jltmoco::CartesianPose>("JMoco", 1, 0, "CartesianPose","qmlRegisterUncreatableType CartesianPose failed!");

    qmlRegisterSingletonType<jltmoco::JGlobalRemoteParam>("JMoco", 1, 0, "JGlobalRemoteParam",JGlobalRemoteParamProvider);
    qmlRegisterSingletonType<jltmoco::JRobot>("JMoco", 1, 0, "JRobot",JRobotProvider);
    qmlRegisterSingletonType<jltmoco::JCamera>("JMoco", 1, 0, "JCamera",JCameraProvider);
    qmlRegisterSingletonType<jltmoco::JCameraDevice>("JMoco", 1, 0, "JCameraDevice",JCameraDeviceProvider);
    qmlRegisterSingletonType<jltmoco::JCameraInstall>("JMoco", 1, 0, "JCameraInstall",JCameraInstallProvider);
    qmlRegisterSingletonType<jltmoco::JTurnplate>("JMoco", 1, 0, "JTurnplate",JTurnplateProvider);
    qmlRegisterSingletonType<jltmoco::JFollowfocus>("JMoco", 1, 0, "JFollowfocus",JFollowfocusProvider);
    qmlRegisterSingletonType<jltmoco::ScriptController>("JMoco", 1, 0, "JScriptController",ScriptControllerProvider);
    qmlRegisterSingletonType<jltmoco::StudioClient>("JMoco", 1, 0, "JStudioClient",JStudioClientProvider);
    qmlRegisterSingletonType<jltmoco::StudioController>("JMoco", 1, 0, "JStudioController",JStudioControllerProvider);
}




