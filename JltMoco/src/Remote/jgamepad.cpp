#include "Remote/jgamepad.h"
#include "Studio/jrobot.h"

#include <QMutex>
#include <QDebug>
#include <QJsonObject>
#include <QTimer>
#include <QTimerEvent>

using namespace jltmoco;

JGamepad* JGamepad::handle = Q_NULLPTR;

JGamepad* JGamepad::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JGamepad;
        mutex.unlock();
    }
    return handle;
}

JGamepad::JGamepad()
{
    XInputGetStateEx = NULL;
    this->gamepadTimerId = 0;
    this->cmdList = QList<double> (7,0);

    this->buttonDown = false;
    this->buttonLeft = false;
    this->buttonRight = false;
    this->buttonUp = false;
    this->buttonBack = false;
    this->buttonStart = false;
    this->buttonL1 = false;
    this->buttonR1 = false;
    this->buttonL3 = false;
    this->buttonR3 = false;
    this->buttonA = false;
    this->buttonB = false;
    this->buttonX = false;
    this->buttonY = false;
}

/**
 * @brief 程序安装
 */
void JGamepad::init()
{
    if (!XInputGetStateEx == false)
    {
        qDebug() << "JGamepad::init() failed;";
        return;
    }

    // get xInput1_4.dll path
    char dll_path[MAX_PATH];
    GetSystemDirectoryA(dll_path, sizeof(dll_path));
    strcat_s(dll_path, "/xinput1_4.dll");
    //Load Library
    HINSTANCE xinputDll = LoadLibraryA(dll_path);
    // get function from xinput dllXInputGetStateEx_t
    XInputGetStateEx = (XInputGetStateEx_t) GetProcAddress(xinputDll, "XInputGetState");
    XInputSetState = (XInputSetState_t) GetProcAddress(xinputDll, "XInputSetState");
    //启动运行
    this->gamepadTimerId = startTimer(33);
}

/**
 * @brief 程序退出
 */
void JGamepad::release()
{
    this->killTimer(gamepadTimerId);
}

void JGamepad::setConnected(bool value)
{
    if(connected != value)
    {
        this->connected = value;
        emit connectedChanged();
    }
}

bool JGamepad::getConnected() const
{
    return this->connected;
}

void JGamepad::timerEvent(QTimerEvent *event)
{
    if(event->timerId() != gamepadTimerId)
        return;

    static bool sendStopFlag = false;
    XINPUT_STATE xState;
    // 读取 id = 0 的手柄状态值
    if (XInputGetStateEx(0, &xState) == ERROR_SUCCESS)
    {
        //更新连接状态
        this->setConnected(true);
        //左扳机
        if(xState.Gamepad.bLeftTrigger == 255 && xState.Gamepad.bRightTrigger == 0)
        {
            if(JRobot::getInstance()->getConnected())
            {
                //[0]前-后 [1]左-右 [2]上-下 [3]左转-右转 [4]抬头-低头 [5]左翻转-右翻转
                auto dList = JRobot::getInstance()->getRemoteDirection();
                QJsonObject root;
                //左摇杆 左-右
                int pm = dList[1]/qAbs(dList[1]);
                root["P"+QString::number(qAbs(dList[1]))] = QString::number(pm*thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbLX/32767.0f)));
                //左摇杆 前-后
                pm = dList[0]/qAbs(dList[0]);
                root["P"+QString::number(qAbs(dList[0]))] = QString::number(pm*thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbLY/32767.0f)));
                //右摇杆 左转-右转
                pm = dList[3]/qAbs(dList[3]);
                root["P"+QString::number(qAbs(dList[3]))] = QString::number(pm*thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbRX/32767.0f)));
                //右摇杆 抬头-低头
                pm = dList[4]/qAbs(dList[4]);
                root["P"+QString::number(qAbs(dList[4]))] = QString::number(pm*thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbRY/32767.0f)));
                //lb rb 上-下
                pm = dList[2]/qAbs(dList[2]);
                QString key = "P"+QString::number(qAbs(dList[2]));
                if((GamePad_lbump & xState.Gamepad.wButtons) != 0)
                    root[key] = QString::number(-pm*0.5);
                else if((GamePad_rbump & xState.Gamepad.wButtons) != 0)
                    root[key] = QString::number(pm*0.5);
                else
                    root[key] = "0";
                //left right 左翻转-右翻转
                pm = dList[5]/qAbs(dList[5]);
                key = "P"+QString::number(qAbs(dList[5]));
                if((GamePad_left & xState.Gamepad.wButtons) != 0)
                    root[key] = QString::number(-pm*0.5);
                else if((GamePad_right & xState.Gamepad.wButtons) != 0)
                    root[key] = QString::number(pm*0.5);
                else
                    root[key] = "0";
                //轨道 up down
                if((GamePad_up & xState.Gamepad.wButtons) != 0)
                    root["P7"] = "0.5";
                else if((GamePad_down & xState.Gamepad.wButtons) != 0)
                    root["P7"] = "-0.5";
                else
                    root["P7"] = "0";
                //发送指令
                // qDebug() << root;
                JRobot::getInstance()->jogMovement(9,root);
                sendStopFlag = false;
            }
        }
        else
        {
            if(!sendStopFlag)
            {
                JRobot::getInstance()->runStop();
                sendStopFlag = true;
            }
        }

        // if(xState.Gamepad.bLeftTrigger == 0)
        // {
        //     //停止遥控
        //     this->setCmdList(readCmd);
        //     if(xState.Gamepad.bRightTrigger == 0)
        //     {
        //         //停止就位
        //         if(buttonA || buttonB || buttonY)
        //         {
        //             this->buttonY = false;
        //             this->buttonB = false;
        //             this->buttonA = false;
        //             JRobot::getInstance()->runStop();
        //         }
        //     }
        //     //就位
        //     else
        //     {
        //         if(!buttonA && !buttonB)
        //         {
        //             this->setButtonY((GamePad_y & xState.Gamepad.wButtons));
        //         }
        //         if(!buttonA && !buttonY)
        //         {
        //             this->setButtonB((GamePad_b & xState.Gamepad.wButtons));
        //         }
        //         if(!buttonB && !buttonY)
        //         {
        //             this->setButtonA((GamePad_a & xState.Gamepad.wButtons));
        //         }
        //     }
        // }
        // //遥控
        // else
        // {
        //     //Z
        //     if ((GamePad_up & xState.Gamepad.wButtons) != 0)
        //         readCmd[2] = 0.3f;
        //     if ((GamePad_down & xState.Gamepad.wButtons) != 0)
        //         readCmd[2] = -0.3;
        //     //C
        //     if ((GamePad_lbump & xState.Gamepad.wButtons) != 0)
        //         readCmd[5] = -0.2;
        //     if ((GamePad_rbump & xState.Gamepad.wButtons) != 0)
        //         readCmd[5] = 0.2;
        //     //E1
        //     if ((GamePad_left & xState.Gamepad.wButtons) != 0)
        //         readCmd[6] = -0.3;
        //     if ((GamePad_right & xState.Gamepad.wButtons) != 0)
        //         readCmd[6] = 0.3;
        //     //X
        //     readCmd[1] = thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbLX/32767.0f));
        //     //Y
        //     readCmd[0] = thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbLY/32767.0f));
        //     //A
        //     readCmd[3] = thumbRange(fmax(-1.0, (double)xState.Gamepad.sThumbRX/32767.0f));
        //     //B
        //     readCmd[4] = thumbRangeLow(fmax(-1.0, (double)xState.Gamepad.sThumbRY/32767.0f));
        //     //更新遥控指令
        //     // this->setCmdList(readCmd);
        //     qDebug() << readCmd;
        // }
    }
    else
    {
        this->setConnected(false);
    }
}

double JGamepad::thumbRange(double value)
{
    if(qAbs(value) < 0.15f)
        return 0;
    return value;
}

double JGamepad::thumbRangeLow(double value)
{
    if(qAbs(value) < 0.15f)
        return 0;
    return value;
}

void JGamepad::setButtonY(bool state)
{
    if(buttonY != state && JRobot::getInstance()->getLoaded() && JRobot::getInstance()->getConnected())
    {
        this->buttonY = state;
        if(buttonY)
        {
            QJsonObject root;
            QJsonObject param;
            param["AssistCA"]=0;
            param["PrgV"]=30;
            param["PathA"]=30;
            param["PathV"]=30;
            param["RobotA"]=30;
            param["RobotV"]=30;
            param["TsValue"]=0;
            QJsonObject target;
            target["X"] = JRobot::getInstance()->getPosition()->getX();
            target["Y"] = JRobot::getInstance()->getPosition()->getY();
            target["Z"] = JRobot::getInstance()->getPosition()->getZ();
            target["A"] = JRobot::getInstance()->getPosition()->getRx();
            target["B"] = JRobot::getInstance()->getPosition()->getRy();
            target["C"] = "0";
            target["E1"] = JRobot::getInstance()->getPosition()->getA7();
            root["param"] = param;
            root["target"] = target;
            root["type"] = 1;
            JRobot::getInstance()->absPosMovement(root);
        }
        else
        {
            JRobot::getInstance()->runStop();
        }
    }
}

void JGamepad::setButtonB(bool state)
{
    if(buttonB != state && JRobot::getInstance()->getLoaded() && JRobot::getInstance()->getConnected())
    {
        this->buttonB = state;
        if(buttonB)
        {
            QJsonObject root;
            QJsonObject param;
            param["AssistCA"]=0;
            param["PrgV"]=30;
            param["PathA"]=30;
            param["PathV"]=30;
            param["RobotA"]=30;
            param["RobotV"]=30;
            param["TsValue"]=0;
            QJsonObject target;
            target["X"] = JRobot::getInstance()->getPosition()->getX();
            target["Y"] = JRobot::getInstance()->getPosition()->getY();
            target["Z"] = JRobot::getInstance()->getPosition()->getZ();
            target["A"] = JRobot::getInstance()->getPosition()->getRx();
            target["B"] = "0";
            target["C"] = JRobot::getInstance()->getPosition()->getRz();
            target["E1"] = JRobot::getInstance()->getPosition()->getA7();
            root["param"] = param;
            root["target"] = target;
            root["type"] = 1;
            JRobot::getInstance()->absPosMovement(root);
        }
        else
        {
            JRobot::getInstance()->runStop();
        }
    }
}

void JGamepad::setButtonA(bool state)
{
    if(buttonA != state && JRobot::getInstance()->getLoaded() && JRobot::getInstance()->getConnected())
    {
        this->buttonA = state;
        if(buttonA)
        {
            QJsonObject root;
            QJsonObject param;
            param["AssistCA"]=0;
            param["PrgV"]=30;
            param["PathA"]=30;
            param["PathV"]=30;
            param["RobotA"]=30;
            param["RobotV"]=30;
            param["TsValue"]=0;
            QJsonObject target;
            target["X"] = JRobot::getInstance()->getPosition()->getX();
            target["Y"] = JRobot::getInstance()->getPosition()->getY();
            target["Z"] = JRobot::getInstance()->getPosition()->getZ();
            target["A"] = "0";
            target["B"] = JRobot::getInstance()->getPosition()->getRy();
            target["C"] = JRobot::getInstance()->getPosition()->getRz();
            target["E1"] = JRobot::getInstance()->getPosition()->getA7();
            root["param"] = param;
            root["target"] = target;
            root["type"] = 1;
            JRobot::getInstance()->absPosMovement(root);
        }
        else
        {
            JRobot::getInstance()->runStop();
        }
    }
}

/**
 * @brief 设置指令数据
 * @param cmd
 */
void JGamepad::setCmdList(const QList<double> &cmd)
{
    if(cmd != cmdList)
    {
        this->cmdList = cmd;
        // if(!JRobot::getInstance()->getConnected())
        //     return;

        // if(cmdList == QList<int> (7,0))
        // {
        //     JRobot::getInstance()->runStop();
        // }
        // else
        // {
        //     QJsonObject root;
        //     root["P1"] = QString::number((double)cmdList[0]/100.0f);
        //     root["P2"] = QString::number((double)cmdList[1]/100.0f);
        //     root["P3"] = QString::number((double)cmdList[2]/100.0f);
        //     root["P4"] = QString::number((double)cmdList[3]/100.0f);
        //     root["P5"] = QString::number((double)cmdList[4]/100.0f);
        //     root["P6"] = QString::number((double)cmdList[5]/100.0f);
        //     root["P7"] = QString::number((double)cmdList[6]/100.0f);
        //     // JRobot::getInstance()->jogMovement(9,root);
        //     qDebug() << root;
        // }
    }
}

/**
 * @brief 按下按钮信号
 */
void JGamepad::sendButtonPressedSignals(int bID)
{
    QList<int> bPressed;
    if ((GamePad_up & bID ) != 0)
        bPressed.append(GamePad_up);

    if ((GamePad_down & bID ) != 0)
        bPressed.append(GamePad_down);

    if ((GamePad_left & bID ) != 0)
        bPressed.append(GamePad_left);

    if ((GamePad_right & bID ) != 0)
        bPressed.append(GamePad_right);

    if ((GamePad_start & bID ) != 0)
        bPressed.append(GamePad_start);

    if ((GamePad_back & bID ) != 0)
        bPressed.append(GamePad_back);

    if ((GamePad_ltdown & bID ) != 0)
        bPressed.append(GamePad_ltdown);

    if ((GamePad_rtdown & bID ) != 0)
        bPressed.append(GamePad_rtdown);

    if ((GamePad_rbump & bID ) != 0)
        bPressed.append(GamePad_rbump);

    if ((GamePad_lbump & bID ) != 0)
        bPressed.append(GamePad_lbump);

    if ((GamePad_guide & bID ) != 0)
        bPressed.append(GamePad_guide);

    if ((GamePad_a & bID ) != 0)
        bPressed.append(GamePad_a);

    if ((GamePad_b & bID ) != 0)
        bPressed.append(GamePad_b);

    if ((GamePad_x & bID ) != 0)
        bPressed.append(GamePad_x);

    if ((GamePad_y & bID ) != 0)
        bPressed.append(GamePad_y);

    //初始化
    if(bPressed.contains(GamePad_a))
    {
        if(!buttonA)
            buttonA = true;
    }
    else
    {
        if(buttonA)
            buttonA = false;
    }
    if(bPressed.contains(GamePad_b))
    {
        if(!buttonB)
            buttonB = true;
    }
    else
    {
        if(buttonB)
            buttonB = false;
    }
    if(bPressed.contains(GamePad_x))
    {
        if(!buttonX)
            buttonX = true;
    }
    else
    {
        if(buttonX)
            buttonX = false;
    }
    if(bPressed.contains(GamePad_y))
    {
        if(!buttonY)
            buttonY = true;
    }
    else
    {
        if(buttonY)
            buttonY = false;
    }

    if(bPressed.contains(GamePad_left))
    {
        if(!buttonLeft)
            buttonLeft = true;
    }
    else
    {
        if(buttonLeft)
            buttonLeft = false;
    }
    if(bPressed.contains(GamePad_right))
    {
        if(!buttonRight)
            buttonRight = true;
    }
    else
    {
        if(buttonRight)
            buttonRight = false;
    }
    if(bPressed.contains(GamePad_up))
    {
        if(!buttonUp)
            buttonUp = true;
    }
    else
    {
        if(buttonUp)
            buttonUp = false;
    }
    if(bPressed.contains(GamePad_down))
    {
        if(!buttonDown)
            buttonDown = true;
    }
    else
    {
        if(buttonDown)
            buttonDown = false;
    }
    if(bPressed.contains(GamePad_lbump))
    {
        if(!buttonL1)
            buttonL1 = true;
    }
    else
    {
        if(buttonL1)
            buttonL1 = false;
    }

    if(bPressed.contains(GamePad_rbump))
    {
        if(!buttonR1)
            buttonR1 = true;
    }
    else
    {
        if(buttonR1)
            buttonR1 = false;
    }
    if(bPressed.contains(GamePad_back))
    {
        if(!buttonBack)
            buttonBack = true;
    }
    else
    {
        if(buttonBack)
            buttonBack = false;
    }
    if(bPressed.contains(GamePad_start))
    {
        if(!buttonStart)
            buttonStart = true;
    }
    else
    {
        if(buttonStart)
            buttonStart = false;
    }

    if(bPressed.contains(GamePad_ltdown))
    {
        if(!buttonL3)
            buttonL3 = true;
    }
    else
    {
        if(buttonL3)
            buttonL3 = false;
    }
    if(bPressed.contains(GamePad_rtdown))
    {
        if(!buttonR3)
            buttonR3 = true;
    }
    else
    {
        if(buttonR3)
            buttonR3 = false;
    }

}


/**
 * @brief 发送左遥感值
 */
void JGamepad::LeftThumbStick(double X, double Y)
{
    // Normalize values between -1.0 and 1.0
    double normX = fmax(-1.0, (double) X / 32767.0);
    double normY = fmax(-1.0, (double) Y / 32767.0);

    // Factoring in deadzone
    double StickX = (abs(normX) < deadzoneX ? 0 : normX);
    double StickY = (abs(normY) < deadzoneY ? 0 : normY);

    axisLeftX = StickX;
    axisLeftY = StickY;
}

/**
 * @brief 发送右遥感值
 */
void JGamepad::RightThumbStick(double X, double Y)
{
    // Normalize values between -1.0 and 1.0
    double normX = fmax(-1.0, (double) X / 32767.0);
    double normY = fmax(-1.0, (double) Y / 32767.0);

    // Factoring in deadzone
    double StickX = (abs(normX) < deadzoneX ? 0 : normX);
    double StickY = (abs(normY) < deadzoneY ? 0 : normY);

    axisRightX = StickX;
    axisRightY = StickY;
}


/**
 * @brief 返回震动
 */
void JGamepad::VibrateController(short uID, WORD LeftMotorSpeed, WORD RightMotorSpeed)
{
    XINPUT_VIBRATION vibration;
    ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );

    if (LeftMotorSpeed < 0) LeftMotorSpeed = 0;
    if (LeftMotorSpeed > 65535) LeftMotorSpeed = 65535;


    if (RightMotorSpeed < 0) RightMotorSpeed = 0;
    if (RightMotorSpeed > 65535) RightMotorSpeed = 65535;

    vibration.wLeftMotorSpeed = LeftMotorSpeed; // use any value between 0-65535 here
    vibration.wRightMotorSpeed = RightMotorSpeed; // use any value between 0-65535 here

    XInputSetState( uID, &vibration );
}
