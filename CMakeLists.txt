cmake_minimum_required(VERSION 3.0)
 
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
 
PROJECT(VTKOpenCV)
 
find_package(VTK REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5Widgets REQUIRED)

include(${VTK_USE_FILE})

# assuming QT5 in
set(CMAKE_AUTOMOC ON)	##replace the qt5_wrap_cpp

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
 
file(GLOB UI_FILES *.ui)
file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

qt5_wrap_ui(UISrcs ${UI_FILES} )

add_executable(VTKOpenCV MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${UISrcs})
#if you want, you can add ${MOCSrcs} to the project

target_link_libraries(VTKOpenCV ${VTK_LIBRARIES} Qt5::Widgets ${OpenCV_LIBS} )