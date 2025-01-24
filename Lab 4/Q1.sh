#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "$0 source_file destination_file"
  exit 1
fi

source_file=$1
destination_file=$2

cp "$source_file" "$destination_file"

if [ $? -eq 0 ]; then
  echo "File copied successfully!"
else
  echo "Failed to copy"
  exit 1
fi
