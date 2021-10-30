#!/bin/bash

coords=
y=0
while IFS= read -r line; do
    line=$(echo -ne "$line" | od -t x1 -An -w1 -v)
    x=0
    while read -r ch; do
        if [ "$ch" != "01" ]; then
            coords="${coords}${x} ${y} ${ch}\n"
        fi
        ((x++))
    done <<< "$line"
    ((y++))
done

coords="$(echo -ne "$coords" | shuf)"

tput clear
echo "$coords" |
while read -r x y ch; do
    sleep 0.02
    tput cup "$y" "$x"
    echo -ne "\x${ch}"
done

tput cup "$(tput lines)" 0
