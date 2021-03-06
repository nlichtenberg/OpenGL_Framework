string(REPLACE "/" ";" p2list "${CMAKE_SOURCE_DIR}")
string(REPLACE "\\" ";" p2list "${p2list}")
list(REVERSE p2list)
list(GET p2list 0 first)
list(GET p2list 1 ProjectId)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

include(${CMAKE_MODULE_PATH}/doxygen.cmake)
include(${CMAKE_MODULE_PATH}/macros.cmake)

set(CMAKE_CONFIGURATION_TYPES Debug;Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

link_dependency(OpenGL3)
link_dependency(GLEW)
link_dependency(GLFW3)
link_dependency(GLM)
link_dependency(DevIL)
link_dependency(ASSIMP)
link_dependency(ZLIB)

#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{PythonLibs})
#find_package(PythonLibs 2.7 REQUIRED)  # cant use macro due to version parameter
#include(${CMAKE_MODULE_PATH}/LinkPythonLibs27.cmake)

if (NOT PYTHON_INCLUDE_DIRS)
    find_package(PythonLibs 3 REQUIRED)
endif()

#link_dependency(NumPy)
#find_package(NumPy REQUIRED)

include_directories(
    ${CORE_PATH}
${PYTHON_INCLUDE_DIRS}
#${NUMPY_INCLUDE_DIRS}
)
link_libraries(
        ${PYTHON_LIBRARIES}
)


if("${CMAKE_SYSTEM}" MATCHES "Linux")
	find_package(X11)
	set(ALL_LIBRARIES ${ALL_LIBRARIES} ${X11_LIBRARIES} Xcursor Xinerama Xrandr Xxf86vm Xi pthread)
endif()

add_definitions(-DSHADERS_PATH="${SHADERS_PATH}")
add_definitions(-DRESOURCES_PATH="${RESOURCES_PATH}")
add_definitions(-DMDTRAJ_PATH="${MDTRAJ_PATH}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-Wall -Wextra)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_definitions(/W2)
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
GENERATE_SUBDIRS(ALL_LIBRARIES ${LIBRARIES_PATH} ${PROJECT_BINARY_DIR}/libraries)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
GENERATE_SUBDIRS(ALL_EXECUTABLES ${EXECUTABLES_PATH} ${PROJECT_BINARY_DIR}/executables)

if(EXISTS ${SHADERS_PATH})
	add_subdirectory(${SHADERS_PATH})
endif()

file (COPY "${CMAKE_MODULE_PATH}/gdb_prettyprinter.py" DESTINATION ${PROJECT_BINARY_DIR})
