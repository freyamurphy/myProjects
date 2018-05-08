#!/bin/bash

# Author: Lucy Taylor 160013018
#		  & Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Check a user/password combination

if [ $# -ne 0 ]; then
	echo "Usage: $0"
	
# Check if repository exists
elif test ! -d ../repository; then
	echo "Error: Repository does not exist."
	exit 1
	
else
	#Specifies the file where user logins are stored
	userDB="../repository/.users.txt"

    if test ! -f $userDB; then
        echo "There are no registered users."
        exit 1
    fi
    
    # Check if user has an account
    findUser=`grep -c "$USER " $userDB`
    if [ $findUser -eq 1 ]; then
    	echo "Welcome $USER."
    	
    	# Get password from user
    	echo -n "Please enter your password:"
    	read password
    	
    else
    	echo "The user $USER does not have access to this repository."
    	exit 1
    fi

    if [ -z $password ] ; then
    	echo "Password Cannot Be Blank!"
    	exit 1
    fi

	#Check for user password combination in file
	line="$USER $password"
	match=`grep -c "$line" "$userDB"`

	if [ $match = 1 ]; then
		# Presents confirmation to the user
		echo "Access granted!"
		exit 0
	else
		echo "Incorrect password."
		echo "Access denied."
		exit 1
	fi
fi
exit 0
