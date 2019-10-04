#!/bin/bash


for ((i = 5 ; i >= 0  ; i--)); do
  sleep 1
  echo $i
done

avrdude -p t2313 -c usbasp -U lfuse:w:0xe4:m
