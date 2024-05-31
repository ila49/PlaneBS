// размер стека увеличен до 1'073'741'824 байт (1 ГБ)
// 1 073 741 824

#include <ctime>
#include <stdio.h>
#include <corecrt_math.h>

int main()
{
    std::clock_t start;
    double duration;
    const double PIx4 = 4.0 * 3.141592653589793;
    const unsigned int arraySize = 176'326 * 14 * 14; // 102400; // 51200;
    unsigned int arraySize1 = arraySize - 1;
    double Vx[arraySize] = { 0.0 };
    double Vy[arraySize] = { 0.0 };
    double Vz[arraySize] = { 0.0 };
    double Ro2 = 0.01;
    double Roo2 = 0.001;

    start = std::clock();

    for (unsigned int i = 0; i <= arraySize1; i++)
    {
        double X1 = 0.001 * i;
        double Y1 = 0.0;
        double Z1 = 0.0;
        double X2 = 1.0 + 0.002 * i;
        double Y2 = 0.0;
        double Z2 = 0.0;
        double X0 = 0.5;
        double Y0 = 0.003 * i;
        double Z0 = 0.5 + 0.004 * i;

        double rDx21 = X2 - X1;
        double rDy21 = Y2 - Y1;
        double rDz21 = Z2 - Z1;
        double rDx01 = X0 - X1;
        double rDy01 = Y0 - Y1;
        double rDz01 = Z0 - Z1;
        double rDx02 = X0 - X2;
        double rDy02 = Y0 - Y2;
        double rDz02 = Z0 - Z2;
        double rAx = rDz01 * rDy21 - rDy01 * rDz21;
        double rAy = rDx01 * rDz21 - rDz01 * rDx21;
        double rAz = rDy01 * rDx21 - rDx01 * rDy21;
        double rH2 = rAx * rAx + rAy * rAy + rAz * rAz;
        double rD2 = rH2 / (rDx21 * rDx21 + rDy21 * rDy21 + rDz21 * rDz21);
        double rA1 = rDx01 * rDx21 + rDy01 * rDy21 + rDz01 * rDz21;
        double rA2 = -(rDx02 * rDx21 + rDy02 * rDy21 + rDz02 * rDz21);
        double rR1 = 0.0;
        double rR2 = 0.0;
        double rC = 0.0;
        if (rD2 > Roo2)
        {
            if (rD2 > Ro2 && rH2 != 0.0)
            {
                rR1 = sqrt(rDx01 * rDx01 + rDy01 * rDy01 + rDz01 * rDz01);
                rR2 = sqrt(rDx02 * rDx02 + rDy02 * rDy02 + rDz02 * rDz02);
                rC = (rA1 / rR1 + rA2 / rR2) / (rH2 * PIx4);
            }
            else if (Ro2 != 0.0 && rD2 <= Roo2)
            {
                rR1 = sqrt(rA1 * rA1 + rH2);
                rR2 = sqrt(rA2 * rA2 + rH2);
                rC = (rA1 / rR1 + rA2 / rR2) / (Ro2 * PIx4);
            }
        }
        Vx[i] = rC * rAx;
        Vy[i] = rC * rAy;
        Vz[i] = rC * rAz;
    }
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    printf("Vx[0] = %.12f\n", Vx[0]);
    printf("Vy[0] = %.12f\n", Vy[0]);
    printf("Vz[0] = %.12f\n", Vz[0]);
    printf("Vx[176326] = %.12f\n", Vx[176326]);
    printf("Vy[176326] = %.12f\n", Vy[176326]);
    printf("Vz[176326] = %.12f\n", Vz[176326]);
    printf("Vx[.] = %.12f\n", Vx[arraySize1]);
    printf("Vy[.] = %.12f\n", Vy[arraySize1]);
    printf("Vz[.] = %.12f\n", Vz[arraySize1]);
    printf("T = %.12f\n", duration);
    printf("Start = %d\n", start);
    printf("Stop  = %d\n", std::clock());

}
