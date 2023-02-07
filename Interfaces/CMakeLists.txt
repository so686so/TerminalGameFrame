# TerminalGameFrame/Interfaces/CmakeLists.txt

# Tier 2 Library
# 참조 가능한 라이브러리 : BasicLibs

SET( LIBRARY_NAME Interfaces )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -pthread -fPIC -std=c++17" )

# AUX_SOURCE_DIRECTORY 명령어는 새로운 파일이 추가될 시,
# 다시 cmake 하기 전까지는 make 단에서 파악이 불가능하다.
SET( INTERFACES_SRC_LISTS
# Frame
    Frame/src/Frame.cpp
)

ADD_LIBRARY( ${LIBRARY_NAME} SHARED 
	${INTERFACES_SRC_LISTS}
)

INCLUDE(GenerateExportHeader)
GENERATE_EXPORT_HEADER( ${LIBRARY_NAME} )

TARGET_LINK_LIBRARIES( ${LIBRARY_NAME}
# Tier 1
    BasicLibs
)

TARGET_INCLUDE_DIRECTORIES( ${LIBRARY_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Frame/include
)