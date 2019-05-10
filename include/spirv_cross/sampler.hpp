/*
 * Copyright 2015-2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SPIRV_CROSS_SAMPLER_HPP
#define SPIRV_CROSS_SAMPLER_HPP

#include <vector>

#define textureProj texture
#define textureLod texture
#define textureProjLod texture
#define textureProjOffset textureOffset
#define textureProjLodOffset textureLodOffset

template <typename T>
struct samplerBase
{
        T data;
};

typedef samplerBase<glm::vec4> sampler1D;
typedef samplerBase<glm::vec4> sampler2D;
typedef samplerBase<glm::vec4> sampler3D;
typedef samplerBase<glm::vec4> samplerCube;
typedef samplerBase<glm::vec4> sampler2DRect;

typedef samplerBase<glm::vec4> sampler1DArray;
typedef samplerBase<glm::vec4> sampler2DArray;
typedef samplerBase<glm::vec4> samplerCubeArray;

typedef samplerBase<float> sampler1DShadow;
typedef samplerBase<float> sampler2DShadow;
typedef samplerBase<float> samplerCubeShadow;
typedef samplerBase<float> sampler2DRectShadow;

typedef samplerBase<float> sampler1DArrayShadow;
typedef samplerBase<float> sampler2DArrayShadow;
typedef samplerBase<float> samplerCubeArrayShadow;

// Base functions
//
// The scalars s1 and s2 could be bias, lod or compare. For the purposes of
// this module which just multiplies everything together, it doesn't matter
// which is which.

inline glm::vec4 textureOffset(const samplerBase<glm::vec4> &samp, const glm::vec4 &uv, const glm::ivec4 &offset, float s0, float s1)
{
        glm::vec4 v = samp.data * uv;
        v *= offset;
        v *= s0;
        v *= s1;
        return v;
}

inline float textureOffset(const samplerBase<float> &samp, const glm::vec4 &uv, const glm::ivec4 &offset, float s0, float s1)
{
        float v = samp.data * uv.x;
        v *= offset.x;
        v *= s0;
        v *= s1;
        return v;
}

// texture

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec4 &uv, float s0 = 1.0f, float s1 = 1.0f)
{
        ivec4 offset = ivec4(1);
	return textureOffset(samp, uv, offset, s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec3 &uv, float s0 = 1.0f, float s1 = 1.0f)
{
	return texture(samp, glm::vec4(uv, 1.0f), s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec2 &uv, float s0 = 1.0f, float s1 = 1.0f)
{
	return texture(samp, glm::vec4(uv, 1.0f, 1.0f), s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, float &uv, float s0 = 1.0f, float s1 = 1.0f)
{
	return texture(samp, glm::vec4(uv, 1.0f 1.0f, 1.0f), s0, s1);
}

// textureOffset

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, glm::ivec3 &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec3 &uv, glm::ivec3 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec3 &uv, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec3 &uv, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec2 &uv, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f), glm::ivec4(offset, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec2 &uv, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, 1.0f);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, float &uv, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, 1.0f);
}

// textureLodOffset

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, float lod, glm::ivec3 &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1), bias, lod);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, float lod, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1, 1), bias, lod);
}

template <typename T>
inline T textureOffset(const samplerBase<T> &samp, glm::vec4 &uv, float lod, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, uv, glm::ivec4(offset, 1, 1, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, glm::vec3 &uv, float lod, glm::ivec3 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, glm::vec3 &uv, float lod, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, glm::vec3 &uv, float lod, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, glm::vec2 &uv, float lod, glm::ivec2 &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f), glm::ivec4(offset, 1, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, glm::vec2 &uv, float lod, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, lod);
}

template <typename T>
inline T textureLodOffset(const samplerBase<T> &samp, float &uv, float lod, int &offset, float bias = 1.0f)
{
	return textureOffset(samp, glm::vec4(uv, 1.0f, 1.0f, 1.0f), glm::ivec4(offset, 1, 1, 1), bias, lod);
}

#endif
