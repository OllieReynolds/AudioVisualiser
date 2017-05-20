#version 450

out vec4 colour;

uniform vec4 uniform_colour;

void main() {
	colour = uniform_colour;
}