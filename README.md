# Laboratory of Nuclear and Subnuclear Physics 2
Material for data analysis for Lab2 course of 2023.

Experimental apparatus: <br />
 ------------	P3 <br />
 ------------	P2 <br />
%%%%%%%%%%%	Fe <br />
 ------------	P1 <br />

Things TO DO:
- Calibration, in order to obtain the relation between clk ticks and ns, in order to finally FIT with exp the plots;
- Analyze the background file R3\_background\_2.csv and fit it with a pol0 to obtain the b parameter;
- Analyze the DATA by fitting mainly P1 and P2 (because they're the closest to Fe).
- Decide how to FILTER the data, for example:
	- filter the TRIPLE occurrences for each trigger
	- filter the occurrences with BOTH P1 and P2 (e- CANNOT be detected both UNDER and OVER the absorber)
	- remove the TRIPLE 4095 (fff) occurrences.
All this filtering can be easily done with Pandas, Python or whatever.
