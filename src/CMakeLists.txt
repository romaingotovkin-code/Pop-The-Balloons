find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)


add_executable(PopTheBalloons
    ../main.cpp
    sources/mainwindow.cpp
    sources/gameengine.cpp
    sources/balloon.cpp
)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
)


qt6_wrap_cpp(MOC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/gameengine.h
)




target_sources(PopTheBalloons PRIVATE ${MOC_FILES} ${UI_HEADERS})


target_link_libraries(PopTheBalloons Qt6::Core Qt6::Widgets Qt6::Gui)
