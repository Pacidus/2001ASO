

system('cat -n SolarSystemPos.dat > SolarP.dat & cat -n SolarSystemVit.dat > SolarV.dat')
system('join SolarV.dat SolarP.dat > SolarT.dat')

M1 = 1.9891*10**30
M2 = 1.8986*10**30
G = 6.674*10**-11
plot "SolarT.dat" u 0:($0==0?(E0=(-G*M1*M2/sqrt(($6-$7)*($6-$7)+($8-$9)*($8-$9)))+((M1*($2*$2+$4*$4))+(M2*($3*$3+$5*$5)))/2):$1)
unset table
E0 = E0

set terminal pdf size 1900/70,1080/70
set output 'Energietot.pdf'
set title "Énergie totale d'un système à 2 corps"

set xlabel "Années"
set ylabel "Énergie en Joules"

plot "SolarT.dat" u ($1/365.25): ((M1*($2*$2+$4*$4))+(M2*($3*$3+$5*$5)))/2 title "Énergie cinétique",\
"SolarT.dat" u ($1/365.25): (-G*M1*M2/sqrt(($6-$7)*($6-$7)+($8-$9)*($8-$9))) title "Énergie potentielle",\
"SolarT.dat" u ($1/365.25): (-G*M1*M2/sqrt(($6-$7)*($6-$7)+($8-$9)*($8-$9)))+((M1*($2*$2+$4*$4))+(M2*($3*$3+$5*$5)))/2 title "Énergie totale"

plot "SolarT.dat" u ($1/365.25): ((-G*M1*M2/sqrt(($6-$7)*($6-$7)+($8-$9)*($8-$9)))+((M1*($2*$2+$4*$4))+(M2*($3*$3+$5*$5)))/2) title "Énergie totale" w l

set ylabel "Raport de l'énergie par rapport à E_0"

plot "SolarT.dat" u ($1/365.25): ((-G*M1*M2/sqrt(($6-$7)*($6-$7)+($8-$9)*($8-$9)))+((M1*($2*$2+$4*$4))+(M2*($3*$3+$5*$5)))/2)/E0 title "Énergie totale Normalisée" w l
