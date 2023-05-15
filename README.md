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
	- fit the exp data with: $`a\left(e^{-t/\tau_0}+\frac{1}{R}e^{-t/\tau_{\mu^-}}\right)+b`$;
	- extract from the FIT the parameters $\tau\_{\mu^-}$ (dirty), $\tau\_0$ (clean) and b (background);
	- use R, Q from literature;
	- derive $\Lambda\_c$ = $1/\tau\_c$ and compare it with the literature value.

Questions:
- Is it ok R = 1.21?
- Are the values of $`\Lambda_c`$ correct? (We don't obtain exactly $`4.4\times10^{6}`$ $`s^{-1}`$)?
- Is the formula of $`G_{F}^2`$ correct (there was probably a mistake in a power of 2)?

Experiment information:
- total duration of data acquisition: 1008896.663 s = 280.249 h = 11 d 16 h
