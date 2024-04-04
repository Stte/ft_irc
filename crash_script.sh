#!/bin/bash
set -m
./ircserv 2345 password &
sleep 1
nc localhost 2345 << EOF
PASS password
NICK nick
USER nick nick nick nick
JOIN #channel
KICK #channel nick
EOF
fg
