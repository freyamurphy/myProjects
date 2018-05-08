#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Delete a file from the repository

if [ $# -ne 0 ]; then
	echo "Usage: $0"
	exit 1

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

	./view_files.sh
	echo -n "Enter the name of the file to delete: "
	read file
	
	while test ! -f ../repository/$file; do
		echo "That file does not exist."
		./view_files.sh
		echo -n "Please enter the name of the file to delete: "
		read file
	done
	
	echo -n "Are you sure you want to delete the file $file ? [y/n] "
	read answer
	
	if [ $answer = "y" ]; then
		rm ../repository/$file
		rm ../repository/$file_log.txt
	fi
fi
exit 0