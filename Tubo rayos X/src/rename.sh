#!/bin/bash

for file in *.hh; do
    mv "$file" "`basename "$file" .hh`.cc"
done
