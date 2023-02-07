# TerminalGameFrame/GameFrame/CMakeLists.txt

CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

# Tier 4 : 실행 파일 생성
# 참조 가능한 라이브러리 : BasicLibs, Key, Frame, Objects, Actions, Management

ADD_COMPILE_DEFINITIONS(
    DEBUG
)

SET( APP_NAME GameFrame )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -fPIC -std=c++17" )

SET( GAMEFRAME_SRC_LIST
    src/main.cpp
)

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
ADD_EXECUTABLE( ${APP_NAME}
    ${GAMEFRAME_SRC_LIST}
)

TARGET_INCLUDE_DIRECTORIES( ${APP_NAME}
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES( ${APP_NAME}
# Tier 1
	BasicLibs
# Tier 2
    Key
    # Actions
    Interfaces
    # Objects
# Tier 3
    # Management
)