PROJECT(color_model)

SET(SOURCES full_network_test_hue.cpp)



ADD_EXECUTABLE(color_model ${SOURCES})
TARGET_LINK_LIBRARIES(color_model tarzann)
