// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f center, float radius, std::shared_ptr<IShader> pShader)
		: CPrim(pShader)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// mathematical derivation, numerically not very stable, but simple
		
		// --> find roots of f(t) = ((R+tD)-C)^2 - r^2
		// f(t) = (R-C)^2 + 2(R-C)(tD) + (tD)^2 -r^2
		// --> f(t) = [D^2] t^2 + [2D(R-C)] t + [(R-C)^2 - r^2]
		Vec3f diff = ray.org - m_center;
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(diff);
		float c = diff.dot(diff) - m_radius * m_radius;
		
		// use 'abc'-formula for finding root t_1,2 = (-b +/- sqrt(b^2-4ac))/(2a)
		float inRoot = b * b - 4 * a * c;
		if (inRoot < 0) return false;
		float root = sqrtf(inRoot);
		
		float dist = (-b - root) / (2 * a);
		if (dist > ray.t)
			return false;
		
		if (dist < Epsilon) {
			dist = (-b + root) / (2 * a);
			if (dist < Epsilon || dist > ray.t)
				return false;
		}
		
		ray.t = dist;
		ray.hit = this;
		return true;
	}
	
	virtual Vec3f GetNormal(const Ray& ray) const override
	{
		Vec3f hit = ray.org + ray.t * ray.dir;
		Vec3f normal = hit - m_center;
		normal = normalize(normal);
		return normal;
	}

	virtual CBoundingBox calcBounds(void) const override
	{
		CBoundingBox res;
		// --- PUT YOUR CODE HERE ---
		res.m_min = std::numeric_limits<Vec3f>::infinity();
		res.m_max = -1 * std::numeric_limits<Vec3f>::infinity();
		res.extend(m_center + Vec3f(m_radius, m_radius, m_radius));
		return res;
	}
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

