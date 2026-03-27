cmake_minimum_required(VERSION 3.30)
project(PC_Hardware_Inventory_Tool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(PC_Hardware_Inventory_Tool src/main.cpp
        src/models/HardwareItem.h
        src/repos/IHardwareRepository.h
        src/repos/CSVHardwareRepository.cpp
        src/repos/CSVHardwareRepository.h
        src/repos/JSONHardwareRepository.cpp
        src/repos/JSONHardwareRepository.h
        src/controllers/ICommand.h
        src/controllers/Commands.cpp
        src/controllers/Commands.h
        src/controllers/HardwareController.cpp
        src/controllers/HardwareController.h
        src/filters/IFilterCriteria.h
        src/filters/ConcreteFilters.cpp
        src/filters/ConcreteFilters.h
        src/filters/AndCriteria.cpp
        src/filters/AndCriteria.h
        src/filters/OrCriteria.cpp
        src/filters/OrCriteria.h
        src/ui/HardwareTableModel.cpp
        src/ui/HardwareTableModel.h
        src/ui/AddEditDialog.cpp
        src/ui/AddEditDialog.h
        src/ui/MainWindow.cpp
        src/ui/MainWindow.h
        src/models/HardwareItem.cpp
)


target_link_libraries(PC_Hardware_Inventory_Tool
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()
    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
    foreach(QT_LIB Core Gui Widgets )
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach(QT_LIB)
endif()
