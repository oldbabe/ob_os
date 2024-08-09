#include "jakaplugin.h"
#include "jrobot.h"
#include "jtrack.h"

using namespace jltmoco;

JakaPlugin::JakaPlugin(QObject *parent)
    : QObject{parent}
{
    JRobot::getInstance()->setRobotPlugin(this);
    JRobot::getInstance()->moveToThread(&mRobotThread);
    QObject::connect(this,&JakaPlugin::taskChanged,
                     JRobot::getInstance(),&JRobot::onTaskChanged);

    mRobotThread.start();
    this->mFunc = NULL;
}

JakaPlugin::~JakaPlugin()
{
}

void JakaPlugin::registerFunc(std::function<void (const QJsonObject &)> func)
{
    this->mFunc = func;
}

void JakaPlugin::setup()
{

}

void JakaPlugin::uninstall()
{
    JRobot::getInstance()->moveStop();
    JRobot::getInstance()->closeRobot();
    mRobotThread.quit();
    mRobotThread.wait();
}

bool JakaPlugin::connect(const QString &robotIp,const QString &railIp)
{
    QJsonObject root;
    root["code"] = -1;
    root["ip"] = robotIp;
    emit taskChanged(root);
    JTrack::getInstance()->connectToHost(railIp,2000);
    return false;
}

bool JakaPlugin::connected() const
{
    return JRobot::getInstance()->connected;
}

void JakaPlugin::disconnect()
{
}

QJsonObject JakaPlugin::getStatusData()
{
    return JRobot::getInstance()->getStatus();
}

QJsonObject JakaPlugin::getStaticData()
{
    QJsonObject root;
    root["model"] = "JAKA_Zu12";
    root["caEnable"] = false;
    return root;
}

void JakaPlugin::parseUserCommand(const QJsonObject &cmd)
{
    int code = cmd["code"].toInt();
    if(code == 1)
    {
        JTrack::getInstance()->railJogMove(0);
        JRobot::getInstance()->moveStop();
    }
    else if(code == 2)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->jogDataUpdate(1,data);
        JTrack::getInstance()->railJogMove(data["P7"].toString().toDouble()*100);
    }
    else if(code == 3)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->jogDataUpdate(2,data);
        JTrack::getInstance()->railJogMove(data["P7"].toString().toDouble()*100);
    }
    else if(code == 4)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->absAxisMove(data);
        JTrack::getInstance()->railAbsMove(data);
    }
    else if(code == 5)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->absPosMove(data);
        JTrack::getInstance()->railAbsMove(data);
    }
    //连续节点数据加载
    else if(code == 6)
    {
        JRobot::getInstance()->dataList.append(cmd["data"].toObject());
    }
    //连续节点运动启动
    else if(code == 7)
    {
        emit taskChanged(cmd);
    }
    else if(code == 9)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->jogDataUpdate(3,data);
        JTrack::getInstance()->railJogMove(data["P7"].toString().toDouble()*100);
    }
    else if(code == 10)
    {
        QJsonObject data = cmd["data"].toObject();
        JRobot::getInstance()->setToolCoord(data["tool"].toObject());
        JRobot::getInstance()->setBaseCoord(data["world"].toObject());
        JRobot::getInstance()->setPayload(data["load"].toObject());
    }
}
