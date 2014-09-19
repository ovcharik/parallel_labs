#!/bin/bash

BLUE="\E[34;1m"
GREEN="\E[32;1m"
RED="\E[31;1m"
RESET="\E[0m"

function exec_cmd {
  if [ $# -eq 1 ]
  then
    $1
  else
    echo -e "$BLUE \bInputs:$RESET\n$(cat $2)\n$BLUE \bResult:$RESET"
    $1 < $2
  fi
  result=$?
  [ $result -eq 0 ] && echo -e "$GREEN \bsuccess $RESET" || echo -e "$RED \bfail $RESET"
  return $result
}

function run_cmd {
  echo "-------------------------"
  echo -e "$BLUE \b\$ $1 $RESET"
  if [ $(ls ./inputs | grep $2 | wc -l) -ge 1 ]
  then
    for input in $(ls ./inputs | grep $2)
    do
      inputf=./inputs/$input
      exec_cmd "$1" $inputf || exit
    done
  else
    exec_cmd "$1" || exit
  fi
}

for bin in $(ls ./bin)
do
  cmd=./bin/$bin
  if [ $(echo $cmd | grep "\.mpi$" | wc -l) -eq 1 ]
  then
    for np in 2 4 5
    do
      cmd="mpiexec -np $np ./bin/$bin"
      run_cmd "$cmd" $bin || exit
    done
  else
    run_cmd "$cmd" $bin || exit
  fi
done
