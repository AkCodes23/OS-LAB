#!/bin/bash
# Script to delete all even numbered lines in a text file

if [ -z "$1" ]; then
  echo "Usage: $0 <file>"
  exit 1
fi

awk 'NR % 2 == 1' "$1" > temp && mv temp "$1"
