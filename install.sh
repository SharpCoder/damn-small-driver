#!/bin/sh

sudo rmmod halfqwerty 2> /dev/null
sudo rmmod halfqwerty-serio 2> /dev/null
sudo insmod src/halfqwerty-serio.ko
