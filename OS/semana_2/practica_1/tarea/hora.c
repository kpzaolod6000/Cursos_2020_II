/* #include <stdio.h>
#include <time.h>
 */
/* int main(int argc,char* argv[]) {

        /* time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        //strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
        strftime(output,128,"%H:%M:%S",tlocal);
        printf("%s\n",output);



        time_t iTotal_seconds = time(0);
        struct tm *ptm = localtime((const time_t *) & iTotal_seconds);

        int iHour = ptm->tm_hour;;
        int iMinute = ptm->tm_min;
        int iSecond = ptm->tm_sec;
        double i = ptm->__tm_gmtoff;

          printf("hora: %d: %d: %d  %d ",iHour,iMinute,iSecond,i);
        return 0;
} */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#include<string.h>


#include <sys/time.h>

long long current_timestamp() {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
  // printf("milliseconds: %lldn", milliseconds);
  return milliseconds;
}


////////////////////////////tiempo 
          /*time_t iTotal_seconds = time(0);
            struct tm *ptm = localtime((const time_t *) & iTotal_seconds);
            char tiempo[8];
            strftime(tiempo, 100, "%H:%M:%S", ptm);
            printf("[%s] ",tiempo);*/

 /*  time_t t;
  struct tm *tm;
  char fechayhora[100];
  char *meses[12]={"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

  t=time(NULL);
  tm=localtime(&t);
  printf ("Hoy es: %02d/%s/%d\n", tm->tm_mday, meses[tm->tm_mon], 1900+tm->tm_year);
 */
  //printf("%llu",current_timestamp());

int main(){
  // Tiempo actual
  int i = 0;
/*   char* sT;
  printf("%2.3f seconds\n", (double)(clock()) / CLOCKS_PER_SEC);
  clock_t st;
  double duration = (double)(clock()) / CLOCKS_PER_SEC; 

  char* sT;

  strftime(sT,100,"%H:%M:%MS",duration);


  clock_t st;
  QueryPerformanceCounter(st);
  time_t ltime;
  GetSystemTime( &ltime );
  printf( "Inicia en %s\n", ctime( &ltime ) ); */



  char fmt[16], buf[16];
  struct timeval tv;
  struct tm tm;

  gettimeofday(&tv, NULL);
  tm = *localtime(&tv.tv_sec);
  strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", &tm);
  snprintf(buf, sizeof buf, fmt, tv.tv_usec);
  printf("%i\n",tm.tm_sec);
  printf("%li\n",tv.tv_usec);

  //printf("%s",s);
  printf("%s\n",fmt);
  printf("%s\n",buf);
  /* while (i<5)
  {    
    time_t iTotal_seconds = time(0);
    struct tm *ptm = localtime((const time_t *) & iTotal_seconds);
    char tiempo[8];
    int iHour = ptm->tm_hour;;
    int iMinute = ptm->tm_min;
    int iSecond = ptm->tm_sec;
    strftime(tiempo, 100, "%H:%M:%S", ptm);

    //printf("hora: %d: %d: %d \n",iHour,iMinute,iSecond);
    printf("hora: %s\n",tiempo);
    //printf("%lu",sizeof(tiempo)/sizeof(tiempo[0]));

    int tam = sizeof(tiempo)/sizeof(tiempo[0]);
    //printf("%d",tam-2);
    char* a[3];
    int j =0;
    char m = tiempo[0];
    printf("%d",m-'0');
     
    for(int k=(tam-2); k<tam ; k++){
      if(tiempo[k] != 0 && k == (tam-2)){
        j = (tiempo[k]-'0')*10;}
      else{
        j = j+(tiempo[k]-'0');}
    }
    printf("\n%i\n",j);
    sleep(1);
    i++;
  }  
  return 0; */
}
