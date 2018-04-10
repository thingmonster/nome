cmake_minimum_required(VERSION  3.9)

# Require  modern C++
set(CMAKE_CXX_STANDARD  14)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

project(Games_Engineering)

####  Setup  Directories  ####

#Main  output  directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Ouput  all  DLLs  from  all  libs  into  main  build  folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})






#### Copy res into build directory  ####
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
	"${PROJECT_SOURCE_DIR}/res"
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)




#### Add  External  Dependencies  ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")





####  Nome ####
file(GLOB_RECURSE SOURCES nome/*.cpp  nome/*.h)
add_executable(NOME ${SOURCES})
target_include_directories(NOME PRIVATE ${SFML_INCS})
target_link_libraries(NOME sfml-graphics sfml-audio engine lib_ecm lib_tiles lib_maths)

set_target_properties(NOME PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY 
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(NOME copy_resources)




#### Game Engine ####
file(GLOB_RECURSE ENGINE engine/*.cpp engine/*.h)
add_library(engine STATIC ${ENGINE})
target_include_directories(engine 
	INTERFACE "${CMAKE_SOURCE_DIR}/engine/" 
	PRIVATE ${SFML_INCS}
)
target_link_libraries(engine lib_ecm lib_tiles lib_maths sfml-graphics)


#### ECM ####
file(GLOB_RECURSE SOURCE_FILES engine/lib_ecm/*.cpp engine/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm 	INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_ecm/")

target_link_libraries(lib_ecm PRIVATE sfml-graphics lib_tiles lib_maths)


#### Tile Loader ####
file(GLOB_RECURSE LOAD_TILES engine/lib_tiles/*.cpp engine/lib_tiles/*.h)
add_library(lib_tiles STATIC ${LOAD_TILES})
target_include_directories(lib_tiles 
	INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_tiles/" 
	PRIVATE ${SFML_INCS}
)
target_link_libraries(lib_tiles lib_maths sfml-graphics)



#### Maths Library ####
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths/maths.h")
target_include_directories(lib_maths 
	INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths/" 
	SYSTEM INTERFACE ${SFML_INCS}
)





