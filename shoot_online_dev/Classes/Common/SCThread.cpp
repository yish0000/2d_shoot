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

///////////////////////////////////////////////////////////////////////////
//  
//  Condition object
//  
///////////////////////////////////////////////////////////////////////////

SCCondition::SCCondition()
{
	pthread_cond_init(&m_cond, NULL);
}

SCCondition::~SCCondition()
{
	pthread_cond_destroy(&m_cond);
}

void SCCondition::wait(SCMutex& m, int timeoutInMillis)
{
	if (timeoutInMillis <= 0)
	{
		pthread_cond_wait(&m_cond, &m.m_mutex);
	}
	else
	{
		struct timeval tv;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		cocos2d::gettimeofday(&tv, NULL);
#else
		gettimeofday(&tv, NULL);
#endif
		uint64_t nowInMicroSeconds = (int64_t)tv.tv_sec*1000000+tv.tv_usec;
		nowInMicroSeconds += timeoutInMillis*1000;
		struct timespec spec;
		spec.tv_sec = nowInMicroSeconds/1000000;
		spec.tv_nsec = (nowInMicroSeconds-1000000*spec.tv_sec)*1000;

		int retcode = pthread_cond_timedwait(&m_cond, &m.m_mutex, &spec);
		if( retcode != 0 && retcode != ETIMEDOUT )
		{
			CCLOG("pthread_cond_timedwait failed");            
		}
	}
}

void SCCondition::signal()
{
	pthread_cond_signal(&m_cond);
}

void SCCondition::broadcast()
{
	pthread_cond_broadcast(&m_cond);
}