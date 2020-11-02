#include <stdio.h>
#include <stdlib.h>
struct Persona
{ 
    int len; 
    char nombre[10000];
};


int main(){
    int a;
    char b;
    char l[10];
    printf("%lu %lu %lu\n",sizeof(a),sizeof(b),sizeof(l));
    printf("%lu\n",sizeof(struct Persona));

}