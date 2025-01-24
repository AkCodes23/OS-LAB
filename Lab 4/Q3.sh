#!/bin/bash

sort_strings() {
  IFS=$'\n' sorted=($(sort <<<"$*"))
  echo "${sorted[*]}"
}
sorted_strings=$(sort_strings "$@")
echo "Sorted strings: $sorted_strings"
