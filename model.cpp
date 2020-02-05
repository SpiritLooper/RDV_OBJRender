#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"
#include <regex>

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
          
            int itrash, idx;
            iss >> trash;
            if ( line.find("/") == std::string::npos ){
                while (iss >> idx ) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
            } else {
                while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;

    // Centrage du model sur l'origine 
    Vec3f min, max, ecart;
    get_bbox(min,max);
    for (int i = 0; i < 3; i++)
    {
        ecart[i] = (min[i] + max[i]) / 2.;
    }
    

    for (int i = 0; i < (int)verts_.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            verts_[i][j] =  verts_[i][j] - ecart[j];
        }   
    }

    get_bbox(min,max);

    // On cherche quel axe déborde le plus à partir de l'origine
    float rapport = std::max( max[0] , std::max( max[1] , max[2] ) );


    // Reduction à l'échelle du model selon l'axe qui nécessite le plus gros rapport de réduction
    for (int i = 0; i < (int)verts_.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            verts_[i][j] = verts_[i][j] / rapport;    
        }
    }

}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

void Model::get_bbox(Vec3f &min, Vec3f &max) {
    min = max = verts_[0];
    for (int i = 1; i < (int)verts_.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            min[j] = std::min(min[j],verts_[i][j] );
            max[j] = std::max(max[j],verts_[i][j] );
        }
    }
   // std::cerr << "bbox: [" << min << " : " << max << "]" << std::endl;
}