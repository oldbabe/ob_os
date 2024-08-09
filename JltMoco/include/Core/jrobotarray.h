/*
* 软件名称   BOBS 操作系统
* 版权所有   上海倔老头智能科技有限公司
* 本软件由上海倔老头智能科技有限公司开发并且开源 使用GPL V3（GNU General Public License） 开源协议
* 如收费请告知他人本软件可免费获得并说明收费缘由（如服务费）
* 联系方式
* vx 号    z1273305587
* 电话号   15536506659
* bilibili： 倔老头的会议室  UID: 3546726275221982
* 软件开源地址 https://github.com/oldbabe/ob_os
*
* Software name BOBS Operating system
*
* Copyright (C) 2024  Shanghai OldBaby technology Co., LTD
*
* This program is free software;you can redistribute it and/or modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation;either version 3 of the License, or (at your option) any later version.
*
* If there is a charge, please inform others that the software is available free of charge and explain the reason for the charge (e.g. service fee).
* Contact information
* Open source address https://github.com/oldbabe/ob_os
*/
#ifndef JROBOTARRAY_H
#define JROBOTARRAY_H

#include "global.h"
#include <QObject>

namespace jltmoco
{

//机械臂空间位置、轴角度数据
class DEVICECONTROLLER_EXPORT JRobotArray : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString x READ getX NOTIFY posXChanged)
    Q_PROPERTY(QString y READ getY NOTIFY posYChanged)
    Q_PROPERTY(QString z READ getZ NOTIFY posZChanged)
    Q_PROPERTY(QString rx READ getRx NOTIFY posRxChanged)
    Q_PROPERTY(QString ry READ getRy NOTIFY posRyChanged)
    Q_PROPERTY(QString rz READ getRz NOTIFY posRzChanged)
    Q_PROPERTY(QString a1 READ getA1 NOTIFY axis1Changed)
    Q_PROPERTY(QString a2 READ getA2 NOTIFY axis2Changed)
    Q_PROPERTY(QString a3 READ getA3 NOTIFY axis3Changed)
    Q_PROPERTY(QString a4 READ getA4 NOTIFY axis4Changed)
    Q_PROPERTY(QString a5 READ getA5 NOTIFY axis5Changed)
    Q_PROPERTY(QString a6 READ getA6 NOTIFY axis6Changed)
    Q_PROPERTY(QString a7 READ getA7 NOTIFY axis7Changed)

public:
    JRobotArray();
    void setX(const QString &value);
    void setY(const QString &value);
    void setZ(const QString &value);
    void setRx(const QString &value);
    void setRy(const QString &value);
    void setRz(const QString &value);
    void setA1(const QString &value);
    void setA2(const QString &value);
    void setA3(const QString &value);
    void setA4(const QString &value);
    void setA5(const QString &value);
    void setA6(const QString &value);
    void setA7(const QString &value);
    QString getX() const {return posX;}
    QString getY() const {return posY;}
    QString getZ() const {return posZ;}
    QString getRx() const {return posRx;}
    QString getRy() const {return posRy;}
    QString getRz() const {return posRz;}
    QString getA1() const {return axis1;}
    QString getA2() const {return axis2;}
    QString getA3() const {return axis3;}
    QString getA4() const {return axis4;}
    QString getA5() const {return axis5;}
    QString getA6() const {return axis6;}
    QString getA7() const {return axis7;}

    QJsonObject toJson();

private:
    QString posX;
    QString posY;
    QString posZ;
    QString posRx;
    QString posRy;
    QString posRz;
    QString axis1;
    QString axis2;
    QString axis3;
    QString axis4;
    QString axis5;
    QString axis6;
    QString axis7;

signals:
    void posXChanged();
    void posYChanged();
    void posZChanged();
    void posRxChanged();
    void posRyChanged();
    void posRzChanged();
    void axis1Changed();
    void axis2Changed();
    void axis3Changed();
    void axis4Changed();
    void axis5Changed();
    void axis6Changed();
    void axis7Changed();
};


/**
* @brief 笛卡尔空间位置数据类型
*/
class DEVICECONTROLLER_EXPORT CartesianTran : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x WRITE setX READ getX NOTIFY xChanged)
    Q_PROPERTY(qreal y WRITE setY READ getY NOTIFY yChanged)
    Q_PROPERTY(qreal z WRITE setZ READ getZ NOTIFY zChanged)
public:
    CartesianTran(){
        mx=0;my=0;mz=0;
    }
    void setX(qreal value);
    void setY(qreal value);
    void setZ(qreal value);
    qreal getX() const {return mx;}
    qreal getY() const {return my;}
    qreal getZ() const {return mz;}

private:
    qreal mx;
    qreal my;
    qreal mz;

signals:
    void xChanged();
    void yChanged();
    void zChanged();
} ;

/**
* @brief 欧拉角姿态数据类型
*/
class DEVICECONTROLLER_EXPORT Rpy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal rx WRITE setRx READ getRx NOTIFY rxChanged)
    Q_PROPERTY(qreal ry WRITE setRy READ getRy NOTIFY ryChanged)
    Q_PROPERTY(qreal rz WRITE setRz READ getRz NOTIFY rzChanged)

public:
    Rpy(){
        mrx=0;mry=0;mrz=0;
    }
    void setRx(qreal value);
    void setRy(qreal value);
    void setRz(qreal value);
    qreal getRx() const {return mrx;}
    qreal getRy() const {return mry;}
    qreal getRz() const {return mrz;}

private:
    double mrx; ///< 绕固定轴X旋转角度，单位：rad
    double mry; ///< 绕固定轴Y旋转角度，单位：rad
    double mrz; ///< 绕固定轴Z旋转角度，单位：rad

signals:
    void rxChanged();
    void ryChanged();
    void rzChanged();

} ;

/**
 *@brief 笛卡尔空间位姿类型
 */
class DEVICECONTROLLER_EXPORT CartesianPose : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CartesianTran *tran READ getTran CONSTANT FINAL)
    Q_PROPERTY(Rpy *rpy READ getRpy CONSTANT FINAL)
public:
    CartesianTran *getTran(){return &mTran;}
    Rpy *getRpy(){return &mRpy;}

    QJsonObject toJson();

private:
    CartesianTran mTran; ///< 笛卡尔空间位置
    Rpy mRpy;

};

/**
 *@brief 笛卡尔空间位姿类型
 */
class DEVICECONTROLLER_EXPORT CartesianPoseLoad : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal mass WRITE setMass READ getMass NOTIFY massChanged)
    Q_PROPERTY(CartesianTran *tran READ getTran CONSTANT FINAL)
    Q_PROPERTY(Rpy *rpy READ getRpy CONSTANT FINAL)
    Q_PROPERTY(CartesianTran *inertia READ getInertia CONSTANT FINAL)

public:
    CartesianPoseLoad(){
        mMass=0;
    }
    CartesianTran *getTran(){return &mTran;}
    Rpy *getRpy(){return &mRpy;}
    CartesianTran *getInertia(){return &mInertia;}

    void setMass(qreal value);
    qreal getMass() const {return mMass;}

    QJsonObject toJson();
private:
    qreal mMass;
    CartesianTran mTran; ///< 笛卡尔空间位置
    Rpy mRpy;			///< 笛卡尔空间姿态
    CartesianTran mInertia; ///< 转动惯量

signals:
    void massChanged();

};

class DEVICECONTROLLER_EXPORT JRobotInstall : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title WRITE setTitle READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(QString model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(JRobotArray *reset READ getReset CONSTANT FINAL)
    Q_PROPERTY(CartesianPose *tool READ getTool CONSTANT FINAL)
    Q_PROPERTY(CartesianPose *world READ getWorld CONSTANT FINAL)
    Q_PROPERTY(CartesianPoseLoad *load READ getLoad CONSTANT FINAL)
signals:
    void titleChanged();
    void modelChanged();

public:
    JRobotInstall(){
        this->mTitle.clear();
    };
    void setTitle(const QString &str){
        this->mTitle = str;
        emit titleChanged();
    }
    void setModel(const QString &str){
        this->mModel = str;
        emit modelChanged();
    }
    QString getTitle(){return mTitle;};
    QString getModel(){return mModel;};
    JRobotArray *getReset(){return &mReset;};
    CartesianPose *getTool(){return &mTool;};
    CartesianPose *getWorld(){return &mWorld;};
    CartesianPoseLoad *getLoad(){return &mLoad;};

private:
    QString mTitle;
    QString mModel;
    JRobotArray mReset;
    CartesianPose mTool;
    CartesianPose mWorld;
    CartesianPoseLoad mLoad;

};

}

#endif // JROBOTARRAY_H
