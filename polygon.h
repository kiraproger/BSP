class polygon{
public:
    float x1;
    float y1;
    float x2;
    float y2;
    float high;
    float normal_x;
    float normal_y;
    polygon (){
        x1 = 0.0;
        x2 = 0.0;
        y1 = 0.0;
        y2 = 0.0;
        high = 0.0;
        front_bsp_tree = NULL;
        back_bsp_tree = NULL;
        normal_x = 0.0;
        normal_y = 0.0;
    }

    polygon (float new_x1, float new_x2, float new_y1, float new_y2, float new_high){
        x1 = new_x1;
        x2 = new_x2;
        y1 = new_y1;
        y2 = new_y2;
        high = new_high;
        front_bsp_tree = NULL;
        back_bsp_tree = NULL;
        get_normal();
    }
    polygon* front_bsp_tree;
    polygon* back_bsp_tree;
private:
    void draw_polygon(){
        glBegin (GL_TRIANGLE_STRIP);
        glVertex3f(x1, y1,0);
        glVertex3f(x1, y1, high);
        glVertex3f(x2, y2, 0);
        glVertex3f(x2, y2, high);
        glEnd();
    }

    void get_normal(){
        // I think , that important only direction of normal
        normal_x = y1 - y2;
        normal_y = x2 - x1;
        //will be better if all normals have positive dirrection with Oy
        if (normal_y < 0){
            normal_x = (-1)*normal_x;
            normal_y = (-1)*normal_y;

        }  
    }


    


};