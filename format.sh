#!/bin/bash

hppFiles=$(find . -type f -name "*.hpp")
cppFiles=$(find . -type f -name "*.cpp")

for file in $hppFiles; do
  echo "clang-format -i ${file}"
  clang-format -i $file
done

for file in $cppFiles; do
  echo "clang-format -i ${file}"
  clang-format -i $file
done