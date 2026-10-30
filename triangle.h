#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "rtweekend.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory>

//

class triangle : public hittable {
    public:

        triangle(const point3& pointA, const point3& pointB, const point3& pointC, std::shared_ptr<material> mat)
         : a(pointA), b(pointB), c(pointC), mat(mat){}


        
        

        // void setNormal(hit_record& rec){
        //     forMain = rec;
        // }

        // vec3 getNormal(){
        //     return forMain.normal;
        // }

        bool hit(const ray&r, interval ray_t, hit_record& rec) const override{

            double earyT;

            vec3 triEdge1 = b - a; // A to B
            vec3 triEdge2 = c - a; // A to C
            vec3 triFlatCross = cross(triEdge1, triEdge2); // Cross product which way the plane is facing
            //Cross product and normal vector are the same thing

            vec3 NormalizedFlatPlane = normalize(triFlatCross); //The plane is technically a infinite size and normalizing it just good practice.
            //Normalizing is just direction sooo



            //plane equation
            // scalar = n-> * (a-> - p->)
            // n is planes normal
            // p is some point on the plane
            // a is the test point


            //ray equation
            //p-> = s-> + d-> * t
            // s is ray start point, d is direction, t is distance to travel

            //0 = n*((s+d*t)-p)
            //0 = n*s +n*d*t-n*p

            // t = n(p-s) / (n*d)


            //denominator check makes sure the ray is not going paralel to the plain
            //It would never hit

            float ndot = dot(NormalizedFlatPlane, r.direction());

            //Added another check
            if(abs(ndot) < 0.0001f || abs(ndot) > ray_t.max){
                return false;
            }

            float n_dot_ps = dot(NormalizedFlatPlane,a - r.origin());
            earyT = n_dot_ps / ndot;

            vec3 pointPlan = r.origin() + earyT * r.direction(); //The point on the plane the ray hits
            //Now need to check whether it is in the triangle


            //Creating edges
            vec3 AtoB = b - a;
            vec3 BtoC = c - b;
            vec3 CtoA = a - c;

            //Create each point
            vec3 AtoPoint = pointPlan - a;
            vec3 BtoPoint = pointPlan - b;
            vec3 CtoPoint = pointPlan - c;

            //Test vectors to compare to the normal of the triangle
            vec3 ATestVec = cross(AtoB, AtoPoint);
            vec3 BTestVec = cross(BtoC, BtoPoint);
            vec3 CTestVec = cross(CtoA, CtoPoint);

            bool AtestVecMatches = dot(ATestVec, NormalizedFlatPlane) > 0.f;
            bool BtestVecMatches = dot(BTestVec, NormalizedFlatPlane) > 0.f;
            bool CtestVecMatches = dot(CTestVec, NormalizedFlatPlane) > 0.f;

            bool hitTriangle = AtestVecMatches && BtestVecMatches & CtestVecMatches;

            // rec.t = null;
            // rec.p = r.at(double t);
            // rec.normal = ()

            if(hitTriangle == true){
                rec.t = earyT;
                rec.p = pointPlan;
                // vec3 outwardNormal = normalize(NormalizedFlatPlane);
                rec.set_face_normal(r, NormalizedFlatPlane);
                rec.mat = mat;
                //setNormal(rec);
                
            }   


            // std::cout << hitTriangle;

            return hitTriangle;
        }



    private:
        vec3 a,b,c;
        shared_ptr<material> mat;
        // hit_record& forMain = form;
};


    

#endif