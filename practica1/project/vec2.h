#pragma once

#include <cmath>

class vec2 {
private:
	float x, y;

public:
	vec2() {
		x = y = 0;
	}
	vec2(float _x, float _y){
		x = _x;
		y = _y;
	}
	vec2(const vec2& v) {
		x = v.x;
		y = v.y;
	}

	vec2 sum(float value) {

		return vec2(x + value, y + value);
	}

	void multiply(float value) {
		x = x * value;
		y = y * value;
	}

	float length() const {
		return std::sqrt(x * x + y * y);
	}

	vec2& normalize() {
		if (length() == 0) {
			return *this;
		}
		else {
			
			return vec2(x / length(), y / length());;
		}
	}

	float dist(vec2 v) const {
		vec2 d(v.x - x, v.y - y);
		return d.length();
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	vec2 ortho() const {
		return vec2(y, -x);
	}

	static float dot(vec2 v1, vec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(vec2 v1, vec2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

};

