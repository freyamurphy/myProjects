#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Add a log entry with username, date and time of check in and a comment

if [ $# -ne 1 ]; then
	echo "Usage $0 filename"
else
	# Assumes the repository is in the parent folder of the script
	logFile="../repository/$1_log.txt"
	
	#Get a comment from the user
	echo -n "Enter a comment: "
	read comment
	
	line="$USER $(date) $comment"
	
	# Send the log to the file
	echo $line >> $logFile
fi
exit 0