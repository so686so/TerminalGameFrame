# TerminalGameFrame/BasicLibs/CmakeLists.txt

# Tier 1 Library
# 참조 가능한 라이브러리 티어 없음. (최상위)

SET( LIBRARY_NAME BasicLibs )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -pthread -fPIC -std=c++17" )

# AUX_SOURCE_DIRECTORY 명령어는 새로운 파일이 추가될 시,
# 다시 cmake 하기 전까지는 make 단에서 파악이 불가능하다.
SET( BASICLIBS_SRC_LIST
# CORE
	Core/src/ConsoleCmd.cpp
    Core/src/KString.cpp
    Core/src/GameThread.cpp
    Core/src/Tiles.cpp

# STRUCTURE
#	Structure/src/hqueue.cpp
)

ADD_LIBRARY( ${LIBRARY_NAME} SHARED 
	${BASICLIBS_SRC_LIST}
)

INCLUDE(GenerateExportHeader)
GENERATE_EXPORT_HEADER( ${LIBRARY_NAME} )

TARGET_LINK_LIBRARIES( ${LIBRARY_NAME}
# OpenSource
#	curlpp
)

TARGET_INCLUDE_DIRECTORIES( ${LIBRARY_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Core/include
	${CMAKE_CURRENT_SOURCE_DIR}/Structure/include
)