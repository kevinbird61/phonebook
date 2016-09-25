reset
set ylabel 'cache-misses'
set style fill solid
set title 'cache-misses statistics'
set term png enhanced font 'Consolas,10'
set output 'cache.png'

plot [:][:]'output_cache.txt' using 2:xtic(1) with histogram title 'original', \
'' using ($0-0.06):(0):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'optimized'  , \
'' using ($0+0.15):(0.01):3 with labels title ' ', \
'' using 4:xtic(1) with histogram title 'string compression'  , \
'' using ($0+0.3):(0):4 with labels title ' '
