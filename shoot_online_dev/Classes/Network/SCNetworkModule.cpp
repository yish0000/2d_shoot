/*
 * ------------------------------------------------------------------------
 *  Name:   SCNetworkModule.cpp
 *  Desc:   网络模块
 *  Author: Yish
 *  Date:   2015/5/25
 * ------------------------------------------------------------------------
 */

#include "SCNetworkModule.h"
#include "netlib/http/HttpProtocolMan.h"
#include "netlib/stream/JsonStreamCoder.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace scnet;

SCNetworkModule::SCNetworkModule()
    : SCModuleBase(MODULE_TYPE_NETWORK)
{
}

SCNetworkModule::~SCNetworkModule()
{
}

bool SCNetworkModule::init()
{
	if( !SCModuleBase::init() )
		return false;

	// 开4个线程处理HTTP请求
	HttpProtocolMan::getInstance()->init(NETWORK_THREAD_NUM);
	HttpProtocolMan::getInstance()->setProtocolCoder(JsonProtocolCoder::getDefaultInstance());
	HttpProtocolMan::getInstance()->setProtoHandler(CC_CALLBACK_1(SCNetworkModule::onNewProtocol, this));
	return true;
}

void SCNetworkModule::update(float dt)
{
}

// 发送协议
void SCNetworkModule::sendProtocol(scnet::Protocol* p)
{
	HttpProtocolMan::getInstance()->post(m_sServerUrl, p);
}

// 收到新协议（注意：此函数是在网络线程中运行的）
void SCNetworkModule::onNewProtocol(const scnet::Protocol* p)
{
}