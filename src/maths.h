#pragma once

#include <ostream>
#include <string>
																													   
namespace maths {
	extern float PI;

	class vec2 {
	public:
		vec2() : n{0.f, 0.f} {}
		vec2(const float v) : n{v, v} {}
		vec2(const float x, const float y) : n{x, y} {}

		vec2& operator  = (const vec2& v) { x  = v.x; y  = v.y; return *this; }
		vec2& operator += (const vec2& v) { x += v.x; y += v.y; return *this; }
		vec2& operator -= (const vec2& v) { x -= v.x; y -= v.y; return *this; }
		vec2& operator *= (const float v) { x *= v; y *= v; return *this; }
		vec2& operator /= (const float v) { x /= v; y /= v; return *this; }

		inline       float& operator [] (int i)       { return n[i]; }
		inline const float& operator [] (int i) const { return n[i]; }

		friend bool operator == (const vec2& a, const vec2& b) { return a.x == b.x && a.y == b.y; }
		friend bool operator != (const vec2& a, const vec2& b) { return !(a == b); }

		friend vec2 operator + (const vec2& a, const vec2& b) { return { a.x + b.x, a.y + b.y }; }
		friend vec2 operator - (const vec2& a, const vec2& b) { return { a.x - b.x, a.y - b.y }; }
		friend vec2 operator * (const vec2& a, const float v) { return { a.x * v, a.y * v }; }
		friend vec2 operator / (const vec2& a, const float v) { return { a.x / v, a.y / v }; }
		friend vec2 operator / (const vec2& a, const vec2& b) { return { a.x / b.x, a.y / b.y}; }

		friend std::ostream& operator << (std::ostream& os, const vec2& v) { 
			os << "(" << v.x << ", " << v.y << ")"; 
			return os; 
		}

		friend std::string to_string(const vec2& v) {
			return std::to_string(v.x) + ", " + std::to_string(v.y);
		}

		union {
			float n[2];
			struct {
				float x;
				float y;
			};
		};
	};

	class vec3 {
	public:
		vec3() : n{0.f, 0.f, 0.f} {}
		vec3(const float v) : n{v, v, v} {}
		vec3(const float x, const float y, const float z) : n{x, y, z} {}
		vec3(const vec2& v, const float z) : n{v.x, v.y, z} {}
		
		vec2 XY() { return vec2{x, y}; }
		vec2 XZ() { return vec2{x, z}; }

		vec3& operator  = (const vec3& v) { x  = v.x; y  = v.y; z  = v.z; return *this; }
		vec3& operator += (const vec2& v) { x += v.x; z += v.y; return *this; }
		vec3& operator += (const vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec3& operator -= (const vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec3& operator *= (const float v) { x *= v; y *= v; z *= v; return *this; }
		vec3& operator /= (const float v) { x /= v; y /= v; z /= v; return *this; }

		inline       float& operator [] (int i)       { return n[i]; }
		inline const float& operator [] (int i) const { return n[i]; }

		friend bool operator == (const vec3& a, const vec3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
		friend bool operator != (const vec3& a, const vec3& b) { return !(a == b); }

		friend vec3 operator + (const vec3& a, const vec3& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
		friend vec3 operator - (const vec3& a, const vec3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
		friend vec3 operator / (const vec3& a, const float b) { return { a.x / b, a.y / b, a.z / b }; }
		friend vec3 operator * (const vec3& a, const float b) { return { a.x * b, a.y * b, a.z * b }; }
		friend vec3 operator * (const float a, const vec3& b) { return { b.x * a, b.y * a, b.z * a }; }

		friend std::ostream& operator << (std::ostream& os, const vec3& v) { 
			os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; 
			return os; 
		}

		union {
			float n[3];
			struct {
				float x;
				float y;
				float z;
			};
		};
	};
	
	class vec4 {
	public:
		vec4() : n{0.f, 0.f, 0.f, 0.f} {}
		vec4(const float v) : n{v, v, v, v} {}
		vec4(const float x, const float y, const float z, const float w) : n{x, y, z, w} {}
		vec4(const vec3& v, const float w) : n{ v.x, v.y, v.z, w } {}

		vec2 XY() { return vec2{x, y}; }
		vec3 XYZ() { return vec3(x, y, z); }

		vec4& operator  = (const vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
		vec4& operator += (const vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec4& operator -= (const vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec4& operator *= (const float v) { x *= v; y *= v; z *= v; w *= v; return *this; }
		vec4& operator /= (const float v) { x /= v; y /= v; z /= v; w /= v; return *this; }

		inline       float& operator [] (int i) { return n[i]; }
		inline const float& operator [] (int i) const { return n[i]; }

		friend bool operator == (const vec4& a, const vec4& b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
		friend bool operator != (const vec4& a, const vec4& b) { return !(a == b); }

		friend vec4 operator + (const vec4& a, const vec4& b) { return{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
		friend vec4 operator - (const vec4& a, const vec4& b) { return{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
		friend vec4 operator * (const vec4& a, const float v) { return{a.x * v, a.y * v, a.z * v, a.w * v}; }
		friend vec4 operator * (const float v, const vec4& a) { return{a.x * v, a.y * v, a.z * v, a.w * v }; }
		friend vec4 operator / (const vec4& a, const float v) { return{a.x / v, a.y / v, a.z / v, a.w / v}; }


		friend std::ostream& operator << (std::ostream& os, const vec4& v) { 
			os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; 
			return os; 
		}

		union {
			float n[4];
			struct {
				float x;
				float y;
				float z;
				float w;
			};
		};
	};

	class mat4 {
	public:
		mat4() : n{{1, 0, 0, 0},{0, 1, 0, 0},{0, 0, 1, 0},{0, 0, 0, 1}} {}
		mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) : n{a, b, c, d} {}

		mat4& operator = (const mat4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }

		inline       vec4& operator [] (int i)       { return n[i]; }
		inline const vec4& operator [] (int i) const { return n[i]; }

		friend std::ostream& operator << (std::ostream& os, const mat4& v) { 
			os << v.x << std::endl << v.y << std::endl << v.z << std::endl << v.w << std::endl;
			return os; 
		}

		void scale(const vec3& v) { x.x = v.x; y.y = v.y; z.z = v.z; }
		void translate(const vec3& v) { w.x = v.x; w.y = v.y; w.z = v.z; }

		union {
			vec4 n[4];
			struct {
				vec4 x;
				vec4 y;
				vec4 z;
				vec4 w;
			};
		};
	};

	bool almost_equal(float x, float y, float error_factor);
	bool almost_equal(const vec2& a, const vec2& b, float error_factor);

	float box2d_to_simulation_angle(const float angle);

	float cartesian_to_polar(const vec2& v);

	vec2 cross_product(const vec2& a, const vec2& b);
	vec3 cross_product(const vec3& a, const vec3& b);

	float determinant(const vec2& a, const vec2& b);

	float distance(const vec2& a, const vec2& b);
	float distance(const vec3& a, const vec3& b);
	float distance(const vec4& a, const vec4& b);

	float dot_product(const vec2& a, const vec2& b);
	float dot_product(const vec3& a, const vec3& b);
	float dot_product(const vec4& a, const vec4& b);

	float lerp(float a, float b, float t);
	vec3 lerp(vec3 a, vec3 b, float t);
	vec4 lerp(vec4 a, vec4 b, float t);

	float magnitude(const vec2& v);
	float magnitude(const vec3& v);
	float magnitude(const vec4& v);

	//float max(float x, float y);

	//float min(float x, float y);

	vec4 mult(const mat4& m, const vec4& v);
	mat4 mult(const mat4& a, const mat4& b);

	vec2 normalise(const vec2& v);
	vec3 normalise(const vec3& v);
	vec4 normalise(const vec4& v);
	
	mat4 orthographic_matrix(const vec2& resolution, float nZ, float fZ, mat4 m);

	bool point_triangle_intersect(const vec2& p, const vec2& a, const vec2& b, const vec2& c);
	bool point_segment_intersect(const vec2& p, const vec2& start, const vec2& o, const vec2& end, const float radius);
	bool point_quad_intersect(const vec2& p, float left, float right, float top, float bottom);

	vec2 polar_to_cartesian(float theta);

	mat4 rotate_x(float degrees);
	mat4 rotate_y(float degrees);
	mat4 rotate_z(float degrees);
	mat4 rotate(const vec3& rotation);

	mat4 scale(const vec3& size);

	float to_degrees(const float rads);
	
	float to_radians(const float degs);

	mat4 translate(const vec3& position);

	mat4 transpose(const mat4& m);
}