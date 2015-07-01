#include "SCNpc.h"

bool SCNpc::init()
{
    return true;
}

int SCNpc::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}