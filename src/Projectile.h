/*
* Vulkan Invaders - Projectile entity class
*
* Copyright (C) 2018 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "GameEntity.h"

#include <glm/glm.hpp>
#include "vulkan/vulkan.h"
#include "VulkanDevice.h"
#include "Model.h"

class Projectile : public GameEntity
{
private:
	struct Matrices {
		glm::mat4 model;
	} uniformData;
	glm::vec3 origin;
	glm::vec3 direction;
public:
	bool updated = true;
	Model* model;
	Projectile();
	Projectile(Model *model, glm::vec3 position, glm::vec3 direction);
	~Projectile();
	void allocateResources(VulkanDevice *device, VkDescriptorPool descriptorPool);
	void update(float deltatime);
	void updateUniformdata();
	void draw(VkCommandBuffer commandBuffer);
};

