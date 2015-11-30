clear all
close all

n = [];
gold = [];
for i = 1:256
       n = [n, 1 + j, -1+j, 1-j, -1-j];
          gold = [gold, 0, 1, 2, 3];
      end
      input_i = real(ifft(n, 1024))';
      input_q = imag(ifft(n, 1024))';

      figure(1)
      subplot(3,1,1)
      plot(1:1024, input_i)
      subplot(3,1,2)
      plot(1:1024, input_q)
      subplot(3,1,3)
      plot(1:1024, gold)

% write out.gold.dat
f = fopen('ofdm_test_vector.h','w');

% write out gold symbols
fprintf(f,'const unsigned int gold_symbols[] = {');
for i = 1:length(gold)
    fprintf(f,'%d,',gold(i));
end
fprintf(f,'};\n',gold(length(gold)));

% write out input_i
fprintf(f,'const DTYPE gold_i[] = {');
for i = 1:length(input_i)
    fprintf(f,'%f,',input_i(i));
end
fprintf(f,'};\n');

% write out input_q
fprintf(f,'const DTYPE gold_q[] = {');
for i = 1:length(input_q)
    fprintf(f,'%f,',input_q(i));
end
fprintf(f,'};\n');

% write out interleaved i/q
fprintf(f,'const DTYPE gold_iq[] = {');
for i = 1:length(input_q)
    fprintf(f,'%f,%f,',input_i(i), input_q(i));
end
fprintf(f,'};\n');


fclose(f)
