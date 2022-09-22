#!/bin/bash
set -e

WORKINGDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HELP=false

function check_platform() {
	if [ "$PLATFORM" != "" ]; then
		echo choose only one platform
		exit
	fi

	var="$1"
	PLATFORM="${var:1}"
}

if [ "$1" == "" ]; then
    HELP=true
fi

while [ "$1" != "" ]; do
	case "$1" in
		"-h")
			HELP=true
		;;
		"-help")
			HELP=true
		;;
		"-mac" | \
		"-mvs19")
			check_platform $1
		;;
		*)
			echo Unknown command $1
			echo -e [-h] show help
			exit
		;;
	esac

    shift
done

function show_help() {
	echo -e '\t' [-mvs19] '\t\t' win mvs19 build
	echo -e '\t' [-mvs17] '\t\t' win mvs17 build
    echo -e '\t' [-mac] '\t\t'   mac xcode build
}

if [ $HELP == true ]; then
	show_help
	exit
fi

if [ "$PLATFORM" == "mac" ]; then
	echo -- build OS X project

	mkdir -p ./build/mac
	cd ./build/mac

	cmake ../.. -G Xcode -DPLATFORM=MACOS
fi

if [ "$PLATFORM" == "mvs19" ]; then
	echo -- building WIN32 project

	mkdir -p ./build/win32
	cd ./build/win32
	
	cmake ../../ -G \
		"Visual Studio 16 2019" \
		-A \
		Win32 \
		-T \
		v142 \
		-DCMAKE_CONFIGURATION_TYPES="Release;Debug;" \
		-DCMAKE_GENERATOR_PLATFORM=x64 \
		-DPLATFORM=WINDOWS
fi
