#!/bin/sh
# show ourselves
cat $0
read

# cat, then compile the host program
rm -f project4_host
read
cat project4_host.c
read
make project4_host
./project4_host
read


# plot the output
rm -f plot.png
gnuplot project4_plot.p
DISPLAY=:0.0 firefox file://$PWD/plot.png
