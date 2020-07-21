#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int n, double val, double ave2);
extern double var_online(int n, double val, double ave3, double save);

int main(void)
{
    int n=0;
    double val, ave=0, save=0, ave3=0, pm, samplemean, samplevariance, populationmean, populationvariance;
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
        n++;
        ave=ave_online(n, val, ave);
        samplevariance=var_online(n, val, save, ave3);
        save=((n-1)*save+val*val)/n;
        ave3=((n-1)*ave3+val)/n;
        samplemean=ave;
     }

populationvariance=n*samplevariance/(n-1);
populationmean=samplemean;
pm=pow(populationvariance/n,0.5);

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

printf("sample mean=%1f\n", samplemean);
printf("sample variance=%1f\n", samplevariance);
printf("population mean=%1f, pm=%1f\n", populationmean, pm);
printf("population variance=%1f\n", populationvariance);
    
    return 0;


}

double ave_online(int n, double val, double ave2)
{
    ave2=((n-1)*ave2+val)/n;
    return ave2;
}

double var_online(int n, double val, double save, double ave3)
{
    return((n-1)*save+val)/n-pow((((n-1)*ave3+val)/n),2);
}
