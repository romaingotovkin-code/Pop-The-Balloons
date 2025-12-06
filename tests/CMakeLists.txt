cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Test)


set(CMAKE_AUTOMOC OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}
)



qt6_wrap_cpp(TEST_BALLOON_MOC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/test_balloon.h
)

add_executable(TestBalloon
    sources/test_balloon.cpp
    ${CMAKE_SOURCE_DIR}/src/sources/balloon.cpp
    ${TEST_BALLOON_MOC}
)

target_link_libraries(TestBalloon
    Qt6::Core
    Qt6::Test
    Qt6::Gui
)



qt6_wrap_cpp(TEST_GAMEENGINE_MOC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/test_gameengine.h
)


qt6_wrap_cpp(GAMEENGINE_MOC
    ${CMAKE_SOURCE_DIR}/src/headers/gameengine.h
)

add_executable(TestGameEngine
    sources/test_gameengine.cpp
    ${CMAKE_SOURCE_DIR}/src/sources/gameengine.cpp
    ${CMAKE_SOURCE_DIR}/src/sources/balloon.cpp
    ${TEST_GAMEENGINE_MOC}
    ${GAMEENGINE_MOC}  
)

target_link_libraries(TestGameEngine
    Qt6::Core
    Qt6::Test
    Qt6::Widgets
    Qt6::Gui
)
