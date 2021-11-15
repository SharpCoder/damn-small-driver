#!/bin/sh

sudo rmmod halfqwerty 2> /dev/null
sudo insmod src/halfqwerty.ko
