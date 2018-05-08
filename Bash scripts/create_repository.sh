#!/bin/bash

# Author: Freya Murphy 170004881
# Date: 15-10-17
# Purpose: Create a repository in the parent folder of the scripts

if [ $# -ne 0 ]; then
	echo "Usage: $0"
else
	mkdir ../repository
fi
exit 0