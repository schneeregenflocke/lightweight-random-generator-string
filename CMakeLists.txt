cmake_minimum_required(VERSION 3.16)

include(CMakePrintHelpers)

file(STRINGS "VERSION" versionFile)
#string(REGEX MATCHALL "([0-9]+)" versionList ${versionFile})
#list(GET versionList 0 ${PROJECT_NAME}_VERSION_MAJOR)
#list(GET versionList 1 ${PROJECT_NAME}_VERSION_MINOR)
#list(GET versionList 2 ${PROJECT_NAME}_VERSION_PATCH)
#set(${PROJECT_NAME}_VERSION_TWEAK)

project(SimpleRandomStringGenerator VERSION ${versionFile})

cmake_print_variables(versionFile versionList ${PROJECT_NAME}_VERSION_MAJOR ${PROJECT_NAME}_VERSION_MINOR ${PROJECT_NAME}_VERSION_PATCH ${PROJECT_NAME}_VERSION_TWEAK PROJECT_VERSION)


cmake_print_variables(
    CMAKE_SYSTEM_NAME
    CMAKE_SYSTEM_VERSION
    CMAKE_C_COMPILER_ID
    CMAKE_CXX_COMPILER_ID
    CMAKE_GENERATOR
    CMAKE_BUILD_TYPE
    CMAKE_GENERATOR_TOOLSET
    CMAKE_TOOLCHAIN_FILE
    CMAKE_ROOT
    CMAKE_COMMAND
    CMAKE_EDIT_COMMAND
    PROJECT_NAME
    CMAKE_PROJECT_VERSION
    CMAKE_CURRENT_SOURCE_DIR
    CMAKE_CURRENT_BINARY_DIR
    CMAKE_CFG_INTDIR
)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
get_target_property(${PROJECT_NAME}_TARGET_CXX_STANDARD ${PROJECT_NAME} CXX_STANDARD)
cmake_print_variables(${PROJECT_NAME}_TARGET_CXX_STANDARD)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/random_string_generator.h
)

if(MSVC)
    set(QT_INSTALLATION_PREFIX CACHE PATH "Set your CMAKE_PREFIX_PATH environment variable to the Qt installation prefix (e.g. C:\\Qt\\6.0.0\\msvc2019_64)")
    list(APPEND CMAKE_PREFIX_PATH ${QT_INSTALLATION_PREFIX})

    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:windows /ENTRY:mainCRTStartup)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${QT_INSTALLATION_PREFIX}/bin/qtenv2.bat 
        COMMAND ${QT_INSTALLATION_PREFIX}/bin/windeployqt.exe $<IF:$<CONFIG:Debug>,"--debug","--release"> --verbose 1 --no-system-d3d-compiler --no-svg ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
        COMMAND ${QT_INSTALLATION_PREFIX}/bin/windeployqt.exe $<IF:$<CONFIG:Debug>,"--debug","--release"> --verbose 1 --no-system-d3d-compiler --no-svg --compiler-runtime --dir ${CMAKE_CURRENT_BINARY_DIR}/windeployqt_stuff $<TARGET_FILE:${PROJECT_NAME}>
    )
endif()


find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

cmake_print_variables(
    CMAKE_PREFIX_PATH
    QT_INSTALLATION_PREFIX
    Qt6Widgets_COMPILE_DEFINITIONS
    Qt6Widgets_DEFINITIONS
    Qt6Widgets_EXECUTABLE_COMPILE_FLAGS
    Qt6Widgets_FOUND
    Qt6Widgets_INCLUDE_DIRS
    Qt6Widgets_LIBRARIES
    Qt6Widgets_PRIVATE_INCLUDE_DIRS
    Qt6Widgets_VERSION_STRING
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

qt6_wrap_cpp(
    ${PROJECT_NAME}_MOC
    ${CMAKE_CURRENT_LIST_DIR}/src/qt_moc/main_window.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qt_moc/checkable_spin_box_widget.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qt_moc/random_string_configuration_widget.h
)

target_sources(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_MOC})

qt_add_resources(${PROJECT_NAME} "license_text"
    PREFIX "/"
    FILES gpl-3.0-standalone.html
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME
    DESTINATION ${PROJECT_NAME}
    COMPONENT ${PROJECT_NAME}_component
)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "schneeregenflocke")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} - Installation Tool")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt)
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_HOMEPAGE_URL https://github.com/schneeregenflocke)

set(CPACK_IFW_VERBOSE ON)
set(CPACK_IFW_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY ${PROJECT_NAME})
set(CPACK_IFW_PRODUCT_URL ${CPACK_PACKAGE_HOMEPAGE_URL})
set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Modern")
set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)
set(CPACK_IFW_TARGET_DIRECTORY "@ApplicationsDirX64@/${PROJECT_NAME}")


set(CPACK_GENERATOR IFW)

include(CPack REQUIRED)
include(CPackIFW REQUIRED)

cpack_add_component(
    ${PROJECT_NAME}_component
    DISPLAY_NAME ${PROJECT_NAME}
    DESCRIPTION "Generates random strings with simple configuration options."
    REQUIRED
)

if(MSVC)
    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/windeployqt_stuff/
        DESTINATION ${PROJECT_NAME}
        COMPONENT ${PROJECT_NAME}_component
    )

    cpack_ifw_configure_component(
        ${PROJECT_NAME}_component
        #NAME ${PROJECT_NAME}_component
        VERSION ${PROJECT_VERSION}
        LICENSES "License" ${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt
        SCRIPT "${CMAKE_CURRENT_LIST_DIR}/installer/component.qs"
    )
endif()

get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
#list(REMOVE_ITEM CPACK_COMPONENTS_ALL "Unspecified" "headers")
cmake_print_variables(CPACK_COMPONENTS_ALL)
