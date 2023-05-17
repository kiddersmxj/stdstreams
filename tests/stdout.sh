#!/bin/bash

SLEEPTIME=0.1
SPEED=40
POTPOSITION=30
THROTTLE=0
while :
do
    i=0
    while [ $i -le 10 ]; do
        i=$(($i+1))
        SPEED=$(($SPEED+$i))
        POTPOSITION=$(($POTPOSITION-$i))
        THROTTLE=$(($THROTTLE+i/2))
        printf "Mode=Neutral, Speed=$SPEED, Potentiometer Position=$POTPOSITION, Status=Throttle but no drive selected, Status2=Fat error code pls handle, Emerg=, longer status=long status, EMERGStatus=there is an emergency status, Throttle=$THROTTLE\n"
        sleep $SLEEPTIME
    done
    i=0
    while [ $i -le 10 ]; do
        i=$(($i+1))
        SPEED=$(($SPEED-$i))
        POTPOSITION=$(($POTPOSITION+$i))
        THROTTLE=$(($THROTTLE-i/2))
        printf "Mode=Neutral, Speed=$SPEED, Potentiometer Position=$POTPOSITION, Status=Throttle but no drive selected, Status2=Fat error code pls handle, Emerg=, longer status=long status, Throttle=$THROTTLE\n"
        sleep $SLEEPTIME
    done
done

