cmake_minimum_required(VERSION 3.28)

#
# Project
#
#   - dictates the output executable filename
#
project(ISAMIV)

# Options you can set via command-line
option(HAS_TERMINAL "Show a terminal window for STDOUT/STDERR" ON)

#
# C_CXX_SOURCES_DIR
#
#   - the place where your C/C++ source files are located
#
set(C_CXX_SOURCES_DIR "src")

#
# C_CXX_HEADERS_DIR
#
#   - the place where your C/C++ header files are located
#
set(C_CXX_HEADERS_DIR "include")

#
# ASSETS_DIR
#
#   - the place where your pictures, sound files, etc.. live
#
set(ASSETS_DIR "assets")

##########################################################################
# DO NOT EDIT BELOW THIS LINE UNLESS YOU KNOW WHAT YOU ARE DOING!!       #
##########################################################################

# Set C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# output executable basename
set(OutputExecutable "${CMAKE_PROJECT_NAME}")

######################################################################
# Directories

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# We need to specify the output for each configuration to make it work
# on Visual Studio solutions.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/bin")

set(SOURCE_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS_DIR})
set(SOURCE_CXX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${C_CXX_HEADERS_DIR})
set(SOURCE_CXX_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${C_CXX_SOURCES_DIR})

# Source Files are Curated Here
file(
		GLOB_RECURSE SOURCE_CXX_FILES
		"${SOURCE_CXX_SRC_DIR}/*.cpp"
)

# Search in the "cmake" directory for additional CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Executable aka binary output
add_executable(${OutputExecutable} ${SOURCE_CXX_FILES})

######################################################################
# Other dependencies

# efsw (Entropia File System Watcher)
add_subdirectory(deps/efsw)
include_directories(deps/efsw/include)
target_link_libraries(${OutputExecutable} efsw)

######################################################################
# Windows: MinGW
######################################################################
if (WIN32 AND MINGW)

	# OpenGL
	set(OpenGL_GL_PREFERENCE LEGACY)
	find_package(OpenGL REQUIRED)
	include_directories(${OpenGL_INCLUDE_DIRS})
	target_link_libraries(${OutputExecutable} ${OpenGL_LIBRARIES} OpenGL::GL)

	if (NOT HAS_TERMINAL)
		target_link_libraries(${OutputExecutable} -mwindows -municode)
	endif (NOT HAS_TERMINAL)

	# GDI+
	set(GDIPLUS_LIBRARY gdiplus)
	target_link_libraries(${OutputExecutable} ${GDIPLUS_LIBRARY})

	# Shlwapi
	set(SHLWAPI_LIBRARY shlwapi)
	target_link_libraries(${OutputExecutable} ${SHLWAPI_LIBRARY})

	# Dwmapi
	set(DWMAPI_LIBRARY dwmapi)
	target_link_libraries(${OutputExecutable} ${DWMAPI_LIBRARY})

	# stdc++fs
	target_link_libraries(${OutputExecutable} stdc++fs)

endif ()

######################################################################
# Windows: Visual Studio / MSVC
######################################################################
if (WIN32 AND MSVC)

	# OpenGL
	set(OpenGL_GL_PREFERENCE LEGACY)
	find_package(OpenGL REQUIRED)
	include_directories(${OpenGL_INCLUDE_DIRS})
	target_link_libraries(${OutputExecutable} ${OpenGL_LIBRARIES} OpenGL::GL)

	# set the startup project to the target executable instead of ALL_BUILD
	set_property(
			DIRECTORY
			${CMAKE_CURRENT_SOURCE_DIR}
			PROPERTY
			VS_STARTUP_PROJECT
			${OutputExecutable}
	)

	# set working directory for Visual Studio Debugger
	set_target_properties(
			${OutputExecutable} PROPERTIES
			VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

	# set subsytem, console if HAS_TERMINAL is true. windows if not
	if (HAS_TERMINAL)
		target_link_options(${OutputExecutable} PRIVATE "/SUBSYSTEM:CONSOLE")
	else ()
		target_link_options(${OutputExecutable} PRIVATE "/SUBSYSTEM:WINDOWS")
	endif ()

	# GDI+
	set(GDIPLUS_LIBRARY gdiplus)
	target_link_libraries(${OutputExecutable} ${GDIPLUS_LIBRARY})

	# Shlwapi
	set(SHLWAPI_LIBRARY shlwapi)
	target_link_libraries(${OutputExecutable} ${SHLWAPI_LIBRARY})

	# Dwmapi
	set(DWMAPI_LIBRARY dwmapi)
	target_link_libraries(${OutputExecutable} ${DWMAPI_LIBRARY})

endif () # Visual Studio / MSVC

######################################################################
# Linux: using anything?
######################################################################
if (UNIX AND NOT APPLE AND NOT EMSCRIPTEN)

	# OpenGL
	set(OpenGL_GL_PREFERENCE LEGACY)
	find_package(OpenGL REQUIRED)
	include_directories(${OpenGL_INCLUDE_DIRS})
	target_link_libraries(${OutputExecutable} ${OpenGL_LIBRARIES} OpenGL::GL)

	# X11
	find_package(X11 REQUIRED)
	target_link_libraries(${OutputExecutable} X11::X11)

	include_directories(${X11_INCLUDE_DIRS})

	# Threads
	find_package(Threads REQUIRED)
	target_link_libraries(${OutputExecutable} Threads::Threads)
	include_directories(${Threads_INCLUDE_DIRS})

	find_package(PNG REQUIRED)
	target_link_libraries(${OutputExecutable} PNG::PNG)
	include_directories(${PNG_INCLUDE_DIRS})

	# stdc++fs
	target_link_libraries(${OutputExecutable} stdc++fs)

endif () # Linux

######################################################################
# Set include directory
######################################################################
if (IS_DIRECTORY ${SOURCE_CXX_INCLUDE_DIR})
	include_directories(${SOURCE_CXX_INCLUDE_DIR})
endif ()

######################################################################
# Copy assets/ directory target
######################################################################

set(DATA_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/${ASSETS_DIR})

file(GLOB_RECURSE src_data_files
		RELATIVE ${SOURCE_DATA_DIR}/ "${SOURCE_DATA_DIR}/*.*" "${SOURCE_DATA_DIR}/*")
foreach (fn ${src_data_files})
	add_custom_command(
			OUTPUT ${DATA_OUTPUT_DIR}/${fn}
			COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE_DATA_DIR}/${fn} ${DATA_OUTPUT_DIR}/${fn}
			MAIN_DEPENDENCY ${SOURCE_DATA_DIR}/${fn})
	list(APPEND out_data_files ${DATA_OUTPUT_DIR}/${fn})
endforeach ()

add_custom_target(copy_data DEPENDS ${out_data_files})

# Copy Asset Files
add_dependencies(${OutputExecutable} copy_data)
