/*
 * ------------------------------------------------------------------------
 *  Name:   SCThread.cpp
 *  Desc:   线程相关
 *  Author: Yish
 *  Date:   2015/5/21
 * ------------------------------------------------------------------------
 */

#include "SCThread.h"
#include "cocos2d.h"

///////////////////////////////////////////////////////////////////////////
//  
//  Mutex object
//  
///////////////////////////////////////////////////////////////////////////

SCMutex::SCMutex(bool recursive)
{
	if( recursive )
	{
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&m_mutex, &attr);
		pthread_mutexattr_destroy(&attr);
	}
	else
	{
		pthread_mutex_init(&m_mutex, NULL);
	}
}

SCMutex::~SCMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void SCMutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}

void SCMutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}
