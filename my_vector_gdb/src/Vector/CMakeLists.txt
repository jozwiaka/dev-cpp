set(VECTOR_SOURCES Vector.cpp)
add_library(Vector SHARED ${VECTOR_SOURCES})
target_include_directories(Vector INTERFACE "./")