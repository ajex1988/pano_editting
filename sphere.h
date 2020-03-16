#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <vector>
#include <math.h>

#define PI 3.1415926

class Sphere
{
public:
    Sphere(int _num_lat, int _num_lon, float _radius);
    ~Sphere();

    std::vector<int> getTopIdx();
    std::vector<std::vector<int>> getMiddleIdx();
    std::vector<int> getBottomIdx();

    std::vector<std::vector<float>> getXYZCoords();
    std::vector<std::vector<float>> getUVCoords();

    int getVerNum();

private:
    int num_lat;  //Number of latitude line
    int num_lon;  //Number of longtitude line
    float radius; //Radius of the sphere
    int num_vertices; //Number of vertices, can be calculated from the above values

    std::vector<std::vector<float>> xyz_coords;
    std::vector<std::vector<float>> uv_coords;

    std::vector<int> top_idx;
    std::vector<std::vector<int>> middle_idx;
    std::vector<int> bottom_idx;

    void makeSphere();
    void makeIdx();

};

#endif // SPHERE_H
