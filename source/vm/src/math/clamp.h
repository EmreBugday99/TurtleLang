#pragma once

#define GENERATE_CLAMP(T) \
	void math_clamp_##T(T* src, T min, T max) \
	{ \
	if (*src < min)\
		*src = min;\
	else if (*src > max) \
		*src = max;\
	}