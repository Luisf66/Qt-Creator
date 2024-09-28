cmake_minimum_required(VERSION 3.16)

project(Projeto_Estoque VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        pg_principal.cpp
        pg_principal.h
        pg_principal.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Projeto_Estoque
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Recursos.qrc
        pg_login.h pg_login.cpp pg_login.ui
        Conexao.h
        pg_nova_venda.h pg_nova_venda.cpp pg_nova_venda.ui
        pg_gestao_vendas.h pg_gestao_vendas.cpp pg_gestao_vendas.ui
        pg_gestao_estoque.h pg_gestao_estoque.cpp pg_gestao_estoque.ui
        pg_gestao_colaboradores.h pg_gestao_colaboradores.cpp pg_gestao_colaboradores.ui
        pg_editar_produto_venda.h pg_editar_produto_venda.cpp pg_editar_produto_venda.ui
        variaveis_globais.h
        funcoes_globais.h funcoes_globais.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Projeto_Estoque APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Projeto_Estoque SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Projeto_Estoque
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Projeto_Estoque PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Projeto_Estoque)
endif()
set_target_properties(Projeto_Estoque PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Projeto_Estoque
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Projeto_Estoque)
endif()
