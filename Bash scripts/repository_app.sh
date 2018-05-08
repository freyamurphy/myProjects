#!/bin/bash

# Author: Freya Murphy 170004881 
#		  & Lucy Taylor 160013018
# Date: 16-10-17
# Purpose: A front end menu allowing the user to access the repository

if [ $# -ne 0 ]; then
	# The script takes no arguments.
	echo "Usage: $0"
else

	# Some files in the shard folder have strange access permissions
	# This makes sure all the scripts can run but does not effect the passwords file.
	chmod 777 ./*

	# Check if the repository exists
	if test ! -d ../repository; then
		echo "You have not created a repository yet."
		echo -n "Would you like to create a repository? [y/n] "
		read answer
		
		if [ $answer = "y" ]; then
			./create_repository.sh
			echo "$USER will be the superuser for this repository."
			./add_user.sh
		else
			echo "You cannot use this application without a repository. Goodbye!"
			exit 0
		fi
	fi
	
	# Check whether the user has access to the repository
	./check_user.sh
		
	#Exit with error code 1 if password incorrect or user not found
	if [ $? != 0 ]; then
		exit 1
	fi

	# Set default value	
	choice=1
	
	# Main program loop
	while [ $choice != "q" ]; do
		cat <<- MENU
			
			Enter 1 to view a list of files in the repository.
			Enter 2 to add a file to the repository.
			Enter 3 to delete a file from the repository.
			Enter 4 to log a file out of the repository.
			Enter 5 to check a file into the repository.
			Enter 6 to edit a file in the repository.
			Enter 7 to add a new user to the repository.
			Enter 8 to delete the repository.
			Enter 9 to backup the repository to a remote server.
			Enter q to quit.
		MENU

		echo -n "Enter your choice: "
		read choice	
		
		case $choice in
			1) ./view_files.sh
			;;
			2) ./add_file.sh
			;;
			3) ./delete_file.sh
			;;
			4) ./log_out.sh
			;;
			5) ./check_in.sh
			;;
			6) ./edit.sh
			;;
			7) ./add_user.sh
			;;
			8) ./delete_repository.sh
			;;
			9) ./scp_backup.sh
			;;
			q) echo "Goodbye!"; exit 0
			;;
			*) echo "Invalid input. Try again."
		esac
		
		# Check that repository still exists
		if test ! -d ../repository; then
			echo "Goodbye!"
			exit 0
		fi
	done
fi
echo "Goodbye!"
exit 0