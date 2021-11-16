#!/bin/sh
sudo /usr/src/linux-headers-5.10.0-9-amd64/scripts/sign-file sha256 /home/josh/.ssh/private_key.priv /home/josh/.ssh/public_key.der ./src/halfqwerty-serio.ko
