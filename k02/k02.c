#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define AVE_A 170.8 
#define STDV_A 5.43
#define AVE_B 169.7
#define STDV_B 5.5

#define N 256 // OK
// int N = 256; //NG

extern double p_stdnorm(double z);

int main(void)
{
    double val, syutugen, z, L1 = 1, L2 = 1, ave_a, var_a, ave_b, var_b;
    char fname[FILENAME_MAX];
    char buf[N];
    FILE *fp;

    ave_a = AVE_A; var_a = STDV_A*STDV_A;
    ave_b = AVE_B; var_b = STDV_B*STDV_B; 

    printf("input the filename of sample:");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';
    printf("the filename of sample: %s\n", fname);

    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        fputs("File open error\n", stderr);
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        sscanf(buf, "%lf", &val);
        
        z = (val-ave_a)/sqrt(var_a);
        syutugen = p_stdnorm(z);
        L1 = L1 * syutugen;

        z = (val-ave_b)/sqrt(var_b);
        syutugen = p_stdnorm(z);
        L2 = L2 * syutugen;
    }

    if (fclose(fp) == EOF)
    {
        fputs("file close error\n", stderr);
        exit(EXIT_FAILURE);
    }

    printf("L_A: %f\n", L1);
    printf("L_B: %f\n", L2);

    return EXIT_SUCCESS;
}

double p_stdnorm(double z)
{
    return 1 / sqrt(2 * M_PI) * exp(-z * z / 2);
}