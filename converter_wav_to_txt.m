
file_wav = "./encore.wav";

# Read files and extract the samples along with its frequency
[samples, freq] = audioread(file_wav);


# Downsample it, to get it to the frequency you want (11.025kHz)
# samples = downsample(samples, round(freq / 11025);

# Adjust the samples (originals are fractions between -1 and 1) to range
#   between 0 and 65535 (16-bits) assuming 16 bit DAC usage on embedded device
bit_size = 16;
dac_precision = 2^16;
#samples = round((samples + 1) * (dac_precision / 2));
width = size(samples);
printf('%d %d\n', freq, width);
for x = 1:1:10
  samples(x, 1)
  samples(x, 2)
  printf('\n')

endfor
x = 1:1:10;
#plot (x, samples);

# write the samples output to a file.
# file = fopen('mapped_sample.txt', 'w');
# fprintf(file, '%d,', samples);
# fprintf(file, '\n');
# file.fclose();