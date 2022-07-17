#ifndef LOADMNIST_HPP
#define LOADMNIST_HPP

#include <vector>
#include <string>
#include <utility>
using label = unsigned;
//using pixel = unsigned;
using pixel = double;



using image = std::vector<std::vector<pixel>>;
pixel getFeature(const image&img,std::size_t idx);//need be implemented!
using dataset = std::pair<std::vector<image>,std::vector<label>>;
dataset load_mnist(std::string ImageFile,std::string LabelFile);
void showDataSet(const dataset&);
#endif
