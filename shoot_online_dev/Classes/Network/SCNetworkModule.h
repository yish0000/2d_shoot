/*
 * ------------------------------------------------------------------------
 *  Name:   SCNetworkModule.h
 *  Desc:   网络模块
 *  Author: Yish
 *  Date:   2015/5/25
 * ------------------------------------------------------------------------
 */

#ifndef __SC_NETWORK_MODULE_H__
#define __SC_NETWORK_MODULE_H__

#include "Module/SCModuleBase.h"
#include "Network/netlib/protocol/Protocol.h"

class SCNetworkModule : public SCModuleBase
{
public:

	enum
	{
		NETWORK_THREAD_NUM = 4,
	};

public:
    SCNetworkModule();
    virtual ~SCNetworkModule();

	virtual bool init();
	virtual void update(float dt);

	// 发送协议
	void sendProtocol(scnet::Protocol* p);

	void setServerUrl(const std::string& url) { m_sServerUrl = url; }
	const std::string& getServerUrl() const { return m_sServerUrl; }

protected:
	std::string m_sServerUrl;

protected:
	// 收到协议
	void onNewProtocol(const scnet::Protocol* p);
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_NETWORK_MODULE_H__