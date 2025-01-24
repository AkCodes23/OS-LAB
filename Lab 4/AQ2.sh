#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 start_year end_year"
  exit 1
fi
start_year=$1
end_year=$2

echo "Files created between $start_year and $end_year:"
find . -type f -newermt "$start_year-01-01" ! -newermt "$(($end_year + 1))-01-01"
