/*
* Vulkan Invaders - 3D model loading class
*
* Copyright (C) 2018 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once

#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VulkanUtils.h"
#include "VulkanDevice.h"

class Model
{
private:
	VulkanDevice &device;
	VkQueue queue;
	VulkanDeviceBuffer vertexBuffer;
	VulkanDeviceBuffer indexBuffer;
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
public:
	std::string id;
	Model(std::string id, std::string filename, VulkanDevice &device, VkQueue queue, VkCommandPool commandPool);
	~Model();
};
