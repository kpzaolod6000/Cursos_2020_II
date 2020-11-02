#include<iostream>

class A
{
private:
    /* data */
public:
    A(/* args */);
    ~A();
};

A::A(/* args */)
{
}

A::~A()
{
}

int main(){

    A obj;
    A* obj2;
    
    std::cout<<&obj;
    return 0;
}