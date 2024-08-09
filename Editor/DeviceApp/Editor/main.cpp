#include <QApplication>
#include <QQmlApplicationEngine>

#include <QIcon>
#include <QQuickWindow>

#include <devicecontroller.h>
#include <livelinkfreed.h>
#include <userserver.h>
//#include <jcameraframeitem.h>

#include "editorqml.h"

QObject *EditorQmlProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return EditorQml::getInstance();
}

QObject *LiveLinkFreeDProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return LiveLinkFreeD::getInstance();
}

//! [0]
int main(int argv, char *args[])
{
    QCoreApplication::setOrganizationName("JueLaoTou");
    QCoreApplication::setOrganizationDomain("www.jlt.com");
    QCoreApplication::setApplicationName("DeviceApp");

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QApplication app(argv, args);
    app.setWindowIcon(QIcon(":/Icon/icon_logo.png"));

    //qmlc++注册
//    qmlRegisterType<JCameraFrameItem>("Jlt.VirtualCamera",1,0,"VirtualCamera");
    qmlRegisterSingletonType<EditorQml>("CppService",1,0,"EditorQml",EditorQmlProvider);
    qmlRegisterSingletonType<LiveLinkFreeD>("Jlt.Moco",1,0,"JLiveLinkFreeD",LiveLinkFreeDProvider);
    LiveLinkFreeD::getInstance()->setup();
    EditorQml::getInstance()->setup();

#ifndef ONLY_VIEW
    //!设备控制器
    DEVICE::DeviceController*deviceController = DEVICE::DeviceController::getInstance();
    deviceController->setStudioType(EditorQml::getInstance()->getStudioType());
    deviceController->setup();

    //!用户服务
    UserServer *userServer = UserServer::getInstance();
    userServer->setup();

    //用户指令解析
    QObject::connect(userServer,&UserServer::parseUserCommand,
            deviceController,&DEVICE::DeviceController::onUserCmdParse);
    //用户连接数量改变
    QObject::connect(userServer,&UserServer::userNumberChanged,
            deviceController,&DEVICE::DeviceController::onUserNumberChanged);
    //设备状态数据
    QObject::connect(deviceController,&DEVICE::DeviceController::devicesPropertiesChanged,
            userServer,&UserServer::onRequestData);
    QObject::connect(deviceController,&DEVICE::DeviceController::devicesPropertiesChanged,
            EditorQml::getInstance(),&EditorQml::onStudioDevicesPropertiesChanged);
    QObject::connect(deviceController,&DEVICE::DeviceController::autoFollowStateChanged,
            EditorQml::getInstance(),&EditorQml::onAutoFollowStateChanged);

    //!livelink
    LiveLinkFreeD *mLiveLinkFreeD = LiveLinkFreeD::getInstance();
    EditorQml::connect(deviceController,&DEVICE::DeviceController::devicesPropertiesChanged,
            mLiveLinkFreeD,&LiveLinkFreeD::onDevicesPropertiesChanged);

#endif

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Qml/main.qml"_qs);
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreated,
                     &app,[url](QObject *obj,const QUrl objUrl){
        if(!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },Qt::QueuedConnection);
    engine.load(url);

    int res = app.exec();

    LiveLinkFreeD::getInstance()->uninstall();
    //!用户服务
    UserServer::getInstance()->uninstall();
    //!设备控制器
    DEVICE::DeviceController::getInstance()->uninstall();

    //! 退出
    return res;
}
//! [0]
