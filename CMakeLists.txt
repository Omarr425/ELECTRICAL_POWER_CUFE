cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# Add source files
# Add source files
#set(SOURCES
#    src/energy_monitor.cpp
#    src/core/data_IO/data_IO.cpp
#    src/core/data_IO/dataTable.cpp
#    # Add more source files if needed
#)

file(GLOB_RECURSE SOURCES "src/*.cpp")


message(STATUS "Source files: ${SOURCES}")


# Add header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add executable
add_executable(energy_monitor ${SOURCES})




# TO CMAKE THE PROJECT AND MAKE it suitable for compiling run 
#   cmake .

# TO build / compile the project run 
# make

# RUN 
# ./energy_monitor to run the binary

# for visual studio integration run  
#   cmake -G "Visual Studio 16 2022" --config Release .