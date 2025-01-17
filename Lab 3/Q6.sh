#!/bin/bash
# Script to replace "ex:" with "Example:" under specific conditions

for file in *; do
  [ -f "$file" ] || continue
  sed -i -E 's/^ex:/Example:/g; s/\.ex:/\.Example:/g' "$file"
done
