cmake_minimum_required(VERSION 3.25)
project(CrimeMapUpdateAssistant)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(src)

add_subdirectory(OpenXLSX)

add_executable(${PROJECT_NAME} src/Application.cpp 
                               src/CSVVidioFrame.cpp 
                               src/DoneFrame.cpp 
                               src/DSSVideoFrame.cpp 
                               src/MainFrame.cpp, 
                               src/Parser.cpp 
                               src/UploadFrame.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} OpenXLSX::OpenXLSX)
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PRIVATE
                        "-Wall"
                        "-Wno-unknown-pragmas")
