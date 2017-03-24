CXX := g++

CXXFLAGS := -Wall Wfatal-errors -Wextra -std=c++14

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
PROG := arachno_bob
###############################################################################

all : ${PROG}

${PROG} : ${SRCS}
	${CXX} -o $@ $^ 

.PHONY : clean
clean:
	rm -rf ${OBJS} ${PROG}

