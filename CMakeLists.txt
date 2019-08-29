project(TarzaNN3_0)
cmake_minimum_required(VERSION 2.8)

# Find necessary packages
find_package(OpenMP)
find_package( PythonLibs 2.7 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )

#Here the executables and headers are defined
#aux_source_directory(${CMAKE_SOURCE_DIR}/test MAIN)
#aux_source_directory(${CMAKE_SOURCE_DIR}/test MAIN)
#set(${CMAKE_SOURCE_DIR}/src/tarzann SRC_LIST)

#add_executable(${PROJECT_NAME} ${MAIN};${SRC_LIST})

#Define the library output dir
#To build the project go to ./build and type: "cmake .. and then make"
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

SET(CMAKE_BUILD_TYPE Release)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -fPIC -std=c++11 -g -Wall -O3 -funroll-loops -ffast-math -fomit-frame-pointer -march=native -flto")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OpenMP_CXX_FLAGS} -fPIC -pg -std=c++11 -g -Wall -DNDEBUG -O3")

#Setting of Python dependencies used to expose TarzaNN  network configuration file
#based on the library BOOST

#find_package(Boost 1.46.0 COMPONENTS python REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)

#if(Boost_FOUND)
#    #CREATE WRAPPER LIBRARY    
#    	#add_library(cell_ST_parameters SHARED ${SRC_LIST} )
#        #target_link_libraries(cell_ST_parameters ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
#    
#    #formating the output library
#    	#set_target_properties(cell_ST_parameters PROPERTIES PREFIX "" )
#
#    message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
#    message(status "** Boost folders: ${Boost_LIBRARY_DIRS}")
#    message(status "** Boost Libraries: ${Boost_LIBRARIES}")
#
#endif()

#################   here ends boost dependencieS   ###########################
##############################################################################
set(CMAKE_AUTOMOC ON)
 find_package(Qt5Widgets REQUIRED)
 include_directories(${Qt5Widgets_INCLUDE_DIRS})
 add_definitions(${Qt5Widgets_DEFINITIONS})

##############################################################################
#################THE NEXT LINES INCLUDE SOURCES AND HEADERS###################

SET(LIB_SOURCES
    include/tarzann/Array2D.h
    include/tarzann/Common.h
    include/tarzann/ComputeStrategy.h    
    include/tarzann/Connection.h
    include/tarzann/ControlSignalGenerator.h
    include/tarzann/Debug.h
    include/tarzann/FeaturalReceptiveField.h
    include/tarzann/Filter.h
    include/tarzann/FilterDoG.h
    include/tarzann/FilterGabor.h
    include/tarzann/FilterType.h
    include/tarzann/FilterGaussian.h
    include/tarzann/FilterIdentity.h
    include/tarzann/GammaUnits.h
    include/tarzann/GatingSignal.h
    include/tarzann/Layer.h
    include/tarzann/Matrix.h
    include/tarzann/Neuron.h
    include/tarzann/NeuronType.h
    include/tarzann/NeuronLinear.h
    include/tarzann/NeuronLinear2.h
    include/tarzann/NeuronSigmoid.h
    include/tarzann/NeuronST.h
    include/tarzann/NeuronST1.h
    include/tarzann/NeuronType.h
    include/tarzann/PLattice.h
    include/tarzann/Probe.h
    include/tarzann/RetinalLayer.h
    include/tarzann/ReceptiveField.h
    include/tarzann/Sheet.h
    include/tarzann/Stimulus.h
    include/tarzann/XMLConfig.h

    src/tarzann/Array2D.cpp
    src/tarzann/ComputeStrategy.cpp
    src/tarzann/Connection.cpp
    src/tarzann/ControlSignalGenerator.cpp
    src/tarzann/Filter.cpp
    src/tarzann/FilterDoG.cpp
    src/tarzann/FilterGabor.cpp
    src/tarzann/FilterGaussian.cpp
    src/tarzann/FilterIdentity.cpp
    src/tarzann/GammaUnits.cpp
    src/tarzann/GatingSignal.cpp
    src/tarzann/Layer.cpp
    src/tarzann/Matrix.cpp
    src/tarzann/Neuron.cpp
    src/tarzann/NeuronLinear.cpp
    src/tarzann/NeuronLinear2.cpp
    src/tarzann/NeuronSigmoid.cpp
    src/tarzann/NeuronST.cpp
    src/tarzann/NeuronST1.cpp
    src/tarzann/PLattice.cpp
    src/tarzann/Probe.cpp
    src/tarzann/ReceptiveField.cpp
    src/tarzann/RetinalLayer.cpp
    src/tarzann/Sheet.cpp
    src/tarzann/Stimulus.cpp
    src/tarzann/XMLConfig.cpp
)

SET(LIB_GUI_SOURCES
    include/tarzann_gui/PLatticeGUI.h
    include/tarzann_gui/NetworkWindow.h
    include/tarzann_gui/SheetImage.h
    include/tarzann_gui/ConnectionGUI.h
    include/tarzann_gui/GUI_config.h

    src/tarzann_gui/PLatticeGUI.cpp
    src/tarzann_gui/NetworkWindow.cpp
    src/tarzann_gui/SheetImage.cpp
    src/tarzann_gui/ConnectionGUI.cpp
)
#+++++++++++++++++++includes and libraries+++++++++++++++++++++++++++++++++++++
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include /opt/ros/hydro/include)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR} /usr/local/lib /usr/lib /opt/local/lib /opt/ros/hydro/lib)

ADD_LIBRARY(tarzann SHARED ${LIB_SOURCES} ${LIB_GUI_SOURCES})
TARGET_LINK_LIBRARIES(tarzann opencv_core opencv_highgui ${Qt5Widgets_LIBRARIES})

#note: when linking libraries it is necessary to check the location
# depending on the version i.e. open cv 2.4 -> opencv 3.1 changes the location
#of the read/write library to imgcodecs (opencv_imgcodecs)
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# next we add the application to be run ("TARGET") into the build/test folder
#ADD_SUBDIRECTORY(tests)

# examples
ADD_SUBDIRECTORY(examples/color_model)
##############################END INCLUDE####################################
##############################################################################
