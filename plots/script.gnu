# DIAGONAL (Compression & Recovery)

plot "Diagonal/F1.dat" using 1:2 title 'Compression' with line, "Diagonal/F1.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/F1.png"
set title "F1"
replot
set terminal wxt

plot "Diagonal/Morris.dat" using 1:2 title 'Compression' with line, "Diagonal/Morris.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/Morris.png"
set title "Morris"
replot
set terminal wxt

plot "Diagonal/Rahn.dat" using 1:2 title 'Compression' with line, "Diagonal/Rahn.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/Rahn.png"
set title "Rahn"
replot
set terminal wxt

plot "Diagonal/Lewin.dat" using 1:2 title 'Compression' with line, "Diagonal/Lewin.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/Lewin.png"
set title "Lewin"
replot
set terminal wxt

plot "Diagonal/Teitelbaum.dat" using 1:2 title 'Compression' with line, "Diagonal/Teitelbaum.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/Teitelbaum.png"
set title "Teitelbaum"
replot
set terminal wxt

plot "Diagonal/Isaacson.dat" using 1:2 title 'Compression' with line, "Diagonal/Isaacson.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "Diagonal/Isaacson.png"
set title "Isaacson"
replot
set terminal wxt



# DIAGONAL (R=f(C))

plot "Diagonal/AllSorted.dat" using 1:2 title 'F1' with line, "Diagonal/AllSorted.dat" using 3:4 title 'Isaacson' with line, "Diagonal/AllSorted.dat" using 5:6 title 'Rahn' with line, "Diagonal/AllSorted.dat" using 7:8 title 'Lewin' with line, "Diagonal/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "Diagonal/AllSorted.dat" using 11:12 title 'Morris' with line, 
set terminal png
set output "Diagonal/RfC.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt



# LZ77 (Compression & Recovery)

plot "LZ77/F1.dat" using 1:2 title 'Compression' with line, "LZ77/F1.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/F1.png"
set title "F1"
replot
set terminal wxt

plot "LZ77/Morris.dat" using 1:2 title 'Compression' with line, "LZ77/Morris.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/Morris.png"
set title "Morris"
replot
set terminal wxt

plot "LZ77/Rahn.dat" using 1:2 title 'Compression' with line, "LZ77/Rahn.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/Rahn.png"
set title "Rahn"
replot
set terminal wxt

plot "LZ77/Lewin.dat" using 1:2 title 'Compression' with line, "LZ77/Lewin.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/Lewin.png"
set title "Lewin"
replot
set terminal wxt

plot "LZ77/Teitelbaum.dat" using 1:2 title 'Compression' with line, "LZ77/Teitelbaum.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/Teitelbaum.png"
set title "Teitelbaum"
replot
set terminal wxt

plot "LZ77/Isaacson.dat" using 1:2 title 'Compression' with line, "LZ77/Isaacson.dat" using 1:3 title 'Recovery' with line
set terminal png
set output "LZ77/Isaacson.png"
set title "Isaacson"
replot
set terminal wxt



# LZ77 (R=f(C))

set xrange [0:10]
plot "LZ77/AllSorted.dat" using 1:2 title 'F1' with line, "LZ77/AllSorted.dat" using 3:4 title 'Isaacson' with line, "LZ77/AllSorted.dat" using 5:6 title 'Rahn' with line, "LZ77/AllSorted.dat" using 7:8 title 'Lewin' with line, "LZ77/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "LZ77/AllSorted.dat" using 11:12 title 'Morris' with line, 
set terminal png
set output "LZ77/RfC.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt
