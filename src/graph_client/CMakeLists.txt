cmake_minimum_required(VERSION 3.8)
project(SfmlTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -std=c++14")

set(SOURCE_FILES main.cpp
        manager/Clock.cpp
        manager/GameManager.hpp
        modules/SfmlModuleMyWorld.hpp
        manager/Clock.hpp
        manager/ModuleLauncher.hpp
        manager/ModuleLauncher.cpp
        modules/ISfmlModule.hpp
        modules/ASfmlModule.hpp
        modules/CsvParser.hpp
        manager/GameManager.cpp
        modules/SfmlModuleMyWorld.cpp
        GameInfo.cpp GameInfo.hpp)

add_executable(sfml ${SOURCE_FILES})

target_link_libraries(sfml sfml-graphics sfml-window sfml-system)