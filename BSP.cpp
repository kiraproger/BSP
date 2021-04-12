#include <iostream>
#include <GL/glut.h>
#include "polygon.h"
#include <vector>

using std::vector;

int check_polygon_position(polygon splitter_polygon, polygon checked_polygon){
    float scalar_mul1 = splitter_polygon.normal_x*(splitter_polygon.x1 - checked_polygon.x1) + splitter_polygon.normal_y*(splitter_polygon.y1 - checked_polygon.y1);
    float scalar_mul2 = splitter_polygon.normal_x*(splitter_polygon.x2 - checked_polygon.x2) + splitter_polygon.normal_y*(splitter_polygon.y2 - checked_polygon.y2);

    if (scalar_mul1 <= 0 && scalar_mul2 <= 0)
        return 1;

    if (scalar_mul2 >= 0 && scalar_mul2 >= 0)
        return 2;
    
    if (scalar_mul1*scalar_mul2 < 0)
        return 3;

    return 3;
}

void find_same_point(polygon polygon1, polygon polygon2, float* finded_x, float* finded_y){
    float a11 = polygon1.x1 - polygon1.x2;
    float a21 = polygon1.y1 - polygon1.y2;
    float a12 = polygon2.x1 - polygon2.x2;
    float a22 = polygon2.y1 - polygon2.y2;
    float c1 = polygon2.x1 - polygon1.x1;
    float c2 = polygon2.y1 - polygon1.y1;
    float det = a11*a22 - a12*a21;
    float det1 = c1*a22 - a12*c2;
    float t_param   = det1/det;
    float same_x = polygon1.x1 + t_param*(polygon1.x1 - polygon1.x2);
    float same_y = polygon1.y1 + t_param*(polygon1.y1 - polygon1.y2);
    *finded_x = same_x;
    *finded_y = same_y;
}

void BSP_Tree_Create( std::vector<polygon> level_polygons){

    size_t size = level_polygons.size();


    if (size == 1)
        return ;
    
    polygon splitter_polygon = level_polygons[0];
    vector<polygon> back_polygons;
    vector<polygon> front_polygons;

    for (int i = 1; i < size; ++i){
        polygon checked_polygon = level_polygons[i];

        int position_flag = check_polygon_position(splitter_polygon, checked_polygon);
        if (position_flag == 1)
            back_polygons.push_back(checked_polygon);
            

        if (position_flag == 2)
            front_polygons.push_back(checked_polygon);

        if (position_flag == 3){
            float same_x;
            float same_y;
            find_same_point(splitter_polygon, checked_polygon, &same_x, &same_y);
            polygon new_polygon1(checked_polygon.x1, same_x, checked_polygon.y1, same_y, 0.0);
            polygon new_polygon2(checked_polygon.x2, same_y, checked_polygon.y1, same_y, 0.0);
            if (check_polygon_position(splitter_polygon, new_polygon1) == 1){
                back_polygons.push_back(new_polygon1);
                front_polygons.push_back(new_polygon2);}
            else{
                back_polygons.push_back(new_polygon2);
                front_polygons.push_back(new_polygon1);
            }

            splitter_polygon. front_bsp_tree = new polygon;
            splitter_polygon. back_bsp_tree = new polygon;
            *splitter_polygon.front_bsp_tree = front_polygons[0];
            *splitter_polygon.back_bsp_tree = back_polygons[0];
            BSP_Tree_Create(back_polygons);
            BSP_Tree_Create(front_polygons);
    }
}
}

int main(){
    
};


    

