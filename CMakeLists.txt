#Required cmake version information.
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

#Our project name.
project(morse)

#A message example
message ("Compiling project: " ${PROJECT_NAME})

#The files required for compiling.
set (${PROJECT_NAME}_headers MorseStack.h MorseTable.h MorseTree.h)
set (${PROJECT_NAME}_sources morse.cpp MorseStack.cpp MorseTable.cpp MorseTree.cpp)

#Create an executable named from the project.
add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

#Configure install to place the executable in a local bin directory.
set (CMAKE_INSTALL_PREFIX ".")
install(TARGETS ${PROJECT_NAME} 
	RUNTIME 
	DESTINATION bin)
