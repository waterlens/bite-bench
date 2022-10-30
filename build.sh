#!/usr/bin/env bash

function compile()
{
    backends=(js chez-callcc chez-monadic chez-lift)
    for elem in "${backends[@]}"
    do
        echo "effekt.sh --backend $elem -c $1 -o \"out-$elem\""
        effekt.sh --backend $elem -c $1 -o "out-$elem"
    done
}

compile counter.effekt
compile layered.effekt
compile nqueens.effekt
compile fsize.effekt
