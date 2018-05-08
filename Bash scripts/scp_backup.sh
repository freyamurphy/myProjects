#!/bin/bash

# Author: Lucy Taylor 160013018
# Date: 15-10-17
# Purpose: Zip Then Use SCP To Backup Repository To Remote Server

if [ $# -ne 0 ]; then
	echo "Usage $0"
else
	# Specifies the repository folder to zip
	folderToZip="../repository/"

	#Read Server Login Into A Variable
	#Check If A Login Exists
	if test -f ../repository/.scpLogin.txt ; then
		login=$(<"../repository/.scpLogin.txt")
	else
		echo "You Must Input Your SCP Login To Continue... (Login Will Be Saved)"
		echo -n "Please Enter Your Host User:"
		read user
		echo -n "Please Enter Your Hostname:"
		read host
		login="$user@$host:~/backups/"
		#Write Login To File
		echo $login >> ../repository/.scpLogin.txt
	fi



	#Prompts the user to enter a name for their backup
	echo -n "Please Name Your Backup:"
	read backupName

	#Creates Zip File Of Repository With Name & Date
	zip -b ../repository/ -r $backupName $folderToZip

	thething="../repository/$backupName.zip $login"
	#Use SCP to commit zipped repository to remote server
	scp $thething

	echo "Complete!"

fi
exit 0