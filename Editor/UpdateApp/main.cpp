#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlEngine>
#include <QProcess>
#include "updatemanager.h"

QObject *UpdateManagerProvider(QQmlEngine *engine,QJSEngine *jsEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(jsEngine);
    return UpdateManager::getInstance();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/Image/icon_logo.png"));

    UpdateManager *updateManager = UpdateManager::getInstance();
    //其它程序启动更新
    if(argc == 3)
    {
        updateManager->setWriterSrcDir(argv[1]);
        updateManager->setQuitApp(argv[2]);
        updateManager->setUpdateEnable(true);
    }
    else
    {
        updateManager->updateEnableCacl();
    }

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<UpdateManager>("CppService", 1, 0, "UpdateManager", UpdateManagerProvider);
    const QUrl url(u"qrc:/Qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    int ret = app.exec();
    if(ret == 0 && argc == 3 && !updateManager->getQuitApp().isEmpty())
    {
        QProcess process;
        process.setProgram(updateManager->getWriterSrcDir()+"/"+updateManager->getQuitApp());
        process.setArguments(QStringList()<<updateManager->getVersion());
        process.startDetached();
    }
    return ret;
}


