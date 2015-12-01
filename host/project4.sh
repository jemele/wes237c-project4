#!/bin/sh
# show ourselves
cat $0
sleep 1

# cat, then compile the host program
rm -f project4_host
sleep 1
cat project4_host.c
sleep 1
make project4_host
sleep 1

# plot the output
rm -f plot.png
gnuplot project4_plot.p
DISPLAY=:0.0 firefox://$PWD/plot.png
