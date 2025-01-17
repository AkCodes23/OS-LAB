#!/bin/bash
# Script to list files containing the input pattern in a specified folder

if [ -z "$1" ]; then
  echo "Usage: $0 <folder> <pattern>"
  exit 1
fi

if [ -z "$2" ]; then
  echo "Usage: $0 <folder> <pattern>"
  exit 2
fi

grep -lr "$2" "$1"
