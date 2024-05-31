#!/bin/sh

basedir=$(dirname "$0")
for file in $(find "$basedir" -name "*.hh" -o -name "*.cc"); do
  echo "$file"
  clang-format -i "$file"
done
