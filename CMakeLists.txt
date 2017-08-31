#Required cmake version information.
CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

#Our project name.
project(morse)

#A message example
message ("Compiling project: " ${PROJECT_NAME})

#The files required for compiling.
set (stack_source
	MorseStack.h
	MorseStack.cpp
)

set (table_source
	MorseTable.h
	MorseTable.cpp
)

set (tree_source
	MorseTree.h
	MorseTree.cpp
	${table_source}
)

set (morsecode_source
	MorseCode.h
	MorseCode.cpp
	${stack_source}
	${tree_source}
)

#Create an executable named from the project.
#add_executable (morse morse.cpp ${stack_source} ${table_source} ${tree_source})
add_executable (morse morse.cpp ${stack_source} ${tree_source})

#Create the morse_ro executable
add_executable (morse_ro  morse_ro.cpp  ${stack_source} ${tree_source})

#Create the morse_generate executable
add_executable (morse_generate morse_generate.cpp ${stack_source} ${tree_source})

#Create the morse_generate2 executable
add_executable (morse_generate2 morse_generate2.cpp ${morsecode_source}) 

#Create the morse_to_ascii executable 
add_executable (morse_to_ascii morse_to_ascii.cpp ${morsecode_source}) 

#Create the morsecode_test executable 
add_executable (morsecode_test morsecode_test.cpp ${morsecode_source}) 

#Configure install to place the executable in a local bin directory.
#set (CMAKE_INSTALL_PREFIX ".")
#install(TARGETS ${PROJECT_NAME} 
#	RUNTIME 
#	DESTINATION bin)
