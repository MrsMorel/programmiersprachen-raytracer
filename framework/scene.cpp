//
// Created by annetelle on 10.07.22.
//
#include "scene.hpp"
Scene sdfParser(std::string const& file_path){
    //std::string file_path = "./test.sdf";
    std::ifstream  sdf_filestream(file_path, std::ios::in);
    /* if (sdf_filestream.is_open()){
         std::cout << "could not open file" << std::endl;
         exit(-1);
     }*/
    std::string line_buffer;
    Scene sc;
    while (std::getline(sdf_filestream,line_buffer)){
        std::istringstream iss(line_buffer);
        std::string keyword = " ";
        iss >> keyword;
        if ("define" == keyword){
            iss >> keyword;
            if ("material" == keyword){
                std::string name;
                float ka_r, ka_g, ka_b;
                float kd_r, kd_g, kd_b;
                float ks_r, ks_g, ks_b;
                float m;
                iss >> name;
                iss >> ka_r >> ka_g >> ka_b;
                iss >> kd_r >> kd_g >> kd_b;
                iss >> ks_r >> ks_g >> ks_b;
                iss >> m;
                Material material{name, {ka_r,ka_g,ka_b},{kd_r,kd_g,kd_b},{ks_r,ks_g,ks_b},m};
                /*float ka[3] = {0.0,0.0,0.0};
                for (unsigned int channel_idx = 0; channel_idx < 3 ; ++channel_idx) {
                    iss >> ka[channel_idx];
                }*/
                sc.material_map.insert({name, std::make_shared<Material>(material)});
                std::cout << "successfully created material" << material << std::endl;
            }
        }
    }
    sdf_filestream.close();
    return sc;
}