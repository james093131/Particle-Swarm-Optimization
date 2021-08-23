reset
set term gif animate delay 0.05
#set term gif animate

set output "./Particle.gif"
set xrange [-32.768: 32.768]
set yrange [-32.768:32.768]
set xyplane at 0

do for [i=20:20000:400]{
  set title sprintf("Ackley NFE = %i",i)
  splot sprintf("/home/ailab/Downloads/Euclidean_distance/PLT_AND_TXT/R10_OG_DE/R10%i.txt",i) u 1:2:3 ps 0.2 pt 14  lc rgb '#8d99ae' t "points" 
  #bfa89e
}
set output
