CXX = g++ -std=c++2a
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCE = $(shell find Source/ | grep .cpp)
HEADERS = -IHeaders #$(shell find Headers -type d | awk '{print "-I"$$1}')
OUTPUT = Binaries/program

TEST_SOURCE = ${shell find Test/Source | grep .cpp}
TEST_HEADERS = -ITest/Headers
TEST_OUTPUT = Binaries/test_suite

DEBUG_FLAGS = -fsanitize=address -g
COMPILER_FLAGS = -Wall -Werror -Wextra -pedantic 

debug:
	${CXX} main.cpp ${COMPILER_FLAGS} ${SOURCE} -o${OUTPUT} -IHeaders ${SFML_LIBS} ${DEBUG_FLAGS}

test:
	${CXX} Test/main.cpp ${COMPILER_FLAGS} -o${TEST_OUTPUT} ${SOURCE} ${HEADERS} ${TEST_SOURCE} ${TEST_HEADERS} ${SFML_LIBS}

