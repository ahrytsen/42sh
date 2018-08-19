#!/bin/bash -i

source tests.sh

gsh=../../cmake-build-debug/gsh
red='\033[0;31m'
green='\033[0;32m'
nc='\033[0m'
num_success=0
num_fail=0

cd testing_directory

for ((i = 0 ; i < ${#tests[*]}; i++))
do
    echo_output=$(echo ${tests[$i]})
    gsh_output=$($gsh "${tests[$i]}")
    if [ $? -ne 0 ]
    then
        echo -e "${red}Expansion failed on ${tests[$i]} (line $((i + 1)))"
        echo -e "Exit code: $?${nc}"
        ((num_fail++))
    else
        if [ "$echo_output" =  "$gsh_output" ]
        then
#            echo -e "${green}TRUE ${nc}"
            ((num_success++))
        else
            echo -e "${red}FALSE: ${tests[$i]} (line $i)"
            echo -e "    Expected output: $echo_output"
            echo -e "    Your output: $gsh_output ${nc}"
#            echo $(wc <<< $echo_output)
#            echo $(wc <<< $gsh_output)
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

cd -