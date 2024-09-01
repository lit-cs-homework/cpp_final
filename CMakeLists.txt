
cmake_minimum_required(VERSION 3.12)

project(cpp_final)

set(mainTargetName "demonslayer")  #

include_directories(${CMAKE_SOURCE_DIR}/include)


# 1. call nim to build static lib

set(NLIB_PATH ${CMAKE_BINARY_DIR}/lib/libnterm.a)

if(NOT WIN32)
  set(NIMC_SH bash -c)
endif()

# execute_process(
#     COMMAND ${NIMC_SH} "nim cpp --noMain --app:staticLib --out:${NLIB_PATH} src/nterm.nim"
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
# )
add_custom_command(
    COMMAND ${NIMC_SH} "nim cpp --noMain --app:staticLib --out:${NLIB_PATH} src/nterm.nim"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    OUTPUT  ${NLIB_PATH}
    DEPENDS ${CMAKE_SOURCE_DIR}/lib/src/*
)
add_custom_target(ntermLibBuild ALL DEPENDS ${NLIB_PATH})

# append built static lib to CMake system
add_library(nterm STATIC IMPORTED)
add_dependencies(nterm ntermLibBuild)
set_property(TARGET nterm PROPERTY IMPORTED_LOCATION ${NLIB_PATH})


# 2. add ftxui
add_subdirectory(lib/ftxui EXCLUDE_FROM_ALL)


# 3. reate target for each dir in src/
file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/*)

foreach(DIR ${SUBDIRS})
    if(NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/${DIR})
      list(REMOVE_ITEM DIR ${CMAKE_SOURCE_DIR}/src/${DIR})
    endif()
endforeach()

foreach(DIR ${SUBDIRS})
    string(COMPARE EQUAL "${DIR}" "main" isMain)
    if( ${isMain} )
      set(CUR_DST ${mainTargetName})
      set(REQ_LIB_DST ${CUR_DST})
    else()
      set(CUR_DST test_${DIR})
      set(REQ_LIB_DST ${DIR})
    endif()

    file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/${DIR}/*.cpp)
    list(REMOVE_ITEM SRCS ${CMAKE_SOURCE_DIR}/src/${DIR}/test.cpp)

    if( ${isMain} )
      add_executable(${CUR_DST} ${SRCS})
    else()
      add_library(${DIR} STATIC ${SRCS})
      set(TEST_MAIN ${CMAKE_SOURCE_DIR}/src/${DIR}/test.cpp)
      # create target named test_${DIR}
      add_executable(${CUR_DST} EXCLUDE_FROM_ALL ${TEST_MAIN})
      target_link_libraries(${CUR_DST} PUBLIC ${DIR})
    endif()

    # hint: ftxui's add_library is also used to expor headers

    # link ftxui and nterm lib
    target_link_libraries(${REQ_LIB_DST}
        PUBLIC ftxui::dom
        PUBLIC ftxui::screen
        PUBLIC ftxui::component
        PUBLIC nterm
    )
endforeach()

# set dependencies relationship
target_link_libraries(test_equip PRIVATE combat)
target_link_libraries(test_combat PRIVATE equip)
# almost a cycle !

target_link_libraries(map PRIVATE combat equip)


# 4. link all ${DIR} target for default target

foreach(DIR ${SUBDIRS})
    #target_sources(${mainTargetName} PUBLIC ${CMAKE_SOURCE_DIR}/src/${DIR}/main.cpp)
    if("${DIR}" STREQUAL "main")
    else()
      target_link_libraries(${mainTargetName} PUBLIC ${DIR})
    endif()
endforeach()


# set default target
#set(DEFAULT_TARGET ${mainTargetName})
