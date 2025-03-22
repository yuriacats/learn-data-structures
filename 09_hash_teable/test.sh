#!/bin/zsh

DATA_SIZE=100000



for i in {1..999} ; do
    CAPACITY=$((DATA_SIZE * 1000 / i))


    DURATION=$( (time ./dist/main $CAPACITY $DATA_SIZE 0)  2>&1 | grep -oe "[0-9.]* total" | sed 's/total//')

    echo "$CAPACITY $DURATION"
done
