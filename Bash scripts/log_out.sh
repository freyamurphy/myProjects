#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Log a file out of the repository

# Check the correct number of arguments were given
if [ $# -gt 2 ]; then
	echo "Usage $0 [filename] [destination]"
	exit 1
	
# Check that repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1
	
else
	# Check if repository is empty
	filelist=`ls ../repository`
	length=${#filelist}
	if [ $length -eq 0 ]; then
		echo "There are no files in the repository."
		exit 0;
	fi

	# If no filename was given as an argument
	if [ $# -eq 0 ]; then
		# Get name of file to log out
		./view_files.sh
		echo -n "Enter the name of the file to log out: "
		read filename
	else
		filename=$1
	fi
	
	file="../repository/$filename"
	
	# Check that file exists
	while test ! -f $file; do
		echo "That file does not exist."
		./view_files.sh
		echo -n "Enter the name of the file to log out:"
		read filename
		file="../repository/$filename"
	done
	
	# Check if the file has been logged out already
	if [ -x $file ]; then
		echo "Error: This file has already been logged out."
		exit 1
	fi
	
	# If no destination was passed as an argument
	if [ $# -ne 2 ]; then
		# Get destination to save file
		echo "Enter the location where you want to save $file : "
		read destination
	else
		destination=$2
	fi
	
	# Check that destination exists
	while test ! -d $destination; do
		echo "That location does not exist."
		echo "Enter the location where you want to save $filename : "
		read destination
	done
	
	# Copy the file to the working folder
	cp $file $destination
	
	# Add an execute permission as a marker that the file is busy
	chmod u+x $file
fi
exit 0