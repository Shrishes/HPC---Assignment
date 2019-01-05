/****************************************************************************
  This program demonstrates the equation of line, which define y as a 
  function of slope(m), x, and intercept(c) with vertical axis. 
  Redirect the output of this program and plot the results as a scatter
  graph in a spreadsheet. 

  Compile with:

    cc -o line-plot-01 line-plot-01.c -lm
  
  Dr Kevan Buckley, University of Wolverhampton, 2018
*****************************************************************************/
#include <stdio.h>
#include <math.h>

double line(double m, double x, double c) {
  double y = (m * x) + c;
  return y;
}

int main() {
  double slope = 1.5;
  double intercept = 2.0;
  double x, y;
  int i;
  
  printf("x,y\n");
  for(i=0;i<200;i++) {
	x = (i / 10.0) - 10;
	y = line(slope, x, intercept);
	printf("%lf,%lf\n", x, y);
  }
  
  return 0;
}
