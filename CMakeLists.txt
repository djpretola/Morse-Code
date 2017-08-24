#Required cmake version information.
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

#Our project name.
project(morse)

#A message example
message ("Compiling project: " ${PROJECT_NAME})

#The files required for compiling.
set (${PROJECT_NAME}_headers 
	MorseStack.h 
	MorseTable.h 
	MorseTree.h
)

set (${PROJECT_NAME}_sources 
	MorseStack.cpp 
	MorseTable.cpp 
	MorseTree.cpp
)

#Create an executable named from the project.
add_executable (morse morse.cpp ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

#Create the morse_ro executable
add_executable (morse_ro  morse_ro.cpp ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

#Create the morse_generate executable
add_executable (morse_generate morse_generate.cpp ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

#Configure install to place the executable in a local bin directory.
set (CMAKE_INSTALL_PREFIX ".")
install(TARGETS ${PROJECT_NAME} 
	RUNTIME 
	DESTINATION bin)
