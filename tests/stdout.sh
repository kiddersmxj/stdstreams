#!/bin/bash

SLEEPTIME=0.1
SPEED=40
POTPOSITION=60
while :
do
    i=0
    while [ $i -le 10 ]; do
        i=$(($i+1))
        SPEED=$(($SPEED+$i))
        POTPOSITION=$(($POTPOSITION-$i))
        printf "Mode=Neutral, Speed=$SPEED, PotPosition=$POTPOSITION, Status=Throttle but no drive selected, Status2=Fat error code pls handle, Emerg=, longer status=long status, EMERGStatus=there is an emergency status\n"
        sleep $SLEEPTIME
    done
    i=0
    while [ $i -le 10 ]; do
        i=$(($i+1))
        SPEED=$(($SPEED-$i))
        POTPOSITION=$(($POTPOSITION+$i))
        printf "Mode=Neutral, Speed=$SPEED, PotPosition=$POTPOSITION, Status=Throttle but no drive selected, Status2=Fat error code pls handle, Emerg=, longer status=long status\n"
        sleep $SLEEPTIME
    done
done

