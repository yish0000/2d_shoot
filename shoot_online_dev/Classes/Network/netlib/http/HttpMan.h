#ifndef _SC_HttpMan_h
#define _SC_HttpMan_h

#include <string>
#include <map>
#include <vector>
#include <queue>
#include "Common/SCThread.h"

namespace scnet
{

enum HttpMethod
{
    GET = 0,
    POST,
};
    
struct HttpReq
{
    HttpMethod method;
    std::string url;
    std::string body;
};

class HttpHandler
{
public:
    virtual ~HttpHandler() {}
    virtual void onRequestStart(const HttpReq &req) {}
    virtual void onResponseSuccess(const HttpReq &req, const std::string &res) {}
    virtual void onResponseFailed(const HttpReq &req) {}
};

struct HttpEntry
{
	HttpReq req;
	HttpHandler *handler;
	int timeout;
};

class HttpEntryQueue
{
public:
	HttpEntryQueue() {}

	void push(HttpEntry* entry);
	bool pop(HttpEntry*& entry, int timeoutInMillis = 0);
	bool tryPop(HttpEntry*& entry);

protected:
	std::queue<HttpEntry*> m_queue;
	SCCondition m_cond;
	SCMutex m_mutex;
};

// 处理HTTP请求的线程
class HttpThread
{    
public:

	enum ThreadState
	{
		TS_CREATED = 0,
		TS_RUNNING,
		TS_STOPPING,
		TS_STOPPED,
	};

public:
	HttpThread(HttpEntryQueue* q);
	virtual ~HttpThread() {}

	bool start();
	void stop();
	void waitStop();
	bool willStop();

	pthread_t getId() const
	{
		return _threadId;
	}

protected:
	//-1:thread object deleted, 0:to stop, 1:continue
	virtual int run();

private:
	static void *threadProc(void *);
	void doStop();

protected:
	pthread_t _threadId;
	ThreadState _state;
	HttpEntryQueue* _queue;
	SCMutex _mutex;
	SCCondition _stopCond;
};

class HttpMan
{    
private:    
    HttpMan() {}
    
public:
    
public:
    static HttpMan *getInstance()
    {
        static HttpMan instance;
        return &instance;
    }
    
    bool init(int threadNums);
    void stop();
    
    void get(const std::string &url, HttpHandler *handler, int timeout, unsigned int priority);
    void post(const std::string &url, const std::string &body, HttpHandler *handler, int timeout, unsigned int priority);
    
private:
    std::vector<HttpThread*> m_httpThreads;
	HttpEntryQueue m_entryQueue;
};

}

#endif
