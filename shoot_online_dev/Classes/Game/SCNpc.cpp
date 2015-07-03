#include "SCNpc.h"

bool SCNpc::init()
{
    _controller = new SCNpcController();
    _dispatcher = new SCNpcDispatcher();
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