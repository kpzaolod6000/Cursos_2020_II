#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Timer.hpp"

using namespace std;

ofstream myFile;
ifstream fe("prueba.txt");
int* counting_sort(int* array,int* new_array,int max){
    int num_max = array[0], num_min = array[0];
    for (int i = 1; i < max; i++)
    {
        if(array[i] > num_max)
            num_max = array[i];
    }
    int count[10000+1]={0};//depende de los valores del arreglo
    for (int j=0; j < max ;j++ )
    {  
        count[array[j]]++;
    }


    //for (int i=0; i < 10000 ;i++ )// aca va 10000 y borrar el for para hallar el maximo

    for (int i=0; i < num_max ;i++ )//fijar el rango 
    {  
        count[i+1] = count[i] + count[i+1];
    }
/*
    for (int i = 0; i < num_max; i++)
    {
        if(i == 46)
            cout<<endl<<count[i]<<endl;
        cout<<count[i]<<" ";
    }*/
    cout<<endl;
    for (int i = 0; i < max; i++)
    {
        new_array[count[array[i]]-1] = array[i];
        count[array[i]]--;
    }
    return new_array;

}

void print(int* new_array,int max){
     for(int i=0;i<max;i++){
        cout<<new_array[i]<<" ";    
    }
}

void read(int* array,int max){
   
    char cadena[128];

    int i = 0;
    while(i<max) {
        fe >> cadena;
        array[i] = atoi(cadena);
        //cout<<array[i] <<" ";
        i++;
    }
}
int main(){

    Timer timer;
    myFile.open("test.csv");

    char cadena[128];
    int max;

    fe >> cadena;
    max = atoi(cadena);
    int aux[max];
    int array[max];
    /* int num;
    int array[max];
    for (int i = 0; i < max; i++)
    {
        cin>>num;
        array[i] = num;
        cout<<array[i] <<" ";
    } */
    read(array,max);
    fe.close();
    print(array,max);
    cout<<endl;
    
    //Counting sort
    timer.start();
    int* new_array = counting_sort(array,aux,max);
    timer.stop();

    //print  
    cout<<endl;
    print(new_array,max);
    

    // to excel
    cout << "Milisegundos: " << timer.elapsedMilliseconds() <<endl;
    myFile << max <<";"<<timer.elapsedMilliseconds()<<endl;
 
    cout<<endl;
    return 0;

}