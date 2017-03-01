################################################################################
#                     ____  _        ____  _   _   ____                        #
#                    / ___|| | _____|  _ \| | | | |___ \                       #
#                    \___ \| |/ / _ \ |_) | | | |   __) |                      #
#                     ___) |   <  __/  __/| |_| |  / __/                       #
#                    |____/|_|\_\___|_|    \___/  |_____|                      #
#                                                                              #
#                        ~ SkePU 2 options CMakeLists ~                        #
################################################################################

cmake_minimum_required(VERSION 3.5)

project(SKEPU2Demo)

# NOTE:
# Override the variables set in Makefile here.

# path to LLVM products directory
set(LLVM_BIN "${CMAKE_CURRENT_SOURCE_DIR}/llvm/bin" CACHE PATH "LLVM-Clang Built with Skepu2 Patch")

# path to Clang source directory (repository root)
set(CLANG_SRC "${CMAKE_CURRENT_SOURCE_DIR}/llvm/lib/clang/4.0.0")

# path to the SkePU sources
set(SKEPU_SRC ${CMAKE_CURRENT_SOURCE_DIR})

#CXX =

#OPENCL_FLAGS =

set( CLANGTOOL_USER_FLAGS -fms-compatibility-version=19.00)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(BACKENDS "-openmp")
endif()


# Location of SkePU precompiler binary.
set(SKEPU "${LLVM_BIN}/skepu-tool")

#---------------------------------------------------------------------------- #
# Test program names and target directories.

set(OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SEQ_DIR ${OUT_DIR}/sequential)

# ---------------------------------------------------------------------------- #
# Compiler flags begin here.

# Flags for precompiler.
set(SKEPU_FLAGS ${BACKENDS} 
	${PRECOMPILER_OPTIONS} 	
	-- -Xclang -std=c++14 
	-Wno-expansion-to-defined 
	-I ${CLANG_SRC}/include
	-I ${SKEPU_SRC}/include 
	#-I "C:/Users/satko03/Documents/llvm/tools/clang/include"
	${CLANGTOOL_USER_FLAGS})


set(FILETYPE "cpp")

# Flags for target compiler (preprocessed sources).
#set(TARGET_FLAGS -g -O3 -std=c++11 ${SKEPU_OPTIONS} -I ${SKEPU_SRC}/include ${BACKEND_FLAGS} -I ${CMAKE_CURRENT_SOURCE_DIR} ${NVCCPASS} -Wno-attributes )

# Flags for non-preprocessed compilation.
set(SEQ_FLAGS -std=c++14 -O3 -I ${SKEPU_SRC}/include -Wno-attributes) # -fno-rtti -fno-exceptions )

set(SRC_FILE_NAME
    tests
)

set(SRC_FILE_CPP
	${CMAKE_CURRENT_SOURCE_DIR}/examples/${SRC_FILE_NAME}.cpp
)

message("src " ${OUT_DIR})

execute_process(COMMAND ${SKEPU} -name ${SRC_FILE_NAME}_precompiled ${SRC_FILE_CPP} -dir ${OUT_DIR} ${SKEPU_FLAGS}
    OUTPUT_VARIABLE SKEPU_output
    ERROR_VARIABLE SKEPU_error
    RESULT_VARIABLE SKEPU_result)

message("OUTPUT: " ${SKEPU_output})
message("ERROR: " ${SKEPU_error})
message("RESULT: " ${SKEPU_result})

file(GLOB_RECURSE SKEPU_SOURCES "${SKEPU_SRC}" "*.inl")
file(GLOB_RECURSE SKEPU_HEADERS "${SKEPU_SRC}/include/*.h*" )


#MESSAGE("SKEPU_SOURCE" ${SKEPU_SOURCES})
#MESSAGE("SKEPU_SOURCE" ${SKEPU_HEADERS})

include_directories( ${CLANG_SRC}/include ${SKEPU_SRC}/include )

add_executable(${SRC_FILE_NAME}_PARALLEL ${OUT_DIR}/${SRC_FILE_NAME}_precompiled ${SKEPU_SOURCES} ${SKEPU_HEADERS})

add_executable(${SRC_FILE_NAME}_SEQENTIAL ${SRC_FILE_CPP} ${SKEPU_SOURCES} ${SKEPU_HEADERS})







