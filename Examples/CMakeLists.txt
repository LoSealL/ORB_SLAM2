# ORB SLAM2 Examples
include_directories(${PROJECT_SOURCE_DIR}/orbslam2)

macro(copydependency target lib)
  foreach(_lib ${lib})
    add_custom_command(TARGET ${target} POST_BUILD COMMAND
      ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${_lib}> $<TARGET_FILE_DIR:${target}>
      VERBATIM
    )
  endforeach()
endmacro()

macro(copyOpenCv3 target)
  set(OpenCV_DLL "${OpenCV_LIB_PATH}/../bin/opencv_world330.dll")
  set(OpenCV_DLLd "${OpenCV_LIB_PATH}/../bin/opencv_world330d.dll")
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy ${OpenCV_DLL} $<TARGET_FILE_DIR:${target}>
    COMMAND
    ${CMAKE_COMMAND} -E copy ${OpenCV_DLLd} $<TARGET_FILE_DIR:${target}>
    VERBATIM
  )
endmacro()

macro(orbslam2_add_executable name files)
  add_executable(${name} ${files})
  target_link_libraries(${name} orbslam2)
  set(dependencies orbslam2 DBoW2 ${G2O_LIBS})
  if(WIN32)
    foreach(_lib ${dependencies})
      copydependency(${name} ${_lib})
    endforeach()
    copyOpenCv3(${name})
  endif()
endmacro()

# RGB-D
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/RGB-D)
orbslam2_add_executable(rgbd_tum RGB-D/rgbd_tum.cc)

# Stereo 3D
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Stereo)
orbslam2_add_executable(stereo_kitti Stereo/stereo_kitti.cc)
orbslam2_add_executable(stereo_euroc Stereo/stereo_euroc.cc)

# Monocular
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Examples/Monocular)
orbslam2_add_executable(mono_tum Monocular/mono_tum.cc)
orbslam2_add_executable(mono_kitti Monocular/mono_kitti.cc)
orbslam2_add_executable(mono_euroc Monocular/mono_euroc.cc)
