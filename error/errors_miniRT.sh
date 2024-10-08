#!/bin/bash

# !!! Place the error folder in the same directory as miniRT !!!
# !!! Run this script from the error folder !!!

COLOR_YIB='\033[1;93m'
COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_END='\033[0m'

VAL_LOG="val.log"

MINIRT="../miniRT"

if test ! -f "$MINIRT" ; then
	printf "${COLOR_R}Error: miniRT not found${COLOR_END}\n"
	exit 1
fi

val_check () {
	if grep -q "definitely lost:" $VAL_LOG; then
		printf "${COLOR_R}";
		cat $VAL_LOG;
		printf "${COLOR_END}Stopping tests...\n";
		rm $VAL_LOG
		exit 1
	else
		printf "[ ${COLOR_G}OK${COLOR_END} ]\n"
		rm $VAL_LOG
	fi
}

run_test () {
	printf "${COLOR_YIB}$1${COLOR_END}\n"
	valgrind --leak-check=full --show-leak-kinds=all --log-file="$VAL_LOG" $MINIRT $2;
	val_check
}

### TESTS BELOW ###

# run_test "No file"
# run_test "Wrong file" a_file
# run_test "Non-existant file" nada.rt
# 	touch nope.rt
# 	chmod -r nope.rt
# run_test "Unreadable file" nope.rt
# 	rm nope.rt
# run_test "Empty file" empty.rt

# run_test "Ambient: Wrong args" A_extra.rt
# run_test "Ambient: Wrong ratio" A_wRatio.rt
# run_test "Ambient: Wrong RGB" A_wRGB.rt

run_test "Camera: Wrong args" C_extra.rt
run_test "Camera: Wrong XYZ" C_wXYZ.rt
run_test "Camera: Wrong vector" C_wVector.rt
run_test "Camera: Wrong FOV" C_wFOV.rt

# run_test "Light: Wrong args" L_extra.rt
# run_test "Plane: Wrong args" pl_extra.rt
# run_test "Sphere: Wrong args" sp_extra.rt
# run_test "Cylinder: Wrong args" cy_extra.rt
