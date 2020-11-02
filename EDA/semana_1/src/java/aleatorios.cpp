#include<iostream>
#include<random>
#include<ctime>
//#define max 5000

using namespace std;

void aleatorio(int*array,int max){

    srand(static_cast<unsigned int>(time(0)));
    int ran;
    for (int i = 0; i < max; i++)
    {
        array[i] = rand()%10000;
    }

}

int main(){

    int max;
    cin>>max;
    int array[max];
    aleatorio(array,max);
   
    cout<<max<<" ";

    for (int i = 0; i < max; i++)
    {
        cout<< array[i]<<" ";

    }
    return 0;
}