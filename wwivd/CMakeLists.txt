# CMake for WWIV Daemon
cmake_minimum_required (VERSION 2.6)
project (wwivd)
include_directories(..)
include_directories(../deps/cereal/include)

set(WWIVD_SOURCES wwivd.cpp)
if (UNIX)
  find_package (Threads)
  list(APPEND WWIVD_SOURCES wwivd_unix.cpp)
  if(CMAKE_SYSTEM_NAME MATCHES "SunOS.*")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsocket -lnsl -lkstat -lssp")
  endif()
elseif(WIN32)
    list(APPEND WWIVD_SOURCES wwivd_win.cpp)
endif()


add_executable(wwivd ${WWIVD_SOURCES})
target_link_libraries(wwivd sdk core ${CMAKE_THREAD_LIBS_INIT})
