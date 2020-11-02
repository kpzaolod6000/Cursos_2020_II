#include <iostream>
#include <fstream>


using namespace std;


int main(){

    char cadena[128];
    ifstream fe("prueba.txt");
    int max;
    fe >> cadena;
    max = atoi(cadena);
    cout << max+1 << endl;
    while(!fe.eof()) {
        fe >> cadena;
        cout << cadena << endl;
    }
    fe.close();

    return 0;
}

/*LECTURA CON ENTRA ./main < prueba.txt 
int num, max;
    cin>>max;
    int array[max];
    Timer timer;
    for (int i = 0; i < max; i++)
    {
        cin>>num;
        array[i] = num;
        cout<<array[i] <<" ";
    } */