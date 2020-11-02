#include <iostream>
using namespace std;
#define max 10

int main(){

    int num;
    int array[max];
    for (int i = 0; i < max; i++)
    {
        cin>>num;
        array[i] = num;
        cout<<array[i] <<" ";
    }
    cout<<endl;

    for(int i=0;i<max-1;i++){
        int temp;    
        for(int j=0;j<max-i-1;j++){
            
            if(array[j] > array[j+1]){
                //cout<<"entro";
                temp = array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }

    }

    for(int i=0;i<max;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    return 0;

}