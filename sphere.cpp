#include "sphere.h"

Sphere::Sphere(int _num_lat, int _num_lon, float _radius):
    num_lat(_num_lat),
    num_lon(_num_lon),
    radius(_radius)
{
    num_vertices = num_lat*(num_lon+1) + 2; // Double the vertices of merdian, plus S/N pole.
    makeSphere();
}

Sphere::~Sphere()
{

}

void Sphere::makeSphere()
{
    // North pole
    std::vector<float> n_pole_xyz{0,radius,0};
    std::vector<float> n_pole_uv{0,1};

    // South pole
    std::vector<float> s_pole_xyz{0,-radius,0};
    std::vector<float> s_pole_uv{0,0};

    float lat_spacing = 1.0 / float(num_lat + 1);
    float lon_spacing = 1.0 / float(num_lon);

    // First push the north pole
    xyz_coords.push_back(n_pole_xyz);
    uv_coords.push_back(n_pole_uv);

    for (int i = 0; i < num_lat; i++) {
        for (int j = 0; j < num_lon+1; j++) {
            float u = j*lon_spacing;
            float v = 1.0 - (i+1)*lat_spacing;

            float theta = u*2.0*PI;
            float phi = (v-0.5)*PI;

            float x = cos(phi)*cos(theta)*radius;
            float y = sin(phi)*radius;
            float z = cos(phi)*sin(theta)*radius;

            std::vector<float> uv{u,v};
            std::vector<float> xyz{x,y,z};

            uv_coords.push_back(uv);
            xyz_coords.push_back(xyz);
        }
    }

    // Finally push the south pole
    xyz_coords.push_back(s_pole_xyz);
    uv_coords.push_back(s_pole_uv);

    makeIdx();
}

void Sphere::makeIdx()
{
    // Top: one triangle_fan, 1 + (num_lon+1) vertices
    for (int i = 0; i < num_lon+2; i++)
        top_idx.push_back(i);
    // Middle: each quad is a triange_fan
    for (int i = 0; i < num_lat-1; i++) {
        int offset = 1 + i*(num_lon+1);
        for (int j = 0; j < num_lon; j++) {
            int top_left = j + offset;
            int bottom_left = j + (num_lon+1) + offset;
            int bottom_right = j + (num_lon+1) + 1 + offset;
            int top_right = j + 1 + offset;

            std::vector<int> tri_fan{top_left,bottom_left,bottom_right,top_right};
            middle_idx.push_back(tri_fan);
        }
    }
    // Bottom: same as top
    for (int i = num_vertices-1; i > num_vertices-num_lon-3; i--)
        bottom_idx.push_back(i);
}

std::vector<int> Sphere::getTopIdx()
{
    return top_idx;
}

std::vector<std::vector<int>> Sphere::getMiddleIdx()
{
    return middle_idx;
}

std::vector<int> Sphere::getBottomIdx()
{
    return bottom_idx;
}

std::vector<std::vector<float>> Sphere::getXYZCoords()
{
    return xyz_coords;
}

std::vector<std::vector<float>> Sphere::getUVCoords()
{
    return uv_coords;
}

int Sphere::getVerNum()
{
    return num_vertices;
}
