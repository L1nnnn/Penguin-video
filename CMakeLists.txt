
#1.定义cmake版本
cmake_minimum_required(VERSION 3.9.5)

#2.设置项目名称
set(EXE_NAME  Penguin-video)
project(${EXE_NAME})

if (NOT DEFINED VERSION)
    set(VERSION 1.0.0)
endif ()

# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11" )


set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON) #要显示执行构建过程中详细的信息(比如为了得到更详细的出错信息)
set(CMAKE_AUTOMOC ON) #打开全局moc
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#对DApplication 进行加速
set(CMAKE_EXE_LINKER_FLAGS "-pie")

#common resource names
set(APP_RES_DIR "assets")
set(APP_QRC "${APP_RES_DIR}/resources.qrc")

# Find the library
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(DtkWidget REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GSTREAMER-Video REQUIRED gstreamer-video-1.0)
pkg_search_module(DtkWidget REQUIRED dtkwidget)


#源文件、头文件和资源文件
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${DtkWidget_INCLUDE_DIRS})
include_directories(${DtkCore_INCLUDE_DIRS})
include_directories(${DtkGui_INCLUDE_DIRS})
include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

SUBDIRLIST(all_src ${CMAKE_CURRENT_SOURCE_DIR}/src)
#Include all app own subdirectorys
foreach(subdir ${all_src})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir})
endforeach()
file(GLOB_RECURSE Penguin-Video_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )

#生成可执行程序
add_executable(${EXE_NAME} ${Penguin-Video_SRC} ${APP_QRC})

target_include_directories(${EXE_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS} ${OBJECT_BINARY_DIR})
target_link_libraries(${EXE_NAME}
    ${DtkWidget_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${GSTREAMER_LIBRARIES}
    ${GSTREAMER-Video_LIBRARIES}
)

# Install files
set(CMAKE_INSTALL_PREFIX /usr)
install(FILES ../translations/desktop/deepin-lianliankan.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
#add_subdirectory(tests)



