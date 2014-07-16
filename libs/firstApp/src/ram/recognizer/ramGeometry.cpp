// 
// ramGeometry.cpp - RAMDanceToolkit
// 
// Copyright 2012-2013 YCAM InterLab, Yoshito Onishi, Satoru Higa, Motoi Shimizu, and Kyle McDonald
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//    http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ramGeometry.h"

using namespace ofxCv;
using namespace cv;

void rotateToNormal(ofVec3f normal) {
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
}


// needs improvement. right now it just looks for the biggest cross product
void approximatePlane(const vector<ofVec3f>& points, int iterations, ofVec3f& center, ofVec3f& normal)
{
	int n = points.size();
	for(int i = 0; i < n; i++)
	{
		center += points[i];
	}
	center /= n;
	float maxLength = 0;
	for(int i = 0; i < n; i++)
	{
		ofVec3f side1 = points[i] - center;
		for(int j = i + 1; j < n; j++)
		{
			ofVec3f side2 = points[j] - center;
			ofVec3f curNormal = side1.getCrossed(side2);
			if(curNormal.z < 0) {
				curNormal *= -1;
			}
			float length = curNormal.length();
			if(length > maxLength)
			{
				normal = curNormal;
				maxLength = length;
			}
		}
	}
	normal.normalize();
}

template <typename Real>
Real DistancePointEllipseSpecial (const Real e[2], const Real y[2], Real x[2])
{
    Real distance;
    if (y[1] > (Real)0)
    {
        if (y[0] > (Real)0)
        {
            // Bisect to compute the root of F(t) for t >= -e1*e1.
            Real esqr[2] = { e[0]*e[0], e[1]*e[1] };
            Real ey[2] = { e[0]*y[0], e[1]*y[1] };
            Real t0 = -esqr[1] + ey[1];
            Real t1 = -esqr[1] + sqrt(ey[0]*ey[0] + ey[1]*ey[1]);
            Real t = t0;
            const int imax = 2*std::numeric_limits<Real>::max_exponent;
            for (int i = 0; i < imax; ++i)
            {
                t = ((Real)0.5)*(t0 + t1);
                if (t == t0 || t == t1)
                {
                    break;
                }
				
                Real r[2] = { ey[0]/(t + esqr[0]), ey[1]/(t + esqr[1]) };
                Real f = r[0]*r[0] + r[1]*r[1] - (Real)1;
                if (f > (Real)0)
                {
                    t0 = t;
                }
                else if (f < (Real)0)
                {
                    t1 = t;
                }
                else
                {
                    break;
                }
            }
			
            x[0] = esqr[0]*y[0]/(t + esqr[0]);
            x[1] = esqr[1]*y[1]/(t + esqr[1]);
            Real d[2] = { x[0] - y[0], x[1] - y[1] };
            distance = sqrt(d[0]*d[0] + d[1]*d[1]);
        }
        else  // y0 == 0
        {
            x[0] = (Real)0;
            x[1] = e[1];
            distance = fabs(y[1] - e[1]);
        }
    }
    else  // y1 == 0
    {
        Real denom0 = e[0]*e[0] - e[1]*e[1];
        Real e0y0 = e[0]*y[0];
        if (e0y0 < denom0)
        {
            // y0 is inside the subinterval.
            Real x0de0 = e0y0/denom0;
            Real x0de0sqr = x0de0*x0de0;
            x[0] = e[0]*x0de0;
            x[1] = e[1]*sqrt(fabs((Real)1 - x0de0sqr));
            Real d0 = x[0] - y[0];
            distance = sqrt(d0*d0 + x[1]*x[1]);
        }
        else
        {
            // y0 is outside the subinterval.  The closest ellipse point has
            // x1 == 0 and is on the domain-boundary interval (x0/e0)^2 = 1.
            x[0] = e[0];
            x[1] = (Real)0;
            distance = fabs(y[0] - e[0]);
        }
    }
    return distance;
}
//----------------------------------------------------------------------------
// The ellipse is (x0/e0)^2 + (x1/e1)^2 = 1.  The query point is (y0,y1).
// The function returns the distance from the query point to the ellipse.
// It also computes the ellipse point (x0,x1) that is closest to (y0,y1).
//----------------------------------------------------------------------------
template <typename Real>
Real DistancePointEllipse (const Real e[2], const Real y[2], Real x[2])
{
    // Determine reflections for y to the first quadrant.
    bool reflect[2];
    int i, j;
    for (i = 0; i < 2; ++i)
    {
        reflect[i] = (y[i] < (Real)0);
    }
	
    // Determine the axis order for decreasing extents.
    int permute[2];
    if (e[0] < e[1])
    {
        permute[0] = 1;  permute[1] = 0;
    }
    else
    {
        permute[0] = 0;  permute[1] = 1;
    }
	
    int invpermute[2];
    for (i = 0; i < 2; ++i)
    {
        invpermute[permute[i]] = i;
    }
	
    Real locE[2], locY[2];
    for (i = 0; i < 2; ++i)
    {
        j = permute[i];
        locE[i] = e[j];
        locY[i] = y[j];
        if (reflect[j])
        {
            locY[i] = -locY[i];
        }
    }
	
    Real locX[2];
    Real distance = DistancePointEllipseSpecial(locE, locY, locX);
	
    // Restore the axis order and reflections.
    for (i = 0; i < 2; ++i)
    {
        j = invpermute[i];
        if (reflect[j])
        {
            locX[j] = -locX[j];
        }
        x[i] = locX[j];
    }
	
    return distance;
}

ofVec2f closestPointOnRay(const ofVec2f& p1, const ofVec2f& p2, const ofVec2f& p3) {
	if(p1 == p2) {
		return p1;
	}
	
	float u = (p3.x - p1.x) * (p2.x - p1.x);
	u += (p3.y - p1.y) * (p2.y - p1.y);
	float len = (p2 - p1).length();
	u /= (len * len);
	
	return p1.getInterpolated(p2, u);
}

ofVec2f closestPointOnLine(const ofVec2f& p1, const ofVec2f& p2, const ofVec2f& p3) {
	if(p1 == p2) {
		return p1;
	}
	
	float u = (p3.x - p1.x) * (p2.x - p1.x);
	u += (p3.y - p1.y) * (p2.y - p1.y);
	float len = (p2 - p1).length();
	u /= (len * len);
	
	// clamp u
	if(u > 1) {
		u = 1;
	} else if(u < 0) {
		u = 0;
	}
	return p1.getInterpolated(p2, u);
}

ofVec2f closestPointOnRect(const cv::RotatedRect& rect, const ofVec2f& point) {
	ofVec2f norm = point;
	ofVec2f offset(rect.center.x, rect.center.y);
	norm -= offset;
	norm.rotate(-rect.angle);
	float w = rect.size.width / 2, h = rect.size.height / 2;
	ofVec2f nearest;
	if((norm.x > w || norm.x < -w) || (norm.y < -h || norm.y > h)) {
		nearest.set(ofClamp(norm.x, -w, w), ofClamp(norm.y, -h, h));
	} else {
		if(fabsf(fabsf(norm.x) - w) < fabsf(fabsf(norm.y) - h)) {
			nearest.set(w * (norm.x > 0 ? 1 : -1), norm.y);
		} else {
			nearest.set(norm.x, h * (norm.y > 0 ? 1 : -1));
		}
	}
	nearest.rotate(rect.angle);
	nearest += offset;
	return nearest;
}

ofVec2f closestPointOnCircle(const ofVec2f& center, float radius, const ofVec2f& point) {
	ofVec2f nearest = point - center;
	nearest *= radius / nearest.length();
	nearest += center;
	return nearest;
}

ofVec2f closestPointOnEllipse(const cv::RotatedRect& ellipse, const ofVec2f& point) {
	ofVec2f norm = point;
	ofVec2f offset(ellipse.center.x, ellipse.center.y);
	norm -= offset;
	norm.rotate(-ellipse.angle);
	bool flipX = norm.x < 0, flipY = norm.y < 0;
	if(flipX) norm.x *= -1;
	if(flipY) norm.y *= -1;
	float e[] = {ellipse.size.width / 2, ellipse.size.height / 2};
	float y[] = {norm.x, norm.y};
	float x[2];
	DistancePointEllipse(e, y, x);
	ofVec2f result(x[0], x[1]);
	if(flipX) result.x *= -1;
	if(flipY) result.y *= -1;
	result.rotate(ellipse.angle);
	result += offset;
	return result;
}

float distanceToEllipse(const ofVec2f& point, const cv::RotatedRect& ellipse) {
	return closestPointOnEllipse(ellipse, point).distance(point);
}

float distanceToRect(const ofVec2f& point, const cv::RotatedRect& rect) {
	return closestPointOnRect(rect, point).distance(point);
}

float distanceToLine(const ofVec2f& point, const ofVec2f& start, const ofVec2f& end) {
	return closestPointOnLine(start, end, point).distance(point);					  
}

float distanceToRay(const ofVec2f& point, const ofVec2f& start, const ofVec2f& end) {
	return closestPointOnRay(start, end, point).distance(point);					  
}


// from the bourkster.
// https://gist.github.com/2724338
//--------------------------------------------------------------
bool lineLineIntersectSegment(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4, ofVec3f &pa, ofVec3f &pb) {
	float mua = 0;
	float mub = 0;
	
	ofVec3f p13,p43,p21;
	
	float d1343,d4321,d1321,d4343,d2121;
	float numer,denom;
	p13 = p1 - p3;
	p43 = p4 - p3;
	
	
	if (ABS(p43.x) < FLT_EPSILON && ABS(p43.y) < FLT_EPSILON && ABS(p43.z) < FLT_EPSILON)
		return false;
	
	p21 = p2 - p1;
	
	if (ABS(p21.x) < FLT_EPSILON && ABS(p21.y) < FLT_EPSILON && ABS(p21.z) < FLT_EPSILON)
		return false;
	
	d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
	d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
	d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
	d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
	d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;
	
	denom = d2121 * d4343 - d4321 * d4321;
	if (ABS(denom) < FLT_EPSILON)
		return false;
	numer = d1343 * d4321 - d1321 * d4343;
	
	mua = numer / denom;
	mub = (d1343 + d4321 * mua) / d4343;
	
	pa = p1 + p21 * mua;
	pb = p3 + p43 * mub;
	
	return true;
}

// https://gist.github.com/2724338
ofVec3f lineLineIntersection(ofVec3f p1, ofVec3f p2, ofVec3f p3, ofVec3f p4) {
	ofVec3f pa, pb;
	lineLineIntersectSegment(p1,p2,p3,p4,pa,pb);
	return (pa+pb)/2.f;
}

void findCircle(const ofVec3f& a, const ofVec3f& b, const ofVec3f& c, ofVec3f& center, ofVec3f& normal, float& radius) {
	ofVec3f ab = a - b, cb = c - b;
	normal = ab.getCrossed(cb);
	ofVec3f abm = ab / 2, cbm = cb / 2;
	ofVec3f abo = abm.getRotated(90, normal), cbo = cbm.getRotated(90, normal);
	abm += b, cbm += b;
	center = lineLineIntersection(abm, abm + abo, cbm, cbm + cbo);
	radius = center.distance(b);
	normal.normalize();
}

void findSphere(const ofVec3f& a, const ofVec3f& b, const ofVec3f& c, const ofVec3f& d, ofVec3f& center, float& radius) {
	ofVec3f c1, c2, n1, n2;
	float r1, r2;
	findCircle(a, b, c, c1, n1, r1);
	findCircle(b, c, d, c2, n2, r2);
	center = lineLineIntersection(c1, c1 + n1, c2, c2 + n2);
	radius = center.distance(a);
}
