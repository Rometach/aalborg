set xlabel "Threshold"
set ylabel "Compression factor"
set y2label "Recovery factor"

# DIAGONAL (Compression & Recovery)
set y2range [0:1]
set y2tics
plot "Diagonal/F1.dat" using 1:2 title 'Compression' with line, "Diagonal/F1.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/F1.png"
set title "F1"
replot
set terminal wxt

set y2range [0:1]
set y2tics
plot "Diagonal/Morris.dat" using 1:2 title 'Compression' with line, "Diagonal/Morris.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/Morris.png"
set title "Morris"
replot
set terminal wxt

set y2range [0:1]
set y2tics
plot "Diagonal/Rahn.dat" using 1:2 title 'Compression' with line, "Diagonal/Rahn.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/Rahn.png"
set title "Rahn"
replot
set terminal wxt

set y2range [0:1]
set y2tics
plot "Diagonal/Lewin.dat" using 1:2 title 'Compression' with line, "Diagonal/Lewin.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/Lewin.png"
set title "Lewin"
replot
set terminal wxt

set y2range [0:1]
set y2tics
plot "Diagonal/Teitelbaum.dat" using 1:2 title 'Compression' with line, "Diagonal/Teitelbaum.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/Teitelbaum.png"
set title "Teitelbaum"
replot
set terminal wxt

set y2range [0:1]
set y2tics
plot "Diagonal/Isaacson.dat" using 1:2 title 'Compression' with line, "Diagonal/Isaacson.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "Diagonal/Isaacson.png"
set title "Isaacson"
replot
set terminal wxt



# LZ77 (Compression & Recovery)

set xrange [0.3:1]
set y2range [0:1]
set y2tics
plot "LZ77/F1.dat" using 1:2 title 'Compression' with line axis x1y1, "LZ77/F1.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/F1.png"
set title "F1"
replot
set terminal wxt

set xrange [0:10]
set y2range [0:1]
set y2tics
plot "LZ77/Morris.dat" using 1:2 title 'Compression' with line, "LZ77/Morris.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/Morris.png"
set title "Morris"
replot
set terminal wxt

set xrange [0.35:1]
set y2range [0:1]
set y2tics
plot "LZ77/Rahn.dat" using 1:2 title 'Compression' with line, "LZ77/Rahn.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/Rahn.png"
set title "Rahn"
replot
set terminal wxt

set xrange [0.475:1]
set y2range [0:1]
set y2tics
plot "LZ77/Lewin.dat" using 1:2 title 'Compression' with line, "LZ77/Lewin.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/Lewin.png"
set title "Lewin"
replot
set terminal wxt

set xrange [0:5]
set y2range [0:1]
set y2tics
plot "LZ77/Teitelbaum.dat" using 1:2 title 'Compression' with line, "LZ77/Teitelbaum.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/Teitelbaum.png"
set title "Teitelbaum"
replot
set terminal wxt

set xrange [0:1]
set y2range [0:1]
set y2tics
plot "LZ77/Isaacson.dat" using 1:2 title 'Compression' with line, "LZ77/Isaacson.dat" using 1:3 title 'Recovery' with line axis x1y2
set terminal png
set output "LZ77/Isaacson.png"
set title "Isaacson"
replot
set terminal wxt



# LZ77 (R=f(C))

set xlabel "Compression factor"
set ylabel "Recovery factor"
unset y2tics

set xrange [1:9]
plot "LZ77/AllSorted.dat" using 1:2 title 'F1' with line, "LZ77/AllSorted.dat" using 3:4 title 'Isaacson' with line, "LZ77/AllSorted.dat" using 5:6 title 'Rahn' with line, "LZ77/AllSorted.dat" using 7:8 title 'Lewin' with line, "LZ77/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "LZ77/AllSorted.dat" using 11:12 title 'Morris' with line, "LZ77/AllSorted.dat" using 13:14 title 'Equality' with points, "LZ77/AllSorted.dat" using 15:16 title 'PCS-prime' with points, "LZ77/AllSorted.dat" using 17:18 title 'Translation' with points, "LZ77/AllSorted.dat" using 19:20 title 'Root note' with points, 
set terminal png
set output "LZ77/RfC.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt

set xrange [1.2:2]
plot "LZ77/AllSorted.dat" using 1:2 title 'F1' with line, "LZ77/AllSorted.dat" using 3:4 title 'Isaacson' with line, "LZ77/AllSorted.dat" using 5:6 title 'Rahn' with line, "LZ77/AllSorted.dat" using 7:8 title 'Lewin' with line, "LZ77/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "LZ77/AllSorted.dat" using 11:12 title 'Morris' with line, "LZ77/AllSorted.dat" using 13:14 title 'Equality' with points, "LZ77/AllSorted.dat" using 15:16 title 'PCS-prime' with points, "LZ77/AllSorted.dat" using 17:18 title 'Translation' with points, "LZ77/AllSorted.dat" using 19:20 title 'Root note' with points, 
set terminal png
set output "LZ77/RfC2.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt


# DIAGONAL (R=f(C))

set yrange [0:0.7]
set xrange [1:9]
plot "Diagonal/AllSorted.dat" using 1:2 title 'F1' with line, "Diagonal/AllSorted.dat" using 3:4 title 'Isaacson' with line, "Diagonal/AllSorted.dat" using 5:6 title 'Rahn' with line, "Diagonal/AllSorted.dat" using 7:8 title 'Lewin' with line, "Diagonal/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "Diagonal/AllSorted.dat" using 11:12 title 'Morris' with line, "Diagonal/AllSorted.dat" using 13:14 title 'Equality' with points, "Diagonal/AllSorted.dat" using 15:16 title 'PCS-prime' with points, "Diagonal/AllSorted.dat" using 17:18 title 'Translation' with points, "Diagonal/AllSorted.dat" using 19:20 title 'Root note' with points, 
set terminal png
set output "Diagonal/RfC.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt

set xrange [1.2:2]
plot "Diagonal/AllSorted.dat" using 1:2 title 'F1' with line, "Diagonal/AllSorted.dat" using 3:4 title 'Isaacson' with line, "Diagonal/AllSorted.dat" using 5:6 title 'Rahn' with line, "Diagonal/AllSorted.dat" using 7:8 title 'Lewin' with line, "Diagonal/AllSorted.dat" using 9:10 title 'Teitelbaum' with line, "Diagonal/AllSorted.dat" using 11:12 title 'Morris' with line, "Diagonal/AllSorted.dat" using 13:14 title 'Equality' with points, "Diagonal/AllSorted.dat" using 15:16 title 'PCS-prime' with points, "Diagonal/AllSorted.dat" using 17:18 title 'Translation' with points, "Diagonal/AllSorted.dat" using 19:20 title 'Root note' with points, 
set terminal png
set output "Diagonal/RfC2.png"
set title "Recovery = f(Compression)"
replot
set terminal wxt
