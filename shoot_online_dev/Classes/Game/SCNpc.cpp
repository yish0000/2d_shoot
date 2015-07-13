#include "SCNpc.h"

bool SCNpc::init()
{
    _controller = new SCNpcController(this);
    _dispatcher = new SCNpcDispatcher(this);
    return true;
}

SCNpc::~SCNpc()
{
    delete _controller;
    _controller = NULL;
    delete _dispatcher;
    _dispatcher = NULL;
}

int SCNpc::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}