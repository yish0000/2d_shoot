﻿/*
 * ------------------------------------------------------------------------
 *  Name:   SCThread.h
 *  Desc:   线程相关
 *  Author: Yish
 *  Date:   2015/5/21
 * ------------------------------------------------------------------------
 */

#ifndef __SC_THREAD_H__
#define __SC_THREAD_H__

#include <pthread.h>

class SCMutex
{
	friend class SCCondition;

public:
	SCMutex(bool recursive=false);
	~SCMutex();

	void lock();
	void unlock();

private:
	SCMutex(const SCMutex&);
	SCMutex& operator = (const SCMutex&);

private:
	pthread_mutex_t m_mutex;
};

class SCScopedMutex
{
public:
	SCScopedMutex(SCMutex& m) : m_mutex(&m)
	{
		m_mutex->lock();
	}

	~SCScopedMutex()
	{
		m_mutex->unlock();
	}

private:
	SCMutex* m_mutex;
};

class SCCondition
{
public:
	SCCondition();
	~SCCondition();

	void wait(SCMutex& m, int timeoutInMillis=0);
	void signal();
	void broadcast();

private:
	SCCondition(const SCCondition&);
	SCCondition& operator =(const SCCondition&);

private:
	pthread_cond_t m_cond;
};

///////////////////////////////////////////////////////////////////////////

#endif	//#ifndef __SC_THREAD_H__