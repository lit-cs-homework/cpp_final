
cmake_minimum_required(VERSION 3.12)

set(PROJ_NAME demonslayer)
project(${PROJ_NAME}
	LANGUAGES CXX
	VERSION 0.0.1
)

option(remote_tui_repo "set on if fetching ftxui from github" OFF)

if (remote_tui_repo)
	include(FetchContent)
	FetchContent_Declare(ftxui
		URL https://github.com/ArthurSonzogni/ftxui
		GIT_TAG v5.0.0
	)

	FetchContent_GetProperties(ftxui)
	if(NOT ftxui_POPULATED)
		FetchContent_Populate(ftxui)
		add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
		FetchContent_MakeAvailable(ftxui)
endif()

else()
	add_subdirectory(lib/ftxui EXCLUDE_FROM_ALL)
endif()

set(tests "")  # a list

macro(cppfinal_addsrc_or_test ARG_SOURCE)
  #cmake_parse_arguments(ARG "WIN32" "SOURCE" "" ${ARGN})
	set(targ test_${ARG_SOURCE})
	set(srcDir src/${ARG_SOURCE})
	set(testSrc "${srcDir}/test.cpp")
  add_executable("${targ}" EXCLUDE_FROM_ALL "${testSrc}")
	#add_test( NAME "${ARG_SOURCE}" COMMAND "${ARG_SOURCE}")
	list(APPEND tests "${targ}")
	file(GLOB cppSrc "${srcDir}/*.cpp" LIST_DIRECTORIES false)
	file(REAL_PATH "${testSrc}" realTestSrc)
	list(REMOVE_ITEM cppSrc "${realTestSrc}")
  target_sources(${PROJ_NAME}Lib PUBLIC ${cppSrc})
endmacro()

	file(GLOB mains "src/main/*.cpp" LIST_DIRECTORIES false)
	list(REMOVE_ITEM mains "${testSrc}")

add_executable(${PROJ_NAME}
	#src/main/main.cpp
	${mains}
	#src/dialog/test.cpp
)

add_library(${PROJ_NAME}Lib)
target_link_libraries(${PROJ_NAME}Lib
	PUBLIC ftxui::dom
	PUBLIC ftxui::screen
	PUBLIC ftxui::component
)
cppfinal_addsrc_or_test(dialog)
cppfinal_addsrc_or_test(equip)
cppfinal_addsrc_or_test(combat)
cppfinal_addsrc_or_test(map)


foreach(elem ${tests})
	target_link_libraries(${elem} ${PROJ_NAME}Lib)
endforeach()

include_directories(include)

target_link_libraries(${PROJ_NAME} PRIVATE ${PROJ_NAME}Lib)

#target_include_directories(${PROJ_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
