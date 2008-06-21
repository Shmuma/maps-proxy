#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double deg2rad (double d)
{
    return d * M_PI / 180.0;
}


void geod2merc (double lat, double lon, double* x, double* y)
{
    double Rn = 6378137.0;
    double e = 0.0818191908426;
    double esinLat = e * sin(lat);
    double tan_temp = tan(M_PI_4 + lat / 2.0);
    double pow_temp = pow (tan (M_PI_4 + asin (esinLat) / 2), e);
    double U = tan_temp / pow_temp;
    
    *x = Rn * lon;
    *y = Rn * log (U);
}




int main ()
{
    double lat = 55.75438;
    double lon = 37.80950;

    double x, y, tx, ty;
    
    geod2merc (deg2rad (lat), deg2rad (lon), &x, &y);
    
    tx = (x + 20037508.342789) * 53.5865938;
    ty = (20037508.342789 - y) * 53.5865938;

    printf ("%f, %f\n", tx, ty);

    printf ("http://base03.maps.yandex.net/tiles/2000/?layer=1&x=%lld&y=%lld&scale=6\n", (unsigned long long)tx, (unsigned long long)ty);

    return 0;
}
