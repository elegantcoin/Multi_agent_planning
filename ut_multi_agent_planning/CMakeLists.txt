CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#avoid linking in default check
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

PROJECT (ut_MultiAgentPlanning)

# set default options
option(MAKE_SHARED_LIB "Set to build as shared library" OFF)

#Setting Executable and Library Output Dir
if (UNIX)
	set(INC_DIR /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../include)
	set(LIB_DIR /usr/local/lib64 /usr/local/lib ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
	SET(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
	add_compile_options(-fPIC -g)
elseif(WIN32)
	SET(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
	SET(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
	SET(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
else()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif()

SET(SRC_DIR ../Multi_agent_planning)

ADD_DEFINITIONS(-D USE_CPU -D_CRT_SECURE_NO_DEPRECATE)

#Setting Source Files
SET(SRC_LIST
	multi_agent_planning_ut.h
	
	multi_agent_planning_ut.cpp
	main_cppunit.cpp

	${SRC_DIR}/multi_agent_planning.cpp
	)

INCLUDE_DIRECTORIES(${INC_DIR} ${SRC_DIR} ${HEADER_DIR})

link_directories(${LIB_DIR})
if (UNIX)
	SET(LINK_LIBS cppunit dl)
else()
	SET(LINK_LIBS cppunit)
endif()

#Setting target output path
SET(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR})
SET(LIBRARY_OUTPUT_PATH ${OUTPUT_DIR})

#Build Executables
if (MAKE_SHARED_LIB)
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
else()
	ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})
endif()


#Setting Librarys needed in linking 
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LINK_LIBS})

if (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4996")
endif (WIN32)

