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

// The scalars s1 and s2 could be bias, lod or compare. For the purposes of
// this module which just multiplies everything together, it doesn't matter
// which is which.

inline glm::vec4 texture(const samplerBase<glm::vec4> &samp, const glm::vec4 &uv, float s0, float s1)
{
        glm::vec4 v = samp.data * uv;
        v *= s0;
        v *= s1;
        return v;
}

inline float texture(const samplerBase<float> &samp, const glm::vec4 &uv, float s0, float s1)
{
        float v = samp.data * uv.x;
        v *= s0;
        v *= s1;
        return v;
}

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec4 &uv, float s0 = 1.0f, float s1 = 1.0)
{
	return texture(samp, uv, s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec3 &uv, float s0 = 1.0f, float s1 = 1.0)
{
	return texture(samp, glm::vec4(uv, 1.0), s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, const glm::vec2 &uv, float s0 = 1.0f, float s1 = 1.0)
{
	return texture(samp, glm::vec4(uv, 1.0, 1.0), s0, s1);
}

template <typename T>
inline T texture(const samplerBase<T> &samp, float &uv, float s0 = 1.0f, float s1 = 1.0)
{
	return texture(samp, glm::vec4(uv, 1.0 1.0, 1.0), s0, s1);
}

#endif
