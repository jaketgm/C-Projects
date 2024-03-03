#define BOUNDARY 20

/************************************************************************************
 * Method: stdNormalFunc: This method defines the standard normal function, note
 * in the standard normal function the mean is equal to zero, and the standard
 * deviation is 1, and thus we get a nice simplification of the standard 
 * distribution from statistics.
 *
 * Input: double z.
 *
 * Output: The standard normal function evaluated at an input z.
 *
************************************************************************************/
double stdNormalFunc(double z) 
{
    double result = exp(-pow(z, 2) / 2) / sqrt(2 * M_PI);
    return result;
}

/************************************************************************************
 * Method: riemannApprox: This method stimates the area under the standard normal 
 * distribution curve from -BOUNDARY to a specified value a using the Riemann sum 
 * method. It iterates from -BOUNDARY to a, incrementing by a step size h, and for
 *  each step, it calculates the average of the standard normal distribution 
 * function's values at the current and next steps, multiplied by h, effectively 
 * estimating the area of a trapezoid. 
 *
 * Input: double h, double a.
 *
 * Output: Approximation.
 *
************************************************************************************/
double riemannApprox(double h, double a) 
{
    double areaUnderCurve = 0.0;
    double i;
    for (i = -BOUNDARY; i < a; i += h) 
    {
        areaUnderCurve += (stdNormalFunc(i) + stdNormalFunc(i + h)) / 2 * h;
    }
    return areaUnderCurve;
}