#pragma once

#include <GL\glew.h>
#include <iostream>
#include <fstream>

#include "maths.h"

namespace utils {
	class Shader {
	public:
		Shader();
		explicit Shader(const char* compute_shader_filename);
		Shader(const char* vertex_shader_filename, const char* fragment_shader_filename);
		Shader(const char* vertex_shader_filename, const char* fragment_shader_filename, const char* geom_shader_filename);
		Shader(const char* vertex_shader_filename, const char* tess_control_shader_filename, const char* tess_eval_shader_filename, const char* fragment_shader_filename);

		void use();
		void release();
		void destroy();

		void set_uniform(const char* name, const bool b);
		void set_uniform(const char* name, const float v);
		void set_uniform(const char* name, const int i);
		void set_uniform(const char* name, const maths::vec2& v);
		void set_uniform(const char* name, const maths::vec3& v);
		void set_uniform(const char* name, const maths::vec4& v);
		void set_uniform(const char* name, const maths::mat4& v);

		GLuint program;
		GLint uniform_handle(const char* name);

	private:
		std::string load_source(const char* filename);
		void compile(GLuint shader, const char* src);
		void link();

		const char* v_shader_filename;
		const char* f_shader_filename;
	};
}
