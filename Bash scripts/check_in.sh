#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Check a file into a repository

# Check the correct number of arguments was given
if [ $# -gt 1 ]; then
	echo "Usage $0 [filepath]"
	exit 1
	
# Check that repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1
	
else

	# If no argument was given
	if [ $# -eq 0 ]; then
		# Get the path to the file to check in
		echo "Enter the path of the file to check in:"
		read filepath
	else
		filepath=$1
	fi
		
	# Check that file exists
	while test ! -f $filepath; do
		echo "That file does not exist."
		echo -n "Enter the path of the file to check in:"
		read filepath
	done
	
	# Strip away everything before the last /
	filename="${filepath##*/}"
	
	# Check if the file is in the repository
	if test ! -f ../repository/$filename; then
		echo "This file does not already exist in the repository."
		echo -n "Do you want to add the file to the repository? [y/n] "
		read answer
		
		if [ $answer = "y" ]; then
			cp $filepath ../repository
		else
			exit 0
		fi
		
	else
		# Add a check that the file was previously logged out
	
		echo -n "Are you sure you want to overwrite the $filename file in the repository? [y/n] "
		read answer
		
		if [ $answer = "y" ]; then
			cp $filepath ../repository/$filename
		else
			exit 0
		fi
	fi
	
	# Log information about who checked in the file, when and why
	./add_log.sh $filename
	
	# Mark the file as no longer busy
	chmod a-x ../repository/$filename
fi
exit 0