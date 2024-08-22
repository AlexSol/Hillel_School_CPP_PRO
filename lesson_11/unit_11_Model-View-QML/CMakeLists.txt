cmake_minimum_required(VERSION 3.16)

project(unit_11_Model-View-QML VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appunit_11_Model-View-QML
    main.cpp
)

qt_add_qml_module(appunit_11_Model-View-QML
    URI unit_11_Model-View-QML
    VERSION 1.0
    QML_FILES main.qml
    RESOURCES images.qrc
    RESOURCES images/apple.png
    RESOURCES images/banana.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appunit_11_Model-View-QML PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appunit_11_Model-View-QML
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appunit_11_Model-View-QML
    PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appunit_11_Model-View-QML
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
