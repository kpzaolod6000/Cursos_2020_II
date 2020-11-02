#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include<random>
//#include<ctime>


/*  void time_measure_
example ()
{
    hrtime_t prev_time_value, time_value;
    hrtime_t time_diff;


    prev_time_value = gethrtime ();

    

    
    time_value = gethrtime ();


    time_diff = time_value - prev_time_value;
}
 */
int time_partition(int ini,int fnl,char HourC[],char HourP[]){
    char timeC[10];
    char timePh[10];
    //printf("%s\n",horal);
    //printf("%lu\n",strlen(horal));
    int indc = 0;
    int indph = 0;
    
    for(int h = ini ;h < fnl ; h++){
        timeC[indc++] = HourC[h];
        timePh[indph++] = HourP[h];
    }
    int tmC =atoi(timeC);
    int tmP =atoi(timePh);
    printf("%d\n",tmC);
    printf("%d\n",tmP);
    return abs(tmC-tmP);
}
char* time_diff(char diff[],char horal[] ,char horaf[] ,int tam){
    strcpy(diff,"");
    for (int j = 0 ,i = 0; i < 4; i++,j+=3)
    {
        if(i == 3){
            //printf("%d\n",time_diff(j,j+6,horal,horaf));
            char transs[10];
            sprintf(transs,"%d",time_partition(j,j+6,horal,horaf) );
            strcat(diff,".");
            strcat(diff,transs);
        }
        else
        {
            //printf("%d\n",time_diff(j,j+2,horal,horaf));
            if(time_partition(j,j+2,horal,horaf) != 0){
                if(strlen(diff) != 0){
                    char trans[10];
                    sprintf(trans,"%d",time_partition(j,j+2,horal,horaf) );
                    strcat(diff,":");
                    strcat(diff,trans);
                }else
                {
                    char trans[10];
                    sprintf(trans,"%d",time_partition(j,j+2,horal,horaf) );
                    strcat(diff,trans);
                }
                
            }
        }
    }
}

int main()
{
    char horal[] = "12:36:00.482042";
    char horaf[] = "12:34:58.705927";
    int tam = strlen(horal);
    char diff[16];
    //time_diff(diff,horal,horaf,tam);
    //printf("%s",diff);

    int i= 0;
    while(i<5){
        srand(time(NULL));
        
        int numero = rand() % 5; 
        printf("%d",numero);
        i++;
    }
    
   /*  struct tm horaff = {0};
    struct timeval tv = {0};
    horaff.tm_hour = atoi(&horal[0]);
    horaff.tm_min = atoi(&horal[3]);
    horaff.tm_sec = atoi(&horal[6]);
    tv.tv_usec = atoi(&horal[10]);
    time_t t = mktime(&horaff); 

    struct tm vv = {0};
    struct timeval ccc = {0};
    vv.tm_hour = atoi(&horaf[0]);
    vv.tm_min = atoi(&horaf[3]);
    vv.tm_sec = atoi(&horaf[6]);
    ccc.tv_usec = atoi(&horaf[10]);
    time_t h = mktime(&vv); 
    printf("%f\n",difftime(t,h)); */

    
    //printf("%s\n",timeC);
    //printf("%s\n",timePh);
    return 0 ;
}