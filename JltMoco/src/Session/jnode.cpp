#include "Session/jnode.h"
#include "Session/jscript.h"
#include "Studio/jrobot.h"
#include "Studio/jglobalremoteparam.h"
#include <QJsonObject>
#include "jltmoco.h"
#include "Studio/studiocontroller.h"

#include <QDir>
#include <QImage>
#include <QFileInfo>
#include "Studio/jcameradevice.h"

namespace jltmoco
{

JNode::JNode(QObject *parent)
    : QObject(parent)
{
    this->mScript = NULL;
    this->mNextNode = NULL;
    this->mLastNode = NULL;

    this->mChecked = false;
    this->mType = NodeType_Move;
    this->mX = 0;
    this->mY = 0;
    this->mPreview.clear();
    this->setTitle("机械臂&轨道");
    this->mFrameCounts = 0;
}

JNode::~JNode()
{
    ;
}

void JNode::setScript(JScript *script)
{
    this->mScript = script;
    emit scriptChanged();
}

void JNode::setData(const QJsonObject &nodeData)
{
    this->setObjectName(nodeData["Key"].toString());
    this->setChecked(nodeData["Checked"].toBool());
    this->setType(nodeData["Type"].toInt());
    this->setX(nodeData["X"].toDouble());
    this->setY(nodeData["Y"].toDouble());
    this->setTitle(nodeData["Title"].toString());
    this->setPreview(nodeData["Preview"].toString());

    //机械臂数据数据
    QJsonObject robotData = nodeData["1"].toObject();
    this->getRobot()->setType(robotData["type"].toInt());
    this->getRobot()->setFrames(robotData["frames"].toInt());
    QJsonObject world = robotData["world"].toObject();
    this->getRobot()->getWorld()->getTran()->setX(world["X"].toDouble());
    this->getRobot()->getWorld()->getTran()->setY(world["Y"].toDouble());
    this->getRobot()->getWorld()->getTran()->setZ(world["Z"].toDouble());
    this->getRobot()->getWorld()->getRpy()->setRx(world["A"].toDouble());
    this->getRobot()->getWorld()->getRpy()->setRy(world["B"].toDouble());
    this->getRobot()->getWorld()->getRpy()->setRz(world["C"].toDouble());
    QJsonObject tool = robotData["tool"].toObject();
    this->getRobot()->getTool()->getTran()->setX(tool["X"].toDouble());
    this->getRobot()->getTool()->getTran()->setY(tool["Y"].toDouble());
    this->getRobot()->getTool()->getTran()->setZ(tool["Z"].toDouble());
    this->getRobot()->getTool()->getRpy()->setRx(tool["A"].toDouble());
    this->getRobot()->getTool()->getRpy()->setRy(tool["B"].toDouble());
    this->getRobot()->getTool()->getRpy()->setRz(tool["C"].toDouble());
    QJsonObject load = robotData["load"].toObject();
    this->getRobot()->getLoad()->setMass(load["Mass"].toDouble());
    this->getRobot()->getLoad()->getTran()->setX(load["X"].toDouble());
    this->getRobot()->getLoad()->getTran()->setY(load["Y"].toDouble());
    this->getRobot()->getLoad()->getTran()->setZ(load["Z"].toDouble());
    this->getRobot()->getLoad()->getRpy()->setRx(load["A"].toDouble());
    this->getRobot()->getLoad()->getRpy()->setRy(load["B"].toDouble());
    this->getRobot()->getLoad()->getRpy()->setRz(load["C"].toDouble());
    this->getRobot()->getLoad()->getInertia()->setX(load["JX"].toDouble());
    this->getRobot()->getLoad()->getInertia()->setY(load["JY"].toDouble());
    this->getRobot()->getLoad()->getInertia()->setZ(load["JZ"].toDouble());
    QJsonObject param = robotData["param"].toObject();
    this->getRobot()->setRobotV(param["RobotV"].toInt());
    this->getRobot()->setRobotA(param["RobotA"].toInt());
    this->getRobot()->setPathV(param["PathV"].toInt());
    this->getRobot()->setPathA(param["PathA"].toInt());
    this->getRobot()->setTsValue(param["TsValue"].toInt());
    this->getRobot()->setWaiting(param["Waiting"].toInt());
    this->getRobot()->setAssistCA(param["AssistCA"].toInt());
    QJsonObject target = robotData["target"].toObject();
    this->getRobot()->getTarget()->setA1(target["A1"].toString());
    this->getRobot()->getTarget()->setA2(target["A2"].toString());
    this->getRobot()->getTarget()->setA3(target["A3"].toString());
    this->getRobot()->getTarget()->setA4(target["A4"].toString());
    this->getRobot()->getTarget()->setA5(target["A5"].toString());
    this->getRobot()->getTarget()->setA6(target["A6"].toString());
    this->getRobot()->getTarget()->setA7(target["E1"].toString());
    this->getRobot()->getTarget()->setX(target["X"].toString());
    this->getRobot()->getTarget()->setY(target["Y"].toString());
    this->getRobot()->getTarget()->setZ(target["Z"].toString());
    this->getRobot()->getTarget()->setRx(target["A"].toString());
    this->getRobot()->getTarget()->setRy(target["B"].toString());
    this->getRobot()->getTarget()->setRz(target["C"].toString());
    if(this->getRobot()->getType() == 3)
    {
        QJsonObject assist = robotData["assist"].toObject();
        this->getRobot()->getAssist()->setA1(assist["A1"].toString());
        this->getRobot()->getAssist()->setA2(assist["A2"].toString());
        this->getRobot()->getAssist()->setA3(assist["A3"].toString());
        this->getRobot()->getAssist()->setA4(assist["A4"].toString());
        this->getRobot()->getAssist()->setA5(assist["A5"].toString());
        this->getRobot()->getAssist()->setA6(assist["A6"].toString());
        this->getRobot()->getAssist()->setA7(assist["E1"].toString());
        this->getRobot()->getAssist()->setX(assist["X"].toString());
        this->getRobot()->getAssist()->setY(assist["Y"].toString());
        this->getRobot()->getAssist()->setZ(assist["Z"].toString());
        this->getRobot()->getAssist()->setRx(assist["A"].toString());
        this->getRobot()->getAssist()->setRy(assist["B"].toString());
        this->getRobot()->getAssist()->setRz(assist["C"].toString());
    }
    this->getRobot()->updateEnable();
    //相机数据数据
    QJsonObject cameraData = nodeData["2"].toObject();
    this->getCamera()->setImageInterval(cameraData["ImageInterval"].toInt());
    this->getCamera()->setImageNum(cameraData["ImageNum"].toInt());
    this->getCamera()->setShootMode(cameraData["ShootMode"].toInt());
    //设置跟焦器数据
    QJsonObject followfocusData = nodeData["3"].toObject();
    this->getFollowFocus()->setFocusValue(followfocusData["FocusValue"].toInt());
    this->getFollowFocus()->setZoomValue(followfocusData["ZoomValue"].toInt());
    this->getFollowFocus()->setIrisValue(followfocusData["IrisValue"].toInt());
    //设置转盘数据
    QJsonObject turnplateData = nodeData["4"].toObject();
    this->getTrunplate()->setAcc(turnplateData["Acc"].toInt());
    this->getTrunplate()->setSpeed(turnplateData["Speed"].toInt());
    this->getTrunplate()->setTarget(turnplateData["target"].toString());
}

void JNode::setNextNode(JNode *node)
{
    if(node != mNextNode)
    {
        this->mNextNode = node;
        emit nextChanged();
    }
}

void JNode::setLastNode(JNode *node)
{
    if(node != mLastNode)
    {
        if(node == NULL)
        {
            this->setParent(mScript);
        }
        else
        {
            this->setParent(node);
        }
        this->mLastNode = node;
        emit lastChanged();
    }
}

void JNode::setChecked(bool value)
{
    if(mChecked != value)
    {
        this->mChecked = value;
        emit checkedChanged();
    }
}

void JNode::setType(int value)
{
    if(mType != value)
    {
        this->mType = value;
        emit typeChanged();
    }
}

void JNode::setX(qreal value)
{
    this->mX = value;
    emit xChanged();
}

void JNode::setY(qreal value)
{
    this->mY = value;
    emit yChanged();
}

void JNode::setTitle(const QString &value)
{
    if(!value.isEmpty())
    {
        this->mTitle = value;
        emit titleChanged();
    }
}

void JNode::setPreview(const QString &value)
{
    this->mPreview= value;
    emit previewChanged();
}

void JNode::setFrameCounts(int value)
{
    if(mFrameCounts != value)
    {
        this->mFrameCounts = value;
        emit frameCountsChanged();
    }
}

void JNode::frameMotion(int frameIndex)
{
    int count = 0,countLast = 0;
    //根据frameIndex查找路径
    JNode *node = getNextNode();
    if(node)
    {
        node = node->getNextNode();
    }
    while (node)
    {
        count+=node->getRobot()->getFrames();
        if(frameIndex <= count)
        {
            double rote = (double)(frameIndex-countLast)/(double)node->getRobot()->getFrames();
            JNodeRobot *nodeRobot = node->getRobot();
            JNodeRobot *nodeLastRobot = node->getLastNode()->getRobot();

            QJsonObject target;
            target["X"] = QString::number(nodeLastRobot->getTarget()->getX().toDouble()+(nodeRobot->getTarget()->getX().toDouble()-nodeLastRobot->getTarget()->getX().toDouble())*rote,'f',6);
            target["Y"] = QString::number(nodeLastRobot->getTarget()->getY().toDouble()+(nodeRobot->getTarget()->getY().toDouble()-nodeLastRobot->getTarget()->getY().toDouble())*rote,'f',6);
            target["Z"] = QString::number(nodeLastRobot->getTarget()->getZ().toDouble()+(nodeRobot->getTarget()->getZ().toDouble()-nodeLastRobot->getTarget()->getZ().toDouble())*rote,'f',6);
            target["A"] = QString::number(nodeLastRobot->getTarget()->getRx().toDouble()+(nodeRobot->getTarget()->getRx().toDouble()-nodeLastRobot->getTarget()->getRx().toDouble())*rote,'f',6);
            target["B"] = QString::number(nodeLastRobot->getTarget()->getRy().toDouble()+(nodeRobot->getTarget()->getRy().toDouble()-nodeLastRobot->getTarget()->getRy().toDouble())*rote,'f',6);
            target["C"] = QString::number(nodeLastRobot->getTarget()->getRz().toDouble()+(nodeRobot->getTarget()->getRz().toDouble()-nodeLastRobot->getTarget()->getRz().toDouble())*rote,'f',6);
            target["E1"] = QString::number(nodeLastRobot->getTarget()->getA7().toDouble()+(nodeRobot->getTarget()->getA7().toDouble()-nodeLastRobot->getTarget()->getA7().toDouble())*rote,'f',6);

            QJsonObject nodeJson;
            QJsonObject robotJson;
            robotJson["code"] = 5;
            robotJson["type"] = node->getRobot()->getType();
            robotJson["param"] = JGlobalRemoteParam::getInstance()->toRobotParamJson();
            robotJson["target"] = target;
            nodeJson[QString::number(Device_Robot)] = robotJson;
            //跟焦器数据
            nodeJson[QString::number(Device_FollowFocus)] = node->getFollowFocus()->toJson();
            //设置转盘数据
            nodeJson[QString::number(Device_Turntable)] = node->getTrunplate()->toJson();
            //发送指令
            QJsonObject cmdJson;
            cmdJson["deviceId"] = Device_ScriptController;
            cmdJson["code"] = ScriptCommandCode_NodeReset;
            cmdJson["index"] = 0;
            cmdJson["data"] = nodeJson;
            StudioController::getInstance()->sendCommandData(cmdJson);
            break;
        }
        countLast = count;
        node = node->getNextNode();
    }
}

void JNode::updateFrameCounts()
{
    int count = 0;
    JNode *node = getNextNode();
    if(node)
    {
        node = node->getNextNode();
    }
    while (node)
    {
        if(node)
        {
            count+=node->getRobot()->getFrames();
            node = node->getNextNode();
        }
    }
    // qDebug() << "JNode::updateFrameCounts()" << count;
    this->setFrameCounts(count);
}

QJsonObject JNode::toJson()
{
    QJsonObject nodeData;
    nodeData["X"] = getX();
    nodeData["Y"] = getY();
    nodeData["Key"] = objectName();
    nodeData["Type"] = getType();
    nodeData["Checked"] = getChecked();
    if(getNextNode())
    {
        nodeData["Next"] = getNextNode()->toJson();
    }
    //非运动节点返回
    if(getType() != JNode::NodeType_Move)
        return nodeData;

    nodeData["Title"] = getTitle();
    nodeData["Preview"] = getPreview();
    //机械臂数据
    QJsonObject robotData;
    robotData["type"] = getRobot()->getType();
    robotData["frames"] = getRobot()->getFrames();
    QJsonObject world;
    world["X"] = getRobot()->getWorld()->getTran()->getX();
    world["Y"] = getRobot()->getWorld()->getTran()->getY();
    world["Z"] = getRobot()->getWorld()->getTran()->getZ();
    world["A"] = getRobot()->getWorld()->getRpy()->getRx();
    world["B"] = getRobot()->getWorld()->getRpy()->getRy();
    world["C"] = getRobot()->getWorld()->getRpy()->getRz();
    robotData["world"] = world;
    QJsonObject tool;
    tool["X"] = getRobot()->getTool()->getTran()->getX();
    tool["Y"] = getRobot()->getTool()->getTran()->getY();
    tool["Z"] = getRobot()->getTool()->getTran()->getZ();
    tool["A"] = getRobot()->getTool()->getRpy()->getRx();
    tool["B"] = getRobot()->getTool()->getRpy()->getRy();
    tool["C"] = getRobot()->getTool()->getRpy()->getRz();
    robotData["tool"] = tool;
    QJsonObject load;
    load["Mass"] = getRobot()->getLoad()->getMass();
    load["X"] = getRobot()->getLoad()->getTran()->getX();
    load["Y"] = getRobot()->getLoad()->getTran()->getY();
    load["Z"] = getRobot()->getLoad()->getTran()->getZ();
    load["A"] = getRobot()->getLoad()->getRpy()->getRx();
    load["B"] = getRobot()->getLoad()->getRpy()->getRy();
    load["C"] = getRobot()->getLoad()->getRpy()->getRz();
    load["JX"] = getRobot()->getLoad()->getInertia()->getX();
    load["JY"] = getRobot()->getLoad()->getInertia()->getY();
    load["JZ"] = getRobot()->getLoad()->getInertia()->getZ();
    robotData["load"] = load;
    QJsonObject param;
    param["RobotV"] = getRobot()->getRobotV();
    param["RobotA"] = getRobot()->getRobotA();
    param["PathV"] = getRobot()->getPathV();
    param["PathA"] = getRobot()->getPathA();
    param["TsValue"] = getRobot()->getTsValue();
    param["Waiting"] = getRobot()->getWaiting();
    param["AssistCA"] = getRobot()->getAssistCA();
    robotData["param"] = param;
    QJsonObject target;
    target["A1"] = getRobot()->getTarget()->getA1();
    target["A2"] = getRobot()->getTarget()->getA2();
    target["A3"] = getRobot()->getTarget()->getA3();
    target["A4"] = getRobot()->getTarget()->getA4();
    target["A5"] = getRobot()->getTarget()->getA5();
    target["A6"] = getRobot()->getTarget()->getA6();
    target["E1"] = getRobot()->getTarget()->getA7();
    target["X"] = getRobot()->getTarget()->getX();
    target["Y"] = getRobot()->getTarget()->getY();
    target["Z"] = getRobot()->getTarget()->getZ();
    target["A"] = getRobot()->getTarget()->getRx();
    target["B"] = getRobot()->getTarget()->getRy();
    target["C"] = getRobot()->getTarget()->getRz();
    robotData["target"] = target;
    if(getRobot()->getType() == 3)
    {
        QJsonObject assist;
        assist["A1"] = getRobot()->getAssist()->getA1();
        assist["A2"] = getRobot()->getAssist()->getA2();
        assist["A3"] = getRobot()->getAssist()->getA3();
        assist["A4"] = getRobot()->getAssist()->getA4();
        assist["A5"] = getRobot()->getAssist()->getA5();
        assist["A6"] = getRobot()->getAssist()->getA6();
        assist["E1"] = getRobot()->getAssist()->getA7();
        assist["X"] = getRobot()->getAssist()->getX();
        assist["Y"] = getRobot()->getAssist()->getY();
        assist["Z"] = getRobot()->getAssist()->getZ();
        assist["A"] = getRobot()->getAssist()->getRx();
        assist["B"] = getRobot()->getAssist()->getRy();
        assist["C"] = getRobot()->getAssist()->getRz();
        robotData["assist"] = assist;
    }
    nodeData["1"] = robotData;

    //相机数据
    QJsonObject cameraData;
    cameraData["ImageInterval"] = getCamera()->getImageInterval();
    cameraData["ImageNum"] = getCamera()->getImageNum();
    cameraData["ShootMode"] = getCamera()->getShootMode();
    nodeData["2"] = cameraData;
    //跟焦器数据
    QJsonObject followfocusData;
    followfocusData["FocusValue"] = getFollowFocus()->getFocusValue();
    followfocusData["ZoomValue"] = getFollowFocus()->getZoomValue();
    followfocusData["IrisValue"] = getFollowFocus()->getIrisValue();
    nodeData["3"] = followfocusData;
    //设置转盘数据
    QJsonObject turnplateData;
    turnplateData["Acc"] = getTrunplate()->getAcc();
    turnplateData["Speed"] = getTrunplate()->getSpeed();
    turnplateData["target"] = getTrunplate()->getTarget();
    nodeData["4"] = turnplateData;

    return nodeData;
}

void JNode::updataRobotTarget()
{
    JRobot *robot = JRobot::getInstance();
    if(!robot->getConnected())
        return;

    mRobot.getTarget()->setA1(robot->getPosition()->getA1());
    mRobot.getTarget()->setA2(robot->getPosition()->getA2());
    mRobot.getTarget()->setA3(robot->getPosition()->getA3());
    mRobot.getTarget()->setA4(robot->getPosition()->getA4());
    mRobot.getTarget()->setA5(robot->getPosition()->getA5());
    mRobot.getTarget()->setA6(robot->getPosition()->getA6());
    mRobot.getTarget()->setA7(robot->getPosition()->getA7());
    mRobot.getTarget()->setX(robot->getPosition()->getX());
    mRobot.getTarget()->setY(robot->getPosition()->getY());
    mRobot.getTarget()->setZ(robot->getPosition()->getZ());
    mRobot.getTarget()->setRx(robot->getPosition()->getRx());
    mRobot.getTarget()->setRy(robot->getPosition()->getRy());
    mRobot.getTarget()->setRz(robot->getPosition()->getRz());
    mRobot.getWorld()->getTran()->setX(robot->getWorld()->getTran()->getX());
    mRobot.getWorld()->getTran()->setY(robot->getWorld()->getTran()->getY());
    mRobot.getWorld()->getTran()->setZ(robot->getWorld()->getTran()->getZ());
    mRobot.getWorld()->getRpy()->setRx(robot->getWorld()->getRpy()->getRx());
    mRobot.getWorld()->getRpy()->setRy(robot->getWorld()->getRpy()->getRy());
    mRobot.getWorld()->getRpy()->setRz(robot->getWorld()->getRpy()->getRz());
    mRobot.getTool()->getTran()->setX(robot->getTool()->getTran()->getX());
    mRobot.getTool()->getTran()->setY(robot->getTool()->getTran()->getY());
    mRobot.getTool()->getTran()->setZ(robot->getTool()->getTran()->getZ());
    mRobot.getTool()->getRpy()->setRx(robot->getTool()->getRpy()->getRx());
    mRobot.getTool()->getRpy()->setRy(robot->getTool()->getRpy()->getRy());
    mRobot.getTool()->getRpy()->setRz(robot->getTool()->getRpy()->getRz());
    mRobot.getLoad()->setMass(robot->getLoad()->getMass());
    mRobot.getLoad()->getTran()->setX(robot->getLoad()->getTran()->getX());
    mRobot.getLoad()->getTran()->setY(robot->getLoad()->getTran()->getY());
    mRobot.getLoad()->getTran()->setZ(robot->getLoad()->getTran()->getZ());
    mRobot.getLoad()->getRpy()->setRx(robot->getLoad()->getRpy()->getRx());
    mRobot.getLoad()->getRpy()->setRy(robot->getLoad()->getRpy()->getRy());
    mRobot.getLoad()->getRpy()->setRz(robot->getLoad()->getRpy()->getRz());
    mRobot.getLoad()->getInertia()->setX(robot->getLoad()->getInertia()->getX());
    mRobot.getLoad()->getInertia()->setY(robot->getLoad()->getInertia()->getY());
    mRobot.getLoad()->getInertia()->setZ(robot->getLoad()->getInertia()->getZ());
    this->getRobot()->updateEnable();
    this->updateCenterCircle();
    this->updatePreview();
}

void JNode::updataRobotAssist()
{
    if(!JRobot::getInstance()->getConnected())
        return;

    JRobot *robot = JRobot::getInstance();
    mRobot.getAssist()->setA1(robot->getPosition()->getA1());
    mRobot.getAssist()->setA2(robot->getPosition()->getA2());
    mRobot.getAssist()->setA3(robot->getPosition()->getA3());
    mRobot.getAssist()->setA4(robot->getPosition()->getA4());
    mRobot.getAssist()->setA5(robot->getPosition()->getA5());
    mRobot.getAssist()->setA6(robot->getPosition()->getA6());
    mRobot.getAssist()->setA7(robot->getPosition()->getA7());
    mRobot.getAssist()->setX(robot->getPosition()->getX());
    mRobot.getAssist()->setY(robot->getPosition()->getY());
    mRobot.getAssist()->setZ(robot->getPosition()->getZ());
    mRobot.getAssist()->setRx(robot->getPosition()->getRx());
    mRobot.getAssist()->setRy(robot->getPosition()->getRy());
    mRobot.getAssist()->setRz(robot->getPosition()->getRz());
    this->getRobot()->updateEnable();
    this->updateCenterCircle();
}

void JNode::updateCenterCircle()
{
    if(getType()!=NodeType_Move)
        return;
    if(getRobot()->getType() != JNodeRobot::RobotType_Arc || !getRobot()->getEnable())
        return;
    if(getLastNode()==NULL || !getLastNode()->getRobot()->getEnable())
        return;
    double x1 = getLastNode()->getRobot()->getTarget()->getX().toDouble();
    double y1 = getLastNode()->getRobot()->getTarget()->getY().toDouble();
    double z1 = getLastNode()->getRobot()->getTarget()->getZ().toDouble();
    double x2 = getRobot()->getAssist()->getX().toDouble();
    double y2 = getRobot()->getAssist()->getY().toDouble();
    double z2 = getRobot()->getAssist()->getZ().toDouble();
    double x3 = getRobot()->getTarget()->getX().toDouble();
    double y3 = getRobot()->getTarget()->getY().toDouble();
    double z3 = getRobot()->getTarget()->getZ().toDouble();
    QList<double> res = getRobot()->centerCircle3d(x1,y1,z1,x2,y2,z2,x3,y3,z3);
    if(res.isEmpty() || res.length() != 5)
        return;
    for(int i = 0; i < res.size(); i++)
    {
        if(qIsNaN(res[i]))
            return;
    }
    getRobot()->setAssistCA(res.last());
}

void JNode::updatePreview()
{
    QDir dir;
    QFileInfo info(getScript()->getFileName());
    if(!dir.exists(info.filePath()))
    {
        return;
    }

    QString path = info.path()+"/nodePreview/";
    if(!dir.exists(path))
    {
        if(!dir.mkpath(path))
        {
            dir.mkpath(path);
        }
    }

    if(dir.exists(path))
    {
        QString img = path+objectName()+".jpg";
        if(JCameraDevice::getInstance()->getFrameImage().save(img))
        {
            setPreview(img);
        }
    }
}

}
