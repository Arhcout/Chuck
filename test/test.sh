#!/bin/bash

test_passed=0

for test in "$@"
do
  echo "Test $test:"
  ./$test
  res=$?
  if [ $res -ne 0 ]; then
    echo "Test $test failed with code $res"
    break
  fi
  let "test_passed=test_passed+1"
done

echo "[$#/$test_passed] Passed"
