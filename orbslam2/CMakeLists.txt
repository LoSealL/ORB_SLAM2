# ORB SLAM2 source

set(API
  ORB2_API.h
  System.h
  Tracking.h
  LocalMapping.h
  LoopClosing.h
  ORBextractor.h
  ORBmatcher.h
  FrameDrawer.h
  Converter.h
  MapPoint.h
  KeyFrame.h
  Map.h
  MapDrawer.h
  Optimizer.h
  PnPsolver.h
  Frame.h
  KeyFrameDatabase.h
  Sim3Solver.h
  Initializer.h
  Viewer.h
)

set(SRC
  System.cc
  Tracking.cc
  LocalMapping.cc
  LoopClosing.cc
  ORBextractor.cc
  ORBmatcher.cc
  FrameDrawer.cc
  Converter.cc
  MapPoint.cc
  KeyFrame.cc
  Map.cc
  MapDrawer.cc
  Optimizer.cc
  PnPsolver.cc
  Frame.cc
  KeyFrameDatabase.cc
  Sim3Solver.cc
  Initializer.cc
  Viewer.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

add_library(orbslam2 ${LIB_TYPE} ${API} ${SRC})

target_link_libraries(orbslam2
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  ${G2O_LIBS}
  DBoW2
)

if(orbslam2_compile_pangolin)
  target_link_libraries(orbslam2 pangolin)
endif()

target_include_directories(orbslam2 PUBLIC
  ${EIGEN3_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/Thirdparty
)