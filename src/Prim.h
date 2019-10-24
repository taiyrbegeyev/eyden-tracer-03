// Geaometrical Primitives base abstract class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"
#include "IShader.h"
#include "BoundingBox.h"

struct Ray;

/**
 * @brief Geometrical Primitives (Prims) base abstract class
 */
class CPrim
{
public:
	/**
	* @brief Constructor
	*/
	CPrim(std::shared_ptr<IShader> pShader) : m_pShader(pShader) {}
	CPrim(const CPrim&) = delete;
	virtual ~CPrim(void) = default;
	const CPrim& operator=(const CPrim&) = delete;

	/**
	 * @brief Checks for intersection between ray \b Ray and the primitive
	 * @details If a valid intersection has been found with the primitive, set Ray::t to the distance to this intersection point (if current t < ray.t)
	 * @param[in,out] ray The ray (Ref. @ref Ray for details)
	 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
	 * @retval false Otherwise
	 */
	virtual bool			Intersect(Ray& ray) = 0;
	/**
	 * @brief Checks if the \b ray.org is occluded
	 */
	virtual bool			Occluded(Ray& ray) { return Intersect(ray); }
	/**
	 * @brief Returns the normalized normal of the primitive
	 * @param ray The ray
	 * @return The normalized normal of the primitive
	 */
	virtual Vec3f			GetNormal(const Ray& ray) const = 0;
	/**
	 * @brief Returns the bounding box, which contain the primitive
	 * @returns The bounding box, which contain the primitive
	 */
	virtual CBoundingBox	calcBounds(void) const = 0;
	/**
	 * @brief Check whether the primitive is contained in the bounding box \b box
	 * @param box The bounding box
	 * @retval true If the primitive's bounding box overlaps the given bounding box \b box
	 * @retval false Otherwise
	 */
	virtual bool 			inVoxel(const CBoundingBox& box) const
	{
		// --- PUT YOUR CODE HERE ---
		CBoundingBox b = calcBounds();
		return b.overlaps(box);
		return true;
	}
	
	std::shared_ptr<IShader> getShader(void) const { return m_pShader; }

	
private:
	std::shared_ptr<IShader>	m_pShader;
};
