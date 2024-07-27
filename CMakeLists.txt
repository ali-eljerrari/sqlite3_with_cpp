cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MySQLiteApp)

# Add the executable
add_executable(main main.cpp)

# Find SQLite3 library
find_package(SQLite3 REQUIRED)

# Include directories for SQLite3
include_directories(${SQLite3_INCLUDE_DIRS})

# Link the SQLite3 library
target_link_libraries(main ${SQLite3_LIBRARIES})
