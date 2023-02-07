#include "GameThread.h"

GameThread::GameThread() noexcept
	: m_bActive( FALSE )
	, m_pExit( nullptr )
	, m_bExitValue( TRUE )
	, m_bWaitThreadFinish( FALSE )
	, run( nullptr )
	, runArg( nullptr )
{
}

GameThread::GameThread( ThreadFunc Run, void* arg = (void*)nullptr ) noexcept
	: m_bActive( FALSE )
	, m_pExit( nullptr )
	, m_bExitValue( TRUE )
	, m_bWaitThreadFinish( FALSE )
{
	run		= Run;
	runArg	= arg;
}

GameThread::~GameThread()
{
	//this->terminateThread();
}

BOOL GameThread::startThread()
{
	if( m_bActive == FALSE ) {
		pthread_attr_t attr;
		pthread_attr_init( &attr );
		pthread_attr_setstacksize( &attr, THREAD_STACK_BYTE_SIZE );

		if( this->run ) {
			if ( m_pExit )
				*m_pExit = !m_bExitValue;

			if( pthread_create( &m_tThread, &attr, this->run, this->runArg ) == -1 ) {
				printf( "[Thread] Error : thread can't create\n" );
				return m_bActive;
			}
		} else {
			printf( "[Thead] Error : thread run proc not set\n" );
			return m_bActive;
		}
	}

    m_bActive = TRUE;
	return m_bActive;
}

void GameThread::stopThread()
{
	if( m_bActive == FALSE ) return;
	
	if( m_pExit ) {
		*m_pExit = m_bExitValue;
	} else {
		printf( "[Thead] m_pExit not set, try force thread cancel...\n" );
		pthread_cancel( m_tThread );
	}

	if( m_bWaitThreadFinish == FALSE ) {
		pthread_join( m_tThread, NULL );
		m_bActive = FALSE;
	}
}

void GameThread::waitFinishThread()
{
	try {
		if( m_bActive == TRUE ) {
			m_bWaitThreadFinish = TRUE;
			pthread_join( m_tThread, NULL );
			m_bActive = FALSE;
		}
	}
	catch ( ... ) {
		printf( "[Thead] wait but this thread terminated?\n" );
	}
}

void GameThread::setExitFlag( BOOL* exitFlag, BOOL exitValue )
{
	m_pExit		 = exitFlag;
	m_bExitValue = exitValue;
}

void GameThread::onExitThread()
{
	if( !m_pExit ) return;
	*m_pExit = m_bExitValue;
}

BOOL GameThread::isExitThread()
{
	if( !m_pExit ) return FALSE;
	return ( *m_pExit == m_bExitValue );
}

void GameThread::terminateThread()
{
	if( m_bActive == TRUE ) {
		if( m_pExit ) {
			this->onExitThread();
		} else {
			printf( "[Thead] m_pExit not set, try force thread cancel...\n" );
			pthread_cancel( m_tThread );
		}

		if( m_bWaitThreadFinish == FALSE ) {
			pthread_join( m_tThread, NULL );
			m_bActive = FALSE;
		}
	}
}

BOOL GameThread::isRunning()
{
	return m_bActive;
}

void GameThread::setRunCallBack( ThreadFunc Run, void* arg )
{
	run		= Run;
	runArg	= arg;
}
