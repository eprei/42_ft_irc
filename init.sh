#!/bin/sh
./ircserv 6667 asd
sleep 1
./test1 &
./test2 &

