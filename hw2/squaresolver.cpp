#include <iostream>
#include <cmath>
#include "complexbase.hpp"
#include "complexalgo.hpp"
#include <cstdio>

int main(){
    double a, b, c;
    scanf("%f %f %f", &a, &b, &c);
    ComplexBase* a1 =  new ComplexAlgo (a,0);
    ComplexBase* b1 =  new ComplexAlgo (b,0);
    ComplexBase* c1 =  new ComplexAlgo (c,0);
    ComplexBase* b1sqrt = b1->mul(*b1);
    ComplexBase* four =  new ComplexAlgo (4,0);
    ComplexBase* two =  new ComplexAlgo (2,0);
    ComplexBase* ac4 = (four-> mul(*a1))->mul(*c1);
    ComplexBase* D = b1sqrt->sub(*ac4);
    ComplexBase* b1neg = b1->neg();
    ComplexBase*  a2 =  two->mul(*a1);
    ComplexBase* x1 = (b1neg -> add (*D->sqrt()) )->div(*a2);
    ComplexBase* x2 = (b1neg ->sub (*D->sqrt()) )->div(*a2);
    delete(a1);
    delete(b1);
    delete(c1);
    delete(D);
    delete(b1sqrt);
    delete(four);
    delete(two);
    delete(ac4);
    delete(b1neg);
    delete(a2);

    std::cout<<"x1 = {"<<x1->getRe()<<";"<<x1->getIm()<<"}"<< std::endl;
    std::cout<<"x2 = {"<<x1->getRe()<<";"<<x2->getIm()<<"}"<< std::endl;

    delete(x1);
    delete(x2);

}