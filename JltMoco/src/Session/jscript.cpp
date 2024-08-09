#include "Session/jscript.h"
#include "Session/jscriptarchive.h"
#include "Studio/jcameradevice.h"
#include "Studio/studiocontroller.h"
#include "Studio/jrobot.h"
#include "Studio/jglobalremoteparam.h"

#include <QFile>
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QQmlEngine>

#include "jltmoco.h"

namespace jltmoco
{

JScript::JScript(QObject *parent)
    : QObject(parent)
{
    this->mCurrentNode = NULL;
    this->mRunningNode = NULL;
    this->mRunningDirection = 0;
    this->setObjectName("Scene");

    this->mChanged = false;
    this->mFileName.clear();
    this->mEditEnable = true;
    this->mFileState = FileState_NULL;
    this->mScriptType = ScriptType_Other;
    this->mRemoteMode = RemoteMode_MoveOnly;

    //机械臂连接成功后数据设置
    connect(JRobot::getInstance(),&JRobot::connectedChanged,
            this,&JScript::onRobotConnectedChanged);
    //更新存档目录
    JScriptArchive *archive = new JScriptArchive(true);
    archive->start();
}

JScript::~JScript()
{
    ;
}

void JScript::setChanged(bool value)
{
    if(mChanged != value)
    {
        this->mChanged = value;
        emit changedChanged();
    }
}

void JScript::setFileName(const QString &fileName)
{
    if(mFileName != fileName)
    {
        this->mFileName = fileName;
        emit fileNameChanged();
    }
}

void JScript::setFileState(int state)
{
    if(state != mFileState)
    {
        this->mFileState = state;
        emit fileStateChanged();
    }
}

void JScript::setEditEnable(bool enable)
{
    if(enable != mEditEnable)
    {
        this->mEditEnable = enable;
        emit editEnableChanged();
    }
}

void JScript::setRemoteMode(int mode)
{
    if(mRemoteMode != mode)
    {
        this->mRemoteMode = mode;
        emit remoteModeChanged();
    }
}

void JScript::setVersion(const QString &version)
{
    if(mVersion != version)
    {
        this->mVersion = version;
        emit versionChanged();
    }
}

void JScript::setScriptType(int type)
{
    if(mScriptType != type)
    {
        this->mScriptType = type;
        emit scriptTypeChanged();
    }
}

void JScript::setCurrentNode(JNode* node)
{
    if(mCurrentNode != node)
    {
        if(mCurrentNode)
        {
            this->mCurrentNode->setChecked(false);
        }
        this->mCurrentNode = node;
        if(mCurrentNode)
        {
            this->mCurrentNode->setChecked(true);
        }
        emit currentNodeChanged();
    }
}

void JScript::setRunningNode(JNode* node)
{
    if(mRunningNode != node)
    {
        this->mRunningNode = node;
        emit runningNodeChanged();
    }
}

JNode *JScript::createNextNodeData(const QJsonObject &nodeData,JNode *parent)
{
    //创建节点对象
    JNode *node = nullptr;
    if(parent==nullptr)
        node = new JNode(this);
    else
        node = new JNode(parent);

    //保证qml调用后不删除
    QQmlEngine::setObjectOwnership(node, QQmlEngine::CppOwnership);
    //设置节点附件的脚本对象
    node->setScript(this);
    //读取脚本节点数据
    node->setData(nodeData);
    //设置绑定节点
    node->setLastNode(parent);
    //设置选中状态
    if(node->getChecked())
    {
        this->setCurrentNode(node);
    }
    if(nodeData.contains("Next"))
    {
        node->setNextNode(createNextNodeData(nodeData["Next"].toObject(),node));
    }

    return node;
}

int JScript::loadFile()
{
    //地址为空
    if(getFileName().isEmpty())
        return 1;

    QFile file(getFileName());
    //文件不存在
    if(!file.exists())
        return 2;
    //文件打开失败
    if(!file.open(QIODevice::ReadOnly))
        return 3;

    //读取文件
    QByteArray datas = file.readAll();
    file.close();

    //文件解析失败
    QJsonParseError *error = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(datas,error);
    if(error->error != QJsonParseError::NoError)
        return 4;

    //文件内容为空
    QJsonObject scriptData = doc.object();
    if(scriptData.isEmpty())
        return 5;

    //文件内容版本错误
    QString version = scriptData["Version"].toString();
    if(!version.contains("JTL_SCRIPT_WINDOW_5_0"))
        return 6;

    this->setVersion(version);
    this->setScriptType(scriptData["CameraType"].toInt());
    this->setRemoteMode(scriptData["RemoteMode"].toInt());
    //! 读取脚本场景数据
    QJsonObject scene = scriptData["Scene"].toObject();
    this->mGlScene.setSceneX(scene["X"].toDouble());
    this->mGlScene.setSceneY(scene["Y"].toDouble());
    this->mGlScene.setGridWidth(scene["GridWidth"].toDouble());
    //! 读取全局数据
    QJsonObject global = scene["Global"].toObject();
    foreach (const QString &key, global.keys())
    {
        QJsonObject item = global.value(key).toObject();
        if(key.toInt() == DeviceNumber::Device_Robot)
        {
            this->mGlRobot.setPrgV(item["PrgV"].toInt());
            //加载脚本时,如果机械臂已经连接,则更新model
            QString str = item["Model"].toString();
            if(str.isEmpty() && JRobot::getInstance()->getConnected())
                this->mGlRobot.setModel(JRobot::getInstance()->getModel());
            else
                this->mGlRobot.setModel(str);
        }
        else if(key.toInt() == DeviceNumber::Device_Camera)
        {
            this->mGlCamera.setRecordingDuration(item["RecordingDuration"].toInt());
            this->mGlCamera.setMoveDelay(item["MoveDelay"].toInt());
        }
        else if(key.toInt() == DeviceNumber::Device_FollowFocus)
        {
            this->mGlFollowFocus.setFocusMode((JScriptFollowFocus::FollowFocusMode)item["FocusMode"].toInt());
            this->mGlFollowFocus.setZoomMode((JScriptFollowFocus::FollowFocusMode)item["ZoomMode"].toInt());
            this->mGlFollowFocus.setIrisMode((JScriptFollowFocus::FollowFocusMode)item["IrisMode"].toInt());
            this->mGlFollowFocus.setPathRecord(item["PathRecord"].toObject());
            this->mGlFollowFocus.setTimeRecord(item["TimeRecord"].toObject());
            QJsonObject constant = item["Constant"].toObject();
            this->mGlFollowFocus.setFocusValue(constant["focus"].toInt());
            this->mGlFollowFocus.setZoomValue(constant["zoom"].toInt());
            this->mGlFollowFocus.setIrisValue(constant["iris"].toInt());
        }
        else if(key.toInt() == DeviceNumber::Device_Turntable)
        {
            this->mGlTurnplate.setAcc(item["Acc"].toInt());
            this->mGlTurnplate.setDec(item["Dec"].toInt());
            this->mGlTurnplate.setSpeed(item["Speed"].toInt());
            this->mGlTurnplate.setDuration(item["Duration"].toInt());
            this->mGlTurnplate.setDirection(item["Ori"].toInt());
            this->mGlTurnplate.setStartTime(item["StartTime"].toInt());
        }
    }

    //读取脚本场景的节点数据
    QJsonArray nodes = scene["Nodes"].toArray();
    for (int var = 0; var < nodes.count(); ++var)
    {
        createNextNodeData(nodes[var].toObject());
    }
    this->setFileState(FileState_Ready);
    return 0;
}

QList<JNode *> JScript::getNodes()
{
    return findChildren<JNode*>(QString(),Qt::FindDirectChildrenOnly);
}

JNode* JScript::getNode(const QString &key)
{
    if(key.isEmpty())
        return nullptr;

    return findChild<JNode*>(key);
}

void JScript::removeNode(JNode *node)
{
    if(node->getNextNode())
    {
        node->getNextNode()->setParent(this);
        node->getNextNode()->setLastNode(NULL);
    }
    if(node->getLastNode())
    {
        node->getLastNode()->setNextNode(NULL);
    }
    if(node == getCurrentNode())
    {
        this->setCurrentNode(NULL);
    }
    node->deleteLater();
}

JNode* JScript::createNode(qreal x,qreal y,int robotType,int nodeType)
{
    JNode *node = new JNode(this);
    QQmlEngine::setObjectOwnership(node, QQmlEngine::CppOwnership);
    node->setScript(this);
    node->setX(x);
    node->setY(y);
    node->setType(nodeType);
    if(nodeType == JNode::NodeType_Move)
        node->setObjectName(getRandomKey());
    else
        node->setObjectName("-");
    node->getRobot()->setType(robotType);
    return node;
}

QString JScript::previewUpdate(const QString &path,JNode *node)
{
    if(path.isEmpty())
        return QString();

    QString img = path+"/nodeFrame/"+QDateTime::currentDateTime().toString("hhmmss_")+node->objectName()+".jpg";
    if(JCameraDevice::getInstance()->getFrameImage().save(img))
    {
        node->setPreview(img);
        return img;
    }

    return QString();
}

void JScript::setNodeTitle(JNode *node,const QString &title)
{
    node->setTitle(title);
}

/**
 * @brief 返回随机字符串
 * @param length
 * @return
 */
QByteArray JScript::getRandomKey(int length)
{
    QByteArray keys = "QWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    QByteArray datas;
    for (int var = 0; var < length; ++var)
        datas.append(keys.at(QRandomGenerator::global()->bounded(keys.length())));

    return datas;
}

void JScript::onRobotConnectedChanged()
{
    if(getFileState() != FileState_Ready)
        return;
    if(JRobot::getInstance()->getConnected() && mGlRobot.getModel().isEmpty())
    {
        mGlRobot.setModel(JRobot::getInstance()->getModel());
        this->setChanged(true);
    }
}

/**
 * @brief 脚本保存
 */
int JScript::save()
{
    if(getFileState() != FileState_Ready)
        return 1;
    if(getFileName().isEmpty())
        return 2;
    QFile file(getFileName());
    if(!file.exists())
        return 3;
    if(!file.open(QIODevice::WriteOnly))
        return 4;

    QJsonDocument doc;
    doc.setObject(toJson());
    file.write(doc.toJson());
    file.close();
    this->setChanged(false);
    return 0;
}

/**
 * @brief 将脚本文件保存为JSON对象
 * @return
 */
QJsonObject JScript::toJson()
{
    QJsonObject scriptData;
    scriptData["Version"] = getVersion();
    scriptData["CameraType"] = getScriptType();
    scriptData["RemoteMode"] = getRemoteMode();
    //! 读取脚本场景数据
    QJsonObject scene;
    scene["X"] = mGlScene.getSceneX();
    scene["Y"] = mGlScene.getSceneY();
    scene["GridWidth"] = mGlScene.getGridWidth();
    //! 转换脚本场景全局数据
    QJsonObject global;
    //机械臂全局数据
    QJsonObject robot;
    robot["PrgV"] = mGlRobot.getPrgV();
    robot["Model"] = mGlRobot.getModel();
    global[QString::number(Device_Robot)] = robot;
    //相机全局数据
    QJsonObject camera;
    camera["MoveDelay"] = mGlCamera.getMoveDelay();
    camera["RecordingDuration"] = mGlCamera.getRecordingDuration();
    global[QString::number(Device_Camera)] = camera;
    //跟焦器全局数据
    global[QString::number(Device_FollowFocus)] = mGlFollowFocus.toJson();
    //转盘全局数据
    QJsonObject trnplates;
    trnplates["Acc"] = mGlTurnplate.getAcc();
    trnplates["Dec"] = mGlTurnplate.getDec();
    trnplates["Speed"] = mGlTurnplate.getSpeed();
    trnplates["Duration"] = mGlTurnplate.getDuration();
    trnplates["Ori"] = mGlTurnplate.getDirection();
    trnplates["StartTime"] = mGlTurnplate.getStartTime();
    global[QString::number(Device_Turntable)] = trnplates;
    //! 转换节点数据
    QJsonArray nodes;
    foreach (JNode *node, getNodes())
    {
        nodes.append(node->toJson());
    }
    scene["Nodes"] = nodes;
    scene["Global"] = global;
    scriptData["Scene"] = scene;
    return scriptData;
}

void JScript::clear()
{
    foreach (JNode *node, getNodes())
    {
        node->deleteLater();
    }
}

/**
 * @brief 节点的辅助位置复位
 * @param code =4轴旋转 =5空间位置
 */
void JScript::assistNodeReset(int code)
{
    if(!getCurrentNode())
        return;
    if(getCurrentNode()->getRobot()->getType() != 3)
        return;
    if(!JRobot::getInstance()->getConnected())
        return;

    QJsonObject nodeJson;
    //机械臂数据
    QJsonObject robotJson;
    robotJson["code"] = code;
    robotJson["type"] = getCurrentNode()->getRobot()->getType();
    robotJson["param"] = JGlobalRemoteParam::getInstance()->toRobotParamJson();
    robotJson["target"] = getCurrentNode()->getRobot()->getAssist()->toJson();
    nodeJson[QString::number(Device_Robot)] = robotJson;
    //跟焦器数据
    nodeJson[QString::number(Device_FollowFocus)] = getCurrentNode()->getFollowFocus()->toJson();
    //设置转盘数据
    nodeJson[QString::number(Device_Turntable)] = getCurrentNode()->getTrunplate()->toJson();
    //发送指令
    QJsonObject cmdJson;
    cmdJson["deviceId"] = Device_ScriptController;
    cmdJson["code"] = ScriptCommandCode_NodeReset;
    cmdJson["index"] = 0;
    cmdJson["data"] = nodeJson;
    StudioController::getInstance()->sendCommandData(cmdJson);
}

/**
 * @brief 节点的目标位置复位
 * @param code =4轴旋转 =5空间位置
 */
void JScript::targetNodeReset(int code)
{
    if(!getCurrentNode())
        return;
    if(!JRobot::getInstance()->getConnected())
        return;
    QJsonObject nodeJson;
    QJsonObject robotJson;
    robotJson["code"] = code;
    robotJson["type"] = getCurrentNode()->getRobot()->getType();
    robotJson["param"] = JGlobalRemoteParam::getInstance()->toRobotParamJson();
    robotJson["target"] = getCurrentNode()->getRobot()->getTarget()->toJson();
    nodeJson[QString::number(Device_Robot)] = robotJson;
    //跟焦器数据
    nodeJson[QString::number(Device_FollowFocus)] = getCurrentNode()->getFollowFocus()->toJson();
    //设置转盘数据
    nodeJson[QString::number(Device_Turntable)] = getCurrentNode()->getTrunplate()->toJson();
    //发送指令
    QJsonObject cmdJson;
    cmdJson["deviceId"] = Device_ScriptController;
    cmdJson["code"] = ScriptCommandCode_NodeReset;
    cmdJson["index"] = 0;
    cmdJson["data"] = nodeJson;
    StudioController::getInstance()->sendCommandData(cmdJson);
}

/**
 * @brief 返回脚本运行需要的Node数据
 * @param node 节点对象
 * @param defaultRobotType =0依据节点数据 =其它则依据该参数
 * @return
 */
QJsonObject JScript::getNodeJson(JNode *node, int defaultRobotType)
{
    QJsonObject nodeJson;
    //机械臂数据
    QJsonObject robotJson;
    if(getScriptType() == ScriptType_Image)
    {
        if(node->getRobot()->getType() == 1)
            robotJson["code"] = 4;
        else
            robotJson["code"] = 5;
    }
    QJsonObject param = node->getRobot()->toParamJson();
    param["PrgV"] = mGlRobot.getPrgV();
    robotJson["param"] = param;
    robotJson["target"] = node->getRobot()->getTarget()->toJson();

    if(defaultRobotType == 0)
    {
        if(mRunningDirection == 1)
        {
            robotJson["type"] = node->getRobot()->getType();
            if(node->getRobot()->getType() == 3)
            {
                robotJson["assist"] = node->getRobot()->getAssist()->toJson();
            }
        }
        else if(mRunningDirection == -1)
        {
            robotJson["type"] = node->getNextNode()->getRobot()->getType();
            if(node->getNextNode()->getRobot()->getType() == 3)
            {
                robotJson["assist"] = node->getNextNode()->getRobot()->getAssist()->toJson();
            }
        }
    }
    else
    {
        robotJson["type"] = defaultRobotType;
    }

    nodeJson[QString::number(Device_Robot)] = robotJson;
    //相机数据
    nodeJson[QString::number(Device_Camera)] = node->getCamera()->toJson();
    //跟焦器数据
    nodeJson[QString::number(Device_FollowFocus)] = getCurrentNode()->getFollowFocus()->toJson();
    //转盘数据
    nodeJson[QString::number(Device_Turntable)] = getCurrentNode()->getTrunplate()->toJson();
    return nodeJson;
}

/**
 * @brief 脚本执行
 * @param skipCount >0则向前执行 <向后执行
 * @param skipCount=0时,当direction=true表示向前执行到末尾 =false向前执行到末尾
 */
void JScript::scriptRun(int skipCount, bool direction)
{
    if(!getCurrentNode())
        return;
    if(!JRobot::getInstance()->getConnected())
        return;

    //开始选中节点无连接
    JNode *node = getCurrentNode();
    if(node->objectName() == NODE_START_NAME)
    {
        if(node->getNextNode() == NULL)
            return;
        node = node->getNextNode();
    }

    QJsonObject scriptJson;
    scriptJson["CameraType"] = getScriptType();
    scriptJson["CurrentIndex"] = 0;
    //视频脚本数据
    if(getScriptType() == ScriptType_Video)
    {
        scriptJson["MoveDelay"] = getGlCamera()->getMoveDelay();
        scriptJson["RecordingDuration"] = getGlCamera()->getRecordingDuration();
    }
    //脚本节点数据
    QJsonArray nodeArray;
    if(skipCount == 0)
    {
        if(direction)
        {
            mRunningDirection = 1;
            while (node != NULL)
            {
                nodeArray.append(getNodeJson(node));
                node = node->getNextNode();
            }
        }
        else
        {
            mRunningDirection = -1;
            //向后执行时初始节点机械臂类型设置为line(2)
            nodeArray.append(getNodeJson(node,2));
            while (node != NULL)
            {
                node = node->getLastNode();
                //过滤掉开始节点
                if(node && node->objectName() != "-")
                {
                    nodeArray.append(getNodeJson(node));
                }
            }
        }
    }
    else if(skipCount > 0)
    {
        mRunningDirection = 1;
        for (int i = 0; i <= skipCount; ++i)
        {
            if(node == NULL)
                break;

            nodeArray.append(getNodeJson(node));
            node = node->getNextNode();
        }
    }
    else if(skipCount < 0)
    {
        mRunningDirection = -1;
        //向后执行时初始节点机械臂类型设置为line(2)
        nodeArray.append(getNodeJson(node,2));
        //向后循环获取数据
        for (int i = skipCount; i < 0; ++i)
        {
            if(node == NULL)
                break;

            node = node->getLastNode();
            //过滤掉开始节点
            if(node && node->objectName() != "-")
            {
                nodeArray.append(getNodeJson(node));
            }
        }
    }
    else
    {
        mRunningDirection = 0;
    }
    scriptJson["Nodes"] = nodeArray;

    //发送指令
    QJsonObject cmdJson;
    cmdJson["deviceId"] = Device_ScriptController;
    cmdJson["code"] = ScriptCommandCode_ScriptExec;
    cmdJson["data"] = scriptJson;
    cmdJson["runmode"] = getRemoteMode();
    StudioController::getInstance()->sendCommandData(cmdJson);
}

void JScript::stopRun()
{
    QJsonObject cmdJson;
    cmdJson["deviceId"] = Device_ScriptController;
    cmdJson["code"] = ScriptCommandCode_Stop;
    StudioController::getInstance()->sendCommandData(cmdJson);
}

}

