# All Targets


# Tool invocations
# Executable "cTrace" depends on the files main.o , Session.o , Graph.o , Agent.o , Tree.o
cTrace: bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o
#@echo 'building target:cTrace'
	g++ -o bin/cTrace bin/main.o bin/Session.o bin/Graph.o bin/Tree.o bin/Agent.o
	bin/cTrace src/config1.json


# Depends on the source and header files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

# Depends on the source and header files
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

# Depends on the source and header files 
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

# Depends on the source and header files 
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp

# Depends on the source and header files 
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp


#Clean the build directory
clean: 
	rm -f bin/*

