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
        if ("#" == keyword){
            continue;
        }
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
                std::cout << "successfully created light: " << light.name<< std::endl;
                std::cout << "pos, x: " << light.pos.x << "   y: " << light.pos.y << "  z: " << light.pos.z << "\n";
                std::cout << "color, x: " << light.color.r << "   y: " << light.color.g << "  z: " << light.color.b << "\n";
                std::cout << "brightness: " << brightness << "\n";
                std::cout << "\n";
            }

            if ("camera" == keyword){
                std::string cam_name;
                float fov_x;
                float dir_x , dir_y, dir_z;
                float up_x, up_y, up_z;
                iss >> cam_name;
                iss >> fov_x;
                iss >> dir_x >> dir_y >> dir_z;
                iss >> up_x >> up_y >> up_z;
                Camera cam{cam_name, fov_x, {dir_x, dir_y, dir_z}, {up_x, up_y, up_z}};
                std::cout << "successfully created camera " << cam_name <<std::endl;
                std::cout << "fov_x: " << cam.get_fov_x() << "\n";
                std::cout << "eye, x: " << cam.get_eye().x << "   y: " << cam.get_eye().y << "  z: " << cam.get_eye().z << "\n";
                std::cout << "direction, x: " << cam.get_direction().x << "   y: " << cam.get_direction().y << "  z: " << cam.get_direction().z << "\n";
                std::cout << "up, x: " << cam.get_up().x << "   y: " << cam.get_up().y << "  z: " << cam.get_up().z << "\n";
                std::cout << "\n";

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
            std::cout << "Filename: " << sc.rend.filename << "\n";
            std::cout << "width: " << sc.rend.width << "\n";
            std::cout << "height: " << sc.rend.height << "\n";

            //erzeugt bild der szene und legt datei ab mit auflösung
        }
        if ("ambient" == keyword){ //ambiente Grundbeleuchtung
            float color_r, color_g, color_b;
            iss >> color_r >> color_g >> color_b;
            sc.ambient.color = {color_r, color_g, color_b};
            sc.ambient.name = "ambient light";
            std::cout << "successfully created ambient light" << std::endl;
            std::cout << "\n";
            std::cout << "name: " << sc.ambient.name << "\n";
            std::cout << "color, r: " << sc.ambient.color.r << "   g: " << sc.ambient.color.g << "  b: " << sc.ambient.color.b << "\n";
        }
        if ("transform" == keyword) {
            std::string shape_name;
            iss >> shape_name;

            auto it = sc.shape_vector.begin();
            if (sc.shape_vector.size() != 1)
            {
                while ((*it)->name() != shape_name) {
                    ++it;
                }
            }
            std::shared_ptr<Shape> obj = *it;

            std::string transformation_type;
            iss >> transformation_type;
            if ("translate" == transformation_type) {
                float x;
                float y;
                float z;
                iss >> x;
                iss >> y;
                iss >> z;
                obj->translate(glm::vec3{ x,y,z });
                std::cout << "translated " << shape_name << std::endl;
            }
            if ("rotate" == transformation_type) {
                float degree;
                float x;
                float y;
                float z;
                iss >> degree;
                degree = degree / 180 * glm::pi<float>();
                iss >> x;
                iss >> y;
                iss >> z;
                obj->rotate(degree, glm::vec3{ x,y,z });
                std::cout << "rotated " << shape_name << std::endl;
            }
            if ("scale" == transformation_type) {
                float x;
                float y;
                float z;
                iss >> x;
                iss >> y;
                iss >> z;
                obj->scale(glm::vec3{ x,y,z });
                std::cout << "scaled " << shape_name << std::endl;
            }
        }
    }
    sdf_filestream.close();
    return sc;
}