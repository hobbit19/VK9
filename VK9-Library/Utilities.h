/*
Copyright(c) 2016 Christopher Joseph Dean Schaefer

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#ifndef UTILITIES_H
#define UTILITIES_H

//#include "resource.h"
#include "CTypes.h"
#include "d3d9.h" // Base class: IDirect3DDevice9
#include "LogManager.h"

#include <vulkan/vk_sdk_platform.h>
#include <vulkan/vulkan.hpp>

#include <Eigen/Dense>

#include <memory>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <string>
#include <locale> 

#ifndef _MSC_VER
// Used D3D9Ex constants, missing in MinGW

#define D3DFMT_D32_LOCKABLE 84
#define D3DFMT_S8_LOCKABLE  85

#define D3DFMT_A1                  118
#define D3DFMT_A2B10G10R10_XR_BIAS 119
#define D3DFMT_BINARYBUFFER        199

#define D3DBLEND_SRCCOLOR2    16
#define D3DBLEND_INVSRCCOLOR2 17
#endif

#define D3DCOLOR_A(dw) (((float)(((dw) >> 24) & 0xFF)) / 255.0f)
#define D3DCOLOR_R(dw) (((float)(((dw) >> 16) & 0xFF)) / 255.0f)
#define D3DCOLOR_G(dw) (((float)(((dw) >> 8) & 0xFF)) / 255.0f)
#define D3DCOLOR_B(dw) (((float)(((dw) >> 0) & 0xFF)) / 255.0f)

#define D3DFMT_INTZ ((D3DFORMAT)(MAKEFOURCC('I','N','T','Z')))
#define D3DFMT_RAWZ ((D3DFORMAT)(MAKEFOURCC('R','A','W','Z')))
#define D3DFMT_DF24 ((D3DFORMAT)(MAKEFOURCC('D','F','2','4')))
#define D3DFMT_DF16 ((D3DFORMAT)(MAKEFOURCC('D','F','1','6')))
#define D3DFMT_INST ((D3DFORMAT)(MAKEFOURCC('I','N','S','T')))
#define D3DFMT_NULL ((D3DFORMAT)(MAKEFOURCC('N','U','L','L')))

#define SPIR_V_MAX_ID 4194303
#define ESTIMATED_SPIR_V_PER_DXBC_OP 5
#define MAX_DXBC_PHASES 2

void MergeState(const DeviceState& sourceState, DeviceState& targetState, D3DSTATEBLOCKTYPE type = D3DSBT_ALL, BOOL onlyIfExists = false);

HMODULE GetModule(HMODULE module = 0);

const std::string mResultStrings[] =
{
	"Unknown",
	"VK_SUCCESS",
	"VK_NOT_READY",
	"VK_TIMEOUT",
	"VK_EVENT_SET",
	"VK_EVENT_RESET",
	"VK_INCOMPLETE",
	"VK_ERROR_OUT_OF_HOST_MEMORY",
	"VK_ERROR_OUT_OF_DEVICE_MEMORY",
	"VK_ERROR_INITIALIZATION_FAILED",
	"VK_ERROR_DEVICE_LOST",
	"VK_ERROR_MEMORY_MAP_FAILED",
	"VK_ERROR_LAYER_NOT_PRESENT",
	"VK_ERROR_EXTENSION_NOT_PRESENT",
	"VK_ERROR_FEATURE_NOT_PRESENT",
	"VK_ERROR_INCOMPATIBLE_DRIVER",
	"VK_ERROR_TOO_MANY_OBJECTS",
	"VK_ERROR_FORMAT_NOT_SUPPORTED",
	"VK_ERROR_FRAGMENTED_POOL",
	"VK_ERROR_SURFACE_LOST_KHR",
	"VK_ERROR_NATIVE_WINDOW_IN_USE_KHR",
	"VK_SUBOPTIMAL_KHR",
	"VK_ERROR_OUT_OF_DATE_KHR",
	"VK_ERROR_INCOMPATIBLE_DISPLAY_KHR",
	"VK_ERROR_VALIDATION_FAILED_EXT",
	"VK_ERROR_INVALID_SHADER_NV",
	"VK_ERROR_OUT_OF_POOL_MEMORY_KHR",
	"VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR",
	"VK_ERROR_NOT_PERMITTED_EXT"
};

inline const std::string& GetResultString(VkResult result) noexcept
{
	switch (result)
	{
	case VK_SUCCESS:
		return mResultStrings[1];
	case VK_NOT_READY:
		return mResultStrings[2];
	case VK_TIMEOUT:
		return mResultStrings[3];
	case VK_EVENT_SET:
		return mResultStrings[4];
	case VK_EVENT_RESET:
		return mResultStrings[5];
	case VK_INCOMPLETE:
		return mResultStrings[6];
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		return mResultStrings[7];
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		return mResultStrings[8];
	case VK_ERROR_INITIALIZATION_FAILED:
		return mResultStrings[9];
	case VK_ERROR_DEVICE_LOST:
		return mResultStrings[10];
	case VK_ERROR_MEMORY_MAP_FAILED:
		return mResultStrings[11];
	case VK_ERROR_LAYER_NOT_PRESENT:
		return mResultStrings[12];
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		return mResultStrings[13];
	case VK_ERROR_FEATURE_NOT_PRESENT:
		return mResultStrings[14];
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		return mResultStrings[15];
	case VK_ERROR_TOO_MANY_OBJECTS:
		return mResultStrings[16];
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		return mResultStrings[17];
	case VK_ERROR_FRAGMENTED_POOL:
		return mResultStrings[18];
	case VK_ERROR_SURFACE_LOST_KHR:
		return mResultStrings[19];
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		return mResultStrings[20];
	case VK_SUBOPTIMAL_KHR:
		return mResultStrings[21];
	case VK_ERROR_OUT_OF_DATE_KHR:
		return mResultStrings[22];
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		return mResultStrings[23];
	case VK_ERROR_VALIDATION_FAILED_EXT:
		return mResultStrings[24];
	case VK_ERROR_INVALID_SHADER_NV:
		return mResultStrings[25];
	case VK_ERROR_OUT_OF_POOL_MEMORY_KHR:
		return mResultStrings[26];
	case VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR:
		return mResultStrings[27];
	case VK_ERROR_NOT_PERMITTED_EXT:
		return mResultStrings[28];
	default:
		return mResultStrings[0];
	}
}

template < typename T, size_t arraySize>
vk::ShaderModule LoadShaderFromConst(vk::Device device, const T(&data)[arraySize])
{
	vk::ShaderModule module;
	vk::ShaderModuleCreateInfo moduleCreateInfo;
	moduleCreateInfo.codeSize = arraySize * sizeof(T);
	moduleCreateInfo.pCode = (const uint32_t*)data; //Why is this uint32_t* if the size is in bytes?

	vk::Result result = device.createShaderModule(&moduleCreateInfo, nullptr, &module);
	if (result != vk::Result::eSuccess)
	{
		Log(fatal) << "LoadShaderFromConst vkCreateShaderModule failed with return code of " << GetResultString((VkResult)result) << std::endl;
	}

	return module;
}

vk::ShaderModule LoadShaderFromFile(vk::Device device, const char *filename);
vk::ShaderModule LoadShaderFromResource(vk::Device device, WORD resource);

void ReallyCopyImage(vk::CommandBuffer commandBuffer, vk::Image srcImage, vk::Image dstImage, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t depth, uint32_t srcMip, uint32_t dstMip, uint32_t srcLayer, uint32_t dstLayer);
void ReallySetImageLayout(vk::CommandBuffer commandBuffer, vk::Image image, vk::ImageAspectFlags aspectMask, vk::ImageLayout oldImageLayout, vk::ImageLayout newImageLayout, uint32_t levelCount, uint32_t mipIndex, uint32_t layerCount);

inline uint32_t FindMemoryType(vk::PhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeFilter, vk::MemoryPropertyFlagBits properties)
{
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	return 0;
}

inline uint32_t FindMemoryType(VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	return 0;
}

inline bool GetMemoryTypeFromProperties(vk::PhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeBits, const vk::MemoryPropertyFlags& requirements_mask, uint32_t *typeIndex)
{
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
	{
		if ((typeBits & 1) == 1)
		{
			if ((memoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}

	return false;
}

inline bool GetMemoryTypeFromProperties(vk::PhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeBits, vk::MemoryPropertyFlagBits requirements_mask, uint32_t *typeIndex)
{
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
	{
		if ((typeBits & 1) == 1)
		{
			if ((memoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}

	return false;
}

inline bool GetMemoryTypeFromProperties(VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex)
{
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
	{
		if ((typeBits & 1) == 1)
		{
			if ((memoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}

	return false;
}

//D3DDECLTYPE

inline vk::Format ConvertDeclType(D3DDECLTYPE input) noexcept
{
	vk::Format output = (vk::Format)VK_FORMAT_UNDEFINED;
	//TODO: finish mapping.
	switch (input)
	{
	case D3DDECLTYPE_FLOAT1: // 1D float expanded to (value, 0., 0., 1.)
		output = (vk::Format)VK_FORMAT_R32_SFLOAT;
		break;
	case D3DDECLTYPE_FLOAT2:  // 2D float expanded to (value, value, 0., 1.)
		output = (vk::Format)VK_FORMAT_R32G32_SFLOAT;
		break;
	case D3DDECLTYPE_FLOAT3: // 3D float expanded to (value, value, value, 1.)
		output = (vk::Format)VK_FORMAT_R32G32B32_SFLOAT;
		break;
	case D3DDECLTYPE_FLOAT4:  // 4D float
		output = (vk::Format)VK_FORMAT_R32G32B32A32_SFLOAT;
		break;
	case D3DDECLTYPE_D3DCOLOR:  // 4D packed unsigned bytes mapped to 0. to 1. range
		output = (vk::Format)VK_FORMAT_B8G8R8A8_UINT;
		break; // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
	case D3DDECLTYPE_UBYTE4: // 4D unsigned byte
		output = (vk::Format)VK_FORMAT_R8G8B8A8_UINT;
		break;
	case D3DDECLTYPE_SHORT2:  // 2D signed short expanded to (value, value, 0., 1.)
		output = (vk::Format)VK_FORMAT_R16G16_SINT;
		break;
	case D3DDECLTYPE_SHORT4:  // 4D signed short
		output = (vk::Format)VK_FORMAT_R16G16B16A16_SINT;
		break;
	case D3DDECLTYPE_UBYTE4N:  // Each of 4 bytes is normalized by dividing to 255.0
		output = (vk::Format)VK_FORMAT_R8G8B8A8_UNORM;
		break;
	case D3DDECLTYPE_SHORT2N: // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
		output = (vk::Format)VK_FORMAT_R16G16_SNORM;
		break;
	case D3DDECLTYPE_SHORT4N:  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
		output = (vk::Format)VK_FORMAT_R16G16B16A16_SNORM;
		break;
	case D3DDECLTYPE_USHORT2N:  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
		output = (vk::Format)VK_FORMAT_R16G16_UNORM;
		break;
	case D3DDECLTYPE_USHORT4N:  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
		output = (vk::Format)VK_FORMAT_R16G16B16A16_UNORM;
		break;
	case D3DDECLTYPE_UDEC3:  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
		//The only 10 10 10 formats I see have four components not 3.
		break;
	case D3DDECLTYPE_DEC3N:  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
		//The only 10 10 10 formats I see have four components not 3.
		break;
	case D3DDECLTYPE_FLOAT16_2:  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
		output = (vk::Format)VK_FORMAT_R16G16_SFLOAT;
		break;
	case D3DDECLTYPE_FLOAT16_4:  // Four 16-bit floating point values
		output = (vk::Format)VK_FORMAT_R16G16B16A16_SFLOAT;
		break;
	case D3DDECLTYPE_UNUSED:  // When the type field in a decl is unused.
		output = (vk::Format)VK_FORMAT_UNDEFINED;
		break;
	default:
		break;
	}

	return output;
}

inline int32_t ConvertPrimitiveCountToVertexCount(D3DPRIMITIVETYPE primtiveType, int32_t primtiveCount) noexcept
{
	int32_t output;

	switch (primtiveType)
	{
	case D3DPT_POINTLIST:
		output = primtiveCount;
		break;
	case D3DPT_LINELIST:
		output = primtiveCount * 2;
		break;
	case D3DPT_LINESTRIP:
		output = primtiveCount + 1;
		break;
	case D3DPT_TRIANGLELIST:
		output = primtiveCount * 3;
		break;
	case D3DPT_TRIANGLESTRIP:
		output = primtiveCount + 2;
		break;
	case D3DPT_TRIANGLEFAN:
		output = primtiveCount + 2;
		break;
	default:
		output = primtiveCount;
		break;
	}

	return output;
}

inline void SetCulling(vk::PipelineRasterizationStateCreateInfo& pipelineRasterizationStateCreateInfo, D3DCULL input) noexcept
{
	switch (input)
	{
	case D3DCULL_NONE:
		pipelineRasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eNone;
		pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		break;
	case D3DCULL_CW:
		pipelineRasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
		pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eCounterClockwise;
		//pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		break;
	case D3DCULL_CCW:
		pipelineRasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eBack;
		pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		//pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eCounterClockwise;
		break;
	default:
		pipelineRasterizationStateCreateInfo.cullMode = vk::CullModeFlagBits::eNone;
		pipelineRasterizationStateCreateInfo.frontFace = vk::FrontFace::eClockwise;
		break;
	}
}

inline void SetCulling(VkPipelineRasterizationStateCreateInfo& pipelineRasterizationStateCreateInfo, D3DCULL input) noexcept
{
	switch (input)
	{
	case D3DCULL_NONE:
		pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
		pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		break;
	case D3DCULL_CW:
		pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
		pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		//pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		break;
	case D3DCULL_CCW:
		pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
		pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		//pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		break;
	default:
		pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
		pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		break;
	}
}

inline vk::SamplerAddressMode ConvertTextureAddress(D3DTEXTUREADDRESS input) noexcept
{
	vk::SamplerAddressMode output;

	switch (input)
	{
	case D3DTADDRESS_WRAP:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_REPEAT;
		break;
	case D3DTADDRESS_MIRROR:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		break;
	case D3DTADDRESS_CLAMP:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		break;
	case D3DTADDRESS_BORDER:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		break;
	case D3DTADDRESS_MIRRORONCE:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
		break;
	default:
		output = (vk::SamplerAddressMode)VK_SAMPLER_ADDRESS_MODE_REPEAT;
		break;
	}

	return output;
}

inline vk::SamplerMipmapMode ConvertMipmapMode(D3DTEXTUREFILTERTYPE input) noexcept
{
	vk::SamplerMipmapMode output;

	switch (input)
	{
	case D3DTEXF_NONE:	// filtering disabled (valid for mip filter only)
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_NEAREST; //revisit
		break;
	case D3DTEXF_POINT:	// nearest
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_NEAREST;
		break;
	case D3DTEXF_LINEAR:	// linear interpolation
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_LINEAR;
		break;
	case D3DTEXF_ANISOTROPIC:	// anisotropic
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_LINEAR; //revisit
		break;
	case D3DTEXF_PYRAMIDALQUAD:	// 4-sample tent
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_LINEAR; //revisit
		break;
	case D3DTEXF_GAUSSIANQUAD:	// 4-sample Gaussian
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_LINEAR; //revisit
		break;
	default:
		output = (vk::SamplerMipmapMode)VK_SAMPLER_MIPMAP_MODE_LINEAR; //revisit
		break;
	}

	return output;
}

inline vk::Filter ConvertFilter(D3DTEXTUREFILTERTYPE input) noexcept
{
	vk::Filter output;

	switch (input)
	{
	case D3DTEXF_NONE:	// filtering disabled (valid for mip filter only)
		output = (vk::Filter)VK_FILTER_NEAREST; //revisit
		break;
	case D3DTEXF_POINT:	// nearest
		output = (vk::Filter)VK_FILTER_NEAREST;
		break;
	case D3DTEXF_LINEAR:	// linear interpolation
		output = (vk::Filter)VK_FILTER_LINEAR;
		break;
	case D3DTEXF_ANISOTROPIC:	// anisotropic
		/*
		https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html
		If either magFilter or minFilter is VK_FILTER_CUBIC_IMG, anisotropyEnable must be VK_FALSE
		*/
		output = (vk::Filter)VK_FILTER_LINEAR;
		//output = VK_FILTER_CUBIC_IMG; //revisit
		break;
	case D3DTEXF_PYRAMIDALQUAD:	// 4-sample tent
		output = (vk::Filter)VK_FILTER_CUBIC_IMG; //revisit
		break;
	case D3DTEXF_GAUSSIANQUAD:	// 4-sample Gaussian
		output = (vk::Filter)VK_FILTER_CUBIC_IMG; //revisit
		break;
	default:
		output = (vk::Filter)VK_FILTER_NEAREST; //revisit
		break;
	}

	return output;
}

inline vk::PolygonMode ConvertFillMode(D3DFILLMODE input) noexcept
{
	vk::PolygonMode output;

	switch (input)
	{
	case D3DFILL_SOLID:
		output = (vk::PolygonMode)VK_POLYGON_MODE_FILL;
		break;
	case D3DFILL_POINT:
		output = (vk::PolygonMode)VK_POLYGON_MODE_POINT;
		break;
	case D3DFILL_WIREFRAME:
		output = (vk::PolygonMode)VK_POLYGON_MODE_LINE;
		break;
	default:
		output = (vk::PolygonMode)VK_POLYGON_MODE_FILL;
		break;
	}

	return output;
}

inline vk::PrimitiveTopology ConvertPrimitiveType(D3DPRIMITIVETYPE input) noexcept
{
	vk::PrimitiveTopology output;

	switch (input)
	{
	case D3DPT_POINTLIST:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		break;
	case D3DPT_LINELIST:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		break;
	case D3DPT_LINESTRIP:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		break;
	case D3DPT_TRIANGLELIST:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	case D3DPT_TRIANGLESTRIP:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		break;
	case D3DPT_TRIANGLEFAN:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		break;
	default:
		output = (vk::PrimitiveTopology)VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		break;
	}

	/* Types D3d9 doesn't support
		VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
		VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
		VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
	*/

	return output;
}

inline bool GetMemoryTypeFromProperties(const vk::PhysicalDeviceMemoryProperties& deviceMemoryProperties, uint32_t typeBits, vk::MemoryPropertyFlagBits requirements_mask, uint32_t *typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++) {
		if ((typeBits & 1) == 1) {
			// Type is available, does it match user properties?
			if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}

inline bool GetMemoryTypeFromProperties(const VkPhysicalDeviceMemoryProperties& deviceMemoryProperties, uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++) {
		if ((typeBits & 1) == 1) {
			// Type is available, does it match user properties?
			if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}

inline vk::Format ConvertFormat(D3DFORMAT format) noexcept
{
	/*
	https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/xhtml/vkspec.html#VkFormat
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb172558(v=vs.85).aspx
	*/
	switch (format)
	{
	case D3DFMT_UNKNOWN:
		return  (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_R8G8B8:
		return (vk::Format)VK_FORMAT_R8G8B8_UNORM;
	case D3DFMT_A8R8G8B8:
		return (vk::Format)VK_FORMAT_B8G8R8A8_UNORM;
	case D3DFMT_X8R8G8B8:
		/*
		There is technically no alpha so this may cause problems but I don't see anything that is a 100% match for this format in Vulkan.
		*/
		return (vk::Format)VK_FORMAT_B8G8R8A8_UNORM; //B8G8R8X8_UNORM
	case D3DFMT_R5G6B5:
		return (vk::Format)VK_FORMAT_R5G6B5_UNORM_PACK16; //Reall this is VK_FORMAT_B5G6R5_UNORM_PACK16 but Nvidia doesn't support that format as an attachment so we'll do it the other way around and remap.
	case D3DFMT_X1R5G5B5:
		return (vk::Format)VK_FORMAT_B5G5R5A1_UNORM_PACK16; //B5G5R5X1_UNORM
	case D3DFMT_A1R5G5B5:
		return (vk::Format)VK_FORMAT_B5G5R5A1_UNORM_PACK16;
	case D3DFMT_A4R4G4B4:
		return (vk::Format)VK_FORMAT_B4G4R4A4_UNORM_PACK16;
	case D3DFMT_R3G3B2:
		return (vk::Format)VK_FORMAT_UNDEFINED; //B2G3R3_UNORM:
	case D3DFMT_A8:
		return (vk::Format)VK_FORMAT_R8_UNORM; //A8_UNORM
	case D3DFMT_A8R3G3B2:
		return (vk::Format)VK_FORMAT_UNDEFINED; //B2G3R3A8_UNORM
	case D3DFMT_X4R4G4B4:
		return (vk::Format)VK_FORMAT_UNDEFINED; //B4G4R4X4_UNORM
	case D3DFMT_A2B10G10R10:
		return (vk::Format)VK_FORMAT_UNDEFINED; //R10G10B10A2_UNORM
	case D3DFMT_A8B8G8R8:
		return (vk::Format)VK_FORMAT_R8G8B8A8_UNORM;
	case D3DFMT_X8B8G8R8:
		return (vk::Format)VK_FORMAT_R8G8B8A8_UNORM; //R8G8B8X8_UNORM
	case D3DFMT_G16R16:
		return (vk::Format)VK_FORMAT_R16G16_UNORM;
	case D3DFMT_A2R10G10B10:
		return (vk::Format)VK_FORMAT_UNDEFINED; //B10G10R10A2_UNORM
	case D3DFMT_A16B16G16R16:
		return (vk::Format)VK_FORMAT_R16G16B16A16_UNORM;
	case D3DFMT_A8P8:
		return (vk::Format)VK_FORMAT_R8G8_UNORM; //P8_UINT_A8_UNORM
	case D3DFMT_P8:
		return (vk::Format)VK_FORMAT_R8_UINT; //P8_UINT
	case D3DFMT_L8:
		return (vk::Format)VK_FORMAT_R8_UNORM;
	case D3DFMT_A8L8:
		return (vk::Format)VK_FORMAT_R8G8_UNORM; //L8A8_UNORM
	case D3DFMT_A4L4:
		return (vk::Format)VK_FORMAT_UNDEFINED; //L4A4_UNORM
	case D3DFMT_V8U8:
		return (vk::Format)VK_FORMAT_R8G8_SNORM;
	case D3DFMT_L6V5U5:
		return (vk::Format)VK_FORMAT_UNDEFINED; //R5G5_SNORM_L6_UNORM
	case D3DFMT_X8L8V8U8:
		return (vk::Format)VK_FORMAT_UNDEFINED; //R8G8_SNORM_L8X8_UNORM
	case D3DFMT_Q8W8V8U8:
		return (vk::Format)VK_FORMAT_R8G8B8A8_SNORM;
	case D3DFMT_V16U16:
		return (vk::Format)VK_FORMAT_R16G16_SNORM;
	case D3DFMT_A2W10V10U10:
		return (vk::Format)VK_FORMAT_UNDEFINED; //R10G10B10_SNORM_A2_UNORM
	case D3DFMT_UYVY:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_R8G8_B8G8:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_YUY2:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_G8R8_G8B8:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_DXT1:
		return (vk::Format)VK_FORMAT_BC1_RGB_UNORM_BLOCK; //VK_FORMAT_BC1_RGB_UNORM_BLOCK
	case D3DFMT_DXT2:
		return (vk::Format)VK_FORMAT_BC2_UNORM_BLOCK; //VK_FORMAT_BC2_UNORM_BLOCK
	case D3DFMT_DXT3:
		return (vk::Format)VK_FORMAT_BC3_UNORM_BLOCK; //VK_FORMAT_BC3_UNORM_BLOCK
	case D3DFMT_DXT4:
		return (vk::Format)VK_FORMAT_BC4_UNORM_BLOCK; //VK_FORMAT_BC4_UNORM_BLOCK
	case D3DFMT_DXT5:
		return (vk::Format)VK_FORMAT_BC5_UNORM_BLOCK; //VK_FORMAT_BC5_UNORM_BLOCK
	case D3DFMT_D16_LOCKABLE:
		return (vk::Format)VK_FORMAT_D16_UNORM; //D16_LOCKABLE
	case D3DFMT_D32:
		return (vk::Format)VK_FORMAT_D32_SFLOAT; //D32_UNORM
	case D3DFMT_D15S1:
		return (vk::Format)VK_FORMAT_UNDEFINED; //S1_UINT_D15_UNORM
	case D3DFMT_D24S8:
		return (vk::Format)VK_FORMAT_D24_UNORM_S8_UINT;
	case D3DFMT_D24X8:
		return (vk::Format)VK_FORMAT_D24_UNORM_S8_UINT; //X8D24_UNORM
	case D3DFMT_D24X4S4:
		return (vk::Format)VK_FORMAT_UNDEFINED; //S4X4_UINT_D24_UNORM
	case D3DFMT_D16:
		return (vk::Format)VK_FORMAT_D16_UNORM;
	case D3DFMT_D32F_LOCKABLE:
		return (vk::Format)VK_FORMAT_D32_SFLOAT;
	case D3DFMT_D24FS8:
		return (vk::Format)VK_FORMAT_D24_UNORM_S8_UINT; //S8_UINT_D24_SFLOAT
#if !defined(D3D_DISABLE_9EX)
	case D3DFMT_D32_LOCKABLE:
		return (vk::Format)VK_FORMAT_D32_SFLOAT;
	case D3DFMT_S8_LOCKABLE:
		return (vk::Format)VK_FORMAT_S8_UINT;
#endif // !D3D_DISABLE_9EX
	case D3DFMT_L16:
		return (vk::Format)VK_FORMAT_R16_UNORM; //L16_UNORM
	case D3DFMT_VERTEXDATA:
		return (vk::Format)VK_FORMAT_UNDEFINED; //VERTEXDATA
	case D3DFMT_INDEX16:
		return (vk::Format)VK_FORMAT_R16_UINT;
	case D3DFMT_INDEX32:
		return (vk::Format)VK_FORMAT_R32_UINT;
	case D3DFMT_Q16W16V16U16:
		return (vk::Format)VK_FORMAT_R16G16B16A16_SNORM;
	case D3DFMT_MULTI2_ARGB8:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_R16F:
		return (vk::Format)VK_FORMAT_R16_SFLOAT;
	case D3DFMT_G16R16F:
		return (vk::Format)VK_FORMAT_R16G16_SFLOAT;
	case D3DFMT_A16B16G16R16F:
		return (vk::Format)VK_FORMAT_R16G16B16A16_SFLOAT;
	case D3DFMT_R32F:
		return (vk::Format)VK_FORMAT_R32_SFLOAT;
	case D3DFMT_G32R32F:
		return (vk::Format)VK_FORMAT_R32G32_SFLOAT;
	case D3DFMT_A32B32G32R32F:
		return (vk::Format)VK_FORMAT_R32G32B32A32_SFLOAT;
	case D3DFMT_CxV8U8:
		return (vk::Format)VK_FORMAT_R8G8_SNORM;
#if !defined(D3D_DISABLE_9EX)
	case D3DFMT_A1:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_A2B10G10R10_XR_BIAS:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	case D3DFMT_BINARYBUFFER:
		return (vk::Format)VK_FORMAT_UNDEFINED;
#endif // !D3D_DISABLE_9EX
	case D3DFMT_FORCE_DWORD:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	default:
		return (vk::Format)VK_FORMAT_UNDEFINED;
	}
}

inline D3DFORMAT ConvertFormat(vk::Format format) noexcept
{
	/*
	https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/xhtml/vkspec.html#VkFormat
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb172558(v=vs.85).aspx
	*/
	switch ((VkFormat)format)
	{
	case VK_FORMAT_UNDEFINED:
		return D3DFMT_UNKNOWN;
	case VK_FORMAT_R8G8B8_UNORM:
		return D3DFMT_R8G8B8;
	case VK_FORMAT_B8G8R8A8_UNORM:
		return D3DFMT_A8R8G8B8;
	case VK_FORMAT_B5G6R5_UNORM_PACK16:
		return D3DFMT_R5G6B5;
	case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
		return D3DFMT_A1R5G5B5;
	case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
		return D3DFMT_A4R4G4B4;
	case VK_FORMAT_R8G8B8A8_UNORM:
		return D3DFMT_A8B8G8R8;
	case VK_FORMAT_R16G16_UNORM:
		return D3DFMT_G16R16;
	case VK_FORMAT_R16G16B16A16_UNORM:
		return D3DFMT_A16B16G16R16;
	case VK_FORMAT_R8G8_SNORM:
		return D3DFMT_V8U8;
	case VK_FORMAT_R8G8B8A8_SNORM:
		return D3DFMT_Q8W8V8U8;
	case VK_FORMAT_R16G16_SNORM:
		return D3DFMT_V16U16;
	case VK_FORMAT_D24_UNORM_S8_UINT:
		return D3DFMT_D24S8;
	case VK_FORMAT_D16_UNORM:
		return D3DFMT_D16;
	case VK_FORMAT_D32_SFLOAT:
		return D3DFMT_D32F_LOCKABLE;
	case VK_FORMAT_R16_UINT:
		return D3DFMT_INDEX16;
	case VK_FORMAT_R32_UINT:
		return D3DFMT_INDEX32;
	case VK_FORMAT_R16G16B16A16_SNORM:
		return D3DFMT_Q16W16V16U16;
	case VK_FORMAT_R16_SFLOAT:
		return D3DFMT_R16F;
	case VK_FORMAT_R16G16_SFLOAT:
		return D3DFMT_G16R16F;
	case VK_FORMAT_R16G16B16A16_SFLOAT:
		return D3DFMT_A16B16G16R16F;
	case VK_FORMAT_R32_SFLOAT:
		return D3DFMT_R32F;
	case VK_FORMAT_R32G32_SFLOAT:
		return D3DFMT_G32R32F;
	case VK_FORMAT_R32G32B32A32_SFLOAT:
		return D3DFMT_A32B32G32R32F;
	default:
		return D3DFMT_UNKNOWN;
	}
}

inline size_t SizeOf(vk::Format format) noexcept
{
	switch (format)
	{
	case vk::Format::eUndefined: //VK_FORMAT_UNDEFINED,
		return 0;
	case vk::Format::eR4G4UnormPack8: //VK_FORMAT_R4G4_UNORM_PACK8,
		return 1;
	case vk::Format::eR4G4B4A4UnormPack16: //VK_FORMAT_R4G4B4A4_UNORM_PACK16,
		return 2;
	case vk::Format::eB4G4R4A4UnormPack16: //VK_FORMAT_B4G4R4A4_UNORM_PACK16,
		return 2;
	case vk::Format::eR5G6B5UnormPack16: //VK_FORMAT_R5G6B5_UNORM_PACK16,
		return 2;
	case vk::Format::eB5G6R5UnormPack16: //VK_FORMAT_B5G6R5_UNORM_PACK16,
		return 2;
	case vk::Format::eR5G5B5A1UnormPack16: //VK_FORMAT_R5G5B5A1_UNORM_PACK16,
		return 2;
	case vk::Format::eB5G5R5A1UnormPack16: //VK_FORMAT_B5G5R5A1_UNORM_PACK16,
		return 2;
	case vk::Format::eA1R5G5B5UnormPack16: //VK_FORMAT_A1R5G5B5_UNORM_PACK16,
		return 2;
	case vk::Format::eR8Unorm: //VK_FORMAT_R8_UNORM,
		return 1;
	case vk::Format::eR8Snorm: //VK_FORMAT_R8_SNORM,
		return 1;
	case vk::Format::eR8Uscaled: //VK_FORMAT_R8_USCALED,
		return 1;
	case vk::Format::eR8Sscaled: //VK_FORMAT_R8_SSCALED,
		return 1;
	case vk::Format::eR8Uint: //VK_FORMAT_R8_UINT,
		return 1;
	case vk::Format::eR8Sint: //VK_FORMAT_R8_SINT,
		return 1;
	case vk::Format::eR8Srgb: //VK_FORMAT_R8_SRGB,
		return 1;
	case vk::Format::eR8G8Unorm: //VK_FORMAT_R8G8_UNORM,
		return 2;
	case vk::Format::eR8G8Snorm: //VK_FORMAT_R8G8_SNORM,
		return 2;
	case vk::Format::eR8G8Uscaled: //VK_FORMAT_R8G8_USCALED,
		return 2;
	case vk::Format::eR8G8Sscaled: //VK_FORMAT_R8G8_SSCALED,
		return 2;
	case vk::Format::eR8G8Uint: //VK_FORMAT_R8G8_UINT,
		return 2;
	case vk::Format::eR8G8Sint: //VK_FORMAT_R8G8_SINT,
		return 2;
	case vk::Format::eR8G8Srgb: //VK_FORMAT_R8G8_SRGB,
		return 2;
	case vk::Format::eR8G8B8Unorm: //VK_FORMAT_R8G8B8_UNORM,
		return 3;
	case vk::Format::eR8G8B8Snorm: //VK_FORMAT_R8G8B8_SNORM,
		return 3;
	case vk::Format::eR8G8B8Uscaled: //VK_FORMAT_R8G8B8_USCALED,
		return 3;
	case vk::Format::eR8G8B8Sscaled: //VK_FORMAT_R8G8B8_SSCALED,
		return 3;
	case vk::Format::eR8G8B8Uint: //VK_FORMAT_R8G8B8_UINT,
		return 3;
	case vk::Format::eR8G8B8Sint: //VK_FORMAT_R8G8B8_SINT,
		return 3;
	case vk::Format::eR8G8B8Srgb: //VK_FORMAT_R8G8B8_SRGB,
		return 3;
	case vk::Format::eB8G8R8Unorm: //VK_FORMAT_B8G8R8_UNORM,
		return 3;
	case vk::Format::eB8G8R8Snorm: //VK_FORMAT_B8G8R8_SNORM,
		return 3;
	case vk::Format::eB8G8R8Uscaled: //VK_FORMAT_B8G8R8_USCALED,
		return 3;
	case vk::Format::eB8G8R8Sscaled: //VK_FORMAT_B8G8R8_SSCALED,
		return 3;
	case vk::Format::eB8G8R8Uint: //VK_FORMAT_B8G8R8_UINT,
		return 3;
	case vk::Format::eB8G8R8Sint: //VK_FORMAT_B8G8R8_SINT,
		return 3;
	case vk::Format::eB8G8R8Srgb: //VK_FORMAT_B8G8R8_SRGB,
		return 3;
	case vk::Format::eR8G8B8A8Unorm: //VK_FORMAT_R8G8B8A8_UNORM,
		return 4;
	case vk::Format::eR8G8B8A8Snorm: //VK_FORMAT_R8G8B8A8_SNORM,
		return 4;
	case vk::Format::eR8G8B8A8Uscaled: //VK_FORMAT_R8G8B8A8_USCALED,
		return 4;
	case vk::Format::eR8G8B8A8Sscaled: //VK_FORMAT_R8G8B8A8_SSCALED,
		return 4;
	case vk::Format::eR8G8B8A8Uint: //VK_FORMAT_R8G8B8A8_UINT,
		return 4;
	case vk::Format::eR8G8B8A8Sint: //VK_FORMAT_R8G8B8A8_SINT,
		return 4;
	case vk::Format::eR8G8B8A8Srgb: //VK_FORMAT_R8G8B8A8_SRGB,
		return 4;
	case vk::Format::eB8G8R8A8Unorm: //VK_FORMAT_B8G8R8A8_UNORM,
		return 4;
	case vk::Format::eB8G8R8A8Snorm: //VK_FORMAT_B8G8R8A8_SNORM,
		return 4;
	case vk::Format::eB8G8R8A8Uscaled: //VK_FORMAT_B8G8R8A8_USCALED,
		return 4;
	case vk::Format::eB8G8R8A8Sscaled: //VK_FORMAT_B8G8R8A8_SSCALED,
		return 4;
	case vk::Format::eB8G8R8A8Uint: //VK_FORMAT_B8G8R8A8_UINT,
		return 4;
	case vk::Format::eB8G8R8A8Sint: //VK_FORMAT_B8G8R8A8_SINT,
		return 4;
	case vk::Format::eB8G8R8A8Srgb: //VK_FORMAT_B8G8R8A8_SRGB,
		return 4;
	case vk::Format::eA8B8G8R8UnormPack32: //VK_FORMAT_A8B8G8R8_UNORM_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SnormPack32: //VK_FORMAT_A8B8G8R8_SNORM_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8UscaledPack32: //VK_FORMAT_A8B8G8R8_USCALED_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SscaledPack32: //VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8UintPack32: //VK_FORMAT_A8B8G8R8_UINT_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SintPack32: //VK_FORMAT_A8B8G8R8_SINT_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SrgbPack32: //VK_FORMAT_A8B8G8R8_SRGB_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UnormPack32: //VK_FORMAT_A2R10G10B10_UNORM_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SnormPack32: //VK_FORMAT_A2R10G10B10_SNORM_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UscaledPack32: //VK_FORMAT_A2R10G10B10_USCALED_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SscaledPack32: //VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UintPack32: //VK_FORMAT_A2R10G10B10_UINT_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SintPack32: //VK_FORMAT_A2R10G10B10_SINT_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UnormPack32: //VK_FORMAT_A2B10G10R10_UNORM_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SnormPack32: //VK_FORMAT_A2B10G10R10_SNORM_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UscaledPack32: //VK_FORMAT_A2B10G10R10_USCALED_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SscaledPack32: //VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UintPack32: //VK_FORMAT_A2B10G10R10_UINT_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SintPack32: //VK_FORMAT_A2B10G10R10_SINT_PACK32,
		return 4;
	case vk::Format::eR16Unorm: //VK_FORMAT_R16_UNORM,
		return 2;
	case vk::Format::eR16Snorm: //VK_FORMAT_R16_SNORM,
		return 2;
	case vk::Format::eR16Uscaled: //VK_FORMAT_R16_USCALED,
		return 2;
	case vk::Format::eR16Sscaled: //VK_FORMAT_R16_SSCALED,
		return 2;
	case vk::Format::eR16Uint: //VK_FORMAT_R16_UINT,
		return 2;
	case vk::Format::eR16Sint: //VK_FORMAT_R16_SINT,
		return 2;
	case vk::Format::eR16Sfloat: //VK_FORMAT_R16_SFLOAT,
		return 2;
	case vk::Format::eR16G16Unorm: //VK_FORMAT_R16G16_UNORM,
		return 4;
	case vk::Format::eR16G16Snorm: //VK_FORMAT_R16G16_SNORM,
		return 4;
	case vk::Format::eR16G16Uscaled: //VK_FORMAT_R16G16_USCALED,
		return 4;
	case vk::Format::eR16G16Sscaled: //VK_FORMAT_R16G16_SSCALED,
		return 4;
	case vk::Format::eR16G16Uint: //VK_FORMAT_R16G16_UINT,
		return 4;
	case vk::Format::eR16G16Sint: //VK_FORMAT_R16G16_SINT,
		return 4;
	case vk::Format::eR16G16Sfloat: //VK_FORMAT_R16G16_SFLOAT,
		return 4;
	case vk::Format::eR16G16B16Unorm: //VK_FORMAT_R16G16B16_UNORM,
		return 6;
	case vk::Format::eR16G16B16Snorm: //VK_FORMAT_R16G16B16_SNORM
		return 6;
	case vk::Format::eR16G16B16Uscaled: //VK_FORMAT_R16G16B16_USCALED,
		return 6;
	case vk::Format::eR16G16B16Sscaled: //VK_FORMAT_R16G16B16_SSCALED,
		return 6;
	case vk::Format::eR16G16B16Uint: //VK_FORMAT_R16G16B16_UINT,
		return 6;
	case vk::Format::eR16G16B16Sint: //VK_FORMAT_R16G16B16_SINT,
		return 6;
	case vk::Format::eR16G16B16Sfloat: //VK_FORMAT_R16G16B16_SFLOAT,
		return 6;
	case vk::Format::eR16G16B16A16Unorm: //VK_FORMAT_R16G16B16A16_UNORM,
		return 8;
	case vk::Format::eR16G16B16A16Snorm: //VK_FORMAT_R16G16B16A16_SNORM,
		return 8;
	case vk::Format::eR16G16B16A16Uscaled: //VK_FORMAT_R16G16B16A16_USCALED,
		return 8;
	case vk::Format::eR16G16B16A16Sscaled: //VK_FORMAT_R16G16B16A16_SSCALED,
		return 8;
	case vk::Format::eR16G16B16A16Uint: //VK_FORMAT_R16G16B16A16_UINT,
		return 8;
	case vk::Format::eR16G16B16A16Sint: //VK_FORMAT_R16G16B16A16_SINT,
		return 8;
	case vk::Format::eR16G16B16A16Sfloat: //VK_FORMAT_R16G16B16A16_SFLOAT,
		return 8;
	case vk::Format::eR32Uint: //VK_FORMAT_R32_UINT,
		return 4;
	case vk::Format::eR32Sint: //VK_FORMAT_R32_SINT,
		return 4;
	case vk::Format::eR32Sfloat: //VK_FORMAT_R32_SFLOAT,
		return 4;
	case vk::Format::eR32G32Uint: //VK_FORMAT_R32G32_UINT,
		return 8;
	case vk::Format::eR32G32Sint: //VK_FORMAT_R32G32_SINT,
		return 8;
	case vk::Format::eR32G32Sfloat: //VK_FORMAT_R32G32_SFLOAT,
		return 8;
	case vk::Format::eR32G32B32Uint: //VK_FORMAT_R32G32B32_UINT,
		return 12;
	case vk::Format::eR32G32B32Sint: //VK_FORMAT_R32G32B32_SINT,
		return 12;
	case vk::Format::eR32G32B32Sfloat: //VK_FORMAT_R32G32B32_SFLOAT,
		return 12;
	case vk::Format::eR32G32B32A32Uint: //VK_FORMAT_R32G32B32A32_UINT,
		return 16;
	case vk::Format::eR32G32B32A32Sint: //VK_FORMAT_R32G32B32A32_SINT,
		return 16;
	case vk::Format::eR32G32B32A32Sfloat: //VK_FORMAT_R32G32B32A32_SFLOAT,
		return 16;
	case vk::Format::eR64Uint: //VK_FORMAT_R64_UINT,
		return 8;
	case vk::Format::eR64Sint: //VK_FORMAT_R64_SINT,
		return 8;
	case vk::Format::eR64Sfloat: //VK_FORMAT_R64_SFLOAT,
		return 8;
	case vk::Format::eR64G64Uint: //VK_FORMAT_R64G64_UINT,
		return 16;
	case vk::Format::eR64G64Sint: //VK_FORMAT_R64G64_SINT,
		return 16;
	case vk::Format::eR64G64Sfloat: //VK_FORMAT_R64G64_SFLOAT,
		return 16;
	case vk::Format::eR64G64B64Uint: //VK_FORMAT_R64G64B64_UINT,
		return 24;
	case vk::Format::eR64G64B64Sint: //VK_FORMAT_R64G64B64_SINT,
		return 24;
	case vk::Format::eR64G64B64Sfloat: //VK_FORMAT_R64G64B64_SFLOAT,
		return 24;
	case vk::Format::eR64G64B64A64Uint: //VK_FORMAT_R64G64B64A64_UINT,
		return 32;
	case vk::Format::eR64G64B64A64Sint: //VK_FORMAT_R64G64B64A64_SINT,
		return 32;
	case vk::Format::eR64G64B64A64Sfloat: //VK_FORMAT_R64G64B64A64_SFLOAT,
		return 32;
	case vk::Format::eB10G11R11UfloatPack32: //VK_FORMAT_B10G11R11_UFLOAT_PACK32,
	case vk::Format::eE5B9G9R9UfloatPack32: //VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
	case vk::Format::eD16Unorm: //VK_FORMAT_D16_UNORM,
		return 2;
	case vk::Format::eX8D24UnormPack32: //VK_FORMAT_X8_D24_UNORM_PACK32,
	case vk::Format::eD32Sfloat: //VK_FORMAT_D32_SFLOAT,
		return 4;
	case vk::Format::eS8Uint: //VK_FORMAT_S8_UINT,
		return 1;
	case vk::Format::eD16UnormS8Uint: //VK_FORMAT_D16_UNORM_S8_UINT,
		return 3;
	case vk::Format::eD24UnormS8Uint: //VK_FORMAT_D24_UNORM_S8_UINT,
		return 5;
	case vk::Format::eD32SfloatS8Uint: //VK_FORMAT_D32_SFLOAT_S8_UINT,
	case vk::Format::eBc1RgbUnormBlock: //VK_FORMAT_BC1_RGB_UNORM_BLOCK,
	case vk::Format::eBc1RgbSrgbBlock: //VK_FORMAT_BC1_RGB_SRGB_BLOCK,
	case vk::Format::eBc1RgbaUnormBlock: //VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
	case vk::Format::eBc1RgbaSrgbBlock: //VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
	case vk::Format::eBc2UnormBlock: //VK_FORMAT_BC2_UNORM_BLOCK,
	case vk::Format::eBc2SrgbBlock: //VK_FORMAT_BC2_SRGB_BLOCK,
	case vk::Format::eBc3UnormBlock: //VK_FORMAT_BC3_UNORM_BLOCK,
	case vk::Format::eBc3SrgbBlock: //VK_FORMAT_BC3_SRGB_BLOCK,
	case vk::Format::eBc4UnormBlock: //VK_FORMAT_BC4_UNORM_BLOCK,
	case vk::Format::eBc4SnormBlock: //VK_FORMAT_BC4_SNORM_BLOCK,
	case vk::Format::eBc5UnormBlock: //VK_FORMAT_BC5_UNORM_BLOCK,
	case vk::Format::eBc5SnormBlock: //VK_FORMAT_BC5_SNORM_BLOCK,
	case vk::Format::eBc6HUfloatBlock: //VK_FORMAT_BC6H_UFLOAT_BLOCK,
	case vk::Format::eBc6HSfloatBlock: //VK_FORMAT_BC6H_SFLOAT_BLOCK,
	case vk::Format::eBc7UnormBlock: //VK_FORMAT_BC7_UNORM_BLOCK,
	case vk::Format::eBc7SrgbBlock: //VK_FORMAT_BC7_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8UnormBlock: //VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8SrgbBlock: //VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8A1UnormBlock: //VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8A1SrgbBlock: //VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8A8UnormBlock: //VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8A8SrgbBlock: //VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
	case vk::Format::eEacR11UnormBlock: //VK_FORMAT_EAC_R11_UNORM_BLOCK,
	case vk::Format::eEacR11SnormBlock: //VK_FORMAT_EAC_R11_SNORM_BLOCK,
	case vk::Format::eEacR11G11UnormBlock: //VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
	case vk::Format::eEacR11G11SnormBlock: //VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
	case vk::Format::eAstc4x4UnormBlock: //VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
	case vk::Format::eAstc4x4SrgbBlock: //VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
	case vk::Format::eAstc5x4UnormBlock: //VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
	case vk::Format::eAstc5x4SrgbBlock: //VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
	case vk::Format::eAstc5x5UnormBlock: //VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
	case vk::Format::eAstc5x5SrgbBlock: //VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
	case vk::Format::eAstc6x5UnormBlock: //VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
	case vk::Format::eAstc6x5SrgbBlock: //VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
	case vk::Format::eAstc6x6UnormBlock: //VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
	case vk::Format::eAstc6x6SrgbBlock: //VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
	case vk::Format::eAstc8x5UnormBlock: //VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
	case vk::Format::eAstc8x5SrgbBlock: //VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
	case vk::Format::eAstc8x6UnormBlock: //VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
	case vk::Format::eAstc8x6SrgbBlock: //VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
	case vk::Format::eAstc8x8UnormBlock: //VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
	case vk::Format::eAstc8x8SrgbBlock: //VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
	case vk::Format::eAstc10x5UnormBlock: //VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
	case vk::Format::eAstc10x5SrgbBlock: //VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
	case vk::Format::eAstc10x6UnormBlock: //VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
	case vk::Format::eAstc10x6SrgbBlock: //VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
	case vk::Format::eAstc10x8UnormBlock: //VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
	case vk::Format::eAstc10x8SrgbBlock: //VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
	case vk::Format::eAstc10x10UnormBlock: //VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
	case vk::Format::eAstc10x10SrgbBlock: //VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
	case vk::Format::eAstc12x10UnormBlock: //VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
	case vk::Format::eAstc12x10SrgbBlock: //VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
	case vk::Format::eAstc12x12UnormBlock: //VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
	case vk::Format::eAstc12x12SrgbBlock: //VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
	case vk::Format::eG8B8G8R8422Unorm: //VK_FORMAT_G8B8G8R8_422_UNORM,
	//case vk::Format::eG8B8G8R8422UnormKHR: //VK_FORMAT_G8B8G8R8_422_UNORM,
	case vk::Format::eB8G8R8G8422Unorm: //VK_FORMAT_B8G8R8G8_422_UNORM,
	//case vk::Format::eB8G8R8G8422UnormKHR: //VK_FORMAT_B8G8R8G8_422_UNORM,
	case vk::Format::eG8B8R83Plane420Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
	//case vk::Format::eG8B8R83Plane420UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
	case vk::Format::eG8B8R82Plane420Unorm: //VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
	//case vk::Format::eG8B8R82Plane420UnormKHR: //VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
	case vk::Format::eG8B8R83Plane422Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
	//case vk::Format::eG8B8R83Plane422UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
	case vk::Format::eG8B8R82Plane422Unorm: //VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
	//case vk::Format::eG8B8R82Plane422UnormKHR: //VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
	case vk::Format::eG8B8R83Plane444Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
	//case vk::Format::eG8B8R83Plane444UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
	case vk::Format::eR10X6UnormPack16: //VK_FORMAT_R10X6_UNORM_PACK16,
	//case vk::Format::eR10X6UnormPack16KHR: //VK_FORMAT_R10X6_UNORM_PACK16,
	case vk::Format::eR10X6G10X6Unorm2Pack16: //VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
	//case vk::Format::eR10X6G10X6Unorm2Pack16KHR: //VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
	case vk::Format::eR10X6G10X6B10X6A10X6Unorm4Pack16: //VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
	//case vk::Format::eR10X6G10X6B10X6A10X6Unorm4Pack16KHR: //VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
	case vk::Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16: //VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
	//case vk::Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16KHR: //VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
	case vk::Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16: //VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
	//case vk::Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16KHR: //VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane420Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane420Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X62Plane420Unorm3Pack16: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X62Plane420Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane422Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane422Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X62Plane422Unorm3Pack16: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X62Plane422Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane444Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane444Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
	case vk::Format::eR12X4UnormPack16: //VK_FORMAT_R12X4_UNORM_PACK16,
	//case vk::Format::eR12X4UnormPack16KHR: //VK_FORMAT_R12X4_UNORM_PACK16,
	case vk::Format::eR12X4G12X4Unorm2Pack16: //VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
	//case vk::Format::eR12X4G12X4Unorm2Pack16KHR: //VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
	case vk::Format::eR12X4G12X4B12X4A12X4Unorm4Pack16: //VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
	//case vk::Format::eR12X4G12X4B12X4A12X4Unorm4Pack16KHR: //VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
	case vk::Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16: //VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
	//case vk::Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16KHR: //VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
	case vk::Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16: //VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
	//case vk::Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16KHR: //VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane420Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane420Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X42Plane420Unorm3Pack16: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X42Plane420Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane422Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane422Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X42Plane422Unorm3Pack16: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X42Plane422Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane444Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane444Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
	case vk::Format::eG16B16G16R16422Unorm: //VK_FORMAT_G16B16G16R16_422_UNORM,
	//case vk::Format::eG16B16G16R16422UnormKHR: //VK_FORMAT_G16B16G16R16_422_UNORM,
	case vk::Format::eB16G16R16G16422Unorm: //VK_FORMAT_B16G16R16G16_422_UNORM,
	//case vk::Format::eB16G16R16G16422UnormKHR: //VK_FORMAT_B16G16R16G16_422_UNORM,
	case vk::Format::eG16B16R163Plane420Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
	//case vk::Format::eG16B16R163Plane420UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
	case vk::Format::eG16B16R162Plane420Unorm: //VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
	//case vk::Format::eG16B16R162Plane420UnormKHR: //VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
	case vk::Format::eG16B16R163Plane422Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
	//case vk::Format::eG16B16R163Plane422UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
	case vk::Format::eG16B16R162Plane422Unorm: //VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
	//case vk::Format::eG16B16R162Plane422UnormKHR: //VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
	case vk::Format::eG16B16R163Plane444Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
	//case vk::Format::eG16B16R163Plane444UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
	case vk::Format::ePvrtc12BppUnormBlockIMG: //VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc14BppUnormBlockIMG: //VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc22BppUnormBlockIMG: //VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc24BppUnormBlockIMG: //VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc12BppSrgbBlockIMG: //VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc14BppSrgbBlockIMG: //VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc22BppSrgbBlockIMG: //VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc24BppSrgbBlockIMG: //VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG
	default:
		return 4;
	}
}

inline vk::BlendFactor ConvertColorFactor(D3DBLEND input) noexcept
{
	vk::BlendFactor output;

	switch (input)
	{
	case D3DBLEND_ZERO:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ZERO;
		break;
	case D3DBLEND_ONE:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE;
		break;
	case D3DBLEND_SRCCOLOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_SRC_COLOR;
		break;
	case D3DBLEND_INVSRCCOLOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
		break;
	case D3DBLEND_SRCALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_SRC_ALPHA;
		break;
	case D3DBLEND_INVSRCALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		break;
	case D3DBLEND_DESTALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_DST_ALPHA;
		break;
	case D3DBLEND_INVDESTALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
		break;
	case D3DBLEND_DESTCOLOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_DST_COLOR;
		break;
	case D3DBLEND_INVDESTCOLOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
		break;
	case D3DBLEND_SRCALPHASAT:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
		break;
	case D3DBLEND_BOTHSRCALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_CONSTANT_ALPHA;
		break;
	case D3DBLEND_BOTHINVSRCALPHA:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
		break;
	case D3DBLEND_BLENDFACTOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_CONSTANT_COLOR;
		break;
	case D3DBLEND_INVBLENDFACTOR:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
		break;
		//Revisit
#if !defined(D3D_DISABLE_9EX)
	case D3DBLEND_SRCCOLOR2:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_SRC1_COLOR;
		break;
	case D3DBLEND_INVSRCCOLOR2:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
		break;
#endif // !D3D_DISABLE_9EX
	default:
		output = (vk::BlendFactor)VK_BLEND_FACTOR_ONE;
		break;
	}

	return output;
}

inline vk::BlendOp ConvertColorOperation(D3DBLENDOP  input) noexcept
{
	vk::BlendOp output;

	switch (input)
	{
	case D3DBLENDOP_ADD:
		output = (vk::BlendOp)VK_BLEND_OP_ADD;
		break;
	case D3DBLENDOP_SUBTRACT:
		output = (vk::BlendOp)VK_BLEND_OP_SUBTRACT;
		break;
	case D3DBLENDOP_REVSUBTRACT:
		output = (vk::BlendOp)VK_BLEND_OP_REVERSE_SUBTRACT;
		break;
	case D3DBLENDOP_MIN:
		output = (vk::BlendOp)VK_BLEND_OP_MIN;
		break;
	case D3DBLENDOP_MAX:
		output = (vk::BlendOp)VK_BLEND_OP_MAX;
		break;
	case D3DBLENDOP_FORCE_DWORD:
		output = (vk::BlendOp)VK_BLEND_OP_MAX_ENUM;
		break;
	default:
		output = (vk::BlendOp)VK_BLEND_OP_ADD;
		break;
	}

	return output;
}

inline vk::StencilOp ConvertStencilOperation(D3DSTENCILOP input) noexcept
{
	vk::StencilOp output;

	switch (input)
	{
	case D3DSTENCILOP_KEEP:
		output = (vk::StencilOp)VK_STENCIL_OP_KEEP;
		break;
	case D3DSTENCILOP_ZERO:
		output = (vk::StencilOp)VK_STENCIL_OP_ZERO;
		break;
	case D3DSTENCILOP_REPLACE:
		output = (vk::StencilOp)VK_STENCIL_OP_REPLACE;
		break;
	case D3DSTENCILOP_INCRSAT:
		output = (vk::StencilOp)VK_STENCIL_OP_INCREMENT_AND_CLAMP;
		break;
	case D3DSTENCILOP_DECRSAT:
		output = (vk::StencilOp)VK_STENCIL_OP_DECREMENT_AND_CLAMP;
		break;
	case D3DSTENCILOP_INVERT:
		output = (vk::StencilOp)VK_STENCIL_OP_INVERT;
		break;
	case D3DSTENCILOP_INCR:
		output = (vk::StencilOp)VK_STENCIL_OP_INCREMENT_AND_WRAP;
		break;
	case D3DSTENCILOP_DECR:
		output = (vk::StencilOp)VK_STENCIL_OP_DECREMENT_AND_WRAP;
		break;
	default:
		output = (vk::StencilOp)VK_STENCIL_OP_MAX_ENUM;
		break;
	}

	return output;
}

inline vk::CompareOp ConvertCompareOperation(D3DCMPFUNC input) noexcept
{
	vk::CompareOp output;

	switch (input)
	{
	case D3DCMP_NEVER:
		output = (vk::CompareOp)VK_COMPARE_OP_NEVER;
		break;
	case D3DCMP_LESS:
		output = (vk::CompareOp)VK_COMPARE_OP_LESS;
		break;
	case D3DCMP_EQUAL:
		output = (vk::CompareOp)VK_COMPARE_OP_EQUAL;
		break;
	case D3DCMP_LESSEQUAL:
		output = (vk::CompareOp)VK_COMPARE_OP_LESS_OR_EQUAL;
		break;
	case D3DCMP_GREATER:
		output = (vk::CompareOp)VK_COMPARE_OP_GREATER;
		break;
	case D3DCMP_NOTEQUAL:
		output = (vk::CompareOp)VK_COMPARE_OP_NOT_EQUAL;
		break;
	case D3DCMP_GREATEREQUAL:
		output = (vk::CompareOp)VK_COMPARE_OP_GREATER_OR_EQUAL;
		break;
	case D3DCMP_ALWAYS:
		output = (vk::CompareOp)VK_COMPARE_OP_ALWAYS;
		break;
	default:
		output = (vk::CompareOp)VK_COMPARE_OP_MAX_ENUM;
		break;
	}

	return output;
}

inline vk::BlendFactor ConvertColorFactor(DWORD input) noexcept
{
	return ConvertColorFactor((D3DBLEND)input);
}

inline vk::BlendOp ConvertColorOperation(DWORD  input) noexcept
{
	return ConvertColorOperation((D3DBLENDOP)input);
}

inline vk::StencilOp ConvertStencilOperation(DWORD input) noexcept
{
	return ConvertStencilOperation((D3DSTENCILOP)input);
}

inline vk::CompareOp ConvertCompareOperation(DWORD input) noexcept
{
	return ConvertCompareOperation((D3DCMPFUNC)input);
}

inline uint32_t ConvertFormat(DWORD fvf) noexcept
{
	//TODO: This should be able to be simplified by bitwise operators.

	if ((fvf & D3DFVF_TEX8) == D3DFVF_TEX8)
	{
		return 8;
	}

	if ((fvf & D3DFVF_TEX7) == D3DFVF_TEX7)
	{
		return 7;
	}

	if ((fvf & D3DFVF_TEX6) == D3DFVF_TEX6)
	{
		return 6;
	}

	if ((fvf & D3DFVF_TEX5) == D3DFVF_TEX5)
	{
		return 5;
	}

	if ((fvf & D3DFVF_TEX4) == D3DFVF_TEX4)
	{
		return 4;
	}

	if ((fvf & D3DFVF_TEX3) == D3DFVF_TEX3)
	{
		return 3;
	}

	if ((fvf & D3DFVF_TEX2) == D3DFVF_TEX2)
	{
		return 2;
	}

	if ((fvf & D3DFVF_TEX1) == D3DFVF_TEX1)
	{
		return 1;
	}

	return 0;
}

inline void Print(std::unordered_map<D3DTRANSFORMSTATETYPE, D3DMATRIX>& transforms)
{
	for (const auto& pair1 : transforms)
	{
		Log(info) << pair1.first << std::endl;
		Log(info) << "{" << pair1.second._11 << "," << pair1.second._12 << "," << pair1.second._13 << "," << pair1.second._14 << "}" << std::endl;
		Log(info) << "{" << pair1.second._21 << "," << pair1.second._22 << "," << pair1.second._23 << "," << pair1.second._24 << "}" << std::endl;
		Log(info) << "{" << pair1.second._31 << "," << pair1.second._32 << "," << pair1.second._33 << "," << pair1.second._34 << "}" << std::endl;
		Log(info) << "{" << pair1.second._41 << "," << pair1.second._42 << "," << pair1.second._43 << "," << pair1.second._44 << "}" << std::endl;
		Log(info) << "" << std::endl;
	}
}

/*
d3d9 has a 32bit format where alpha is ignored but so far vulkan does not so to handle that I need to set alpha to be opaque.
*/
inline void SetAlpha(char* imageData, uint32_t height, uint32_t width, uint32_t rowPitch)
{
	for (uint32_t y = 0; y < height; y++)
	{
		color_A8R8G8B8 *row = (color_A8R8G8B8*)imageData;
		for (uint32_t x = 0; x < width; x++)
		{
			row->A = UCHAR_MAX; //0xFF;

			row++;
		}
		imageData += rowPitch;
	}
}

inline void SaveImage(const char *filename, char* imageData, uint32_t height, uint32_t width, uint32_t rowPitch)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	// Write the header
	file << "P6\n" << width << "\n" << height << "\n" << 255 << "\n";

	// Write the pixel data.
	for (uint32_t y = 0; y < height; y++)
	{
		unsigned int *row = (unsigned int*)imageData;
		for (uint32_t x = 0; x < width; x++)
		{
			file.write((char*)row, 3);
			row++;
		}
		imageData += rowPitch;
	}

	file.close();
}

/*
Optimizing compilers are magic. The memcpy should go away. If not performance will take a hit here.
*/

template <class TargetType, class SourceType>
inline void assign(TargetType& target, const SourceType& source) noexcept
{
	static_assert(!std::is_same<TargetType, SourceType>::value, "You've made a mistake, you don't need to bit cast if the types are the same.");
	constexpr size_t size = std::min(sizeof(TargetType), sizeof(SourceType));
	memcpy(&target, &source, size);
}

template <class TargetType, class SourceType>
inline TargetType bit_cast(const SourceType& source) noexcept
{
	static_assert(!std::is_same<TargetType, SourceType>::value, "You've made a mistake, you don't need to bit cast if the types are the same.");
	constexpr size_t size = std::min(sizeof(TargetType), sizeof(SourceType));
	TargetType returnValue;
	memcpy(&returnValue, &source, size);
	return returnValue;
}

inline DWORD bit_cast(const float& source) noexcept
{
	DWORD returnValue;
	memcpy(&returnValue, &source, sizeof(DWORD));
	return returnValue;
}

inline float bit_cast(const DWORD& source) noexcept
{
	float returnValue;
	memcpy(&returnValue, &source, sizeof(float));
	return returnValue;
}

void IUnknownDeleter(IUnknown* ptr);

template <class T>
class com_ptr
	: public std::unique_ptr<T, decltype(&IUnknownDeleter)>
{

};

static inline void LTrim(std::string &s) 
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) 
	{
		std::locale loc;
		return !std::isspace(ch,loc);
	}));
}

static inline void RTrim(std::string &s) 
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) 
	{
		std::locale loc;
		return !std::isspace(ch, loc);
	}).base(), s.end());
}

static inline void Trim(std::string &s) 
{
	LTrim(s);
	RTrim(s);
}

#endif // UTILITIES_H
