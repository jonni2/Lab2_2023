# Laboratory of Nuclear and Subnuclear Physics 2
Material for data analysis for Lab2 course of 2023.

Experimental apparatus: <br />
 ------------	P3 <br />
 ------------	P2 <br />
%%%%%%%%%%%	Fe <br />
 ------------	P1 <br />

Things TO DO:
- Analyze the background file R3\_background\_P123.csv and fit it with a pol0 to obtain the b parameter;
- Analyze the CLEANED data by fitting mainly P1 and P2 (because they're the closest to Fe). We defined the following PROCEDURE:
	- fit the exp data with: $a$($`e^{-t/\tau_0}`$+$`\frac{1}{R}e^{-t/\tau}`$)+b;
	- extract from the FIT the parameters $\tau\_{\mu^-}$ (dirty), $\tau\_0$ (clean) and b (background);
	- use R, Q from literature;
	- derive $\Lambda\_c$ = $1/\tau\_c$ and compare it with the literature value.

Questions:
- What is value of R?
- Is the fitting equation described above the correct one? 

Experiment information:
- total duration of data acquisition: 1008896.663 s = 280.249 h = 11 d 16 h
