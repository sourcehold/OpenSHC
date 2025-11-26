# ======================================================================
# CMake script to generate the source lists,
# since GLOB in build is discouraged.
# Rerun on source change.
# Usage:  cmake -P generate_file_list.cmake
# ======================================================================

cmake_minimum_required(VERSION 3.10)

function(generate_file_list SOURCE_ROOT PATTERNS_LIST OUTPUT_FILE VAR_NAME)
    set(ALL_ENTRIES "")

    # 1. Recursively collect entries for each pattern
    foreach(PAT ${PATTERNS_LIST})
        file(GLOB_RECURSE ENTRIES_FOR_PAT RELATIVE "${SOURCE_ROOT}" "${SOURCE_ROOT}/${PAT}")
        list(APPEND ALL_ENTRIES ${ENTRIES_FOR_PAT})
    endforeach()

    # 2. Keep only files
    set(FILES_ONLY "")
    foreach(entry IN LISTS ALL_ENTRIES)
        if(EXISTS "${SOURCE_ROOT}/${entry}" AND NOT IS_DIRECTORY "${SOURCE_ROOT}/${entry}")
            list(APPEND FILES_ONLY "${entry}")
        endif()
    endforeach()

    # 3. Remove duplicates (possible if patterns overlap)
    list(REMOVE_DUPLICATES FILES_ONLY)

    # 4. Sort alphabetically
    list(SORT FILES_ONLY)

    # 5. Generate output include file
    file(WRITE "${OUTPUT_FILE}" "# Auto-generated file — do not edit!\n")
    file(APPEND "${OUTPUT_FILE}" "set(${VAR_NAME}\n")
    foreach(FILE IN LISTS FILES_ONLY)
        file(APPEND "${OUTPUT_FILE}" "    ${FILE}\n")
    endforeach()
    file(APPEND "${OUTPUT_FILE}" ")\n")

    message(STATUS "Generated file list in: ${OUTPUT_FILE}")
endfunction()


# Directory whose files you want to list
set(SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/src")

# File pattern (e.g., "*.cpp", "*.h", "*.*", "*.txt")
set(PATTERN "*.cpp")

# Where to write the generated include file
set(OUTPUT_FILE "${CMAKE_CURRENT_LIST_DIR}/file_list.cmake")

# Variable name that will appear inside file_list.cmake
set(VAR_NAME "GENERATED_FILES")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/cmake")

# core sources
generate_file_list("${CMAKE_CURRENT_LIST_DIR}" "src/core/*.c;src/core/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/cmake/core-sources.cmake" CORE_SOURCES)

# pklib sources
generate_file_list("${CMAKE_CURRENT_LIST_DIR}" "dependencies/pklib/*.c" "${CMAKE_CURRENT_LIST_DIR}/cmake/pklib-sources.cmake" PKLIB_SOURCES)

# ucp definition
generate_file_list("${CMAKE_CURRENT_LIST_DIR}/ucp" "*.lua;*.yml;*.md" "${CMAKE_CURRENT_LIST_DIR}/cmake/ucp-definition.cmake" UCP_DEFINITION)
