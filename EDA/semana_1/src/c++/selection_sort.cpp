#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Timer.hpp"
using namespace std;

ofstream myFile;
ifstream fe("prueba.txt");
void selection_sort(int* array,int max){
    int primer;
    int temp;
    for(int i = 0; i < max-1; i++)
    {
        primer = i;
        for (int j = i+1; j < max; j++)
        {
            if(array[primer] > array[j])
                primer = j;
        }
        temp = array[primer];
        array[primer] = array[i];
        array[i] = temp;
    }
}

void print(int* array,int max){
    for(int i=0;i<max;i++){
        cout<<array[i]<<" ";
        //myFile << array[i] <<endl;
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
    int array[max];

    read(array,max);
    fe.close();

 
    cout<<endl;

    //Selection Sort
    timer.start();
    selection_sort(array,max);
    timer.stop();
    
    //print
    print(array,max);


    cout<<endl;
    // to excel
    cout << "Milisegundos: " << timer.elapsedMilliseconds() <<endl;
    myFile << max <<";"<<timer.elapsedMilliseconds()<<endl;
    
    cout<<endl;
    return 0;

}