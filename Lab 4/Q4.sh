#!/bin/bash

if [ "$#" -lt 2 ]; then
  echo "Usage: $0 -option filename"
  echo "Options: -linecount, -wordcount, -charcount"
  exit 1
fi

option=$1
file=$2

case $option in
  -linecount)
    line_count=$(wc -l < "$file")
    echo "Line count: $line_count"
    ;;
  -wordcount)
    word_count=$(wc -w < "$file")
    echo "Word count: $word_count"
    ;;
  -charcount)
    char_count=$(wc -m < "$file")
    echo "Character count: $char_count"
    ;;
  *)
    echo "Invalid option. Use -linecount, -wordcount, or -charcount."
    exit 1
    ;;
esac
