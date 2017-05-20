#pragma once

#include "maths.h"
#include "utils.h"

#include <map>

using namespace maths;
using namespace utils;

struct Camera {
	Camera(const vec2& res = {});
	void update(std::map<int, Transform>& transforms);

	bool follow_vehicle;
	bool target_changed;
	
	int last_target_index;
	int current_target_index;
	
	float target_distance;
	float field_of_view;
	float aspect_ratio;
	
	vec2 resolution;
	vec2 depth_range_ortho;
	vec2 depth_range_persp;
	
	vec3 position_start;
	vec3 position_current;
	vec3 position_target;
	vec3 orientation_up;
	vec3 old_position;
	vec3 old_target;
	
	mat4 matrix_view;
	mat4 matrix_projection_persp;
	mat4 matrix_projection_ortho;

	float height;
	int index_list_position_current;
	std::vector<vec3> list_position_current;
};