#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <bass.h>
#include <cstdio>

#include "camera.h"
#include "shader.h"

const int FFT_SAMPLES = 1024;
const int RES_X = 800;
const int RES_Y = 600;
const int NUM_BINS = 512;

const float NUM_BINSf = (float)NUM_BINS;
const float FFT_SAMPLESf = (float)FFT_SAMPLES;
const float RES_Xf = (float)RES_X;
const float RES_Yf = (float)RES_Y;
const float FFT_SCALEf = 5.f * RES_Xf;
const float	FFT_SAMPLE_RANGEf = FFT_SAMPLESf / NUM_BINSf;
const float bin_heightf = (RES_Yf / NUM_BINSf);
const float bin_distancef = 1.5;
const float bin_pos_xf = RES_Xf * 0.5f;

const char* title = "demo";
const char* tune = "music/Rolemusic_-_pl4y1ng.mp3";

static void exit_error(const char* fmt, ...) 
{
	char tmp[4096];
	va_list va;
	va_start(va, fmt);
	vsnprintf(tmp, sizeof(tmp), fmt, va);
	va_end(va);

	fprintf(stderr, "*** Application Error: %s\n", fmt);

	exit(EXIT_FAILURE);
}

GLFWwindow* glfw_init()
{
	// Check lib initialised successfully
	if (!glfwInit())
		exit_error("Failed to init Glew");

	// Set window parameters
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

	// Create the window
	int count;
	GLFWwindow* window = glfwCreateWindow(RES_X, RES_Y, title, NULL, NULL);
	
	// Check window creation successful
	if (!window) {
		glfwTerminate();
		exit_error("Failed to create GLFW window");
	}

	// Make window context active
	glfwMakeContextCurrent(window);

	return window;
}

void glew_init()
{
	glewExperimental = GL_TRUE;

	// Check glew initialised successfully
	if (glewInit() != GLEW_OK)
		exit_error("Glew failed to initialise");
}

HSTREAM bass_init() 
{
	if (!BASS_Init(-1, 44100, 0, 0, 0))
		exit_error("Bass failed to initialise");
	
	HSTREAM stream;
	stream = BASS_StreamCreateFile(false, tune, 0, 0, BASS_STREAM_PRESCAN);
	
	if (!stream)
		exit_error("Bass failed to open tune");
	
	BASS_Start();
	BASS_ChannelPlay(stream, false);
	
	return stream;
}

int main(int argc, char* argv[])
{
	// Init external libraries
	GLFWwindow* window = glfw_init();
	glew_init();
	HSTREAM stream = bass_init();
	
	// Init OpenGL data
	GLuint vao, vbo;
	Shader shader_2D{ "shaders/v.uniform_MP.glsl", "shaders/f.uniform_colour.glsl" };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh::quad_points_textured), &mesh::quad_points_textured, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// Init the camera
	Camera cam({ RES_Xf, RES_Yf });

	// Init Bin arrays
	float oldbins[NUM_BINS] = { 0.f };
	float bins[NUM_BINS] = { 0.f };


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get the FFT
		float fft[FFT_SAMPLES];
		BASS_ChannelGetData(stream, fft, BASS_DATA_FFT2048);
                for (int i = 0; i < FFT_SAMPLES; i++)
                        fft[i] = sqrt(fft[i]);

                // Normalise FFT values for consistent scaling
                float max_fft = 0.f;
                for (int i = 0; i < FFT_SAMPLES; i++)
                        if (fft[i] > max_fft)
                                max_fft = fft[i];
                if (max_fft > 0.f)
                        for (int i = 0; i < FFT_SAMPLES; i++)
                                fft[i] = (fft[i] / max_fft) * FFT_SCALEf;

		// Update the old bins
		std::copy(bins, bins + NUM_BINS, oldbins);

		// Update the new bins
		for (int i = 0; i < NUM_BINS; i++) {
			// Reset the bin array representing next FFT samples
			bins[i] = 0.f;

			// Get upper and lower values for FFT sampling
			int lower = roundf(FFT_SAMPLE_RANGEf * (float)(i));
			int upper = roundf(FFT_SAMPLE_RANGEf * (float)(i + 1));

			// Average of FFT values is the new value for that bin
                        for (int j = lower; j < upper; j++)
                                bins[i] += fft[j];
                        int sample_count = upper - lower;
                        if (sample_count > 0)
                                bins[i] /= static_cast<float>(sample_count);

			// Average the new bin value with the previous value for smoother display
			bins[i] = (bins[i] + oldbins[i]) * 0.5f;

			// Draw quads representing each bin's intensity
			float b = (bin_heightf * 0.5f) + (i * bin_heightf);
			float relative_loudness = bins[i] / 400.f;
			vec4 col = lerp(utils::colour::red, utils::colour::green, relative_loudness);

			glBindVertexArray(vao);
			shader_2D.use();
			shader_2D.set_uniform("uniform_colour", col);
			shader_2D.set_uniform("projection", cam.matrix_projection_ortho);
			shader_2D.set_uniform("model", utils::gen_model_matrix({ bins[i], bin_heightf }, { bin_pos_xf, b }));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
			shader_2D.release();
		}

		// Quit if the tune ended
		if (BASS_ErrorGetCode() == BASS_ERROR_ENDED)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Cleanup
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	shader_2D.destroy();

	BASS_StreamFree(stream);
	BASS_Free();

	glfwTerminate();

	return 0;
}