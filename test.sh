#!/bin/sh
teststring="blah blah blah"

for interpreter in python python3
do
    for pastebin in $(./pastebinit -l | egrep "^-" | sed "s/^- //g")
    do
        echo "Trying http://$pastebin ($interpreter)"
        URL=$(echo -e "$teststring\n$teststring\n$teststring" | $interpreter pastebinit -b http://$pastebin)
        out=$(wget -O - -q "$URL" | grep "$teststring")
        if [ -n "$out" ]; then
            echo "PASS: http://$pastebin ($URL) ($interpreter)"
        else
            echo "FAIL: http://$pastebin ($URL) ($interpreter)"
        fi
        echo ""
    done
done
