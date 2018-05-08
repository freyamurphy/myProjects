#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Add a file to the repository

if [ $# -ne 0 ]; then
	echo "Usage: $0"
	exit 1
	
# Check if repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1

else
	# Get name of file to add
	echo -n "Enter the name of the file to add: "
	read file

	# Check if a file with that name already exists.
	while test -f ../repository/$file; do
		echo -n "A file with that name already exists."
		echo -n "Enter a different name for the file to add: "
		read file
	done

	# Create the file
	touch ../repository/$file
fi
exit 0