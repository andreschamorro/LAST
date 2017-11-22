#!/bin/sh
# convert fasta sequence to uppercase
awk '/^>/ {print($0)}; /^[^>]/ {print(toupper($0))}' $1 > $2
