cmake_minimum_required(VERSION 3.18.0)
project(PATH VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

include(CTest)
enable_testing()
#set(CMAKE_CXX_CPPCHECK "cppcheck")

add_executable(PATH main.cpp)

FetchContent_Declare(rapidjson                          # name of the content
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git  # the repository
  GIT_TAG        master                                 # the tag
  )
set(RAPIDJSON_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(RAPIDJSON_BUILD_DOC OFF CACHE INTERNAL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(RAPIDJSON_BUILD_CXX11 OFF CACHE INTERNAL "" FORCE)	
set(RAPIDJSON_BUILD_CXX17 ON CACHE INTERNAL "" FORCE)	
FetchContent_MakeAvailable(rapidjson)

FetchContent_Declare(cxxopts          # name of the content
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git  # the repository
  GIT_TAG        master                                 # the tag
  )
set(CXXOPTS_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(CXXOPTS_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
FetchContent_MakeAvailable(cxxopts)


set(DIRS src/config src/path)
set(FILES src/config/config.cpp src/path/path.cpp)
target_include_directories(PATH PRIVATE ${DIRS} ${FETCHCONTENT_BASE_DIR}/rapidjson-src/include)
target_include_directories(PATH PRIVATE ${DIRS} ${FETCHCONTENT_BASE_DIR}/cxxopts-src/include)
target_sources(PATH PRIVATE ${FILES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)