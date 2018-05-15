PROJECT(connectdots)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(third-party)
INCLUDE_DIRECTORIES(third-party/boost/include)
LINK_DIRECTORIES(${SOURCE_DIR}/third-party/boost/lib)

SET(COMMON_SOURCE Match.cc)
ADD_EXECUTABLE(play ${COMMON_SOURCE} play.cc)
ADD_EXECUTABLE(server ${COMMON_SOURCE} Server.cc)
TARGET_LINK_LIBRARIES(server boost_coroutine boost_system pthread)
