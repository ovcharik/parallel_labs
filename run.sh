#!/bin/bash

BLUE="\E[34;1m"
GREEN="\E[32;1m"
RED="\E[31;1m"
RESET="\E[0m"

for bin in $(ls ./bin)
do
  cmd=./bin/$bin
  echo "-------------------------"
  echo -e "$BLUE \bexec $cmd $RESET"
  $cmd && echo -e "$GREEN \bsuccess $RESET" || echo -e "$RED \bfail $RESET"
  echo "-------------------------"
done
