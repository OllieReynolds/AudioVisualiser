#include "shader.h"

namespace utils {
	Shader::Shader() {
		v_shader_filename = "";
		f_shader_filename = "";
		program = 0;
	}

	Shader::Shader(const char* compute_shader_filename) {
		GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
		std::string src = load_source(compute_shader_filename);
		compile(computeShader, src.c_str());
		
		program = glCreateProgram();

		glAttachShader(program, computeShader);

		link();
		use();
	}

	Shader::Shader(const char* vertex_shader_filename, const char* fragment_shader_filename) {
		v_shader_filename = vertex_shader_filename;
		f_shader_filename = fragment_shader_filename;

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string v_src = load_source(vertex_shader_filename);
		compile(vertShader, v_src.c_str());

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string f_src = load_source(fragment_shader_filename);
		compile(fragShader, f_src.c_str());

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

		link();
		use();
	}

	Shader::Shader(const char* vertex_shader_filename, const char* fragment_shader_filename, const char* geom_shader_filename) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string v_src = load_source(vertex_shader_filename);
		compile(vertShader, v_src.c_str());

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string f_src = load_source(fragment_shader_filename);
		compile(fragShader, f_src.c_str());

		GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		std::string g_src = load_source(geom_shader_filename);
		compile(geomShader, g_src.c_str());

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glAttachShader(program, geomShader);

		link();
		use();
	}

	Shader::Shader(const char* vertex_shader_filename, const char* tess_control_shader_filename, const char* tess_eval_shader_filename, const char* fragment_shader_filename) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string v_src = load_source(vertex_shader_filename);
		compile(vertShader, v_src.c_str());

		GLuint tcShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		std::string tc_src = load_source(tess_control_shader_filename);
		compile(tcShader, tc_src.c_str());

		GLuint teShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		std::string te_src = load_source(tess_eval_shader_filename);
		compile(teShader, te_src.c_str());

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string f_src = load_source(fragment_shader_filename);
		compile(fragShader, f_src.c_str());

		program = glCreateProgram();

		glAttachShader(program, vertShader);
		glAttachShader(program, tcShader);
		glAttachShader(program, teShader);
		glAttachShader(program, fragShader);

		link();
		use();
	}

	void Shader::compile(GLuint shader, const char* src) {
		GLint status;
		GLchar infoLog[512];
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}
	}

	void Shader::link() {
		GLint status;
		GLchar infoLog[512];
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}
	}

	void Shader::use() {
		glUseProgram(program);
	}

	void Shader::release() {
		glUseProgram(0);
	}

	void Shader::destroy() {
		glDeleteProgram(program);
	}

	void Shader::set_uniform(const char* name, const bool b) {
		GLuint uniform_location = uniform_handle(name);
		glUniform1i(uniform_location, b);
	}

	void Shader::set_uniform(const char* name, const float v) {
		GLuint uniform_location = uniform_handle(name);
		glUniform1f(uniform_location, v);
	}

	void Shader::set_uniform(const char* name, const int i) {
		GLuint uniform_location = uniform_handle(name);
		glUniform1i(uniform_location, i);
	}

	void Shader::set_uniform(const char* name, const maths::vec2& v) {
		GLuint uniform_location = uniform_handle(name);
		glUniform2fv(uniform_location, 1, &v[0]);
	}

	void Shader::set_uniform(const char* name, const maths::vec3& v) {
		GLuint uniform_location = uniform_handle(name);
		glUniform3fv(uniform_location, 1, &v[0]);
	}

	void Shader::set_uniform(const char* name, const maths::vec4& v) {
		GLuint uniform_location = uniform_handle(name);
		glUniform4fv(uniform_location, 1, &v[0]);
	}

	void Shader::set_uniform(const char* name, const maths::mat4& v) {
		GLuint uniform_location = uniform_handle(name);
		glUniformMatrix4fv(uniform_location, 1, GL_FALSE, &v[0][0]);
	}

	GLint Shader::uniform_handle(const char* name) {
		return glGetUniformLocation(program, name);
	}

	std::string Shader::load_source(const char* filename) {
		std::ifstream input{filename};
		return std::string{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
	}
}
