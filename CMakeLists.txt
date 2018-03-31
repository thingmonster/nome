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








#### Add  External  Dependencies  ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")





####  Nome ####
file(GLOB_RECURSE SOURCES nome/*.cpp  nome/*.h)
add_executable(NOME ${SOURCES})
target_include_directories(NOME PRIVATE ${SFML_INCS})
target_link_libraries(NOME sfml-graphics engine lib_ecm)




#### Game Engine ####
file(GLOB_RECURSE ENGINE engine/*.cpp engine/*.h)
add_library(engine STATIC ${ENGINE})
target_include_directories(engine 
	INTERFACE "${CMAKE_SOURCE_DIR}/engine/" 
	PRIVATE ${SFML_INCS}
)
target_link_libraries(engine lib_ecm sfml-graphics)


#### ECM ####
file(GLOB_RECURSE SOURCE_FILES engine/lib_ecm/*.cpp engine/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm 	INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_ecm/")

target_link_libraries(lib_ecm PRIVATE sfml-graphics)








