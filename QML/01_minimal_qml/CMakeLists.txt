cmake_minimum_required(VERSION 3.16)
project(minimal_qml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(minimal_qml
    main.cpp
)

qt_add_qml_module(minimal_qml
    URI MinimalQml
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(minimal_qml
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS minimal_qml
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
