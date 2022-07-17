#ifndef EM_HPP 
#define EM_HPP

#include <vector>
#include <memory>
#include "LoadMnist.hpp"
#include <time.h>
#include <iostream>
std::vector<double>binary_data(const image& img);
//EM algorithm model
class model{
public:
    model(int feature_num, int label_num)
        :label_size{label_num}, feature_size{feature_num}{
            srand(time(NULL));
            //initialize the px,pz
            pz.resize(label_num,1 / double(label_num));
            px.resize(label_num,{});
            for(int i = 0;i < label_num;i++){
                px.at(i).reserve(feature_num);
                for(int f = 0;f < feature_num;f++){
                    px.at(i).push_back(0.5*(double) rand() / (RAND_MAX) + 0.25);
                }
            }
        }
    int EM(const std::vector<image>& imgs);
// private:
    using bin_img = std::vector<double>;
    using bernoulli = double;
    using bernoulli_label = std::vector<bernoulli>; 

    // p(img = x | label) = p(f1,f2,f3..fk | label) joint probability of all features.
    double likelihood(int label, const bin_img& x);

    // return all wij(responsibility) , i : idex of N data , j : index of labels.
    std::vector<std::vector<double>> Estep(const std::vector<bin_img>& bin_imgs);

    // use Estep result to update  px,pz
    // return difference between original model parameter.
    double Mstep(std::vector<std::vector<double>>& responsbility, const std::vector<bin_img>& bin_imgs);

    // model parameter :
    std::vector<bernoulli_label>px;//p(x|zj,model) = p(f1,f2,f3,..fn|zj,model)
    std::vector<double>pz;//p(zj|model)
    int label_size, feature_size;
};


#endif
