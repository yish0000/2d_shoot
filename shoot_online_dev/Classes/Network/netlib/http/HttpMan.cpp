#include "HttpMan.h"
#include "HttpCurl.h"
#include "cocos2d.h"

namespace scnet
{

///////////////////////////////////////////////////////////////////////////
//  
//  class HttpEntryQueue
//  
///////////////////////////////////////////////////////////////////////////

void HttpEntryQueue::push(HttpEntry* entry)
{
	SCScopedMutex keeper(m_mutex);
	bool empty = m_queue.empty();
	m_queue.push(entry);
	if( empty )
		m_cond.broadcast();
}

bool HttpEntryQueue::pop(HttpEntry*& entry, int timeoutInMillis)
{
	SCScopedMutex keeper(m_mutex);
	if( m_queue.empty() )
		m_cond.wait(m_mutex, timeoutInMillis);

	if( m_queue.empty() )
		return false;
	else
	{
		entry = m_queue.front();
		m_queue.pop();
		return true;
	}
}

bool HttpEntryQueue::tryPop(HttpEntry*& entry)
{
	SCScopedMutex keeper(m_mutex);
	if( m_queue.empty() )
		return false;
	else
	{
		entry = m_queue.front();
		m_queue.pop();
		return true;
	}
}

///////////////////////////////////////////////////////////////////////////
//  
//  class HttpThread
//  
///////////////////////////////////////////////////////////////////////////

HttpThread::HttpThread(HttpEntryQueue* q) : _state(TS_CREATED), _queue(q)
{
}

bool HttpThread::start()
{    
	_state = TS_RUNNING;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if( 0 != pthread_create(&_threadId, &attr, threadProc, this) )
	{
		CCLOG("pthread_create failed");
		pthread_attr_destroy(&attr);
		return false;
	}
	pthread_attr_destroy(&attr);
	return true;
}

void HttpThread::waitStop()
{
	SCScopedMutex keeper(_mutex);
	if( _state != TS_STOPPED )
	{
		_stopCond.wait(_mutex);
	}
}

void HttpThread::stop()
{
	SCScopedMutex keeper(_mutex);
	if( _state != TS_STOPPED )
	{
		_state = TS_STOPPING;
	}
}

bool HttpThread::willStop()
{
	SCScopedMutex keeper(_mutex);
	return _state == TS_STOPPING;
}

void* HttpThread::threadProc(void* arg)
{
	HttpThread* t = (HttpThread*)arg;
	while( !t->willStop() )
	{
		int ret = t->run();
		if( ret < 0 )		//deleted
			return NULL;
		else if( ret == 0 )	//to stop
			break;
	}
	t->doStop();
	return NULL;
}

void HttpThread::doStop()
{
	SCScopedMutex keeper(_mutex);
	_state = TS_STOPPED;
	_stopCond.signal();
}
    
int HttpThread::run()
{
    HttpEntry *entry = NULL;
    if( !_queue->pop(entry, 1000) )
        return 1;
    
    entry->handler->onRequestStart(entry->req);
    
    bool success = false;
    std::string res;
    switch (entry->req.method)
    {
        case GET:
            success = HttpCurl::get(entry->req.url, res, entry->timeout);
            break;
            
        default:
            success = HttpCurl::post(entry->req.url, entry->req.body, res, entry->timeout);
            break;
    }
    
    if (success)
    {
        entry->handler->onResponseSuccess(entry->req, res);
    }
    else
    {
        entry->handler->onResponseFailed(entry->req);
    }
    
    delete entry;
    return 1;
}

///////////////////////////////////////////////////////////////////////////
//  
//  class HttpMan
//  
///////////////////////////////////////////////////////////////////////////

bool HttpMan::init(int threadNums)
{
	for(int i=0; i<threadNums; ++i)
	{
		m_httpThreads.push_back(new HttpThread(&m_entryQueue));
		HttpThread* thread = m_httpThreads.back();
		if( !thread->start() )
		{
			stop();
			return false;
		}
	}
    
    return true;
}

void HttpMan::stop()
{
    size_t threadNum = m_httpThreads.size();
    
    for(size_t i = 0; i < threadNum; ++i)
        m_httpThreads[i]->stop();

    for(size_t i = 0; i < threadNum; ++i)
    {
        m_httpThreads[i]->waitStop();
        delete m_httpThreads[i];
    }
    
	HttpEntry* entry = NULL;
    while( m_entryQueue.tryPop(entry) )
    {
        delete entry;
    }
}

void HttpMan::get(const std::string &url, HttpHandler *handler, int timeout, unsigned int priority)
{
    HttpEntry *entry = new HttpEntry();
    entry->req.method = GET;
    entry->req.url = url;
    entry->handler = handler;
    entry->timeout = timeout;
    m_entryQueue.push(entry);
}

void HttpMan::post(const std::string &url, const std::string &body, HttpHandler *handler, int timeout, unsigned int priority)
{
    HttpEntry *entry = new HttpEntry();
    entry->req.method = POST;
    entry->req.url = url;
    entry->req.body = body;
    entry->handler = handler;
    entry->timeout = timeout;
    m_entryQueue.push(entry);
}

}
