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
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Key )
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces )
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Objects )
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Actions )
# ---------------------------------------------------------------------

# Tier 3 Libs
# ---------------------------------------------------------------------
# ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/Engine )
# ---------------------------------------------------------------------

# Tier 4 Excutable Runfile
# ---------------------------------------------------------------------
ADD_SUBDIRECTORY( ${CMAKE_CURRENT_SOURCE_DIR}/GameFrame )
# ---------------------------------------------------------------------
