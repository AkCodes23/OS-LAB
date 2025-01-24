#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

file=$1

# Check if the file exists
if [ ! -e "$file" ]; then
  echo "File does not exist."
  exit 1
fi

permissions=$(ls -l "$file" | awk '{print $1}')
echo "Permissions for $file:"
echo "Owner: ${permissions:1:3}"
echo "Group: ${permissions:4:3}"
echo "Others: ${permissions:7:3}"
