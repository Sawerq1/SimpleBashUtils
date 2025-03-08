CC=gcc
CC_FLAGS=-Wall -Werror -Wextra -std=c11
BUILD_NAME=s21_grep

all: build

build: ${BUILD_NAME}

rebuild: clean build

${BUILD_NAME}: s21_grep.c
	${CC} ${CC_FLAGS} s21_grep.c -o ${BUILD_NAME}

clean:
	rm -rf ./${BUILD_NAME}
