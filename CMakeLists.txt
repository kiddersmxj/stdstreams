cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  # Important: Specify a GIT_TAG XXXXX here.
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
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

target_sources(stdstreams PRIVATE src/output.cpp)
target_sources(stdstreams PRIVATE src/child.cpp)
target_sources(stdstreams PRIVATE src/display.cpp)
target_sources(stdstreams PRIVATE lib/std-k/std-k.cpp)
target_include_directories(stdstreams PRIVATE src)

target_link_libraries(stdstreams
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
