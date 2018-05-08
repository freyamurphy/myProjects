#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 13-10-17
# Purpose: View a list of files in the repository

if [ $# -ne 0 ]; then
	# The script takes no arguments
	echo "Usage: $0"

# Check if repository exists
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

	echo `ls ../repository`
	
	# This could be improved to show which files are currently checked out
fi
exit 0