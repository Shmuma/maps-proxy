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


#define MAX_ZOOM (20)
#define TILE_SIZE_P2 (8)
#define unit2ztile(unit, ZOOM) ((unit) >> (TILE_SIZE_P2 + (ZOOM)))


int main ()
{
    double lat = 55.75698;
    double lon = 37.62435;

    double x, y;
    unsigned int tx, ty;
    unsigned int xx, yy, zoom, sz;
    
    sz = 4;

    geod2merc (deg2rad (lat), deg2rad (lon), &x, &y);
    
    tx = (x + 20037508.342789) * 53.5865938;
    ty = (20037508.342789 - y) * 53.5865938;

    printf ("%u, %u\n", tx, ty);

    for (zoom = sz; zoom < sz+4; zoom++) {
        xx = unit2ztile (tx, zoom);
        yy = unit2ztile (ty, zoom);

        printf ("%u, %u, %u\n", xx, yy, zoom);
        printf ("http://vec.maps.yandex.net/tiles?l=map&v=1.0.0&x=%d&y=%d&z=%d\n", xx, yy, MAX_ZOOM + 3 - zoom);
    }

    return 0;
}
