reset
set terminal gif size 1024,768
set term gif animate delay 50
#set term gif animate

set output "./Particle.gif"
set xrange [-35.0: 35.0]
set yrange [-35.0:35.0]
set title font ",18"
do for [i=50:5050:500]{
  set title sprintf("Ackley NFE = %i",i-50)
  plot sprintf("./2d_ackley_points/%i.txt",i) u 1:2 ps 2.5 pt 7  lc rgb '#8d99ae' t "Particles" 
  #bfa89e
}
set output
