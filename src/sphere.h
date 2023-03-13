#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	auto a 	= r.direction().length_squared();
	auto half_b = dot(r.direction(), oc);
	auto c	= dot(oc, oc) - radius * radius;

	auto discriminant = half_b*half_b - a*c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root within `t` range
	auto root = (-half_b - sqrtd ) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	// There was a hit; store it
	// TODO?: more than one hit (case where equation has two solutions)
	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - center) / radius;

	return true;
}

#endif