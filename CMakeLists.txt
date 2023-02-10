# TerminalGameFrame/CMakeLists.txt : 최상위 CMake 프로젝트 파일.
# 전역 구성을 수행하고, 여기에 하위 프로젝트를 포함합니다.

CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

PROJECT("TerminalGameFrame")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -fPIC -std=c++17" )

# 하위 프로젝트를 포함합니다.
# 각 Tier 설명은 라이브러리 별 CMakeLists.txt 참조

# Tier 1 Libs
# ---------------------------------------------------------------------
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/BasicLibs )
# ---------------------------------------------------------------------

# Tier 2 Libs
# ---------------------------------------------------------------------
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Key )             # 입력 관련 제어
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces )      # 게임 인터페이스 모음
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Actions )       # 게임 내 액션 클래스
# ---------------------------------------------------------------------

# Tier 3 Libs
# ---------------------------------------------------------------------
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Engine )        # 게임 내 환경 관리 클래스
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Objects )       # 엔진을 제외한 게임 내 모든 객채 관리
# ---------------------------------------------------------------------

# Tier 4 Excutable Runfile
# ---------------------------------------------------------------------
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/GameFrame )
# ---------------------------------------------------------------------
