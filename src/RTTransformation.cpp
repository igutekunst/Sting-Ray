#include "RTTransformation.h"


RTTransformation::RTTransformation(void)
{
}
RTTransformation::RTTransformation(RTMatrix newTransM, RTMatrix newInvM)
{
	trans_m = newTransM;
	inv_m = newInvM;
}

RTTransformation::~RTTransformation(void)
{
}


// transformation of position vector
 RTVector RTTransformation::multiply_m_v(RTMatrix & m, RTVector & v)
{
  static RTVector ret;

  ret.x = m.mat[0][0] * v.x + m.mat[0][1] * v.y + m.mat[0][2] * v.z + m.mat[3][1];
  ret.y = m.mat[1][0] * v.x + m.mat[1][1] * v.y + m.mat[1][2] * v.z + m.mat[3][2];
  ret.z = m.mat[2][0] * v.x + m.mat[2][1] * v.y + m.mat[2][2] * v.z + m.mat[3][3];

  return ret;
}

// transformation of direction vector (i.e., no translation)
 RTVector RTTransformation::multiply_m_v_dir(RTMatrix & m, RTVector & vdir)
{
  static RTVector ret;

  ret.x = m.mat[0][0] * vdir.x + m.mat[0][1] * vdir.y + m.mat[0][2] * vdir.z;
  ret.y = m.mat[1][0] * vdir.x + m.mat[1][1] * vdir.y + m.mat[1][2] * vdir.z;
  ret.z = m.mat[2][0] * vdir.x + m.mat[2][1] * vdir.y + m.mat[2][2] * vdir.z;

  return ret;
}

// transform a point
RTVector RTTransformation::transform_point(RTVector & pt)
{
  
  return multiply_m_v(trans_m, pt);
  
}

// transform a ray direction
RTVector RTTransformation::transform_direction(RTVector & dir)
{
 
  return multiply_m_v_dir(trans_m, dir);
  
}

// transform a normal vector
RTVector RTTransformation::transform_normal(RTVector & nrm)
{
  // note the use of the INVERSE TRANSPOSE matrix
  static RTVector ret;
  ret.x = nrm.x * inv_m.mat[0][0] + nrm.y * inv_m.mat[1][0] + nrm.z * inv_m.mat[2][0];
  ret.y = nrm.x * inv_m.mat[0][1] + nrm.y * inv_m.mat[1][1] + nrm.z * inv_m.mat[2][1];
  ret.z = nrm.x * inv_m.mat[0][2] + nrm.y * inv_m.mat[1][2] + nrm.z * inv_m.mat[2][2];
  return ret;
}




RTRay RTTransformation::transformRay(RTRay & ray)
{
	
	RTVector newDir = (*this).transform_direction(ray.dir);
	RTVector newPoint = (*this).transform_point(ray.point);
	return RTRay(newPoint,newDir);


}