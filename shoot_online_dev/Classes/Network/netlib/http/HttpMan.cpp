//
//  NetMan.cpp
//
//  Created by bihai wu on 12-3-22.
//

#include "HttpMan.h"
#include "HttpCurl.h"
#include "Assert.h"

namespace wge
{
struct HttpEntry
{
    HttpReq req;
    HttpHandler *handler;
    int timeout;
};
    
class HttpThread : public Thread
{
public:
    HttpThread(BlockingQueue<const HttpEntry *> *queue):_queue(queue)
    {}
    
protected:
    virtual int run();
    
private:
    HttpThread(const HttpThread &);
    HttpThread &operator=(const HttpThread &);
    
private:
    BlockingQueue<const HttpEntry *> *_queue;
};
    
int HttpThread::run()
{
    const HttpEntry *entry = NULL;
    if (!_queue->pop(entry, 1000))
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

bool HttpMan::init(const std::map<int, int> &threadNums)
{
    std::map<int, int>::const_iterator it = threadNums.begin(), ie = threadNums.end();
    for (; it != ie; ++it)
    {
        int priority = it->first;
        int threadNum = it->second;
        
        BlockingQueue<const HttpEntry *> *queue = new BlockingQueue<const HttpEntry *>();
        _entryQueues[priority] = queue;
        
        for (int i = 0; i < threadNum; ++i)
        {
            _httpThreads.push_back(new HttpThread(queue));
            Thread *thread = _httpThreads.back();
            if (!thread->start())
            {
                stop();
                return false;
            }
        }
    }
    
    return true;
}

void HttpMan::stop()
{
    size_t threadNum = _httpThreads.size();
    
    for (size_t i = 0; i < threadNum; ++i)
        _httpThreads[i]->stop();
    
    for (size_t i = 0; i < threadNum; ++i)
    {
        _httpThreads[i]->waitStop();
        delete _httpThreads[i];
    }
    
    std::map<int, BlockingQueue<const HttpEntry *> *>::iterator it = _entryQueues.begin(), ie = _entryQueues.end();
    for (; it != ie; ++it)
    {
        BlockingQueue<const HttpEntry *> *queue = it->second;
        const HttpEntry *entry = NULL;
        while (queue->tryPop(entry))
        {
            delete entry;
        }
        delete queue;
    }
}

void HttpMan::get(const std::string &url, HttpHandler *handler, int timeout, unsigned int priority)
{
    std::map<int, BlockingQueue<const HttpEntry *> *>::iterator it = _entryQueues.find(priority);
    WGEASSERT(it != _entryQueues.end());
    if (it == _entryQueues.end())
        return;
    HttpEntry *entry = new HttpEntry();
    entry->req.method = GET;
    entry->req.url = url;
    entry->handler = handler;
    entry->timeout = timeout;
    
    it->second->push(entry);
}

void HttpMan::post(const std::string &url, const std::string &body, HttpHandler *handler, int timeout, unsigned int priority)
{
    std::map<int, BlockingQueue<const HttpEntry *> *>::iterator it = _entryQueues.find(priority);
    WGEASSERT(it != _entryQueues.end());
    if (it == _entryQueues.end())
        return;
    HttpEntry *entry = new HttpEntry();
    entry->req.method = POST;
    entry->req.url = url;
    entry->req.body = body;
    entry->handler = handler;
    entry->timeout = timeout;
    
    it->second->push(entry);
}
};
