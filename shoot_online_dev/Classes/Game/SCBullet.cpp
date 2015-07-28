#include "SCBullet.h"

bool SCBullet::init()
{
    _controller = new SCBulletController(this);
    _dispatcher = new SCBulletDispatcher(this);
    return true;
}

SCBullet::~SCBullet()
{
    delete _controller;
    _controller = NULL;
    delete _dispatcher;
    _dispatcher = NULL;
}

int SCBullet::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}