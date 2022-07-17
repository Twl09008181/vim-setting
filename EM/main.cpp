#include "EM.hpp"
#include "LoadMnist.hpp"


#include <iostream>

#include <time.h>
int main(){

    dataset training = load_mnist("train-images.idx3-ubyte","train-labels.idx1-ubyte"); 


    clock_t start,end;
    start = clock();
    model bernoulli_EM(784,10);

    int iteration = bernoulli_EM.EM(training.first);

    end = clock();
    std::cout<<"EM done, total iterations:"<<iteration<<" spend: "<<(end-start)/CLOCKS_PER_SEC<<" seconds \n";



    return 0;
}
