#!/bin/sh
teststring="blah blah blah"

for pastebin in $(./pastebinit -l | egrep "^-" | sed "s/^- //g")
do
    echo "Trying http://$pastebin"
    URL=$(echo -e "$teststring\n$teststring\n$teststring" | ./pastebinit -b http://$pastebin)
    out=$(wget -O - -q "$URL" | grep "$teststring")
    if [ -n "$out" ]; then
        echo "PASS: http://$pastebin ($URL)"
    else
        echo "FAIL: http://$pastebin ($URL)"
    fi
done
