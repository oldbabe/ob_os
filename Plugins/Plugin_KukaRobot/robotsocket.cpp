#include "robotsocket.h"

RobotSocket::RobotSocket(QObject *parent)
    : QTcpSocket{parent}
{
    QObject::connect(this,&QTcpSocket::readyRead,
            this,&RobotSocket::onReadyRead);

    this->mRunMode = -1;
    this->continueNumber = 0;

    //创建根目录
    XMLElement* root = cmdDoc.NewElement("CMD");
    cmdDoc.InsertEndChild(root);
    //RunMode
    XMLElement* runMode = cmdDoc.NewElement("RunMode");
    root->InsertEndChild(runMode);
    runMode->SetText(mRunMode);
    //NodeType
    XMLElement* nodeType = cmdDoc.NewElement("NodeType");
    root->InsertEndChild(nodeType);
    nodeType->SetText(0);
    //NodeType
    XMLElement* nodeNumber = cmdDoc.NewElement("NodeNumber");
    root->InsertEndChild(nodeNumber);
    nodeNumber->SetText(0);
    //param
    XMLElement* param = cmdDoc.NewElement("Param");
    root->InsertEndChild(param);
    param->SetAttribute("PrgV",30);
    param->SetAttribute("RobotV",30);
    param->SetAttribute("RobotA",30);
    param->SetAttribute("PathV",30);
    param->SetAttribute("PathA",30);
    param->SetAttribute("TsValue",0);
    param->SetAttribute("Waiting",0);
    //target
    XMLElement* target = cmdDoc.NewElement("Target");
    root->InsertEndChild(target);
    target->SetAttribute("P1","0");
    target->SetAttribute("P2","0");
    target->SetAttribute("P3","0");
    target->SetAttribute("P4","0");
    target->SetAttribute("P5","0");
    target->SetAttribute("P6","0");
    target->SetAttribute("E1","0");
    //assist
    XMLElement* assist = cmdDoc.NewElement("Assist");
    root->InsertEndChild(assist);
    assist->SetAttribute("P1","0");
    assist->SetAttribute("P2","0");
    assist->SetAttribute("P3","0");
    assist->SetAttribute("P4","0");
    assist->SetAttribute("P5","0");
    assist->SetAttribute("P6","0");
    assist->SetAttribute("E1","0");
    assist->SetAttribute("CA","0");

    // cmdDoc.SaveFile("C:\\Users\\yxh\\Desktop\\dasd.xml");
}

void RobotSocket::moveControl(const QJsonObject &cmd)
{
    // qDebug() << "moveControl:" << cmd;
    int code = cmd["code"].toInt();
    if(code == 1)//运动停止
    {
        this->rumMode = -1;
        this->continueNumber = 0;
        this->continueList.clear();
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText(1);
        this->sendDoc();
    }
    else if(code == 2||code == 3||code == 9)
    {
        jogData = cmd["data"].toObject();
        rumMode = code;
    }
    else if(code == 4)
    {
        QJsonObject data = cmd["data"].toObject();
        QJsonObject paramJson = data["param"].toObject();
        QJsonObject targetJson = data["target"].toObject();
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText("4");
        XMLElement* param = cmdDoc.RootElement()->FirstChildElement("Param");
        param->SetAttribute("PrgV",paramJson["PrgV"].toInt());
        param->SetAttribute("RobotV",paramJson["RobotV"].toInt());
        param->SetAttribute("RobotA",paramJson["RobotA"].toInt());
        param->SetAttribute("PathV",paramJson["PathA"].toInt());
        param->SetAttribute("PathA",paramJson["PathV"].toInt());
        param->SetAttribute("TsValue",paramJson["TsValue"].toInt());
        param->SetAttribute("Waiting",paramJson["Waiting"].toInt());
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        target->SetAttribute("P1",targetJson["A1"].toString("0").toStdString().c_str());
        target->SetAttribute("P2",targetJson["A2"].toString("0").toStdString().c_str());
        target->SetAttribute("P3",targetJson["A3"].toString("0").toStdString().c_str());
        target->SetAttribute("P4",targetJson["A4"].toString("0").toStdString().c_str());
        target->SetAttribute("P5",targetJson["A5"].toString("0").toStdString().c_str());
        target->SetAttribute("P6",targetJson["A6"].toString("0").toStdString().c_str());
        target->SetAttribute("E1",targetJson["E1"].toString("0").toStdString().c_str());
        this->sendDoc();
    }
    else if(code == 5)
    {
        QJsonObject data = cmd["data"].toObject();
        QJsonObject paramJson = data["param"].toObject();
        QJsonObject targetJson = data["target"].toObject();
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText("5");
        XMLElement* param = cmdDoc.RootElement()->FirstChildElement("Param");
        param->SetAttribute("PrgV",paramJson["PrgV"].toInt());
        param->SetAttribute("RobotV",paramJson["RobotV"].toInt());
        param->SetAttribute("RobotA",paramJson["RobotA"].toInt());
        param->SetAttribute("PathV",paramJson["PathA"].toInt());
        param->SetAttribute("PathA",paramJson["PathV"].toInt());
        param->SetAttribute("TsValue",paramJson["TsValue"].toInt());
        param->SetAttribute("Waiting",paramJson["Waiting"].toInt());
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        target->SetAttribute("P1",targetJson["X"].toString("0").toStdString().c_str());
        target->SetAttribute("P2",targetJson["Y"].toString("0").toStdString().c_str());
        target->SetAttribute("P3",targetJson["Z"].toString("0").toStdString().c_str());
        target->SetAttribute("P4",targetJson["A"].toString("0").toStdString().c_str());
        target->SetAttribute("P5",targetJson["B"].toString("0").toStdString().c_str());
        target->SetAttribute("P6",targetJson["C"].toString("0").toStdString().c_str());
        target->SetAttribute("E1",targetJson["E1"].toString("0").toStdString().c_str());
        this->sendDoc();
    }
    else if(code == 6)
    {
        QJsonObject data = cmd["data"].toObject();
        QJsonObject paramJson = data["param"].toObject();
        QJsonObject targetJson = data["target"].toObject();
        QJsonObject assistJson = data["assist"].toObject();

        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText("6");
        XMLElement* type = cmdDoc.RootElement()->FirstChildElement("NodeType");
        type->SetText(data["type"].toInt());
        XMLElement* number = cmdDoc.RootElement()->FirstChildElement("NodeNumber");
        number->SetText(continueNumber);
        XMLElement* param = cmdDoc.RootElement()->FirstChildElement("Param");
        param->SetAttribute("PrgV",paramJson["PrgV"].toInt());
        param->SetAttribute("RobotV",paramJson["RobotV"].toInt());
        param->SetAttribute("RobotA",paramJson["RobotA"].toInt());
        param->SetAttribute("PathV",paramJson["PathA"].toInt());
        param->SetAttribute("PathA",paramJson["PathV"].toInt());
        param->SetAttribute("TsValue",paramJson["TsValue"].toInt());
        param->SetAttribute("Waiting",paramJson["Waiting"].toInt());
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        target->SetAttribute("P1",targetJson["X"].toString("0").toStdString().c_str());
        target->SetAttribute("P2",targetJson["Y"].toString("0").toStdString().c_str());
        target->SetAttribute("P3",targetJson["Z"].toString("0").toStdString().c_str());
        target->SetAttribute("P4",targetJson["A"].toString("0").toStdString().c_str());
        target->SetAttribute("P5",targetJson["B"].toString("0").toStdString().c_str());
        target->SetAttribute("P6",targetJson["C"].toString("0").toStdString().c_str());
        target->SetAttribute("E1",targetJson["E1"].toString("0").toStdString().c_str());
        XMLElement* assist = cmdDoc.RootElement()->FirstChildElement("Assist");
        assist->SetAttribute("P1",assistJson["X"].toString("0").toStdString().c_str());
        assist->SetAttribute("P2",assistJson["Y"].toString("0").toStdString().c_str());
        assist->SetAttribute("P3",assistJson["Z"].toString("0").toStdString().c_str());
        assist->SetAttribute("P4",assistJson["A"].toString("0").toStdString().c_str());
        assist->SetAttribute("P5",assistJson["B"].toString("0").toStdString().c_str());
        assist->SetAttribute("P6",assistJson["C"].toString("0").toStdString().c_str());
        assist->SetAttribute("E1",assistJson["E1"].toString("0").toStdString().c_str());
        assist->SetAttribute("CA",paramJson["AssistCA"].toDouble());
        this->continueNumber++;
        this->sendDoc();
    }
    else if(code == 7)
    {
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText("7");
        this->sendDoc();
    }
    else if(code == 10)
    {
        coordinatesData = cmd["data"].toObject();
        rumMode = code;
    }
}

void RobotSocket::onReadyRead()
{
    if(bytesAvailable() <= 0)
        return;

    this->recvBuffer.append(readAll());
    this->traversalRecvData();
    //指令轮询
    this->commandLoop();
}

void RobotSocket::commandLoop()
{
    if(rumMode == 2)//轴控制
    {
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText(2);
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        double P1 = jogData["P1"].toString().toDouble()*1.5f;
        double P2 = jogData["P2"].toString().toDouble()*1.5f;
        double P3 = jogData["P3"].toString().toDouble()*1.5f;
        double P4 = jogData["P4"].toString().toDouble()*1.5f;
        double P5 = jogData["P5"].toString().toDouble()*1.5f;
        double P6 = jogData["P6"].toString().toDouble()*1.5f;
        double P7 = jogData["P7"].toString().toDouble()*35.0f;
        target->SetAttribute("P1",QString::number(P1,'f',6).toStdString().c_str());
        target->SetAttribute("P2",QString::number(P2,'f',6).toStdString().c_str());
        target->SetAttribute("P3",QString::number(P3,'f',6).toStdString().c_str());
        target->SetAttribute("P4",QString::number(P4,'f',6).toStdString().c_str());
        target->SetAttribute("P5",QString::number(P5,'f',6).toStdString().c_str());
        target->SetAttribute("P6",QString::number(P6,'f',6).toStdString().c_str());
        target->SetAttribute("E1",QString::number(P7,'f',6).toStdString().c_str());
        this->sendDoc();
    }
    else if(rumMode == 3)
    {
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText(3);
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        double P1 = jogData["P1"].toString().toDouble()*20.0f;
        double P2 = jogData["P2"].toString().toDouble()*20.0f;
        double P3 = jogData["P3"].toString().toDouble()*20.0f;
        double P4 = jogData["P4"].toString().toDouble()*1.0f;
        double P5 = jogData["P5"].toString().toDouble()*1.0f;
        double P6 = jogData["P6"].toString().toDouble()*1.0f;
        double P7 = jogData["P7"].toString().toDouble()*35.0f;
        target->SetAttribute("P1",QString::number(P1,'f',6).toStdString().c_str());
        target->SetAttribute("P2",QString::number(P2,'f',6).toStdString().c_str());
        target->SetAttribute("P3",QString::number(P3,'f',6).toStdString().c_str());
        target->SetAttribute("P4",QString::number(P4,'f',6).toStdString().c_str());
        target->SetAttribute("P5",QString::number(P5,'f',6).toStdString().c_str());
        target->SetAttribute("P6",QString::number(P6,'f',6).toStdString().c_str());
        target->SetAttribute("E1",QString::number(P7,'f',6).toStdString().c_str());
        this->sendDoc();
    }
    else if(rumMode == 9)
    {
        XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
        code->SetText(9);
        XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
        double P1 = jogData["P1"].toString().toDouble()*20.0f;
        double P2 = jogData["P2"].toString().toDouble()*20.0f;
        double P3 = jogData["P3"].toString().toDouble()*20.0f;
        double P4 = jogData["P4"].toString().toDouble()*1.0f;
        double P5 = jogData["P5"].toString().toDouble()*1.0f;
        double P6 = jogData["P6"].toString().toDouble()*1.0f;
        double P7 = jogData["P7"].toString().toDouble()*35.0f;
        target->SetAttribute("P1",QString::number(P1,'f',6).toStdString().c_str());
        target->SetAttribute("P2",QString::number(P2,'f',6).toStdString().c_str());
        target->SetAttribute("P3",QString::number(P3,'f',6).toStdString().c_str());
        target->SetAttribute("P4",QString::number(P4,'f',6).toStdString().c_str());
        target->SetAttribute("P5",QString::number(P5,'f',6).toStdString().c_str());
        target->SetAttribute("P6",QString::number(P6,'f',6).toStdString().c_str());
        target->SetAttribute("E1",QString::number(P7,'f',6).toStdString().c_str());
        this->sendDoc();
    }
    else if(rumMode == 10)
    {
        if(coordinatesData.contains("world"))
        {
            QJsonObject world = coordinatesData.take("world").toObject();
            XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
            code->SetText(13);
            XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
            target->SetAttribute("P1",QString::number(world["X"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P2",QString::number(world["Y"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P3",QString::number(world["Z"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P4",QString::number(world["A"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P5",QString::number(world["B"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P6",QString::number(world["C"].toDouble(),'f',6).toStdString().c_str());
            this->sendDoc();
        }
        else if(coordinatesData.contains("tool"))
        {
            QJsonObject tool = coordinatesData.take("tool").toObject();
            XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
            code->SetText(12);
            XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
            target->SetAttribute("P1",QString::number(tool["X"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P2",QString::number(tool["Y"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P3",QString::number(tool["Z"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P4",QString::number(tool["A"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P5",QString::number(tool["B"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P6",QString::number(tool["C"].toDouble(),'f',6).toStdString().c_str());
            this->sendDoc();
        }
        else if(coordinatesData.contains("load"))
        {
            QJsonObject load = coordinatesData.take("load").toObject();
            XMLElement* code = cmdDoc.RootElement()->FirstChildElement("RunMode");
            code->SetText(14);
            XMLElement* target = cmdDoc.RootElement()->FirstChildElement("Target");
            target->SetAttribute("P1",QString::number(load["X"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P2",QString::number(load["Y"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P3",QString::number(load["Z"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P4",QString::number(load["A"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P5",QString::number(load["B"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("P6",QString::number(load["C"].toDouble(),'f',6).toStdString().c_str());
            target->SetAttribute("E1",QString::number(load["M"].toDouble(),'f',6).toStdString().c_str());
            XMLElement* assist = cmdDoc.RootElement()->FirstChildElement("Assist");
            assist->SetAttribute("P1",QString::number(load["JX"].toDouble(),'f',6).toStdString().c_str());
            assist->SetAttribute("P2",QString::number(load["JY"].toDouble(),'f',6).toStdString().c_str());
            assist->SetAttribute("P3",QString::number(load["JZ"].toDouble(),'f',6).toStdString().c_str());
            this->sendDoc();
        }
        else
        {
            rumMode = -1;
        }
    }
}

void RobotSocket::traversalRecvData()
{
    int startIndex = recvBuffer.indexOf("<Data>");
    if(startIndex == -1)
    {
        qDebug() << "head error: clearAll" << QDateTime::currentDateTime().toString("hh::mm::ss::zzz");
        this->recvBuffer.clear();
        return;
    }

    int endIndex = recvBuffer.indexOf("</Data>",startIndex+6);
    if(endIndex == -1)
    {
        return;
    }

    //读取一包数据
    this->parseRecvData(recvBuffer.mid(startIndex,endIndex+7));
    //移除已读取数据
    this->recvBuffer.remove(0,endIndex+7);

    //递归遍历
    if(!recvBuffer.isEmpty())
    {
        this->traversalRecvData();
    }
}

void RobotSocket::parseRecvData(const QByteArray &buffer)
{
    static bool errFlag = false;
    // 解析xml数据,旧数据会被清空
    XMLError error = recvDoc.Parse(buffer);
    if(error != XMLError::XML_SUCCESS && errFlag == false)
    {
        qDebug() << "XMLError::XML_SUCCESS" << QDateTime::currentDateTime().toString("hh::mm::ss::zzz");
        errFlag = true;
        return;
    }

    errFlag = false;
    XMLElement *pRoot = recvDoc.RootElement();
    XMLElement *runModeElement = pRoot->FirstChildElement("RunMode");
    if(runModeElement->ToElement() != NULL)
    {
        this->mRunMode = runModeElement->IntText(-1);
    }
    XMLElement *modelElement = pRoot->FirstChildElement("model");
    if(modelElement->ToElement() != NULL)
    {
        this->mModel = modelElement->GetText();
    }
    XMLElement *runNumberElement = pRoot->FirstChildElement("RunNumber");
    if(runNumberElement->ToElement() != NULL)
    {
        this->mRunNumber = runNumberElement->IntText(-1);
    }
    XMLElement *posElement = pRoot->FirstChildElement("Pos");
    if(posElement->ToElement() != NULL)
    {
        mPosition["X"] = posElement->Attribute("X");
        mPosition["Y"] = posElement->Attribute("Y");
        mPosition["Z"] = posElement->Attribute("Z");
        mPosition["A"] = posElement->Attribute("A");
        mPosition["B"] = posElement->Attribute("B");
        mPosition["C"] = posElement->Attribute("C");
    }
    XMLElement *axisElement = pRoot->FirstChildElement("Axis");
    if(axisElement->ToElement() != NULL)
    {
        mPosition["A1"] = axisElement->Attribute("A1");
        mPosition["A2"] = axisElement->Attribute("A2");
        mPosition["A3"] = axisElement->Attribute("A3");
        mPosition["A4"] = axisElement->Attribute("A4");
        mPosition["A5"] = axisElement->Attribute("A5");
        mPosition["A6"] = axisElement->Attribute("A6");
        mPosition["E1"] = axisElement->Attribute("E1");
    }
    XMLElement *baseElement = pRoot->FirstChildElement("Base");
    if(baseElement->ToElement() != NULL)
    {
        mWorld["X"] = baseElement->DoubleAttribute("X");
        mWorld["Y"] = baseElement->DoubleAttribute("Y");
        mWorld["Z"] = baseElement->DoubleAttribute("Z");
        mWorld["A"] = baseElement->DoubleAttribute("A");
        mWorld["B"] = baseElement->DoubleAttribute("B");
        mWorld["C"] = baseElement->DoubleAttribute("C");
    }
    XMLElement *toolElement = pRoot->FirstChildElement("Tool");
    if(toolElement->ToElement() != NULL)
    {
        mTool["X"] = toolElement->DoubleAttribute("X");
        mTool["Y"] = toolElement->DoubleAttribute("Y");
        mTool["Z"] = toolElement->DoubleAttribute("Z");
        mTool["A"] = toolElement->DoubleAttribute("A");
        mTool["B"] = toolElement->DoubleAttribute("B");
        mTool["C"] = toolElement->DoubleAttribute("C");
    }
    XMLElement *loadElement = pRoot->FirstChildElement("Load");
    if(loadElement->ToElement() != NULL)
    {
        mLoad["X"] = loadElement->DoubleAttribute("X");
        mLoad["Y"] = loadElement->DoubleAttribute("Y");
        mLoad["Z"] = loadElement->DoubleAttribute("Z");
        mLoad["JX"] = loadElement->DoubleAttribute("JX");
        mLoad["JY"] = loadElement->DoubleAttribute("JY");
        mLoad["JZ"] = loadElement->DoubleAttribute("JZ");
        mLoad["A"] = loadElement->DoubleAttribute("A");
        mLoad["B"] = loadElement->DoubleAttribute("B");
        mLoad["C"] = loadElement->DoubleAttribute("C");
        mLoad["mass"] = loadElement->DoubleAttribute("Mass");
    }
}

void RobotSocket::sendDoc()
{
    XMLPrinter printer;
    cmdDoc.Print(&printer);
    this->write(printer.CStr(),printer.CStrSize());
    // qDebug() << printer.CStr();
}
