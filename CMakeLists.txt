cmake_minimum_required (VERSION 3.11)
 
# --- Fetch libs --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(std-k
  GIT_REPOSITORY https://github.com/kiddersmxj/std-k
  GIT_TAG main
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(std-k)
if(NOT std-k_POPULATED)
  FetchContent_Populate(std-k)
  add_subdirectory(${std-k_SOURCE_DIR} ${std-k_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------

project(stdstreams
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(stdstreams src/stdstreams.cpp)
# add_custom_target(stdstreams ALL)

install(
    TARGETS stdstreams
    DESTINATION /usr/local/bin/
)

if(DISPLAY STREQUAL "no")
    message("NODISPLAY enabled")
    add_compile_definitions(NODISPLAY)
endif()
if(DISPLAY STREQUAL "yes")
    message("DISPLAY enabled")
endif()
if(OCOUT STREQUAL "yes")
    message("OCOUT enabled")
    add_compile_definitions(OCOUT)
endif()
if(ICOUT STREQUAL "yes")
    message("ICOUT enabled")
    add_compile_definitions(ICOUT)
endif()

target_sources(stdstreams PRIVATE src/output.cpp)
target_sources(stdstreams PRIVATE src/child.cpp)
target_sources(stdstreams PRIVATE src/display.cpp)
#target_sources(stdstreams PRIVATE lib/std-k/std-k.cpp)
target_include_directories(stdstreams PRIVATE src)

target_link_libraries(stdstreams
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE std-k
)
