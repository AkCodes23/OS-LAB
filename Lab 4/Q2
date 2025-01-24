#!/bin/bash

for file in "$@"; do
  read -p "delete $file? (y/n) " answer
  if [ "$answer" = "y" ]; then
    rm "$file"
    echo "$file deleted."
  else
    echo "$file not deleted."
  fi
done
