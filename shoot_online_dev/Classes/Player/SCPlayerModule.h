/*
 * ------------------------------------------------------------------------
 *  Name:   SCPlayerModule.h
 *  Desc:   主玩家模块
 *  Author: Yish
 *  Date:   2015/6/2
 * ------------------------------------------------------------------------
 */

#ifndef __SC_PLAYERMODULE_H__
#define __SC_PLAYERMODULE_H__

#include "SCRole.h"
#include "Module/SCModuleBase.h"

class SCPlayerModule : public SCModuleBase
{
public:
    SCPlayerModule();
    virtual ~SCPlayerModule();
    
    virtual bool init();
    virtual void update(float dt);
    
    // 清理资源
    virtual void clearResources();
    
    SCRoleData* getRoleData() { return m_pRole; }
    
protected:
    SCRoleData* m_pRole;
};

#endif
