#include "jltscriptnode.h"
#include <QPainter>
#include <QPainterPath>

JltScriptNode::JltScriptNode(QQuickItem *parent)
    : QQuickItem(parent)
{
    this->mInputConnector = NULL;
    this->mOutputConnector = NULL;
}

JltScriptNode::~JltScriptNode()
{
    // if(getInputConnector() && getInputConnector()->getBindConnector())
    //     getInputConnector()->getBindConnector()->setBindConnector(NULL);
    // if(getOutputConnector() && getOutputConnector()->getBindConnector())
    //     getOutputConnector()->getBindConnector()->setBindConnector(NULL);

    // if(getInputConnector())
    //     this->getInputConnector()->setBindConnector(NULL);
    // if(getOutputConnector())
    //     this->getOutputConnector()->setBindConnector(NULL);
}

void JltScriptNode::setInputConnector(JltScriptConnector *connector)
{
    if(mInputConnector != connector)
    {
        this->mInputConnector = connector;
        if(mInputConnector)
        {
            this->mInputConnector->setBindNode(this);
        }
        emit inputConnectorChanged();
    }
}

void JltScriptNode::setOutputConnector(JltScriptConnector *connector)
{
    if(mOutputConnector != connector)
    {
        this->mOutputConnector = connector;
        if(mOutputConnector)
        {
            this->mOutputConnector->setBindNode(this);
        }
        emit outputConnectorChanged();
    }
}


