#!/bin/bash
# Script to replace .txt extension with .text in current directory recursively

find . -type f -name "*.txt" -exec bash -c 'mv "$0" "${0%.txt}.text"' {} \;
