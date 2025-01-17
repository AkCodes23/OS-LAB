#!/bin/bash
# Script to calculate gross salary

echo "Enter Basic Salary:"
read basic
echo "Enter TA:"
read ta

# Calculate 10% of Basic Salary
percent=$(echo "0.1 * $basic" | bc)

# Calculate Gross Salary
gross_salary=$(echo "$basic + $ta + $percent" | bc)

echo "Gross Salary is: $gross_salary"
