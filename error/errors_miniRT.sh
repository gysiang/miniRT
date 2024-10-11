#!/bin/bash

# !!! Place the error folder in the same directory as miniRT !!!
# !!! Run this script from the error folder !!!

COLOR_YIB='\033[1;93m'
COLOR_R='\033[0;31m'
COLOR_G='\033[0;32m'
COLOR_END='\033[0m'
declare -i fileCheck=0

VAL_LOG="val.log"

MINIRT="../miniRT"

if [ ! -f $MINIRT ] ; then
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
	if [ -z "$1" ] ; then
		return
	fi
	printf "${COLOR_YIB}$1${COLOR_END}\n"
	if (( fileCheck )) && [ ! -f $2 ] ; then
		printf "${COLOR_R}Error: test file not found${COLOR_END}\n"
		return
	fi
	valgrind --leak-check=full --show-leak-kinds=all --log-file="$VAL_LOG" $MINIRT $2;
	val_check
}

### TESTS BELOW ###

run_test "No file"
run_test "Wrong file" a_file
run_test "Non-existant file" nada.rt

fileCheck=1

	touch nope.rt
	chmod -r nope.rt
run_test "Unreadable file" nope.rt
	rm nope.rt
run_test "Empty file" empty.rt
run_test "Wrong Element" wElement.rt
run_test "No Ambient" noAmbient.rt
run_test "No Camera" noCamera.rt

run_test "Ambient: Wrong args" A_wArgs.rt
run_test "Ambient: Wrong ratio" A_wRatio.rt
run_test "Ambient: Wrong RGB" A_wRGB.rt

run_test "Camera: Wrong args" C_wArgs.rt
run_test "Camera: Wrong XYZ" C_wXYZ.rt
run_test "Camera: Wrong vector" C_wVector.rt
run_test "Camera: Wrong FOV" C_wFOV.rt

run_test "Light: Wrong args" L_wArgs.rt
run_test "Light: Wrong XYZ" L_wXYZ.rt
run_test "Light: Wrong ratio" L_wRatio.rt

run_test "Sphere: Wrong args" sp_wArgs.rt
run_test "Sphere: Wrong XYZ" sp_wXYZ.rt
run_test "Sphere: Wrong diameter" sp_wDiameter.rt
run_test "Sphere: Wrong RGB" sp_wRGB.rt

run_test "Plane: Wrong args" pl_wArgs.rt
run_test "Plane: Wrong XYZ" pl_wXYZ.rt
run_test "Plane: Wrong vector" pl_wVector.rt
run_test "Plane: Wrong RGB" pl_wRGB.rt

run_test "Cylinder: Wrong args" cy_wArgs.rt
run_test "Cylinder: Wrong XYZ" cy_wXYZ.rt
run_test "Cylinder: Wrong vector" cy_wVector.rt
run_test "Cylinder: Wrong diameter" cy_wDiameter.rt
run_test "Cylinder: Wrong height" cy_wHeight.rt
run_test "Cylinder: Wrong RGB" cy_wRGB.rt

printf "\n${COLOR_YIB}Tests Done!${COLOR_END}\n"
