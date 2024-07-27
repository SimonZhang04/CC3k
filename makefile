CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = cc3k
CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${OBJECTS:.o=.d}

${EXEC}:${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}

.PHONY : clean
clean :
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
