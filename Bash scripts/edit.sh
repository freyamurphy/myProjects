#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Edit a text file from within the terminal

if [ $# -gt 0 ]; then
	echo "Usage: $0"
	
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

	# Get the file to edit
	./view_files.sh
	echo -n "Enter the name of the file you want to edit: "
	read filename
	
	# Check that the file exists in the repository
	while test ! -f ../repository/$filename; do
		echo "There is no file called $filename in the repository."
		./view_files.sh
		echo -n "Enter the name of the file you want to edit: "
		read filename
	done
	
	# Make a temporary folder to save the file in while editing
	mkdir ../repository/temp
	# Log file out of repository before editing
	./log_out.sh $filename ../repository/temp
	
	# Edit the (temporary) file
	pico ../repository/temp/$filename
	
	# Check the file back in once editing is finished
	./check_in.sh ../repository/temp/$filename
	
	# Delete the temporary file and folder
	rm ../repository/temp/$filename
	rmdir ../repository/temp
fi
exit 0