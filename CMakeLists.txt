cmake_minimum_required(VERSION 3.21)

project(BeerWanter VERSION 9.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT EMSCRIPTEN)
  add_compile_options(-Wall -Wextra -Werror)
endif()

set(BEERWANTER_LOGIC_SOURCES
  beerwantermaindialog.cpp
  beerwantermaindialog.h
  beerwantermenudialog.cpp
  beerwantermenudialog.h
)

# The game. It is called 'Desktop' for historical reasons:
# this is also the target that is built for WebAssembly
qt_add_executable(BeerWanterDesktop
  ${BEERWANTER_LOGIC_SOURCES}
  BeerWanter.qrc
  qtbeerwanteraboutdialog.cpp
  qtbeerwanteraboutdialog.h
  qtbeerwantermaindialog.cpp
  qtbeerwantermaindialog.h
  qtbeerwantermaindialog.ui
  qtbeerwantermenudialog.cpp
  qtbeerwantermenudialog.h
  qtbeerwantermenudialog.ui
  qtbeerwanterwidget.cpp
  qtbeerwanterwidget.h
  qtmain.cpp
)
target_link_libraries(BeerWanterDesktop PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

if(EMSCRIPTEN)
  return()
endif()

set_target_properties(BeerWanterDesktop PROPERTIES WIN32_EXECUTABLE ON)

# Desktop installation, with the Qt libraries it needs
install(TARGETS BeerWanterDesktop RUNTIME DESTINATION bin)
if(Qt6_VERSION VERSION_GREATER_EQUAL 6.5)
  qt_generate_deploy_app_script(
    TARGET BeerWanterDesktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
  )
  install(SCRIPT ${deploy_script})
endif()

# Console version
add_executable(BeerWanterConsole
  ${BEERWANTER_LOGIC_SOURCES}
  main.cpp
)

# Tests
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
enable_testing()
add_executable(BeerWanterConsoleTest
  ${BEERWANTER_LOGIC_SOURCES}
  BeerWanter.qrc
  beerwantermaindialog_test.cpp
  beerwantermenudialog_test.cpp
  main_test.cpp
)
target_link_libraries(BeerWanterConsoleTest PRIVATE
  Boost::unit_test_framework
  Qt6::Core
)
add_test(NAME BeerWanterConsoleTest COMMAND BeerWanterConsoleTest)
