#include "maths.h"

namespace maths {
	float PI = 3.14159265358979f;

	vec2 polar_to_cartesian(float theta) {
		float c = cos(theta);
		float s = sin(theta);
		return vec2{c, s};
	}

	float cartesian_to_polar(const vec2& v) {
		return atan2(v.y, v.x);
	}

	vec4 mult(const mat4& m, const vec4& v) {
		float x = (m.x.x * v.x) + (m.x.y * v.y) + (m.x.z * v.z) + m.x.w;
		float y = (m.y.x * v.x) + (m.y.y * v.y) + (m.y.z * v.z) + m.y.w;
		float z = (m.z.x * v.x) + (m.z.y * v.y) + (m.z.z * v.z) + m.z.w;
		float w = (m.w.x * v.x) + (m.w.y * v.y) + (m.w.z * v.z) + m.w.w;
		
		return vec4{x, y, z, w};
	}

	mat4 mult(const mat4& a, const mat4& b) {
		float xx = a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x;
		float xy = a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y;
		float xz = a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z;
		float xw = a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w;

		float yx = a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x;
		float yy = a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y;
		float yz = a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z;
		float yw = a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w;

		float zx = a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x;
		float zy = a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y;
		float zz = a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z;
		float zw = a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w;

		float wx = a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x;
		float wy = a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y;
		float wz = a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z;
		float ww = a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w;
		
		return mat4{
			{xx, xy, xz, xw},
			{yx, yy, yz, yw},
			{zx, zy, zz, zw},
			{wx, wy, wz, ww}
		};
	}


	// http://totologic.blogspot.co.uk/2014/01/accurate-point-in-triangle-test.html
	bool point_triangle_intersect(const vec2& p, const vec2& a, const vec2& b, const vec2& c) {
		float div = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));

		float x = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y)) / div;
		float y = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y)) / div;
		float z = 1.f - x - y;

		return 
			0.f <= x && x <= 1.f && 
			0.f <= y && y <= 1.f && 
			0.f <= z && z <= 1.f;
	}

	float lerp(float a, float b, float t) {
		return (1 - t) * a + t * b;
	}

	vec3 lerp(vec3 a, vec3 b, float t) {
		return ((1.f - t) * b) + (t * a);
	}

	vec4 lerp(vec4 a, vec4 b, float t) {
		return ((1.f - t) * b) + (t * a);
	}

	bool almost_equal(float x, float y, float error_factor) {
		float diff = std::abs(x - y);
		return diff < error_factor;
	}

	bool almost_equal(const vec2& a, const vec2& b, float error_factor) {
		float diff_x = std::abs(a.x - b.x);
		float diff_y = std::abs(a.y - b.y);
		return diff_x < error_factor && diff_y < error_factor;
	}

	float box2d_to_simulation_angle(const float angle) {
		return (angle * (180.f / PI)) + 90.f;
	}

	vec2 cross_product(const vec2& a, const vec2& b) {
		return{

		};
	}

	vec3 cross_product(const vec3& a, const vec3& b) {
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	float determinant(const vec2& a, const vec2& b) {
		return (a.x * b.y) - (a.y * b.x);
	}

	float distance(const vec2& a, const vec2& b) {
		return sqrt(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y)
		);
	}

	float distance(const vec3& a, const vec3& b) {
		return sqrt(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y) +
			(a.z - b.z) * (a.z - b.z)
		);
	}

	float distance(const vec4& a, const vec4& b) {
		return sqrt(
			(a.x - b.x) * (a.x - b.x) +
			(a.y - b.y) * (a.y - b.y) +
			(a.z - b.z) * (a.z - b.z) +
			(a.w - b.w) * (a.w - b.w)
		);
	}

	float dot_product(const vec2& a, const vec2& b) { 
		return (a.x * b.x) + (a.y * b.y); 
	}

	float dot_product(const vec3& a, const vec3& b) { 
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); 
	}

	float dot_product(const vec4& a, const vec4& b) { 
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w); 
	}

	float magnitude(const vec2& v) { 
		return sqrt(v.x * v.x + v.y * v.y); 
	}

	float magnitude(const vec3& v) { 
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); 
	}

	float magnitude(const vec4& v) { 
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); 
	}

	vec2 normalise(const vec2& v) { 
		return (v == vec2{0.f}) ? v : v / magnitude(v); 
	}

	vec3 normalise(const vec3& v) { 
		return (v == vec3{0.f}) ? v : v / magnitude(v); 
	}

	vec4 normalise(const vec4& v) { 
		return (v == vec4{0.f}) ? v : v / magnitude(v); 
	}

	mat4 orthographic_matrix(const vec2& resolution, float nZ, float fZ, mat4 m) {
		m.x.x =  2.f / resolution.x;
		m.y.y =  2.f / resolution.y;
		m.z.z = -2.f / (fZ - nZ);

		m.w.x = -resolution.x / resolution.x;
		m.w.y = -resolution.y / resolution.y;
		m.w.z = -(fZ + nZ) / (fZ - nZ);
		return m;
	}

	bool check_clockwise(vec2 v1, vec2 v2) {
		return (-v1.x * v2.y) + (v1.y * v2.x) >= 0;
	}

	bool point_segment_intersect(const vec2& p, const vec2& start, const vec2& o, const vec2& end, const float radius) {
		float origin_to_point = distance(o, p);

		bool b1 = origin_to_point <= radius;
		bool b2 = !check_clockwise(start, p - o);
		bool b3 = check_clockwise(end, p - o);

		return b1 && b2 && b3;
	}

	bool point_quad_intersect(const vec2& p, float left, float right, float top, float bottom) {
		return p.x >= left && p.x <= right && p.y >= bottom && p.y <= top;
	}

	mat4 rotate(const vec3& rotation) {
		mat4 x = rotate_x(rotation.x);
		mat4 y = rotate_y(rotation.y);
		mat4 z = rotate_z(rotation.z);

		return mult(mult(z, y), x);
	}

	mat4 rotate_x(float degrees) {
		float rads = degrees * (PI / 180.f);

		return mat4{
			{1.f, 0.f,        0.f,       0.f},
			{0.f, cos(rads), -sin(rads), 0.f},
			{0.f, sin(rads),  cos(rads), 0.f},
			{0.f, 0.f,        0.f,       1.f}
		};
	}

	mat4 rotate_y(float degrees) {
		float rads = degrees * (PI / 180.f);

		return mat4{
			{cos(rads),  0.f,       sin(rads), 0.f},
			{0.f,        1.f,       0.f,       0.f},
			{-sin(rads), 0.f,       cos(rads), 0.f},
			{0.f,        0.f,       0.f,       1.f}
		};
	}

	mat4 rotate_z(float degrees) {
		float rads = degrees * (PI / 180.f);

		return mat4{
			{cos(rads), -sin(rads), 0.f, 0.f},
			{sin(rads),  cos(rads), 0.f, 0.f},
			{0.f,        0.f,       1.f, 0.f},
			{0.f,        0.f,       0.f, 1.f}
		};
	}

	mat4 translate(const vec3& position) {
		mat4 m = {};
		m.x.w = position.x;
		m.y.w = position.y;
		m.z.w = position.z;
		return m;
	}

	mat4 scale(const vec3& size) {
		mat4 m = {};
		m.x.x = size.x;
		m.y.y = size.y;
		m.z.z = size.z;
		return m;
	}

	float to_degrees(const float rads) {
		return rads * 180.f / PI;
	}

	float to_radians(const float degs) {
		return degs / 180.f * PI;
	}

	mat4 transpose(const mat4& m) {
		return mat4{
			{m.x.x, m.y.x, m.z.x, m.w.x},
			{m.x.y, m.y.y, m.z.y, m.w.y},
			{m.x.z, m.y.z, m.z.z, m.w.z},
			{m.x.w, m.y.w, m.z.w, m.w.w}
		};
	}
}