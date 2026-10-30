#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include <cstdio>
#import <fstream>
#import "vec3.h"

//global veriables in class may need new locations
#define TX 1300
#define TY 827

#define X 1024
#define Y 1024

#define SAMPLES_PER_PIXEL 100

#define frand() (rand() / (RAND_MAX + 1.0))


    class load_texture{

        

        double image[Y][X][3]; // Zero by placement

        double texture[TY][TX][3];


        void loading_texture(){
            FILE *f = fopen("earth2.ppm", "r");
            char s[5];
            int x, y;
            int r,g,b;


            fscanf(f, "%s", s); //p3
            fscanf(f, "%s", s); //tx
            fscanf(f, "%s", s); //ty
            fscanf(f, "%s", s); //255

            for(y = TY - 1; y >= 0; y--){
                for(x = 0; x < TX; x++){
                    fscanf(f, "%d %d %d", &r, &g, &b);
                    texture[y][x][0] = r / 255.0;
                    texture[y][x][1] = g / 255.0;
                    texture[y][x][2] = b / 255.0;
                }
            }

            fclose(f);

            f = fopen("foo.ppm", "w");
            fprintf(f, "P3\n1300 827\n255\n");
            for(y = 0; y < TY; y++){
                for(x = 0; x < TX; x++){
                    fprintf(f, "%d %d %d\n", (int) (texture[y][x][0] * 255),
                    (int) (texture[y][x][1] * 255), (int) (texture[y][x][2] * 255));
                }
            }

            fclose(f);
        }

        int main(int argc, char *argv[])
        {
            int y, x;
            double dy, dx;
            FILE *f;
            vec3 p;
            vec3 a, b;
            vec3 na, nb, nc, n;
            vec3 bary;
            vec3 d0, d1;
            vec3 uv;
            double sx, sy;
            int s;
            int u, v;
            int i;
            
            // Make a triangle
            struct triangle t[2];

            load_texture();
            
            srand(time(NULL));

            t[0].a[0]  = -1.0;
            t[0].a[1]  = -1.0;
            t[0].a[2]  = -1.0;
            t[0].ta[0] =  0.0;
            t[0].ta[1] =  0.0;
            t[0].ta[2] =  0.0;

            t[0].b[0]  =  1.0;
            t[0].b[1]  =  0.0;
            t[0].b[2]  = -1.0;
            t[0].tb[0] =  1.0;
            t[0].tb[1] =  1.0;
            t[0].tb[2] =  0.0;

            t[0].c[0]  = -1.0;
            t[0].c[1]  =  1.0;
            t[0].c[2]  = -1.0;
            t[0].tc[0] =  0.0;
            t[0].tc[1] =  1.0;
            t[0].tc[2] =  0.0;

            t[1].a[0]  = -1.0;
            t[1].a[1]  = -1.0;
            t[1].a[2]  = -1.0;
            t[1].ta[0] =  0.0;
            t[1].ta[1] =  0.0;
            t[1].ta[2] =  0.0;

            t[1].b[0]  =  1.0;
            t[1].b[1]  = -1.0;
            t[1].b[2]  = -1.0;
            t[1].tb[0] =  1.0;
            t[1].tb[1] =  0.0;
            t[1].tb[2] =  0.0;

            t[1].c[0]  =  1.0;
            t[1].c[1]  =  1.0;
            t[1].c[2]  = -1.0;
            t[1].tc[0] =  1.0;
            t[1].tc[1] =  1.0;
            t[1].tc[2] =  0.0;

            // n = (b - a) x (c - a) 
            //a b and n are all out
            a = sub(t[0].b, t[0].a);
            b = sub(t[0].c, t[0].a);
            n = cross(a, b);
            // vec3_sub(a, t[0].b, t[0].a);
            // vec3_sub(b, t[0].c, t[0].a);
            // vec3_cross(n, a, b);
            
            // Produce image
            for (y = 0; y < Y; y++) {
                for (x = 0; x < X; x++) {
                for (s = 0; s < SAMPLES_PER_PIXEL; s++) {
                    for (i = 0; i < 2; i++) {
        

                    // Get a random number.  Scale it to the dimensions of the a pixel.
                    // Then subtract half a pixel.
                    sx = (frand() / X) - (1.0 / (2.0 * X));
                    sy = (frand() / Y) - (1.0 / (2.0 * Y));

                    dx = ((x - (X / 2.0)) / (X / 2.0)) + (1.0 / X) + sx;
                    dy = ((y - (Y / 2.0)) / (Y / 2.0)) + (1.0 / Y) + sy;

                    p[0] = dx;
                    p[1] = dy;
                    p[2] = -1.0; // Triangle plane is at -1
                
                    //      na = (c - b) x (p - b)

                    a = sub(t[i].c, t[i].b);
                    //vec3_sub(a, t[i].c, t[i].b);
                    //vec3_sub(b, p, t[i].b);
                    b = sub(p, t[i].b);
                    //vec3_cross(na, a, b);

                    na = cross(a, b);

                    //      nb = (a - c) x (p - c)
                    //vec3_sub(a, t[i].a, t[i].c);
                    a = sub(t[i].a, t[i].c);
                    //vec3_sub(b, p, t[i].c);
                    b = sub(p, t[i].c);
                    //vec3_cross(nb, a, b);
                    nb = cross(a,b);

                    //      nc = (b - a) x (p - a)
                    //vec3_sub(a, t[i].b, t[i].a);
                    a = sub(t[i].b, t[i].a);
                    //vec3_sub(b, p, t[i].a);
                    b = sub(p, t[i].a);
                    //vec3_cross(nc, a, b);
                    nc = cross(a, b);

                    bary[0] = dot(n, na) / dot(n, n);
                    bary[1] = dot(n, nb) / dot(n, n);
                    bary[2] = dot(n, nc) / dot(n, n);

                    // Texture coordinate calculations
                    // uv = ta + bary[1] * (tb - ta) + bary[2] * (tc - ta)
                    //vec3_sub(d0, t[i].tb, t[i].ta);
                    d0 = sub(t[i].tb, t[i].ta);
                    //vec3_mul_scalar(d0, d0, bary[1]);
                    d0 = mul_scalar(d0, bary[1]);
                    //vec3_sub(d1, t[i].tc, t[i].ta);
                    d1 = sub(t[i].tc, t[i].ta);
                    //vec3_mul_scalar(d1, d1, bary[2]);
                    d1 = mul_scalar(d1, bary[2]);
                    //vec3_add(uv, t[i].ta, d0);
                    uv = add(t[i].ta, d0);
                    //vec3_add(uv, uv, d1);
                    uv = add(uv, d1);
                    
                    if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0) {
                        u = (int) (uv[0] * TX);
                        v = (int) (uv[1] * TY);

                        if (u >= 1300) {
                        u = 1299;
                        }
                        if (v >= 827) {
                        v = 827;
                        }
                        
                        //            printf("%d %d, %d, %d\n", x, y, u, v);
                        image[y][x][0] += texture[v][u][0];
                        image[y][x][1] += texture[v][u][1];
                        image[y][x][2] += texture[v][u][2];
                    }
                    }
                }
                }
            }

                // Write image
                f = fopen("barycentric.ppm", "w");
                fprintf(f, "P3\n%d\n%d\n255\n", X, Y);
                for (y = Y - 1; y >= 0; y--) {
                    for (x = 0; x < X; x++) {
                    fprintf(f, "%d %d %d\n",
                            (unsigned char) (image[y][x][0] * 255.99 / SAMPLES_PER_PIXEL),
                            (unsigned char) (image[y][x][1] * 255.99 / SAMPLES_PER_PIXEL),
                            (unsigned char) (image[y][x][2] * 255.99 / SAMPLES_PER_PIXEL));
                    }
                }
                
                return 0;
            }

    };

#endif