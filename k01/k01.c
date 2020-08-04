#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(double val,double ave, int n);
extern double var_online(double val, double ave, double square_ave, int n);
 
int main(void)
{
    int n=0;
    double val, ave_new=0, var=0, ave=0, square_ave=0, square_ave_new, ave_bo;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);
        n=n+1;
        ave_new=ave_online(val, ave, n);
        square_ave_new = ave_online(val*val, square_ave, n);
        var=var_online(val, ave, square_ave, n);

        ave = ave_new;
        square_ave = square_ave_new;

    }
    ave_bo=n*var/(n-1);
    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("sample mean: %lf\n sample variance: %lf\n population mean (estimated): %lf\n population variance (estimated): %lf\n", ave, var, ave, ave_bo);

    return 0;


}

double ave_online(double val, double ave, int n)
{
    return ((n-1)*ave+val)/n;
}

double var_online(double val, double ave, double square_ave, int n)
{
    double var=((n-1)*square_ave/n+val*val/n)-pow((n-1)*ave/n+val/n,2);
    return var;
}