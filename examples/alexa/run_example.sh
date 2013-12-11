#!/bin/sh

if ! which harry > /dev/null ; then
    echo "Could not find harry in PATH"
    exit
fi

# Compute Levenshtein distance
harry -v -d '' -m levenshtein alex1000.txt dist_levenshtein.txt

# Print most similar sites
python most_similar.py dist_levenshtein.txt

# Compute Jaro-Winkler distance
harry -v -d '' -m jarowinkler alex1000.txt dist_jarowinkler.txt

# Print most similar sites
python most_similar.py dist_jarowinkler.txt


