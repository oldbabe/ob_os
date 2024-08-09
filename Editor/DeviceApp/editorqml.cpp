#include "editorqml.h"

#include <QMutex>
#include <QSettings>
#include <QMessageBox>

EditorQml* EditorQml::handle = Q_NULLPTR;

EditorQml* EditorQml::getInstance()
{
    static QMutex mutex;
    if(handle == Q_NULLPTR)
    {
        mutex.lock();
        handle = new EditorQml;
        mutex.unlock();
    }

    return handle;
}

EditorQml::EditorQml()
{
}

/**
 * @brief 显示弹窗
 * @param 标题
 * @param 内容文本
 * @return
 */
bool EditorQml::showDialog(const QString &title,const QString &content)
{
    int ret = QMessageBox::information(NULL,title,content,QMessageBox::Yes, QMessageBox::No);
    return (ret == QMessageBox::Yes) ? true : false;
}

