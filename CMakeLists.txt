cmake_minimum_required(VERSION 3.16)

project(MatCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MatCalc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        panes/vectorpane.h panes/vectorpane.cpp panes/vectorpane.ui
        vectorSquare.qrc
        calculatorPage/vectorpage.h calculatorPage/vectorpage.cpp
        numbers/vector.h numbers/vector.cpp
        dimensionmismatchexception.cpp
        dimensionmismatchexception.h
        util.h util.cpp
        panes/decimallineedit.h panes/decimallineedit.cpp
        panes/abstractnumberpane.h panes/abstractnumberpane.cpp
        panes/numberpane.h panes/numberpane.cpp
        genericnumber.h genericnumber.cpp
        panes/genericpane.h panes/genericpane.cpp
        panes/signpane.h panes/signpane.cpp
        calculatorPage/abstractpage.h calculatorPage/abstractpage.cpp
        calculator_basic.h
        panes/genericpane.ui
        calculatorPage/sizerbar.h calculatorPage/sizerbar.cpp
        panes/controlpane.h panes/controlpane.cpp
        calculationselectionlabel.h calculationselectionlabel.cpp
        numbers/matrix.h numbers/matrix.cpp
        panes/matrixpane.h panes/matrixpane.cpp
        calculatorPage/matrixpage.h calculatorPage/matrixpage.cpp
        panes/volatilestackedwidget.h panes/volatilestackedwidget.cpp
        numbers/reducedmatrix.h numbers/reducedmatrix.cpp
        panes/labelpane.h panes/labelpane.cpp
        numbers/spanset.h numbers/spanset.cpp
        panes/incompatiblepasteexception.h panes/incompatiblepasteexception.cpp
        panes/spansetpane.h panes/spansetpane.cpp panes/spansetpane.ui
        calc/calculator.h calc/calculator.cpp
        calc/inputmatcher.h calc/inputmatcher.cpp
        calc/token.h calc/token.cpp
        calc/logger.h calc/logger.cpp
        calc/numbertoken.h calc/numbertoken.cpp
        calc/operatortoken.h calc/operatortoken.cpp
        calc/roottoken.h calc/roottoken.cpp
        calc/parenthesistoken.h calc/parenthesistoken.cpp
        calc/binaryoperatortoken.h calc/binaryoperatortoken.cpp
        history/calculationhistory.h history/calculationhistory.cpp
        history/historywriter.h history/historywriter.cpp
        history/historywindow.h history/historywindow.cpp
        history/historyitem.h history/historyitem.cpp history/historyitem.ui
        calculatorPage/evaluationpage.h calculatorPage/evaluationpage.cpp calculatorPage/evaluationpage.ui
        calculatorPage/calculatorlineedit.h calculatorPage/calculatorlineedit.cpp
        numbers/polynomial.h numbers/polynomial.cpp
        numbers/sturm.h numbers/sturm.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MatCalc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MatCalc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MatCalc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(MatCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER net.ofts.MatCalc)
endif()
set_target_properties(MatCalc PROPERTIES
    ${BUNDLE_ID_OPTION}
    BUNDLE_IDENTIFIER "net.ofts.matCalc"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MatCalc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MatCalc)
endif()
