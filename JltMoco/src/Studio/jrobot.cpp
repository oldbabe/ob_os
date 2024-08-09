#include "Studio/jrobot.h"
#include "Interface/abstractrobot.h"
#include "Studio/studiocontroller.h"
#include "Studio/jglobalremoteparam.h"
#include <QMutex>
#include <QDebug>
#include <QJsonArray>
#include <QSettings>
#include <QStandardPaths>
#include <QQmlEngine>

#include "jltmoco.h"
#include "jconfig.h"

using namespace jltmoco;

JRobot* JRobot::handle = Q_NULLPTR;

JRobot* JRobot::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JRobot;
        mutex.unlock();
    }
    return handle;
}

JRobot::JRobot()
{
    this->pluginHandle = nullptr;
    this->mConnected = false;
    this->railConnected = false;
    this->runNumber = 0;
    this->runNumberLast = 0;
    this->mCaEnable = false;

    this->mInstallIndex = 0;
    for (int i = 0; i < 12; ++i)
    {
        JRobotInstall* install = new JRobotInstall;
        //保证qml调用后不删除
        QQmlEngine::setObjectOwnership(install, QQmlEngine::CppOwnership);
        mInstallList.append(install);
    }

    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JConfig.ini", QSettings::IniFormat);
    this->mRemoteType = settings.value("JRobotRemoteType",RemoteType_Tool).toInt();
    if(settings.contains("InstallIndex"))
    {
        this->mInstallIndex = settings.value("InstallIndex").toInt();
        int size = settings.beginReadArray("Installs");
        for (int i = 0; i < size; ++i)
        {
            settings.setArrayIndex(i);
            //设置数据
            JRobotInstall* install = mInstallList[i];
            install->setTitle(settings.value("title").toString());
            install->setModel(settings.value("model").toString());
            install->getReset()->setA1(settings.value("resetA1").toString());
            install->getReset()->setA2(settings.value("resetA2").toString());
            install->getReset()->setA3(settings.value("resetA3").toString());
            install->getReset()->setA4(settings.value("resetA4").toString());
            install->getReset()->setA5(settings.value("resetA5").toString());
            install->getReset()->setA6(settings.value("resetA6").toString());
            install->getReset()->setA7(settings.value("resetA7").toString());
            install->getReset()->setX(settings.value("resetX").toString());
            install->getReset()->setY(settings.value("resetY").toString());
            install->getReset()->setZ(settings.value("resetZ").toString());
            install->getReset()->setRx(settings.value("resetRx").toString());
            install->getReset()->setRy(settings.value("resetRy").toString());
            install->getReset()->setRz(settings.value("resetRz").toString());

            install->getWorld()->getTran()->setX(settings.value("worldX").toDouble());
            install->getWorld()->getTran()->setY(settings.value("worldY").toDouble());
            install->getWorld()->getTran()->setZ(settings.value("worldZ").toDouble());
            install->getWorld()->getRpy()->setRx(settings.value("worldRx").toDouble());
            install->getWorld()->getRpy()->setRy(settings.value("worldRy").toDouble());
            install->getWorld()->getRpy()->setRz(settings.value("worldRz").toDouble());

            install->getTool()->getTran()->setX(settings.value("toolX").toDouble());
            install->getTool()->getTran()->setY(settings.value("toolY").toDouble());
            install->getTool()->getTran()->setZ(settings.value("toolZ").toDouble());
            install->getTool()->getRpy()->setRx(settings.value("toolRx").toDouble());
            install->getTool()->getRpy()->setRy(settings.value("toolRy").toDouble());
            install->getTool()->getRpy()->setRz(settings.value("toolRz").toDouble());

            install->getLoad()->setMass(settings.value("loadM").toDouble());
            install->getLoad()->getTran()->setX(settings.value("loadX").toDouble());
            install->getLoad()->getTran()->setY(settings.value("loadY").toDouble());
            install->getLoad()->getTran()->setZ(settings.value("loadZ").toDouble());
            install->getLoad()->getRpy()->setRx(settings.value("loadRx").toDouble());
            install->getLoad()->getRpy()->setRy(settings.value("loadRy").toDouble());
            install->getLoad()->getRpy()->setRz(settings.value("loadRz").toDouble());
            install->getLoad()->getInertia()->setX(settings.value("loadJX").toDouble());
            install->getLoad()->getInertia()->setY(settings.value("loadJY").toDouble());
            install->getLoad()->getInertia()->setZ(settings.value("loadJZ").toDouble());
        }
        settings.endArray();
    }
    else
    {
        for (int i = 0; i < mInstallList.size(); ++i)
        {
            mInstallList[i]->setTitle("方式"+QString::number(i));
        }
    }
    //读取方向记录
    mDirectionList.append(settings.value("JRobotRemoteDirection1",1).toInt());
    mDirectionList.append(settings.value("JRobotRemoteDirection2",2).toInt());
    mDirectionList.append(settings.value("JRobotRemoteDirection3",3).toInt());
    mDirectionList.append(settings.value("JRobotRemoteDirection4",4).toInt());
    mDirectionList.append(settings.value("JRobotRemoteDirection5",5).toInt());
    mDirectionList.append(settings.value("JRobotRemoteDirection6",6).toInt());
}

JRobot::~JRobot()
{
    qDeleteAll(mInstallList);
    this->mInstallList.clear();
}


void JRobot::installSave()
{
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JConfig.ini", QSettings::IniFormat);
    settings.setValue("InstallIndex",mInstallIndex);
    settings.beginWriteArray("Installs");
    for (int i = 0; i < mInstallList.size(); ++i)
    {
        settings.setArrayIndex(i);
        //设置数据
        JRobotInstall* install = mInstallList[i];
        settings.setValue("title",install->getTitle());
        settings.setValue("model",install->getModel());
        settings.setValue("resetA1",install->getReset()->getA1());
        settings.setValue("resetA2",install->getReset()->getA2());
        settings.setValue("resetA3",install->getReset()->getA3());
        settings.setValue("resetA4",install->getReset()->getA4());
        settings.setValue("resetA5",install->getReset()->getA5());
        settings.setValue("resetA6",install->getReset()->getA6());
        settings.setValue("resetA7",install->getReset()->getA7());
        settings.setValue("resetX",install->getReset()->getX());
        settings.setValue("resetY",install->getReset()->getY());
        settings.setValue("resetZ",install->getReset()->getZ());
        settings.setValue("resetRx",install->getReset()->getRx());
        settings.setValue("resetRy",install->getReset()->getRy());
        settings.setValue("resetRz",install->getReset()->getRz());
        settings.setValue("worldX",install->getWorld()->getTran()->getX());
        settings.setValue("worldY",install->getWorld()->getTran()->getY());
        settings.setValue("worldZ",install->getWorld()->getTran()->getZ());
        settings.setValue("worldRx",install->getWorld()->getRpy()->getRx());
        settings.setValue("worldRy",install->getWorld()->getRpy()->getRy());
        settings.setValue("worldRz",install->getWorld()->getRpy()->getRz());
        settings.setValue("toolX",install->getTool()->getTran()->getX());
        settings.setValue("toolY",install->getTool()->getTran()->getY());
        settings.setValue("toolZ",install->getTool()->getTran()->getZ());
        settings.setValue("toolRx",install->getTool()->getRpy()->getRx());
        settings.setValue("toolRy",install->getTool()->getRpy()->getRy());
        settings.setValue("toolRz",install->getTool()->getRpy()->getRz());
        settings.setValue("loadM",install->getLoad()->getMass());
        settings.setValue("loadX",install->getLoad()->getTran()->getX());
        settings.setValue("loadY",install->getLoad()->getTran()->getY());
        settings.setValue("loadZ",install->getLoad()->getTran()->getZ());
        settings.setValue("loadRx",install->getLoad()->getRpy()->getRx());
        settings.setValue("loadRy",install->getLoad()->getRpy()->getRy());
        settings.setValue("loadRz",install->getLoad()->getRpy()->getRz());
        settings.setValue("loadJX",install->getLoad()->getInertia()->getX());
        settings.setValue("loadJY",install->getLoad()->getInertia()->getY());
        settings.setValue("loadJZ",install->getLoad()->getInertia()->getZ());
    }
    settings.endArray();
}

void JRobot::setInstallIndex(int index)
{
    if(mInstallIndex != index)
    {
        this->mInstallIndex = index;
        emit installIndexChanged();
    }
}

void JRobot::installUpdate(int index)
{
    if(index<0||index>=mInstallList.size())
        return;
    if(!getConnected())
        return;

    JRobotInstall* install = mInstallList[getInstallIndex()];
    install->setModel(getModel());
    install->getReset()->setA1(getPosition()->getA1());
    install->getReset()->setA2(getPosition()->getA2());
    install->getReset()->setA3(getPosition()->getA3());
    install->getReset()->setA4(getPosition()->getA4());
    install->getReset()->setA5(getPosition()->getA5());
    install->getReset()->setA6(getPosition()->getA6());
    install->getReset()->setA7(getPosition()->getA7());
    install->getReset()->setX(getPosition()->getX());
    install->getReset()->setY(getPosition()->getY());
    install->getReset()->setZ(getPosition()->getZ());
    install->getReset()->setRx(getPosition()->getRx());
    install->getReset()->setRy(getPosition()->getRy());
    install->getReset()->setRz(getPosition()->getRz());
    install->getWorld()->getTran()->setX(getWorld()->getTran()->getX());
    install->getWorld()->getTran()->setY(getWorld()->getTran()->getY());
    install->getWorld()->getTran()->setZ(getWorld()->getTran()->getZ());
    install->getWorld()->getRpy()->setRx(getWorld()->getRpy()->getRx());
    install->getWorld()->getRpy()->setRy(getWorld()->getRpy()->getRy());
    install->getWorld()->getRpy()->setRz(getWorld()->getRpy()->getRz());
    install->getTool()->getTran()->setX(getTool()->getTran()->getX());
    install->getTool()->getTran()->setY(getTool()->getTran()->getY());
    install->getTool()->getTran()->setZ(getTool()->getTran()->getZ());
    install->getTool()->getRpy()->setRx(getTool()->getRpy()->getRx());
    install->getTool()->getRpy()->setRy(getTool()->getRpy()->getRy());
    install->getTool()->getRpy()->setRz(getTool()->getRpy()->getRz());
    install->getLoad()->setMass(getLoad()->getMass());
    install->getLoad()->getTran()->setX(getLoad()->getTran()->getX());
    install->getLoad()->getTran()->setY(getLoad()->getTran()->getY());
    install->getLoad()->getTran()->setZ(getLoad()->getTran()->getZ());
    install->getLoad()->getRpy()->setRx(getLoad()->getRpy()->getRx());
    install->getLoad()->getRpy()->setRy(getLoad()->getRpy()->getRy());
    install->getLoad()->getRpy()->setRz(getLoad()->getRpy()->getRz());
    install->getLoad()->getInertia()->setX(getLoad()->getInertia()->getX());
    install->getLoad()->getInertia()->setY(getLoad()->getInertia()->getY());
    install->getLoad()->getInertia()->setZ(getLoad()->getInertia()->getZ());
}

void JRobot::installApply(int index)
{
    QJsonObject data = installToJson(index);
    if(data.isEmpty())
        return;

    QJsonObject cmd;
    cmd["code"] = 10;
    cmd["deviceId"] = Device_Robot;
    cmd["data"] = data;
    this->sendData(cmd);
}

void JRobot::installReset(int index)
{
    QJsonObject data = installToJson(index);
    if(data.isEmpty())
        return;

    data["type"] = 2;
    data["code"] = 4;
    QJsonObject param;
    param["PrgV"] = JGlobalRemoteParam::getInstance()->getRobotPrgV();
    param["RobotV"] = JGlobalRemoteParam::getInstance()->getRobotV();
    param["RobotA"] = JGlobalRemoteParam::getInstance()->getRobotA();
    param["PathV"] = JGlobalRemoteParam::getInstance()->getRailV();
    param["PathA"] = JGlobalRemoteParam::getInstance()->getRailA();
    param["AssistCA"] = 0;
    param["TsValue"] = 0;
    param["Waiting"] = 0;
    data["param"] = param;
    QJsonObject target;
    target["X"] = mInstallList.at(index)->getReset()->getX();
    target["Y"] = mInstallList.at(index)->getReset()->getY();
    target["Z"] = mInstallList.at(index)->getReset()->getZ();
    target["A"] = mInstallList.at(index)->getReset()->getRx();
    target["B"] = mInstallList.at(index)->getReset()->getRy();
    target["C"] = mInstallList.at(index)->getReset()->getRz();
    target["A1"] = mInstallList.at(index)->getReset()->getA1();
    target["A2"] = mInstallList.at(index)->getReset()->getA2();
    target["A3"] = mInstallList.at(index)->getReset()->getA3();
    target["A4"] = mInstallList.at(index)->getReset()->getA4();
    target["A5"] = mInstallList.at(index)->getReset()->getA5();
    target["A6"] = mInstallList.at(index)->getReset()->getA6();
    target["E1"] = mInstallList.at(index)->getReset()->getA7();
    data["target"] = target;
    this->absPosMovement(data);
}

QJsonObject JRobot::installToJson(int index)
{
    if(!getConnected())
        return QJsonObject();
    if(index<0||index>=mInstallList.size())
        return QJsonObject();

    QJsonObject data,world,tool,load;
    world["X"] = mInstallList.at(index)->getWorld()->getTran()->getX();
    world["Y"] = mInstallList.at(index)->getWorld()->getTran()->getY();
    world["Z"] = mInstallList.at(index)->getWorld()->getTran()->getZ();
    world["A"] = mInstallList.at(index)->getWorld()->getRpy()->getRx();
    world["B"] = mInstallList.at(index)->getWorld()->getRpy()->getRy();
    world["C"] = mInstallList.at(index)->getWorld()->getRpy()->getRz();
    tool["X"] = mInstallList.at(index)->getTool()->getTran()->getX();
    tool["Y"] = mInstallList.at(index)->getTool()->getTran()->getY();
    tool["Z"] = mInstallList.at(index)->getTool()->getTran()->getZ();
    tool["A"] = mInstallList.at(index)->getTool()->getRpy()->getRx();
    tool["B"] = mInstallList.at(index)->getTool()->getRpy()->getRy();
    tool["C"] = mInstallList.at(index)->getTool()->getRpy()->getRz();
    load["M"] = mInstallList.at(index)->getLoad()->getMass();
    load["X"] = mInstallList.at(index)->getLoad()->getTran()->getX();
    load["Y"] = mInstallList.at(index)->getLoad()->getTran()->getY();
    load["Z"] = mInstallList.at(index)->getLoad()->getTran()->getZ();
    load["A"] = mInstallList.at(index)->getLoad()->getRpy()->getRx();
    load["B"] = mInstallList.at(index)->getLoad()->getRpy()->getRy();
    load["C"] = mInstallList.at(index)->getLoad()->getRpy()->getRz();
    load["JX"] = mInstallList.at(index)->getLoad()->getInertia()->getX();
    load["JY"] = mInstallList.at(index)->getLoad()->getInertia()->getY();
    load["JZ"] = mInstallList.at(index)->getLoad()->getInertia()->getZ();
    data["world"] = world;
    data["tool"] = tool;
    data["load"] = load;
    return data;
}

void JRobot::setRemoteType(int type)
{
    if(mRemoteType != type)
    {
        this->mRemoteType = type;
        emit remoteTypeChanged();
        QSettings settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JConfig.ini", QSettings::IniFormat);
        settings.setValue("JRobotRemoteType",type);
    }
}

QList<int> JRobot::getRemoteDirection()
{
    return mDirectionList;
}

void JRobot::saveRemoteDirection(QList<int> list)
{
    QSettings settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JltApp/JConfig.ini", QSettings::IniFormat);
    for(int i = 0; i < list.size(); i++)
    {
        QString key = "JRobotRemoteDirection"+QString::number(i+1);
        settings.setValue(key,list.at(i));
    }
    this->mDirectionList = list;
}

/**
 * @brief 初始化
 */
void JRobot::init()
{
    QObject *obj = nullptr;
    JConfig *jConfig = JConfig::getInstance();
    //加载插件
    if(jConfig->getType() == 0)
    {
        obj = loadPlugin("Plugins/JakaRobot.dll");
    }else
    {
        obj = loadPlugin("Plugins/KukaRobot.dll");
    }
    //加载插件数据
    if(obj)
    {
        QJsonObject pluginData = getPluginMetaData();
        this->setPluginConfig(pluginData["MetaData"].toObject());
        this->pluginHandle = qobject_cast<AbstractRobot *>(obj);
        this->pluginHandle->setup();
        this->pluginHandle->connect(jConfig->getRobotAddr(),jConfig->getRailAddr());
        this->pluginHandle->registerFunc(std::bind(&JRobot::pluginCallBack,this,std::placeholders::_1));
        this->setAddress(jConfig->getRobotAddr());
        this->setRailAddress(jConfig->getRailAddr());
    }
}

/**
 * @brief 释放
 */
void JRobot::release()
{
    if(pluginHandle)
    {
        this->pluginHandle->uninstall();
    }
}

/**
 * @brief 返回状态数据
 * @return QJsonObject
 */
QJsonObject JRobot::getStatusData()
{
    QJsonObject root;
    if(pluginHandle){
        root = this->pluginHandle->getStatusData();
    }
    root["loaded"] = getLoaded();
    root["power"] = getPower();
    root["deviceId"] = DeviceNumber::Device_Robot;

    this->setRailConnected(root["railConnected"].toBool());
    this->setState(root["state"].toInt());
    this->setRunNumber(root["runNumber"].toInt());
    this->updateData(root);
    this->setConnected(root["connected"].toBool());
    return root;
}

/**
 * @brief Server->Client->设置状态数据
 * @param obj
 */
void JRobot::setStatusData(const QJsonObject &obj)
{
    this->setPower(obj["power"].toInt());
    this->setLoaded(obj["loaded"].toBool());
    this->setConnected(obj["connected"].toBool());
    this->setRailConnected(obj["railConnected"].toBool());
    this->setRunNumber(obj["runNumber"].toInt());
    this->updateData(obj);
    emit coordinateChanged();
}

/**
 * @brief 返回静态数据
 * @return
 */
QJsonObject JRobot::getStaticData()
{
    QJsonObject root;
    if(pluginHandle)
    {
        root = pluginHandle->getStaticData();
        root["pluginData"] = getPluginMetaData();
    }
    root["deviceId"] = Device_Robot;
    root["code"] = 1;
    root["address"] = getAddress();
    root["railAddress"] = getRailAddress();
    return root;
}

/**
 * @brief Server->Client->设置静态数据
 * @param obj
 */
void JRobot::setStaticData(const QJsonObject &obj)
{
    if(obj["code"].toInt() == 1)
    {
        this->setPluginConfig(obj["pluginData"].toObject());
        this->setModel(obj["model"].toString());
        this->setAddress(obj["address"].toString());
        this->setRailAddress(obj["railAddress"].toString());
        this->setCaEnable(obj["caEnable"].toBool());
    }
    else
    {
        emit pluginMsgChanged(obj);
    }
}

void JRobot::pluginCallBack(const QJsonObject &obj)
{
    if(obj["code"].toInt() == 0x2000)
    {
        emit pluginMsgChanged(obj["data"].toObject());
    }
    emit dataChanged(obj);
}

/**
 * @brief 设置插件配置数据
 * @param metaData
 */
void JRobot::setPluginConfig(const QJsonObject &metaData)
{
    ;
}

/**
 * @brief 设置机械臂连接状态
 * @param value
 */
void JRobot::setConnected(bool value)
{
    if(value != mConnected)
    {
        this->mConnected = value;
        emit connectedChanged();
    }
}

void JRobot::setCaEnable(bool value)
{
    if(mCaEnable != value)
    {
        this->mCaEnable = value;
        emit caEnableChanged();
    }
}

/**
 * @brief 设置轨道连接状态
 * @param value
 */
void JRobot::setRailConnected(bool value)
{
    if(value != railConnected)
    {
        this->railConnected = value;
        emit railConnectedChanged(value);
    }
}

/**
 * @brief 更新实时数据
 * @param data
 */
void JRobot::updateData(const QJsonObject &obj)
{
    QJsonObject data = obj["data"].toObject();
    this->mPosition.setX(data["X"].toString());
    this->mPosition.setY(data["Y"].toString());
    this->mPosition.setZ(data["Z"].toString());
    this->mPosition.setRx(data["A"].toString());
    this->mPosition.setRy(data["B"].toString());
    this->mPosition.setRz(data["C"].toString());

    this->mPosition.setA1(data["A1"].toString());
    this->mPosition.setA2(data["A2"].toString());
    this->mPosition.setA3(data["A3"].toString());
    this->mPosition.setA4(data["A4"].toString());
    this->mPosition.setA5(data["A5"].toString());
    this->mPosition.setA6(data["A6"].toString());
    this->mPosition.setA7(data["E1"].toString());

    QJsonObject tool = obj["tool"].toObject();
    this->mTool.getTran()->setX(tool["X"].toDouble());
    this->mTool.getTran()->setY(tool["Y"].toDouble());
    this->mTool.getTran()->setZ(tool["Z"].toDouble());
    this->mTool.getRpy()->setRx(tool["A"].toDouble());
    this->mTool.getRpy()->setRy(tool["B"].toDouble());
    this->mTool.getRpy()->setRz(tool["C"].toDouble());

    QJsonObject base = obj["base"].toObject();
    this->mWorld.getTran()->setX(base["X"].toDouble());
    this->mWorld.getTran()->setY(base["Y"].toDouble());
    this->mWorld.getTran()->setZ(base["Z"].toDouble());
    this->mWorld.getRpy()->setRx(base["A"].toDouble());
    this->mWorld.getRpy()->setRy(base["B"].toDouble());
    this->mWorld.getRpy()->setRz(base["C"].toDouble());

    QJsonObject load = obj["load"].toObject();
    this->mLoad.setMass(load["mass"].toDouble());
    this->mLoad.getTran()->setX(load["X"].toDouble());
    this->mLoad.getTran()->setY(load["Y"].toDouble());
    this->mLoad.getTran()->setZ(load["Z"].toDouble());
    this->mLoad.getRpy()->setRx(base["A"].toDouble());
    this->mLoad.getRpy()->setRy(base["B"].toDouble());
    this->mLoad.getRpy()->setRz(base["C"].toDouble());
    this->mLoad.getInertia()->setX(load["JX"].toDouble());
    this->mLoad.getInertia()->setY(load["JY"].toDouble());
    this->mLoad.getInertia()->setZ(load["JZ"].toDouble());
}

/**
 * @brief 指令处理
 * @param obj
 */
void JRobot::commandProcessing(const QJsonObject &obj)
{
    this->pluginCommand(obj);
}

/**
 * @brief 插件对指令进行处理
 * @param root
 */
void JRobot::pluginCommand(const QJsonObject &root)
{
    if(pluginHandle)
    {
        pluginHandle->parseUserCommand(root);
    }
}

/**
 * @brief 到目标位置了吗
 * @param target
 * @return =true已到达 (未加载或未连接时默认已到达)
 */
bool JRobot::isArrived(const QJsonObject &target,int code)
{
    bool isSendFlag = true;
    double errorAngle = 0.5f;

    if(code == 4)
    {
        //轴位置是否到位置判断
        if(qAbs(target["A1"].toString().toDouble()-mPosition.getA1().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A2"].toString().toDouble()-mPosition.getA2().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A3"].toString().toDouble()-mPosition.getA3().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A4"].toString().toDouble()-mPosition.getA4().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A5"].toString().toDouble()-mPosition.getA5().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A6"].toString().toDouble()-mPosition.getA6().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["E1"].toString().toDouble()-mPosition.getA7().toDouble()) > errorAngle)
            isSendFlag = false;
    }
    else if(code == 5)
    {
        //空间位置是否到位置判断
        if(qAbs(target["X"].toString().toDouble()-mPosition.getX().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["Y"].toString().toDouble()-mPosition.getY().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["Z"].toString().toDouble()-mPosition.getZ().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["A"].toString().toDouble()-mPosition.getRx().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["B"].toString().toDouble()-mPosition.getRy().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["C"].toString().toDouble()-mPosition.getRz().toDouble()) > errorAngle)
            isSendFlag = false;
        if(qAbs(target["E1"].toString().toDouble()-mPosition.getA7().toDouble()) > errorAngle)
            isSendFlag = false;
    }

    return isSendFlag;
}


void JRobot::sendData(const QJsonObject &data)
{
    StudioController *studioController = StudioController::getInstance();
    if(studioController->getControllerType() == StudioController::RemoteControllerOnly)
    {
        emit dataChanged(data);
    }
    else
    {
        this->commandProcessing(data);
    }
}

/**
 * @brief 手动控制
 * @param data code =9工具坐标系遥控 =3世界坐标系遥控
 */
void JRobot::jogMovement(int code,const QJsonObject &data)
{
    QJsonObject root;
    root["code"] = code;
    root["data"] = data;
    root["deviceId"] = Device_Robot;
    this->sendData(root);
}

/**
 * @brief 笛卡尔空间运动
 * @param data
 */
void JRobot::absPosMovement(const QJsonObject &data)
{
    QJsonObject cmd;
    cmd["code"] = data["code"].toInt();
    cmd["data"] = data;
    cmd["deviceId"] = Device_Robot;
    this->sendData(cmd);
}

/**
 * @brief 连续任务
 * @param data
 */
void JRobot::continueMovement(const QJsonObject &data)
{
    QJsonObject cmd;
    cmd["code"] = RobotRemote_ContinuousLoad;
    cmd["data"] = data;
    this->sendData(cmd);
}

/**
 * @brief 连接运动开始
 */
void JRobot::continueMovementStart()
{
    QJsonObject cmd;
    cmd["code"] = RobotRemote_ContinuousLoadFinished;
    this->sendData(cmd);
}

/**
 * @brief 运行停止
 */
void JRobot::runStop()
{
    QJsonObject cmd;
    cmd["code"] = RobotRemote_Stop;
    cmd["deviceId"] = Device_Robot;
    this->sendData(cmd);
}

void JRobot::setModel(const QString &str)
{
    this->mModel = str;
    emit modelChanged();
}

void JRobot::setRunNumber(int value)
{
    if(runNumber != value)
    {
        this->runNumberLast = runNumber;
        this->runNumber = value;
        emit runNumberChanged();
    }
}

void JRobot::setAddress(const QString &str)
{
    this->mAddress = str;
    emit addressChanged();
}

void JRobot::setRailAddress(const QString &str)
{
    this->mRailAddress = str;
    emit railAddressChanged();
}
