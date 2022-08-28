//
// Created by annetelle on 10.07.22.
//
#include "sphere.hpp"
#include "scene.hpp"
#include "box.hpp"
#include "ambient.hpp"
#include "camera.hpp"

Scene sdfParser(std::string const& file_path){
    std::ifstream  sdf_filestream(file_path, std::ios::in);
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
                sc.material_map.insert({name, std::make_shared<Material>(material)});
                std::cout << "successfully created material" << material << std::endl;
            }
            if ("shape" == keyword){
                iss >> keyword;
                if ("sphere" == keyword){
                    std::string name;
                    glm::vec3 center;
                    float radius;
                    std::string material;
                    iss >> name;
                    iss >> center.x >> center.y >> center.z;
                    iss >> radius;
                    iss >> material;
                    auto material_help = sc.material_map.find(material);
                    if (material_help == sc.material_map.end()){
                        std::cerr << "material not found " << "\n";
                    }
                    Sphere sp{center, radius, name, material_help->second};
                    sc.shape_vector.push_back(std::make_shared<Sphere>(sp));
                    std::cout << "successfully created sphere" << sp << std::endl;
                }
                if ("box" == keyword){
                    std::string name;
                    glm::vec3 min;
                    glm::vec3 max;
                    std::string material;
                    iss >> name;
                    iss >> min.x >> min.y >> min.z;
                    iss >> max.x >> max.y >> max.z;
                    iss >> material;

                    auto material_help = sc.material_map.find(material);
                    if (material_help == sc.material_map.end()){
                        std::cerr << "material not found " << "\n";
                    }
                    Box box{min, max, name, material_help->second};
                    sc.shape_vector.push_back(std::make_shared<Box>(box));
                    std::cout << "successfully created box" << box << std::endl;
                }
            }
            if ("light" == keyword){ //diffuse Punktlichtquellen
                std::string name;
                glm::vec3 pos;
                float color_r, color_g, color_b;
                float brightness;
                iss >> name;
                iss >> pos.x >> pos.y >> pos.z;
                iss >> color_r >> color_g >> color_b;
                iss >> brightness;
                Light light{name, pos, {color_r, color_g, color_b}, brightness};
                sc.light_vector.push_back(std::make_shared<Light>(light));
                std::cout << "successfully created light" << std::endl;
            }
            if ("ambient" == keyword){ //ambiente Grundbeleuchtung
                float color_r, color_g, color_b;
                iss >> color_r >> color_g >> color_b;
                sc.ambient.color = {color_r, color_g, color_b};
                sc.ambient.name = "ambient light";
                std::cout << "successfully created ambient light" << std::endl;
            }
            if ("camera" == keyword){
                std::string cam_name;
                float fov_x;
                iss >> cam_name;
                iss >> fov_x;
                sc.camera.name = cam_name;
                sc.camera.fov_x = fov_x;
                std::cout << "successfully created camera " << sc.camera.name <<std::endl;
            }
        }
        if ("render" == keyword){
            std::string cam_name, filepath;
            unsigned x_res, y_res;
            iss >> cam_name;
            iss >> filepath;
            iss >> x_res >> y_res;
            sc.rend.camera_name = cam_name;
            sc.rend.filename = filepath;
            sc.rend.width = x_res;
            sc.rend.height = y_res;
            std::cout << "successfully created render "<< sc.rend.camera_name << std::endl;
            //erzeugt bild der szene und legt datei ab mit auflösung
        }
    }
    sdf_filestream.close();
    return sc;
}