hillclimber
===========

Generic hill climber for multivariate functions


How to run?

Compile : ```g++ hillclimber.cpp -o optimize```

This program requires an input file in the following format:

```
  alphaInit
  2
  10 10
  10 10
```
where first line is the number of variables, 
second line contain the seeds for the variables
and the third line is the initial stepsize parameter.

```
  ./optimize alphaInit
  
  Best Score : -9.99879e-05
  Best Coordinates : 0.00799894 -0.0060004 
```
Displays the best score achieved by the climber and the coordinates at that peak.


PS: Modify the getScore() function according to your needs.
