#include <iostream>

using namespace std;

#define MX 1000

int main() {
    cout<<2<<endl;
    for(int i=10000; i<=20000; i+=10000) {
            cout<<i<<endl;
            for (int k = 0; k < 2; k++)
            {
                for( int j=0; j<i; j++) {
                        cout << rand()%MX << ' ';
                }
                cout<< endl;
            }         
    }
    return 0;
}