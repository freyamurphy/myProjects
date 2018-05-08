#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Delete the repository and all files in it.

if [ $# -ne 0 ]; then
	# The script takes 0 arguments
	echo "Usage: $0"
	exit 1

# Check that repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1
	
else
	echo -n "Are you sure you want to delete the repository? This will also delete all files in the repository. [y/n] "
	read answer
	
	if [ $answer = "y" ]; then
		rm -rf ../repository
	fi
	exit 0
fi
exit 0