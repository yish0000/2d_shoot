/*
 * ------------------------------------------------------------------------
 *  Name:   SCRole.h
 *  Desc:   角色数据
 *  Author: Yish
 *  Date:   2015/6/2
 * ------------------------------------------------------------------------
 */

#ifndef __SC_ROLE_H__
#define __SC_ROLE_H__

#include "Network/netlib/stream/KeyedStream.h"

class SCRoleData : public scnet::KeyedStreamObj
{
public:
    SCRoleData();
    virtual ~SCRoleData();
    
    void encode(scnet::KeyedStream& stream) const;
    void decode(const scnet::KeyedStream& stream);
    
protected:
    int64_t m_iiRoleId;     // 角色ID
    std::string m_sName;    // 角色名字
    int m_iLevel;           // 当前等级
};

#endif
