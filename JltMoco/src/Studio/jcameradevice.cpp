#include "Studio/jcameradevice.h"
#include <QMutex>
#include <QDebug>
#include <QTimer>

#include <QImage>
#include <QPainter>
#include <QCameraDevice>
#include <QMediaDevices>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

#include "jconfig.h"

using namespace jltmoco;

JCameraDevice* JCameraDevice::handle = Q_NULLPTR;

JCameraDevice* JCameraDevice::getInstance()
{
    static QMutex mutex;
    if (handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new JCameraDevice;
        mutex.unlock();
    }
    return handle;
}

JCameraDevice::JCameraDevice()
{
    this->runEnable = false;
    this->mPlaying = false;
    this->mVideoSink = NULL;
    this->mCurrentIndex = -1;
    this->mVerticalMirrored = JConfig::getInstance()->value("JCameraDevice/mVerticalMirrored").toBool();
    this->mHorizontalMirrored = JConfig::getInstance()->value("JCameraDevice/mHorizontalMirrored").toBool();
    this->mGridFlag = (GridFlags)JConfig::getInstance()->value("JCameraDevice/mGridFlag",GridFlags_Close).toInt();
    this->mRotateFlag = (RotateFlags)JConfig::getInstance()->value("JCameraDevice/mRotateFlag",RotateFlag_0).toInt();
    this->mControlFlag = (ControlFlags)JConfig::getInstance()->value("JCameraDevice/mControlFlag",ControlFlags_NULL).toInt();
}

/**
 * @brief 返回相机列表
 * @return [""]
 */
QStringList JCameraDevice::cameraList()
{
    QStringList names;
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : cameras)
    {
        names.append(cameraDevice.description());
    }
    names.insert(0,"关闭");
    return names;
}

/**
 * @brief 相机播放
 * @param index 相机索引
 */
void JCameraDevice::play(int index)
{
    //关闭已经打开的相机
    if(isRunning())
    {
        this->runEnable = false;
        this->wait();
    }
    //打开新相机
    this->setCurrentIndex(index);
    this->runEnable = true;
    this->start();
}

/**
 * @brief 停止播放
 */
void JCameraDevice::stop()
{
    this->setCurrentIndex(-1);
    this->runEnable = false;
    this->wait();
}

/**
 * @brief 返回帧图像
 * @return
 */
QImage JCameraDevice::getFrameImage()
{
    QImage img;
    if(mVideoSink == NULL)
        return img;

    return mVideoSink->videoFrame().toImage();
}

/**
 * @brief 子线程
 */
void JCameraDevice::run()
{
    //初始化行人识别模型
    cv::HOGDescriptor mHOGDescriptor;
    mHOGDescriptor.setSVMDetector(mHOGDescriptor.getDefaultPeopleDetector());

    //查找并打开相机
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if(getCurrentIndex() > -1 && getCurrentIndex() < cameras.length() && getVideoSink() != NULL)
    {
        cv::VideoCapture videoCapture(getCurrentIndex());
        videoCapture.set(cv::CAP_PROP_FOURCC ,cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
        videoCapture.set(cv::CAP_PROP_FRAME_WIDTH,1920);
        videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT,1080);
        if(videoCapture.isOpened())
        {
            while (runEnable)
            {
                cv::Mat frame;
                videoCapture.read(frame);
                if(!frame.empty())
                {
                    //帧处理
                    this->cameraFrameProcessing(frame,mHOGDescriptor);
                }
                //loop
                QThread::msleep(10);
            }
            //释放资源
            videoCapture.release();
        }
    }
}

/**
 * @brief 相机帧处理
 * @param frame
 */
void JCameraDevice::cameraFrameProcessing(cv::Mat &frame,cv::HOGDescriptor hog)
{
    cv::Mat rotateFrame;
    //旋转
    if(getRotateFlag() == RotateFlag_0)
    {
        rotateFrame = frame;
    }
    else
    {
        cv::rotate(frame,rotateFrame,getRotateFlag()-1);
    }
    //BGR转RGB
    cv::Mat qtFrame;
    cv::cvtColor(rotateFrame, qtFrame, cv::COLOR_BGR2RGB);
    //Mat转QImage
    QImage img(qtFrame.data,qtFrame.cols,qtFrame.rows,qtFrame.step,QImage::Format_RGB888);
    if(getHorizontalMirrored() || getVerticalMirrored())
    {
        img.mirror(getHorizontalMirrored() , getVerticalMirrored());
    }
    img.convertTo(QImage::Format_RGBX8888);
    //更新视频流
    this->updateVideoFrame(img);
}

/**
 * @brief 更新视频流数据
 */
void JCameraDevice::updateVideoFrame(QImage &img)
{
    //绘制网格线
    QPainter painter;
    painter.begin(&img);
    QPen pen;
    pen.setWidth(4);
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    if(getGridFlag() == GridFlags::GridFlags_Trisector)
    {
        painter.drawLine(img.width()/3,0,img.width()/3,img.height());
        painter.drawLine(img.width()/3*2,0,img.width()/3*2,img.height());
        painter.drawLine(0,img.height()/3,img.width(),img.height()/3);
        painter.drawLine(0,img.height()/3*2,img.width(),img.height()/3*2);
    }
    else if(getGridFlag() == GridFlags::GridFlags_Square)
    {
        painter.drawLine(img.width()/2,  0,img.width()/2,  img.height());
        painter.drawLine(0,img.height()/2,  img.width(),img.height()/2);
        painter.drawLine(img.width()/4*3,  0,img.width()/4*3,  img.height());
        painter.drawLine(img.width()/4,  0,img.width()/4,  img.height());
        painter.drawLine(0,img.height()/4*3,  img.width(),img.height()/4*3);
        painter.drawLine(0,img.height()/4,  img.width(),img.height()/4);
    }
    else if(getGridFlag() == GridFlags::GridFlags_Diagonal)
    {
        painter.drawLine(img.width()/2,  0,img.width()/2,  img.height());
        painter.drawLine(0,img.height()/2,  img.width(),img.height()/2);
        painter.drawLine(0,0, img.width(),img.height());
        painter.drawLine(img.width(),0,0,img.height());
        painter.drawLine(img.width()/4*3,  0,img.width()/4*3,  img.height());
        painter.drawLine(img.width()/4,  0,img.width()/4,  img.height());
        painter.drawLine(0,img.height()/4*3,  img.width(),img.height()/4*3);
        painter.drawLine(0,img.height()/4,  img.width(),img.height()/4);
    }
    //更新帧
    QVideoFrameFormat frameFormat(img.size(),QVideoFrameFormat::Format_RGBX8888);
    QVideoFrame vframe(frameFormat);
    if (vframe.map(QVideoFrame::WriteOnly))
    {
        //数据拷贝
        memcpy(vframe.bits(0), img.bits(), img.sizeInBytes());
        //设置显示帧
        vframe.unmap();
        if(mVideoSink != NULL)
        {
            mVideoSink->setVideoFrame(vframe);
        }
    }
}

/**
 * @brief 设置播放的相机索引
 * @param index
 */
void JCameraDevice::setCurrentIndex(int index)
{
    if(mCurrentIndex != index)
    {
        this->mCurrentIndex = index;
        emit currentIndexChanged();
    }
}

/**
 * @brief 设置帧管理器
 * @param newVideoSink
 */
void JCameraDevice::setVideoSink(QVideoSink *newVideoSink)
{
    this->mVideoSink = newVideoSink;
    emit videoSinkChanged();
}

/**
 * @brief 设置旋转类型
 * @param flag
 */
void JCameraDevice::setRotateFlag(RotateFlags flag)
{
    if(mRotateFlag != flag)
    {
        this->mRotateFlag = flag;
        emit rotateFlagChanged();
        JConfig::getInstance()->setValue("JCameraDevice/mRotateFlag",flag);
    }
}

/**
 * @brief 设置水平镜像
 * @param value =true启动 =false关闭
 */
void JCameraDevice::setHorizontalMirrored(bool value)
{
    if(this->mHorizontalMirrored != value)
    {
        this->mHorizontalMirrored = value;
        emit horizontalMirroredChanged();
        JConfig::getInstance()->setValue("JCameraDevice/mHorizontalMirrored",value);
    }
}

/**
 * @brief 设置垂直镜像
 * @param value =true启动 =false关闭
 */
void JCameraDevice::setVerticalMirrored(bool value)
{
    if(this->mVerticalMirrored != value)
    {
        this->mVerticalMirrored = value;
        emit verticalMirroredChanged();
        JConfig::getInstance()->setValue("JCameraDevice/mVerticalMirrored",value);
    }
}

void JCameraDevice::setGridFlag(GridFlags flag)
{
    if(flag != mGridFlag)
    {
        this->mGridFlag = flag;
        emit gridFlagChanged();
        JConfig::getInstance()->setValue("JCameraDevice/mGridFlag",flag);
    }
}

void JCameraDevice::setControlFlag(ControlFlags flag)
{
    if(flag != mControlFlag)
    {
        this->mControlFlag = flag;
        emit controlFlagChanged();
        JConfig::getInstance()->setValue("JCameraDevice/mControlFlag",flag);
    }
}
