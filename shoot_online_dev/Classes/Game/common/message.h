#ifndef __LOGIC_COMMON_MESSAGE__H
#define __LOGIC_COMMON_MESSAGE__H
/*
* ------------------------------------------------------------------------
*  Name:   message.h
*  Desc:   消息体定义
*  Author: umiringo
*  Date:   2015/6/1
* ------------------------------------------------------------------------
*/


#include <stdlib.h>
#include "type.h"
#include "cocos2d.h"

class Message
{
public:
	int type; 	//类型，具体枚举在此文件下方
	GID dest; 	//目的方
	GID src; 	//发送方
	cocos2d::Vec2 pos;	//发送时的位置
	int64_t param;	//预留参数1
	int64_t param2;	//预留参数2

	size_t pack_length;	//作为参数的结构体长度
	const void * pack; 	//作为参数的结构体数据

public:
	Message() : type(0), dest(), src(), pos(), param(0), param2(0), pack_length(0), pack(NULL) {}

public:
    static inline void * PackMessage(const Message& msg)
    {
        void *buf;
        size_t length = msg.pack_length;
        buf = new char[sizeof(Message) + length];
        memcpy(buf, &msg, sizeof(Message));
        if(length){
            memcpy((char *)buf + sizeof(Message), msg.pack, msg.pack_length);
        }
        return buf;
    }
    
    static inline void FreeMessage(Message *msg)
    {
       // ASSERT(msg->pack == ((char *)msg) + sizeof(Message));
        delete[] msg;
    }
    
    static inline Message *DuplicateMessage(const Message& msg)
    {
        Message *pMsg = (Message *)PackMessage(msg);
        pMsg->pack = ((char *)pMsg) + sizeof(Message);
        return pMsg;
    }
    
    static inline void BuildMessage(Message &msg, int _type, const GID& _dest, const GID& _src, const cocos2d::Vec2& _pos,
                                             int64_t _param = 0, int64_t _param2 = 0, const void * _pack = NULL, size_t _pack_length = 0)
    {
        msg.type = _type;
        msg.dest = _dest;
        msg.src = _src;
        msg.pos = _pos;
        msg.param = _param;
        msg.param2 = _param2;
        msg.pack_length = _pack_length;
        msg.pack = _pack;
    }
};



//下面是各种消息类型的enum定义
enum
{
	MSG_NULL = 0,
	MSG_HEARTBEAT = 1, //心跳
    MSG_ATTACK = 2,     //攻击
};

//下面是消息pack结构体定义（不一定所有消息都有，注释请写清楚对应的消息的enum
//命名风格为xxxx_msg
struct attack_msg
{
    GID attacker; //区别于发送的src，因为攻击消息可能是子弹发出，而攻击者不是子弹
    int damage_low;
    int damage_high;
    int crit_ratio; //百分比
    float crit_rate;
};
#endif //__LOGIC_COMMON_MESSAGE__H