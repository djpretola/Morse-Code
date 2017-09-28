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

set (queue_source
	MorseQueue.h
	MorseQueue.cpp
)

set (morseschedulerqueue_source
	MorseSchedulerQueue.h
	MorseSchedulerQueue.cpp
)

set (morsescheduler_source
	MorseScheduler.h
	MorseScheduler.cpp
	${morseschedulerqueue_source}
)

#Create an executable named from the project.
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

#Create the morsequeue_test executable
add_executable (morsequeue_test morsequeue_test.cpp ${queue_source})

#Create the morsescheduler_test executable
add_executable (morsescheduler_test morsescheduler_test.cpp ${morsescheduler_source})

#Add a custom command to create the Arduino source files from this project.
add_custom_command (TARGET morse
			POST_BUILD
			COMMAND mkdir -p Arduino/lib/
			COMMAND cpp -P -D_H_ARDUINO MorseStack.cpp Arduino/lib/MorseStack.cpp
			COMMAND cpp -P -D_H_ARDUINO MorseTable.cpp Arduino/lib/MorseTable.cpp
			COMMAND cpp -P -D_H_ARDUINO MorseTree.cpp Arduino/lib/MorseTree.cpp
			COMMAND cpp -P -D_H_ARDUINO MorseCode.cpp Arduino/lib/MorseCode.cpp
			COMMAND cpp -P -D_H_ARDUINO MorseQueue.cpp Arduino/lib/MorseQueue.cpp
			COMMAND cp MorseStack.h MorseTable.h MorseTree.h MorseCode.h MorseQueue.h Arduino/lib/
			WORKING_DIRECTORY . 
			COMMENT "Ardunio source files Preprocessed and copied."
)

#Configure install to place the executable in a local bin directory.
#set (CMAKE_INSTALL_PREFIX ".")
#install(TARGETS ${PROJECT_NAME} 
#	RUNTIME 
#	DESTINATION bin)
