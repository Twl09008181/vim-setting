#include "EM.hpp"
#include <iostream>
#include <cmath>
#include <omp.h>

//return vector consist of 0 or 1.
std::vector<double>binary_data(const image& img){
    std::vector<double>bin_data(784,0);
    for(int f = 0;f < 784; f++){
        bin_data.at(f) = getFeature(img, f) > 128 ? 1 : 0;
    }    
    return bin_data;
}
double model::likelihood(int label, const bin_img& x){
    double prob = 1;
    for(int f = 0; f < feature_size; f++){
        double theta = std::max(px.at(label).at(f),0.01); // get p(f = f|z = label) = theta (bernoulli distribution).
        theta = std::min(0.99,theta);
        prob *= (theta * x.at(f) + (1 - theta) * (1 - x.at(f)) ); // p(xi|theta) = theta * xi + (1-theta)*(1-xi) (bernoulli).
    }
    return prob;
}

std::vector<std::vector<double>> model::Estep(const std::vector<bin_img>& bin_imgs){
    // int N = bin_imgs.size();
    int N = 60000;
    //N x label
    //each data i has wi0,wi1,...,wi9
    std::vector<std::vector<double>>responsibility(label_size, std::vector<double>(N, 0));//posterior p(zj|xi,model)
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        double normalization = 0;
        for(int zj = 0; zj < label_size; zj++){
            // p(xi,zj|old model) = p(zj|old model) * p(xi|zj,old model)
            responsibility.at(zj).at(i) = pz.at(zj) * likelihood(zj, bin_imgs.at(i));
            // marginalize all p(xi,zj|old model) wrt z = p(xi|old model)
            normalization += responsibility.at(zj).at(i); 
        }
        // posterior = P(z|xi,model old) = p(xi,zj|model old) / normalization
        for(int z = 0; z < label_size; z++) responsibility.at(z).at(i) /= normalization; 
    }
    return responsibility;
}

double model::Mstep(std::vector<std::vector<double>>& responsbility, const std::vector<bin_img>& bin_imgs){

    double diff = 0;
    // int N = bin_imgs.size();
    int N = 60000;
    
    //find pz_MLE : P(z|model)
    #pragma omp parallel for
    for(int zj = 0; zj < label_size; zj++){
        double responsibility_zj = 0;//sum of responsibility wrt zj
        for(int i = 0;i < N; i++)
            responsibility_zj += responsbility.at(zj).at(i);
        // now we get both sum of responsibility_zj = pz_MLE * N and pz_MLE.
        responsibility_zj /= N;// pz_MLE = sum of wij over all data i=0~N-1 / N.
        diff += std::abs(pz.at(zj) - responsibility_zj);
        pz.at(zj) = responsibility_zj;
    }

    //update P(x|zj,model)
    #pragma omp parallel for
    for(int zj = 0; zj < label_size; zj++){
        double responsibility_zj = pz.at(zj) * N;//sum of responsibility wrt zj = get sum of wij for all i.

        std::vector<bernoulli>px_temp(feature_size,0);//for each zj

        for(int i = 0; i < N; i++)
            for(int f = 0;f < feature_size; f++)
                px_temp.at(f) += bin_imgs.at(i).at(f) * responsbility.at(zj).at(i);//caculate sum of wij * xi for all i.
        
        for(int f = 0;f < feature_size; f++){
            px_temp.at(f) /= responsibility_zj;//normalize by sum of wij.
            diff += std::abs(px.at(zj).at(f) - px_temp.at(f));
            px.at(zj).at(f) = px_temp.at(f);
        }
    }
    return diff;
}

int model::EM(const std::vector<image>&imgs){

    std::vector<bin_img>bin_imgs;

    // convert to binary images.
    for(const auto& img:imgs)
        bin_imgs.push_back(binary_data(img));
    
    // do E-M (Expectation-Maximization)
    double diff;
    int iteration = 0;
    do{
        auto wijs = Estep(bin_imgs);
        diff = Mstep(wijs,bin_imgs);
        for(int z = 0;z < label_size;z++){
            std::cout<<"label:"<<z<<"\n";
            for(int f = 0;f < feature_size;f++){
                if(f%28==0)std::cout<<"\n";
                if(px.at(z).at(f)>0.5){
                    std::cout<<"1";
                }else{
                    std::cout<<"0";
                }
            }
            std::cout<<"\n";
        }
        std::cout<<"diff="<<diff<<"\n";
        iteration++;
    }while(diff > 1);
    return iteration;// return iteration
}

