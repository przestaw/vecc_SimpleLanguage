#!/bin/bash

EXE=./bin/Release/vecc-program
if [ -f "$EXE" ]; then
        echo $EXE -i ./example_files/example_1.vecc
    $EXE -v 3 -i ./example_files/example_1.vecc

        echo $EXE -i ./example_files/example_2.vecc
    $EXE -v 3 -i ./example_files/example_2.vecc

        echo $EXE --vec -i ./example_files/example_3.vecc
    $EXE --vec -v 3 -i ./example_files/example_3.vecc

        echo $EXE --vec -i ./example_files/example_4.vecc
    $EXE --vec -v 3 -i ./example_files/example_4.vecc

        echo $EXE --fib -i ./example_files/example_fib.vecc
    $EXE --fib -v 3 -i ./example_files/example_fib.vecc
else
    echo "$EXE does not exist. Compile program."
fi
