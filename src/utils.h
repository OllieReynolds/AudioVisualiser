#pragma once

#include <chrono>
#include <random>
#include <fstream>

#include "maths.h"

namespace utils {
	using namespace maths;

	struct dimensions {
		int width, height;
	};

	struct Light {
		vec3 position;
		vec3 colour;
		float intensity;
	};

	struct Transform {
		vec3 position;
		vec3 size;
		vec3 rotation;
	};

	static void output(const char* filename, const std::string& str) {
		std::ofstream file;
		file.open(filename, std::ios::app);
		file << str << std::endl;
		file.close();
	}

	static int line_count(const char* filename) {
		int count = 0;
		std::string line;
		std::ifstream ifs(filename, std::istream::in);

		while (std::getline(ifs, line))
			count++;

		ifs.close();
		return count;
	}

	static dimensions png_dimensions(const char* filename) {
		std::ifstream file(filename, std::ios_base::binary | std::ios_base::in);

		file.seekg(16, std::ios_base::cur);

		__int32 width;
		__int32 height;

		file.read((char*)&width, 4);
		file.read((char*)&height, 4);

		file.close();

		return{ (int)_byteswap_ulong(width), (int)_byteswap_ulong(height) };
	}

	static float elapsed_time() {
		using namespace std::chrono;
		static time_point<steady_clock> start = steady_clock::now();
		return duration_cast<duration<float>>(steady_clock::now() - start).count();
	}

	static float gen_random(float min = 0.f, float max = 10.f) {
		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(mt);
	}

	static vec2 gen_random(vec2 min, vec2 max) {
		float x = gen_random(min.x, max.x);
		float y = gen_random(min.y, max.y);
		return vec2(x, y);
	}

	static std::string friendly_float(const float f, int num_digits) {
		std::string str = std::to_string(f);
		str.erase(str.begin() + num_digits, str.end());
		return str;
	}

	static std::string friendly_float(const int i, int num_digits) {
		std::string str = std::to_string(i);
		if (i < 10) str = "0" + str;
		return str;
	}

	static mat4 gen_model_matrix(const vec2& size, const vec2& position) {
		mat4 s = scale(vec3{size, 0.f});
		mat4 t = transpose(translate(vec3{position, 0.f}));
		return mult(s, t);
	}

	static mat4 gen_model_matrix(const vec3& size, const vec3& position, float rotation) {
		mat4 s = scale(size);
		mat4 t = transpose(translate(position));
		mat4 r = rotate_y(rotation);
		return mult(mult(s, r), t);
	}

	static mat4 gen_model_matrix(const vec3& size, const vec3& position, const vec3& rotation) {
		mat4 s = scale(size);
		mat4 t = transpose(translate(position));
		mat4 r = rotate(rotation);
		
		return mult(mult(s, r), t);
	}

	static mat4 gen_model_matrix(const Transform& transform) {
		mat4 s = scale(transform.size);
		mat4 t = transpose(translate(transform.position));
		mat4 r = rotate(transform.rotation);

		return mult(mult(s, r), t);
	}

	namespace config {
		extern vec2 resolution;
		extern bool fullscreen;
	}

	namespace colour {
		extern vec4 black;
		extern vec4 white;
		extern vec4 red;
		extern vec4 green;
		extern vec4 blue;
		extern vec4 yellow;
		extern vec4 grey;
		extern vec4 dark_grey;
	};

	namespace mesh {
		extern float quad_points_textured[20];
		extern float cube_points[108];
		extern float cube_vertices_normals[216];

		extern float triangle_points_textured[15];

		extern vec3 quad_points[4];
		extern vec4 quad_points_and_uvs[4];
	}

	namespace shared {
		static mat4 perspective_matrix(float fov, float aspect, float _near, float _far) {
			float b = 1.f / tan(to_radians(fov) / 2.f);
			float a = b / aspect;

			return mat4{
				{ a, 0.f, 0.f, 0.f },
				{ 0.f, b , 0.f, 0.f },
				{ 0.f, 0.f, (_far + _near) / (_near - _far), -1.f },
				{ 0.f, 0.f, (_far * _near) / (_near - _far), 0.f }
			};
		}

	

		static mat4 view_matrix(const vec3& eye, const vec3& target, const vec3& up_rel) {
			vec3 forward = normalise(eye - target);
			vec3 right = normalise(cross_product(up_rel, forward));
			vec3 up = cross_product(forward, right);

			mat4 viewMatrix = {
				vec4(right.x, up.x, forward.x, 0),
				vec4(right.y, up.y, forward.y, 0),
				vec4(right.z, up.z, forward.z, 0),
				vec4(-dot_product(right, eye), -dot_product(up, eye), -dot_product(forward, eye),  1)
			};

			return viewMatrix;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// http://gamedev.stackexchange.com/questions/21096/what-is-an-efficient-2d-line-segment-versus-triangle-intersection-test
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/* Check whether P and Q lie on the same side of line AB */
		static float Side(vec2 p, vec2 q, vec2 a, vec2 b)
		{
			float z1 = (b.x - a.x) * (p.y - a.y) - (p.x - a.x) * (b.y - a.y);
			float z2 = (b.x - a.x) * (q.y - a.y) - (q.x - a.x) * (b.y - a.y);
			return z1 * z2;
		}

		/* Check whether segment P0P1 intersects with triangle t0t1t2 */
		static bool Intersecting(vec2 p0, vec2 p1, vec2 t0, vec2 t1, vec2 t2)
		{
			/* Check whether segment is outside one of the three half-planes
			* delimited by the triangle. */
			float f1 = Side(p0, t2, t0, t1), f2 = Side(p1, t2, t0, t1);
			float f3 = Side(p0, t0, t1, t2), f4 = Side(p1, t0, t1, t2);
			float f5 = Side(p0, t1, t2, t0), f6 = Side(p1, t1, t2, t0);
			/* Check whether triangle is totally inside one of the two half-planes
			* delimited by the segment. */
			float f7 = Side(t0, t1, p0, p1);
			float f8 = Side(t1, t2, p0, p1);

			/* If segment is strictly outside triangle, or triangle is strictly
			* apart from the line, we're not intersecting */
			if ((f1 < 0 && f2 < 0) || (f3 < 0 && f4 < 0) || (f5 < 0 && f6 < 0)
				|| (f7 > 0 && f8 > 0))
				return false;

			/* If segment is aligned with one of the edges, we're overlapping */
			if ((f1 == 0 && f2 == 0) || (f3 == 0 && f4 == 0) || (f5 == 0 && f6 == 0))
				return true;

			/* If segment is outside but not strictly, or triangle is apart but
			* not strictly, we're touching */
			if ((f1 <= 0 && f2 <= 0) || (f3 <= 0 && f4 <= 0) || (f5 <= 0 && f6 <= 0)
				|| (f7 >= 0 && f8 >= 0))
				return true;

			/* If both segment points are strictly inside the triangle, we
			* are not intersecting either */
			if (f1 > 0 && f2 > 0 && f3 > 0 && f4 > 0 && f5 > 0 && f6 > 0)
				return false;

			/* Otherwise we're intersecting with at least one edge */
			return true;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	};
};