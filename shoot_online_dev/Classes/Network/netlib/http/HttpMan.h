//
//  HttpMan.h
//
//  Created by bihai wu on 12-3-22.
//  Copyright (c) 2012å¹?Zentertain. All rights reserved.
//

#ifndef _HttpMan_h
#define _HttpMan_h

#include "Thread.h"
#include "BlockingQueue.h"
#include <string>
#include <map>
#include <vector>

namespace wge
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
    virtual void onRequestStart(const HttpReq &req)
    {}
    virtual void onResponseSuccess(const HttpReq &req, const std::string &res)
    {}
    virtual void onResponseFailed(const HttpReq &req)
    {}
};

struct HttpEntry;
class Thread;
class HttpMan
{    
private:    
    HttpMan() {}
    
public:
    enum
    {
        PRIORITY_LOADER     = 0,
        PRIORITY_PROTOCOL,
        PRIORITY_MAX,
    };
    
public:
    static HttpMan *getInstance()
    {
        static HttpMan instance;
        return &instance;
    }
    
    bool init(const std::map<int, int> &threadNums);
    void stop();
    
    void get(const std::string &url, HttpHandler *handler, int timeout, unsigned int priority);
    void post(const std::string &url, const std::string &body, HttpHandler *handler, int timeout, unsigned int priority);
    
private:
    std::vector<Thread *> _httpThreads;
    std::map<int, BlockingQueue<const HttpEntry *> *>_entryQueues;
};
};
#endif
