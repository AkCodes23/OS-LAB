#!/bin/bash

if [ "$#" -lt 2 ]; then
  echo "Usage: $0 pattern1 pattern2 ... filename"
  exit 1
fi

file="${@: -1}"

patterns=("${@:1:$#-1}")

while true; do
  echo "Choose an option:"
  echo "1. Search patterns in the file"
  echo "2. Delete all occurrences of the patterns in the file"
  echo "3. Exit"
  read -p "Enter your choice: " choice

  case $choice in
    1)
      for pattern in "${patterns[@]}"; do
        echo "Lines containing pattern '$pattern':"
        grep "$pattern" "$file"
        echo
      done
      ;;
    2)
      for pattern in "${patterns[@]}"; do
        sed -i "/$pattern/d" "$file"
        echo "All occurrences of pattern '$pattern' have been deleted from $file."
      done
      ;;
    3)
      echo "Exiting the script."
      exit 0
      ;;
    *)
      echo "Invalid option. Please choose 1, 2, or 3."
      ;;
  esac
done
