# Laboratory of Nuclear and Subnuclear Physics 2
The aim of the experiment is to measure the muon half life $`\tau`$. To do this an apparatus has been built with an iron slab (Fe) 3 scintillators P1, P2, P3 each coupled to 2 PMTs (PhotoMultiplierTubes).

Experimental apparatus: <br />
 ------------	P3 <br />
 ------------	P2 <br />
%%%%%%%%%	Fe <br />
 ------------	P1 <br />

Things to do:
- Analyze the background file R3\_background\_P123.csv and fit it with a pol0 to obtain the b parameter;
- Analyze the CLEANED data by fitting mainly P1 and P2 (because they're the closest to Fe). We defined the following PROCEDURE:
	- fit the exp data with: $`a\left(e^{-t/\tau_0}+\frac{1}{R}e^{-t/\tau_{\mu^-}}\right)+b`$;
	- extract from the FIT the parameters $\tau\_{\mu^-}$ (dirty), $\tau\_0$ (clean) and b (background);
	- use R, Q from literature;
	- derive $\Lambda\_c$ = $1/\tau\_c$ and compare it with the literature value.


Experiment information:
- total duration of data acquisition: 1008896.663 s = 280.249 h = 11 d 16 h
- total number of recorded events: 37149 => Rate = 0.0368 Hz
- total duration of background acquisition: 15726.539 s = 4 h 22 min
- total number of recorded background events: 1540 => Rate = 0.0980 Hz
