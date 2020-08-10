#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct DATA{
    int ID; 
    int gender; 
    double height;
};

int main(void)
{
    int i,n;
    double val;
    int id, ID;
    char fname[FILENAME_MAX];
    char fname2[FILENAME_MAX];
    char buf[256];
    char buf2[256];
    FILE*fp, *fp2;
    int male, female, unknown, whole;
    int gender;
    struct DATA date[14];

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

i=0;
fgets(buf, sizeof(buf), fp);
while(fgets(buf, sizeof(buf), fp)!=NULL)
{
    sscanf(buf, "%d, %lf", &gender, &val);


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
    i++;

}

whole=male+female+unknown;

i=0;
while(fgets(buf2, sizeof(buf2), fp2)!=NULL)
{
    sscanf(buf2, "%d", &ID);
    date[i].ID=ID;
    i++;

}


printf("   ID    | g | height \n");
for(i=0; i<whole; i++){
    printf("%8d | %d | %6.2lf\n", date[i].ID, date[i].gender, date[i].height );
}
printf("====");



printf("which ID's date do you want? :");
scanf("%d", &id);
printf("---\n");

for(i=0; i<whole; i++)
{
    if(date[i].ID==id)
    {
        printf("ID:%d\n", date[i].ID);
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

return 0;

}