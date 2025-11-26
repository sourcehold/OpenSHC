# ======================================================================
# CMake script to generate the source lists,
# since GLOB in build is discouraged.
# Rerun on source change.
# Usage:  cmake -P generate_file_list.cmake
# ======================================================================

cmake_minimum_required(VERSION 3.10)

function(generate_file_list SOURCE_ROOT PATTERNS_LIST OUTPUT_FILE)
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

    # 5. Generate output file
    string(JOIN "\n" FILES_ONLY_STRING ${FILES_ONLY})
    file(WRITE "${OUTPUT_FILE}" "${FILES_ONLY_STRING}\n")

    message(STATUS "Generated file list in: ${OUTPUT_FILE}")
endfunction()

# core sources
generate_file_list("${CMAKE_CURRENT_LIST_DIR}" "src/core/*.c;src/core/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/cmake/core-sources.txt")

# pklib sources
generate_file_list("${CMAKE_CURRENT_LIST_DIR}" "dependencies/pklib/*.c" "${CMAKE_CURRENT_LIST_DIR}/cmake/pklib-sources.txt")

# ucp definition
generate_file_list("${CMAKE_CURRENT_LIST_DIR}/ucp" "*.lua;*.yml;*.md" "${CMAKE_CURRENT_LIST_DIR}/cmake/ucp-definition.txt")
