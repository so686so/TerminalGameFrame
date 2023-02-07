#pragma once

#include <pthread.h>
#include <malloc.h>
#include <memory>
#include <functional>
#include <stdio.h>
#include "Types.h"


// 4Mb allowed per thread
DEFINE THREAD_STACK_BYTE_SIZE = (4*1024*1024);

// typedef
using ThreadFunc = void*(*)( void* );

class GameThread
{
private:
	BOOL		m_bActive;
	pthread_t	m_tThread;
	BOOL*		m_pExit;
	BOOL		m_bExitValue;
	BOOL		m_bWaitThreadFinish;

	ThreadFunc  run;
	void*		runArg;

public:
	GameThread() noexcept;
	explicit GameThread( ThreadFunc run, void* arg ) noexcept;
	~GameThread();

	BOOL startThread();
	void stopThread();
	void waitFinishThread();
	void setExitFlag( BOOL* exitFlag, BOOL exitValue );
	void onExitThread();
	BOOL isExitThread();
	void terminateThread();
	BOOL isRunning();
	void setRunCallBack( ThreadFunc Run, void* arg );
};
