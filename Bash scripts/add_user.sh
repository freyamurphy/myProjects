#!/bin/bash

# Author: Lucy Taylor 160013018
#		  & Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Add a user to the repository

if [ $# -ne 0 ]; then
	echo "Usage: $0"
	
# Check if repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1
	
else
	#Specifies the file where user logins are stored
	userDB="../repository/.users.txt"
	
	# Check if there are any registered users
	if test ! -f ../repository/.users.txt; then
		# Create a superuser account
		username=$USER
	else
		# Read superuser line from file (first line)
		read line < $userDB
		# Extract the username from the line
		superuser=${line% *}
		
		if [ $USER != $superuser ]; then
			echo "Access denied."
			exit 1
		else
			echo -n "Please enter a username: "
			read username
		fi
	fi

	#Prompt user for a password
	echo -n "Please create a password for $username:"
	read password

	#Adds user and password as new line to the file
	line="$username $password\n"
	echo $line >> $userDB

	#Presents confirmation to the user
	echo "User $username Created Successfully!"
fi
exit 0