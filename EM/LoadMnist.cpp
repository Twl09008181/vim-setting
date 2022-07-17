#include <iostream>
#include <fstream>
#include "LoadMnist.hpp"

int reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}


pixel getFeature(const image&img,std::size_t idx){
    int c = img.at(0).size();
    int row = idx / c;
    int col = idx % c;
    return img.at(row).at(col);
}
std::vector<image> readImage(std::string ImageFile){
    std::ifstream Image (ImageFile,std::ios::binary);
    std::vector<image>images;
    if (Image.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        Image.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number= reverseInt(magic_number);
        Image.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);
        Image.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);
        Image.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);

        images.resize(number_of_images);
        for(int i=0;i<number_of_images;++i){
            images.at(i).resize(n_rows);
            for(int r=0;r<n_rows;++r){
                images.at(i).at(r).resize(n_cols);
                for(int c=0;c<n_cols;++c){
                    unsigned char temp=0;
                    Image.read((char*)&temp,sizeof(temp));
                    images.at(i).at(r).at(c) = pixel(temp);
                }
            }
        }
    }
    else{
        std::cout<<"can't open"<< ImageFile <<"\n";
        exit(1);
    }
    Image.close();
    return images;
}
std::vector<label> readLabel(std::string LabelFile){
    std::ifstream Label (LabelFile,std::ios::binary);
    std::vector<label>labels;
    if(Label.is_open()){
        int magic_number=0;
        int number_of_labels=0;
        Label.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number= reverseInt(magic_number);
        Label.read((char*)&number_of_labels,sizeof(number_of_labels));
        number_of_labels= reverseInt(number_of_labels);
        labels.resize(number_of_labels);
        for(int i = 0;i<number_of_labels;i++){
            unsigned char l=0;
            Label.read((char*)&l,sizeof(l));
            labels.at(i) = label(l);
        }
    }else{
        std::cout<<"can't open"<<LabelFile<<"\n";exit(1);
    }
    return labels;
}


dataset load_mnist(std::string ImageFile,std::string LabelFile){
    return dataset{readImage(ImageFile),readLabel(LabelFile)};
}


void showDataSet(const dataset&ds){
    const auto &X = ds.first;
    const auto &Y = ds.second;
    for(int i = 0;i < X.size();i++){
        for(auto &row:X.at(i)){
            for(auto &col:row){
                if(col > 128){
                    std::cout<<"1 ";
                }
                else{
                    std::cout<<"0 ";
                }     
           }
           std::cout<<"\n";
        }
        std::cout<<"label:"<<Y.at(i)<<"\n";
    }
}
