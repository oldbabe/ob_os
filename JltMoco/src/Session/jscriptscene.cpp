#include "Session/jscriptscene.h"
#include <QDebug>

namespace jltmoco
{

JScriptScene::JScriptScene(QObject *parent)
    : QObject(parent)
{
    this->setSceneX(0);
    this->setSceneY(0);
    this->setGridWidth(16);
}

JScriptScene::~JScriptScene()
{

}

void JScriptScene::setSceneX(qreal value)
{
    this->mSceneX = value;
    emit sceneXChanged();
}

void JScriptScene::setSceneY(qreal value)
{
    this->mSceneY = value;
    emit sceneYChanged();
}

void JScriptScene::setGridWidth(qreal value)
{
    this->mGridWidth = value;
    emit gridWidthChanged();
}


}


