cmake_minimum_required( VERSION 2.8 )
project( fisheye_camera_calibration )

set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( fisheye_camera_calibration fisheye_camera_calibration.cpp )

target_link_libraries( fisheye_camera_calibration ${OpenCV_LIBS} )
