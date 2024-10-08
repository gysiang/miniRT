#!/bin/bash

COLOR_YIB='\033[1;93m'
COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_END='\033[0m'

# Destination of miniRT
MINIRT=../miniRT

val_check () {
	if grep -q "definitely lost:" val.log; then
		printf "${COLOR_R}" && cat val.log && printf "${COLOR_END}"
	else
		printf "[ ${COLOR_G}OK${COLOR_END} ]\n"
	fi
	rm -fr val.log
}

run_test () {
	printf "${COLOR_YIB}$1${COLOR_END}\n"
	valgrind --leak-check=full --show-leak-kinds=all $MINIRT $2 2>val.log; val_check
}

# TESTS BELOW

run_test "No file"
run_test "Wrong file" a_file
run_test "Invalid ambient" A_extra.rt
