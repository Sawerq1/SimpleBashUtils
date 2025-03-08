CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -std=c11
BUILD_NAME = s21_cat

all: build

build: ${BUILD_NAME}

rebuild: clean build

${BUILD_NAME}: cat_parse.c cat_print.c s21_cat.c
	${CC} ${CC_FLAGS} cat_parse.c cat_print.c s21_cat.c -o ${BUILD_NAME}

clean:
	rm -rf ./${BUILD_NAME}
