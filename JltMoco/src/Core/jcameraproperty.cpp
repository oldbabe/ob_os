#include "Core/jcameraproperty.h"
#include <QJsonObject>

using namespace jltmoco;

JCameraProperty::JCameraProperty()
{
    key = -1;
    writable = -1;//-1未初始化0只读1读写
    value = "";
    values = {};
};

void JCameraProperty::setContent(const QJsonObject &item)
{
    this->setKey(item["key"].toInt());
    this->setWritable(item["writable"].toInt());
    if(!item["value"].isNull())
        this->setValue(item["value"].toString());
    if(!item["values"].isNull())
        this->setValues(item["values"].toVariant().toStringList());
}

void JCameraProperty::setKey(int data)
{
    if(data != key)
    {
        this->key = data;
        emit keyChanged();
    }
}

void JCameraProperty::setWritable(int data)
{
    if(data != writable)
    {
        this->writable = data;
        emit writableChanged();
    }
}

void JCameraProperty::setValue(const QString &data)
{
    if(data != value)
    {
        this->value = data;
        emit valueChanged();
    }
}

void JCameraProperty::setValues(const QStringList &data)
{
    if(data != values)
    {
        this->values = data;
        emit valuesChanged();
    }
}
