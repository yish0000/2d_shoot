#include "SCNpc.h"

int SCNpc::DispatchMessage(const Message &msg)
{
    return _controller->MessageHandler(msg);
}