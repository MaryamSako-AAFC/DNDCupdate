#include "stdafx.h"
#include "dndc71.h"
#include "SitePara.h"
#include "dndc_main.h"

int JulianDay(int month, int day)
{
    int i, JDay;
	int   Mday[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (month<1 ||month>12 || day<1 ||day>31) return -1;

    JDay = 0;
    for (i = 1; i< month; i++)
	{
        JDay += Mday[i];
	}
    JDay += day;
	return JDay;
}

float day_par(int Jday, float LATITUDE, float* Day_Hrs)
{
	/*
	   daylength and horizontal potential insolation for day
		  from Swift (1976) Water Resour Res 12:108 and Sellers (1965) Physical Climatology
	   Jday     day of the year
	   Lat      latitude, radians
	   I0       potential insolation (horizontal) J/m2
	   DECL     declination of the sun, radians
	   R        radius vector of the sun, dimensionless
	   h        half daylength
	   isc      solar constant, W/m2, Lean 1991 Rev. Geophysics 29:
	   Half daylength and declination equations from:
		   Swift, L.W.Jr.(1976). Algorithm for solar radiation on mountain
		   slopes. Water Resources Research, 12(1) 118-112.
	*/
	float pi, isc, lat, r, Z, decl, z2, H, TA, AC, acos, psolrad, solrad;
	float DayPAR, PARc, cloud;

	pi = 3.1416;
	isc = 1367.0;     //solar max Lean 1991 Rev. Geophysics 29
	cloud = 0.75;//.48;

	lat = LATITUDE * (2.0 * 3.1416) / 360.0; //latitude in radians

	r = 1.0 - .0167 * (float)cos(.0172 * (Jday - 3)); //radius vector of the sun

	Z = .398 * (float)sin(4.869 + .0172 * Jday + .0334 * (float)sin(6.224 + .0172 * Jday)); //temporary variable

	if (fabs(Z) < .7)
	   decl = (float)atan(Z / ((float)powf((1 - Z * Z), 0.5)));
	else
	   decl = pi / 2 - (float)atan((float)powf((1 - Z * Z), 0.5) / Z);

	if (fabs(lat) >= pi / 2) lat = (pi / 2 - .01);

	z2 = -(float)tan(decl) * (float)tan(lat); //temporary variable

	if (z2 >= 1)            //sun stays below horizon
	  H = 0;
	else if (z2 <= -1)      //sun stays above the horizon
	  H = pi;
	else
	{
	  TA = fabs(z2);
	  if (TA < .7) AC = 1.571 - (float)atan(TA / (float)powf((1 - TA * TA), 0.5));
	  else	AC = (float)atan((float)powf((1 - TA * TA), 0.5) / TA);

	  if (z2 < 0) acos = 3.1416 - AC;
	  else acos = AC;

	  H = acos;
	}

	*Day_Hrs = 2 * (H * 24) / (2 * 3.1416); //Length of day (hr)

	psolrad = isc * (86400 / (3.1416 * r*r)) *
		  (H * (float)sin(lat) * (float)sin(decl) +
		  (float)cos(lat) * (float)cos(decl) * (float)sin(H));
		  //potential insolation, J/m2/day

	solrad = psolrad * cloud / 1000000.0; // million J/m2/day

	DayPAR = solrad * 2.05; //PAR, moles/m2/day

	PARc = DayPAR / (*Day_Hrs * .0036); //daily instantaneous PAR, u moles/m2/second

	return (solrad);

}