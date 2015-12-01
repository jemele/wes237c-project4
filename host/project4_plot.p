set terminal png;
set output "plot.png";
set multiplot layout 4, 1
set tmargin 2;

# input i samples
set title "Input I";
unset key;
plot "input_i.txt" using 1:2 with lines;

# input q samples
set title "Input Q"
plot "input_q.txt" using 1:2 with lines;

# output symbols
set title "Output"
plot "output.txt" using 1:2 with lines;

# output symbols (1-125)
set title "Output points (1 - 125)"
plot [1:125] "output.txt" using 1:2 with lines;
