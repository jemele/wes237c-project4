############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls_restructured
set_top ofdm
add_files fft.cpp
add_files fft.h
add_files ofdm_test_vector.h
add_files -tb fft_test.cpp
add_files -tb out.gold.dat
open_solution "solution1"
set_part  {xc7z020clg484-1}
create_clock -period 10

source "./directives.tcl"
csynth_design
