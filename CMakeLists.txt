cmake_minimum_required(VERSION 3.28)
project(BatchRename)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BatchRename main.cpp
        utils/utils.cpp
        utils/utils.h
        widgets/mainwindow.cpp
        widgets/mainwindow.h
        widgets/mainwindow.ui
        widgets/BrWidgetTable.h
        widgets/BrWidgetTable.cpp
        widgets/AddDirMsgBox.h
        widgets/BrPalletFindAndRepl.cpp
        widgets/BrPalletFindAndRepl.h
        widgets/AddDirMsgBox.cpp
        widgets/BrWidgetRulesList.cpp
        widgets/BrWidgetRulesList.h
        widgets/BrPallet.h
        widgets/BrPallet.cpp
        utils/enums.h
)
target_link_libraries(BatchRename
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

