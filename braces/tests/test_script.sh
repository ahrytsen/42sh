#!/usr/bin/env bash

source brace_tests.sh
source brace_output.sh

gsh=../../cmake-build-debug/gsh
red='\033[0;31m'
green='\033[0;32m'
nc='\033[0m'
num_success=0
num_fail=0

for ((i = 0 ; i < ${#tests[*]}; i++))
do
    gsh_output=$($gsh "${tests[$i]}")
    if [ $? -ne 0 ]
    then
        echo -e "${red}Expansion failed on ${tests[$i]} (line $((i + 1)))"
        echo -e "Exit code: $?${nc}"
        ((num_fail++))
    else
        diff=$(diff <(echo ${output[$i]}) <(echo $gsh_output))
        if [ -z "$diff" ] && [ $? -eq 0 ]
        then
            echo -e "${green}TRUE ${nc}"
            ((num_success++))
        else
            echo -e "${red}FALSE: ${tests[$i]} (line $i)"
            echo -e "    Expected output: ${output[$i]}"
            echo -e "    Your output: $gsh_output ${nc}"
            ((num_fail++))
        fi
    fi
done
echo "============================================"
echo -e "${green}SUCCEED: $num_success ${nc}"
if [ $num_fail -eq 0 ]
then
    echo -en "${green}"
else
    echo -en "${red}"
fi
echo -e "FAILED: $num_fail ${nc}"
