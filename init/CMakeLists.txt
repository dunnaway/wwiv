# CMake for WWIV 5
cmake_minimum_required (VERSION 2.6)
project (INIT)
include_directories(..)
Include(FindWWIVCurses)


set(COMMON_SOURCES
  archivers.cpp
  autoval.cpp
  convert.cpp
  editors.cpp
  init.cpp 
  languages.cpp
  levels.cpp
  menus.cpp
  networks.cpp
  newinit.cpp
  paths.cpp
  protocols.cpp
  regcode.cpp
  subacc.cpp 
  subsdirs.cpp 
  system_info.cpp
  sysop_account.cpp
  user_editor.cpp 
  utility.cpp 
  wwivd_ui.cpp
  )

add_executable(init ${COMMON_SOURCES})
target_link_libraries(init localui core sdk ${CURSES_LIBRARIES})
