CC=gcc
BUILD_FOLDER=./build/

all: aoc3 aoc4 aoc5 aoc6 aoc7

aoc3: aoc3.c
	${CC} -o ${BUILD_FOLDER}aoc3 aoc3.c

aoc4: aoc4.c
	${CC} -o ${BUILD_FOLDER}aoc4 aoc4.c

aoc5: aoc5.c
	${CC} -o ${BUILD_FOLDER}aoc5 aoc5.c

aoc6: aoc6.c
	${CC} -o ${BUILD_FOLDER}aoc6 aoc6.c

aoc7: aoc7.c
	${CC} -o ${BUILD_FOLDER}aoc7 aoc7.c

clean:
	rm ${BUILD_FOLDER}aoc3 ${BUILD_FOLDER}aoc4 ${BUILD_FOLDER}aoc5 ${BUILD_FOLDER}aoc6 ${BUILD_FOLDER}aoc7
