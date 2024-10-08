#!/bin/bash

COLOR_YIB='\033[1;93m'
COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_END='\033[0m'

# Absolute path to miniRT (leave empty if in the same parent directory as the script)
LOCATION=

if test -z "$LOCATION" ; then
	MINIRT="../miniRT"
else
	MINIRT="$LOCATION/miniRT"
fi

if test ! -f "$MINIRT" ; then
	printf "${COLOR_R}Error: miniRT not found${COLOR_END}\n"
	exit 1
fi

val_check () {
	if grep -q "definitely lost:" val.log; then
		printf "${COLOR_R}";
		cat val.log;
		printf "${COLOR_END}Stopping tests...\n";
		rm val.log
		exit 1
	else
		printf "[ ${COLOR_G}OK${COLOR_END} ]\n"
		rm val.log
	fi
}

run_test () {
	printf "${COLOR_YIB}$1${COLOR_END}\n"
	valgrind --leak-check=full --show-leak-kinds=all $MINIRT $2 2>val.log; val_check
}

# SETUP

# TESTS BELOW
run_test "No file"
run_test "Wrong file" a_file
run_test "Non-existant file" nada.rt
	touch nope.rt
	chmod -r nope.rt
run_test "Unreadable file" nope.rt
	rm nope.rt
run_test "Empty file" empty.rt
run_test "Invalid ambient" A_extra.rt
run_test "Invalid camera" C_extra.rt
run_test "Invalid light" L_extra.rt
run_test "Invalid plane" pl_extra.rt
run_test "Invalid sphere" sp_extra.rt
run_test "Invalid cylinder" cy_extra.rt
