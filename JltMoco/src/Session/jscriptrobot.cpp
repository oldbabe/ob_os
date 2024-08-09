#include "Session/jscriptrobot.h"

namespace jltmoco
{

JScriptRobot::JScriptRobot(QObject *parent)
    : QObject(parent)
{
    this->setPrgV(30);
    this->mModel.clear();
}

JScriptRobot::~JScriptRobot()
{
}

void JScriptRobot::setPrgV(int value)
{
    if(mPrgV != value)
    {
        this->mPrgV= value;
        emit prgVChanged();
    }
}

void JScriptRobot::setModel(const QString &name)
{
    if(mModel != name)
    {
        this->mModel = name;
        emit modelChanged();
    }
}

}
