/*
 * ------------------------------------------------------------------------
 *  Name:   ObjectManager.h
 *  Desc:   gameobject列表
 *  Author: umiringo
 *  Date:   2015/6/1
 * ------------------------------------------------------------------------
 */
 
#ifndef __LOGIC_OBJECTMANAGER_H__
#define __LOGIC_OBJECTMANAGER_H__

#include <set>
#include <map>
#include <Logic/common/message.h>
#include <Common/SCThread.h>

template <typename T>
class ObjectManager
{
private:
    SCMutex lock;
    typedef std::map<int64_t,T *> OBJECT_MAP;
    
    OBJECT_MAP obj_map;
    
public:
    ObjectManager():_cur_obj(NULL), _hb_obj_count(0)
    {}
    
    ~ObjectManager() {}
    
private:
    void Insert(int64_t gid)
    {
        SCScopedMutex keeper(lock);
        auto oi = obj_map.find(gid);
        if(oi != obj_map)
        {
            delete oi->second;
            obj_map.erase(oi);
        }
        T* node = new T();
        obj_map.insert(OBJECT_MAP::pair(gid, T*));
    }
    
    void Remove(int64_t gid)
    {
        SCScopedMutex keeper(lock);
        auto oi = obj_map.find(gid);
        if(oi == obj_map.end() || oi->second == NULL)
        {
            return;
        }
        delete oi->second;
        obj_map.erase(oi);
    }
    
    T* GetByID(int64_t id)
    {
        SCScopedMutex keeper(lock);
        auto oi = obj_map.find(gid);
        if(oi == obj_map.end())
        {
           return NULL;
        }
        if(oi->second == NULL)
        {
            obj_map.erase(oi);
            return NULL;
        }
        return oi.second;
    }

    void Destory()
    {
        SCScopedMutex keeper(lock);
        for(auto oi : obj_map)
        {
            if(oi.second != NULL){
                delete oi.second;
            }
        }
        obj_map.clear();
    }

    void Update(float dt)
    {
        SCScopedMutex keeper(lock);
        Message msg;
        Message msg;
        memset(&msg, 0, sizeof(msg));
        msg.type = MSG_HEARTBEAT;
        msg.param = (int64_t) dt * 1000;
 
        for(auto oi : obj_map)
        {
            if(oi.second != NULL)
            {
                //TODO 调用处理msg函数
            }
        }
    }

};

#endif //__LOGIC_OBJECTMANAGER_H__