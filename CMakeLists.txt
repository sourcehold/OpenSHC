# CMakeList.txt : CMake project for StrongholdCrusader-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
  #cmake_policy(SET CMP0141 NEW)
  #set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

#if (NOT CMAKE_BUILD_TYPE)
    #message(STATUS "No build type selected, default to RelWithDebInfo")
    #set(CMAKE_BUILD_TYPE "RelWithDebInfo")
#endif()

function(add_file_copy target src dest)
    message(STATUS "Ensure file from \"${src}\" is copied to \"${dest}\" for target: ${target}")
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${src}" "${dest}"
    )
endfunction()

project ("StrongholdCrusader")

set(CRUSADER_DIR "${CMAKE_SOURCE_DIR}/_original")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "VCINSTALLDIR = $ENV{VCINSTALLDIR}")
    set(MSVC80_DEBUGCRT_SOURCE_DIR
        "$ENV{VCINSTALLDIR}/redist/Debug_NonRedist/x86/Microsoft.VC80.DebugCRT"
    )

    set(MSVC80_DEBUGCRT_DEST_DIR
        "${PROJECT_BINARY_DIR}/Microsoft.VC80.DebugCRT"
    )

    file(MAKE_DIRECTORY "${MSVC80_DEBUGCRT_DEST_DIR}")

    file(GLOB MSVC80_DEBUGCRT_FILES
        "${MSVC80_DEBUGCRT_SOURCE_DIR}/*.dll"
        "${MSVC80_DEBUGCRT_SOURCE_DIR}/*.manifest"
    )

    foreach(FILE ${MSVC80_DEBUGCRT_FILES})
        message(STATUS "copy file from: ${FILE} to: ${MSVC80_DEBUGCRT_DEST_DIR}/")
        configure_file("${FILE}"
                       "${MSVC80_DEBUGCRT_DEST_DIR}/"
                       COPYONLY)
    endforeach()
endif()

# /MD is required to make alignment happen (first function 0x401000)
# /Ob1 for release builds to prevent unwanted inlining
set(CMAKE_CXX_FLAGS "/W3 /EHsc /D \"WIN32\" /D \"_WINDOWS\"")
set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Zi /Od /D \"_DEBUG\" /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /D \"NDEBUG\" /MD /Ob1")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Zi /O2 /D \"NDEBUG\" /MD /Ob1")
set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /D \"NDEBUG\" /MD")

set(CMAKE_EXE_LINKER_FLAGS "/machine:I386")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/incremental:no")
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/incremental:no")

set(CMAKE_STATIC_LINKER_FLAGS "/machine:I386")

set(CMAKE_SHARED_LINKER_FLAGS "/machine:I386")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/incremental:no")
set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/incremental:no")

message("CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_RELWITHDEBINFO is ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message("CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

# Handled by path, but explicitly included to support IntelliSense
include_directories(
    ${CMAKE_SOURCE_DIR}/MSVC1400/VC/include
    ${CMAKE_SOURCE_DIR}/MSVC1400/VC/PlatformSDK/Include
)

# Handle dependencies without source files
include_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/recreated/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/recreated/lib
)

# Add source to this project's executable.
add_executable(StrongholdCrusader "StrongholdCrusader.cpp" "ViewportRenderState.h" "ViewportRenderState.cpp" "framework.h" "ViewportRenderStateStruct.h" "ViewportState.h"  "windowslib.h" "windowslib.cpp" "FunctionResolver.h" ViewportRenderState.func.h)

# Checks if a binkw32_real is present and uses this instead; only checks on reconfigure
if(EXISTS "${CRUSADER_DIR}/binkw32_real.dll")
    add_file_copy(StrongholdCrusader "${CRUSADER_DIR}/binkw32_real.dll" "$<TARGET_FILE_DIR:StrongholdCrusader>/binkw32.dll")
else()
    add_file_copy(StrongholdCrusader "${CRUSADER_DIR}/binkw32.dll" "$<TARGET_FILE_DIR:StrongholdCrusader>/binkw32.dll")
endif()
add_file_copy(StrongholdCrusader "${CRUSADER_DIR}/Mss32.dll" "$<TARGET_FILE_DIR:StrongholdCrusader>/Mss32.dll")

# shfolder is a normal windows lib, however, the game needs to work with the games version, so we still copy it
# it should be checked later if the compiler emits a shfolder.dll on its own
add_file_copy(StrongholdCrusader "${CRUSADER_DIR}/shfolder.dll" "$<TARGET_FILE_DIR:StrongholdCrusader>/shfolder.dll")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
  #set_property(TARGET StrongholdCrusader PROPERTY CXX_STANDARD 20)
#endif()

add_library(OpenSHC SHARED "StrongholdCrusader.cpp" "ViewportRenderState.h" "ViewportRenderState.cpp" "framework.h" "ViewportRenderStateStruct.h" "ViewportState.h"  "windowslib.h" "windowslib.cpp" "FunctionResolver.h" ViewportRenderState.func.h)

# TODO: Add tests and install targets if needed.
