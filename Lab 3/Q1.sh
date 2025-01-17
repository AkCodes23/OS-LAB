#!/bin/bash
# Script to check if a given file is a directory or a regular file

if [ -z "$1" ]; then
  echo "Usage: $0 <file>"
  exit 1
fi

if [ ! -e "$1" ]; then
  echo "The file $1 does not exist."
  exit 2
fi

if [ -d "$1" ]; then
  echo "$1 is a directory."
elif [ -f "$1" ]; then
  echo "$1 is a regular file."
else
  echo "$1 is neither a directory nor a regular file."
fi
