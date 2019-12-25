#!/usr/bin/env bash
# Version Mon Apr  1 19:48:21 PDT 2019
for i in tests/*.gpl
#for i in tests/t001.gpl t106.gpl
do
  echo -n $i
  valgrind ./gpl $i 2>/tmp/$$ >/dev/null
  grep "definitely lost: 0 bytes in 0 blocks" /tmp/$$ 2>&1 1>/dev/null
  first=$?
  grep "indirectly lost: 0 bytes in 0 blocks" /tmp/$$ 2>&1 1>/dev/null
  second=$?
  grep "possibly lost: 0 bytes in 0 blocks" /tmp/$$ 2>&1 1>/dev/null
  third=$?
  grep "no leaks are possible" /tmp/$$ 2>&1 1>/dev/null
  fourth=$?
  if [[ $fourth -eq 0 || $first -eq 0 && $second -eq 0 && $third -eq 0 ]]
  then
    echo " -- Success!"
  else
    echo " -- ################### Memory leak!"
  fi
done
