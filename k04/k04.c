#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

extern void get_bound(int male, int whole, double* lower, double* upper);
extern int choose(int n, int r);

struct D(double ID; int gender; double height;);

int main(void)
{
    int i,n;
    double val, id, ID;
    char fname[FILENAME_MAX];
    char fname2[FILENAME_MAX];
    char buf[256];
    char buf2[256];
    FILE*fp, *fp2;
    int male, female, unknown, whole;
    int gender;
    double bound, bound;
    struct D date[14];

    i=-1;
    n=0;

    printf("input the filename of sample height:");
    fgets(fname, sizeof(fname),stdin);
    fname[strlen(fname)-1]='\0';
    printf("the filename of sample: %s\n", fname);

    printf("input the filename of sample ID:");
    fgets(fname2, sizeof(fname2), stdin);
    fname2[strlen(fname2)-1]='\0';
    printf("the filename of sample: %s\n", fname2);

    fp=fopen(fname, "r");
    
    if(fp==NULL)
    {
        fputs("file open error\n", stderr);
        exit(EXIT_FAILURE);
    }

    fp2=fopen(fname2, "r");
    
    if(fp2==NULL)
    {
        fputs("file open error\n", stderr);
        exit(EXIT_FAILURE);
    }

male=female=unknown=0;

while(fgets(buf, sizeof(buf), fp)!=NULL)
{
    sscanf(buf, "%d, %lf", &gender, &val);

    i++;

    date[i].gender=gender;
    date[i].height=val;

    if(gender==1)
    {
        male++;
    }
    else if(gender==2)
    {
        female++;
    }
    else
    {
        unknown++;
    }
}

whole=male+female+unknown;

i=0;

printf("which ID's date do you want? :");
scanf("%lf", &id);
printf("---\n");

while(fgets(buf2, sizeof(buf2), fp2)!=NULL)
{
    scanf(buf, "%lf", &ID);
    i+++
    date[i].ID=ID;

}

for(i=1, i<=whole; i++)
{
    if(date[i].ID==id)
    {
    　　printf("ID:%.0lf\n", date[i].ID);
        printf("gender:");
        if(date[i].gender==1){printf("male\n");}
        else{printf("female\n");}
        printf("height:%.1lf\n", date[i].height);
        n=1;
    }
}

if(n==0)
{
    printf("no date\n");
}

printf("---\n");

printf("=========================\n");
printf("number of male sample : %d\n", male);
printf("number of female sample : %d\n", female);
printf("mele ratio : %lf\n", (double)male/whole);

if(fclose(fp)==EOF)
{
    fputs("file close error\n", stderr);
    exit(EXIT_FAILURE);
}

if(fclose(fp2)==EOF)
{
    fputs("file close error\n", stderr);
    exit(EXIT_FAILURE);
}

get_bound(male, whole, &bound, &bound);

printf("population male ratio : %lf--%lf\n", bound, bound);
printf("=============================\n");

return 0;

}