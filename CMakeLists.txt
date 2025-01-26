cmake_minimum_required(VERSION 3.15...3.27)

project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)
  
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEPS "${PROJECT_SOURCE_DIR}/deps")


# C++ Library

set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/src/")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
file(GLOB_RECURSE SOURCES "${SOURCES_DIR}/*.cpp" "${SOURCES_DIR}/*.h")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(noise2d STATIC ${SOURCES} ${HEADERS})
target_include_directories(noise2d PUBLIC ${INCLUDE_DIR})

install(TARGETS noise2d
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY ${INCLUDE_DIR} DESTINATION include)


# Python Bindings

set(MODULE_SOURCE "${PROJECT_SOURCE_DIR}/python_bindings")
file(GLOB_RECURSE SOURCES "${MODULE_SOURCE}/*.cpp" "${MODULE_SOURCE}/*.h")
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES})

add_subdirectory(${DEPS}/pybind11)

pybind11_add_module (
	pynoise2d
	${SOURCES}
)

target_link_libraries(pynoise2d PRIVATE noise2d)

target_include_directories (
	pynoise2d
	PRIVATE ${MODULE_SOURCE}
)

target_compile_definitions(pynoise2d PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS pynoise2d DESTINATION pynoise2d)
