cmake_minimum_required(VERSION 3.5)


project(Skepu2-Demo)

#set(LLVM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/llvm/LLVM-5.0.0svn-win64")
#set(module_dir "${LLVM_ROOT_DIR}/lib/cmake/llvm;${LLVM_DIR}/lib/cmake/clang")
#set(LLVM_DIR "${LLVM_ROOT_DIR}/lib/cmake/llvm")
#list(INSERT CMAKE_MODULE_PATH 0 "${module_dir}" )
#find_package(LLVM REQUIRED CONFIG)

#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

#include_directories(${LLVM_INCLUDE_DIRS} skepu2/include)
#add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(skepu2-examples)