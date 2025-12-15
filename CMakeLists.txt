# CMakeList.txt : CMake project for OpenSHC

cmake_minimum_required (VERSION 3.20)

# NOTE: POST_BUILD does not run if the target is unchanged, so a config switch will not trigger them again, so clean + build if issues happen
function(target_file_copy_if_different TARGET FILE DEST)
    message(STATUS "Ensure file \"${FILE}\" is copied to \"${DEST}\" if different for target: ${TARGET}")
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FILE}" "${DEST}"
    )
endfunction()
function(file_dependent_read_list FILE LIST)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${FILE}) # watch the file
    file(STRINGS "${FILE}" TEMP_LIST)
    set(${LIST} "${TEMP_LIST}" PARENT_SCOPE)
endfunction()

project ("OpenSHC")

# Name of exe and dll should be the same
set(OPEN_SHC_NAME "OpenSHC")

# Set to the games version we try to reimplement
# TODO: Discuss: Since the approach should not entail module releases, the version could stay fixed.
# Only devs and interested users would use it and it will have no options to begin with
set(OPEN_SHC_VERSION 1.41.0)

set(CRUSADER_DIR "${CMAKE_SOURCE_DIR}/_original")

# Use static runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_FLAGS "/W3 /EHsc /D \"WIN32\" /D \"_WINDOWS\"")
set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Zi /Od /D \"_DEBUG\"")
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /D \"NDEBUG\"")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Zi /O2 /D \"NDEBUG\"")
set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /D \"NDEBUG\"")

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
include_directories(${CMAKE_SOURCE_DIR}/MSVC1400/VC/include ${CMAKE_SOURCE_DIR}/MSVC1400/VC/PlatformSDK/Include)

# Handle dependencies without source files
include_directories(${CMAKE_SOURCE_DIR}/dependencies/recreated/include)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/recreated/lib)
link_libraries(binkw32 Mss32)

# Handle DirectDraw and DirectPlay
include_directories(${CMAKE_SOURCE_DIR}/dependencies/DXSDK_Aug2007/include)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/DXSDK_Aug2007/lib)
link_libraries(ddraw dplayx)

# Handle pklib
file_dependent_read_list("${CMAKE_SOURCE_DIR}/cmake/pklib-sources.txt" PKLIB_SOURCES)
add_library(pklib ${PKLIB_SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/dependencies/pklib)
link_libraries(pklib)

# Handle lua and ucp3 dynamic libs for DLL target
# TODO?: Would it make any sense at this stage to only add them to the dll?
include_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/ucp3/include
    ${CMAKE_SOURCE_DIR}/dependencies/lua/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/ucp3/lib
    ${CMAKE_SOURCE_DIR}/dependencies/lua/lib
)
link_libraries(
    ucp3
    lua
)


# Include core source and precomp header
set(PCH_FILE ${CMAKE_SOURCE_DIR}/src/precomp/pch.h)
file_dependent_read_list("${CMAKE_SOURCE_DIR}/cmake/core-sources.txt" CORE_SOURCES)



# Add source to this project's executable.
add_executable(OpenSHC.exe WIN32 ${CORE_SOURCES})
set_target_properties(OpenSHC.exe PROPERTIES OUTPUT_NAME ${OPEN_SHC_NAME})
target_compile_definitions(OpenSHC.exe PRIVATE OPEN_SHC_EXE)
target_precompile_headers(OpenSHC.exe PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${PCH_FILE}>)

# Checks if a binkw32_real is present and uses this instead; only checks on reconfigure
if(EXISTS "${CRUSADER_DIR}/binkw32_real.dll")
    target_file_copy_if_different(OpenSHC.exe "${CRUSADER_DIR}/binkw32_real.dll" "$<TARGET_FILE_DIR:OpenSHC.exe>/binkw32.dll")
else()
    target_file_copy_if_different(OpenSHC.exe "${CRUSADER_DIR}/binkw32.dll" "$<TARGET_FILE_DIR:OpenSHC.exe>/binkw32.dll")
endif()
target_file_copy_if_different(OpenSHC.exe "${CRUSADER_DIR}/Mss32.dll" "$<TARGET_FILE_DIR:OpenSHC.exe>/Mss32.dll")

# shfolder is a normal windows lib, however, the game needs to work with the games version, so we still copy it
# it should be checked later if the compiler emits a shfolder.dll on its own or if it statically links, which we do not want
target_file_copy_if_different(OpenSHC.exe "${CRUSADER_DIR}/shfolder.dll" "$<TARGET_FILE_DIR:OpenSHC.exe>/shfolder.dll")



set(OPEN_SHC_DLL_DEST "${CRUSADER_DIR}/ucp/modules/${OPEN_SHC_NAME}-${OPEN_SHC_VERSION}")

add_library(OpenSHC.dll SHARED ${CORE_SOURCES})
set_target_properties(OpenSHC.dll PROPERTIES OUTPUT_NAME ${OPEN_SHC_NAME})
target_compile_definitions(OpenSHC.dll PRIVATE OPEN_SHC_DLL)
target_precompile_headers(OpenSHC.dll PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${PCH_FILE}>)

# Using module folder as runtime output to properly place the dll and other libs
set_target_properties(OpenSHC.dll PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OPEN_SHC_DLL_DEST})

# This strange workaround does ensure that the module folder is generated and that a config change regenerates the dll.
# It "only" costs a file creation and a compare minimum while not changing the actual source. Found no other way.
set(BUILD_TRIGGER_FILE "${OPEN_SHC_DLL_DEST}/buildtrigger.c")
add_custom_target(
    OpenSHC.dll.trigger
    BYPRODUCTS ${BUILD_TRIGGER_FILE}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OPEN_SHC_DLL_DEST}"
    COMMAND ${CMAKE_COMMAND} -E echo "// $<CONFIG>" > ${BUILD_TRIGGER_FILE}.tmp
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${BUILD_TRIGGER_FILE}.tmp ${BUILD_TRIGGER_FILE}
    COMMAND ${CMAKE_COMMAND} -E remove ${BUILD_TRIGGER_FILE}.tmp
    VERBATIM
)
target_sources(OpenSHC.dll PRIVATE ${BUILD_TRIGGER_FILE})
add_dependencies(OpenSHC.dll OpenSHC.dll.trigger)

# Copy ucp definition files
file_dependent_read_list("${CMAKE_SOURCE_DIR}/cmake/ucp-definition.txt" UCP_DEFINITION)
foreach(FILE IN LISTS UCP_DEFINITION)
    get_filename_component(DIR "${FILE}" DIRECTORY)
    if (DIR)
        set(DEST_FILE_DIR "${OPEN_SHC_DLL_DEST}/${DIR}")
        add_custom_command(TARGET OpenSHC.dll POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${DEST_FILE_DIR}"
        )
    else()
        set(DEST_FILE_DIR "${OPEN_SHC_DLL_DEST}")
    endif()
    target_file_copy_if_different(OpenSHC.dll "${CMAKE_SOURCE_DIR}/ucp/${FILE}" "${DEST_FILE_DIR}/${FILE}")
endforeach()
