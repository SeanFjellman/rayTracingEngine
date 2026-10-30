//#include "color.h"
//#include "ray.h"
//#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "triangle.h"
#include <memory>
//#include "vec3.h"


// #include <climits>
// #include <fstream>
// #include <cstdlib>
// #include <memory>
//#include <iostream>


//Takes in center of the sphere, the radius, and the ray. And returns true of there is a hit

// double hit_sphere(const point3& center, double radius, const ray& r) {
//     vec3 oc = center - r.origin();
//     auto a = r.direction().length_squared();
//     auto h = dot(r.direction(), oc);
//     auto c = oc.length_squared() - radius*radius;
//     auto discriminant = h*h - a*c;


//     //Make sure we do not render the sphere if it is behind us
//     if (discriminant < 0) {
//         return -1.0;
//     } else {
//         return (h - std::sqrt(discriminant)) / a;
//     }
// }
//It expects a number 0 - 1 that is a percentage of that color in the sphere

// color ray_color(const ray& r, const hittable& world) {
//     hit_record rec;
//     if (world.hit(r, interval(0, infinity), rec)) {
//         return 0.5 * (rec.normal + color(1,1,1));
//     }

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    // if(world.hit(r, 0, -2, rec)){
    //     return color(0.2, 0.2,0.2);
    // }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

// int main() {
//     hittable_list world;

//     auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
//     world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

//     for (int a = -11; a < 11; a++) {
//         for (int b = -11; b < 11; b++) {
//             auto choose_mat = random_double();
//             point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

//             if ((center - point3(4, 0.2, 0)).length() > 0.9) {
//                 shared_ptr<material> sphere_material;

//                 if (choose_mat < 0.8) {
//                     // diffuse
//                     auto albedo = color::random() * color::random();
//                     sphere_material = make_shared<lambertian>(albedo);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 } else if (choose_mat < 0.95) {
//                     // metal
//                     auto albedo = color::random(0.5, 1);
//                     auto fuzz = random_double(0, 0.5);
//                     sphere_material = make_shared<metal>(albedo, fuzz);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 } else {
//                     // glass
//                     sphere_material = make_shared<dielectric>(1.5);
//                     world.add(make_shared<sphere>(center, 0.2, sphere_material));
//                 }
//             }
//         }
//     }

//     auto material1 = make_shared<dielectric>(1.5);
//     world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

//     auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
//     world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

//     auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
//     world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

//     camera cam;

//     cam.aspect_ratio      = 16.0 / 9.0;
//     cam.image_width       = 1200;
//     cam.samples_per_pixel = 1;
//     cam.max_depth         = 50;

//     cam.vfov     = 20;
//     cam.lookfrom = point3(13,2,3);
//     cam.lookat   = point3(0,0,0);
//     cam.vup      = vec3(0,1,0);

//     cam.defocus_angle = 0.6;
//     cam.focus_dist    = 10.0;

//     cam.render(world);
// }

int main() {

    hittable_list world;

    // world.add(make_shared<sphere> (point3(1,0,2), 0.5));
    // world.add(make_shared<sphere> (point3(0,-100.5,-1), 100));
    // world.add(make_shared<sphere> (point3(-1,0,2),0.5));

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    //dielectric glass material
    // auto material_left = make_shared<dielectric>(1.0 / 1.33);
    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);


    
    //fuzzy materaial
    //auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    //Material for a triangle
    auto material_triangle = make_shared<lambertian>(color(1.0, 0.2, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), 0.4, material_bubble));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    world.add(make_shared<triangle>(
        point3(-1.0, 1.0, -5),
        point3(-1.0, -1.0, -5), 
        point3(1.0, -1.0,-5), material_triangle));

    /* 
    world.add(make_shared<triangle> (
     point3(-1.0, 1.0, 4.0),
     point3(-1.0, -1.0, 4.0), 
     point3(1.0, -1.0,4.0)));
     */

    // auto R = std::cos(pi/4);

    // auto materialleft  = make_shared<lambertian>(color(0,0,1));
    // auto materialright = make_shared<lambertian>(color(1,0,0));

    // world.add(make_shared<sphere>(point3(-R, 0, -1), R, materialleft));
    // world.add(make_shared<sphere>(point3( R, 0, -1), R, materialright));
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 1000;
    cam.max_depth = 50;

    //Camera position
    cam.vfov = 40;
    cam.lookfrom = point3(0,0,1);
    cam.lookat   = point3(0,0,-3.1);
    cam.vup      = vec3(0,1,0);
    cam.defocus_angle = 0; //Aperature
    cam.focus_dist    = 3.4;

    cam.render(world);
















//     // Image

//     auto aspect_ratio = 16.0 / 9.0;
//     int image_width = 1000;

//     // Calculate the image height, and ensure that it's at least 1.
//     int image_height = int(image_width / aspect_ratio);
//     image_height = (image_height < 1) ? 1 : image_height;

//     // Camera

//     auto focal_length = 1.0;
//     auto viewport_height = 2.0;
//     auto viewport_width = viewport_height * (double(image_width)/image_height);
//     auto camera_center = point3(0, 0, 0);

//     // Calculate the vectors across the horizontal and down the vertical viewport edges.
//     auto viewport_u = vec3(viewport_width, 0, 0);
//     auto viewport_v = vec3(0, -viewport_height, 0);

//     int mark, steven, three;

//     mark = steven = three = 0;


//     // World

//     hittable_list world;


//     // x y and z and then radius
//     world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
//     world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
//     world.add(make_shared<sphere>(point3(0, 40, -1 ), 100));

//     // Calculate the horizontal and vertical delta vectors from pixel to pixel.
//     auto pixel_delta_u = viewport_u / image_width;
//     auto pixel_delta_v = viewport_v / image_height;

//     // Calculate the location of the upper left pixel.
//     auto viewport_upper_left = camera_center
//                              - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
//     auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

//     // Render

//     std::ofstream image("image.ppm");

// image << "P3\n" << image_width << " " << image_height << "\n255\n";

//     for (int j = 0; j < image_height; j++) {
//         std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
//         for (int i = 0; i < image_width; i++) {
//             auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
//             auto ray_direction = pixel_center - camera_center;
//             ray r(camera_center, ray_direction);

//             color pixel_color = ray_color(r, world);;
//             write_color(image, pixel_color);
//         }
//     }

//     std::clog << "\rDone.                 \n";
//     // system("xdg-open image.ppm &");

//     image.close();

//     system("xdg-open image.ppm &");

    
}