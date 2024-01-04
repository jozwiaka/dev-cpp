set(EXE_SOURCES main.cpp)
add_executable(exe ${EXE_SOURCES})
target_link_libraries(exe PRIVATE Vector)