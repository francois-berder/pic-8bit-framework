#!/bin/sh -e

INPUT_DIRS="mcu/"

beautify_dir()
{
    local DIR=$1
    local MCU_SOURCES="$(find ${DIR} -type f -iname *.[c\|h])"
    for f in ${MCU_SOURCES}; do
        uncrustify -q -c uncrustify.cfg -l C --no-backup --replace $f
    done
}

for d in ${INPUT_DIRS}; do
    beautify_dir $d
done
