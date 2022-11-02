#!/usr/bin/env bash

function effekt_compile()
{
    backends=(js chez-callcc chez-monadic chez-lift)
    for elem in "${backends[@]}"
    do
        echo "effekt.sh --backend $elem -c $1 -o \"out-$elem\""
        effekt.sh --backend $elem -c $1 -o "out-$elem"
    done
}

function koka_compile()
{
    echo "koka -c $1 --builddir='out-koka'"
    koka -c $1 --builddir='out-koka'
}

koka_compile   counter.kk
koka_compile   layered.kk
koka_compile   nqueens.kk
koka_compile   fsize.kk
koka_compile   logger.kk
koka_compile   pingpong.kk
koka_compile   iter.kk
effekt_compile counter.effekt
effekt_compile layered.effekt
effekt_compile nqueens.effekt
effekt_compile fsize.effekt
effekt_compile logger.effekt
effekt_compile pingpong.effekt
effekt_compile iter.effekt
