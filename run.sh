#!/bin/bash

BLUE="\E[34;1m"
GREEN="\E[32;1m"
RED="\E[31;1m"
RESET="\E[0m"

function run_cmd {
  if [ $# -eq 1 ]
  then
    $1
  else
    echo -e "$BLUE \bInputs:$RESET\n$(cat $2)\n$BLUE \bResult:$RESET"
    $1 < $2
  fi
  [ $? -eq 0 ] && echo -e "$GREEN \bsuccess $RESET" || echo -e "$RED \bfail $RESET"
}

for bin in $(ls ./bin)
do
  cmd=./bin/$bin
  echo "-------------------------"
  echo -e "$BLUE \bexec $cmd $RESET"
  if [ $(ls ./inputs | grep $bin | wc -l) -ge 1 ]
  then
    for input in $(ls ./inputs | grep $bin)
    do
      inputf=./inputs/$input
      run_cmd $cmd $inputf
    done
  else
    run_cmd $cmd
  fi
  echo "-------------------------"
done
