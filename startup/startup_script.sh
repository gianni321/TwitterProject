#!/bin/bash

# "crontab -e" to edit the boot commands

# Start up the dynamic update client

sudo /usr/local/bin/noip2

sleep 5

# Pipe the hostname -I (ipaddress) to noip2 -i (sets ipaddress)

sudo /usr/local/bin/noip2 -i `hostname -I`

# We may need to call gpsmon and ctrl+c to Start GPS daemon
# pipe GPS daemon to our program

sudo gpspipe -rn 50 | grep "GPGLL" > "Coordinates.txt"

mv Coordinates.txt ~/TwitterProject/resources/Coordinates.txt

~/TwitterProject/bin/gpstweet > ~/gpstweet.txt 2>&1 &

sleep 10

~/TwitterProject/src/tweeting/receive_tweet.py > ~/receive_tweet.txt 2>&1 &

sleep 1

~/TwitterProject/bin/server > ~/server.txt 2>&1 &


echo "test"
