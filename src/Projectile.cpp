/*
* Vulkan Invaders - Projectile entity class
*
* Copyright (C) 2018 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(Model *model, glm::vec3 position, glm::vec3 direction) : model(model), origin(position), direction(direction)
{
	this->position = position;
	this->speed = glm::vec3(7.5f);
	this->size = glm::vec3(0.25f, 0.5f, 0.25f);
}

Projectile::~Projectile()
{
	vkDestroyDescriptorSetLayout(ubo.device, descriptorSetLayout, nullptr);
	ubo.destroy();
}

void Projectile::allocateResources(VulkanDevice *device, VkDescriptorPool descriptorPool)
{
	ubo = device->createBuffer(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, sizeof(uniformData), &uniformData);

	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
		{ 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT, nullptr }
	};

	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI{};
	descriptorSetLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutCI.pBindings = setLayoutBindings.data();
	descriptorSetLayoutCI.bindingCount = 1;
	VK_CHECK_RESULT(vkCreateDescriptorSetLayout((VkDevice)*device, &descriptorSetLayoutCI, nullptr, &descriptorSetLayout));

	VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
	descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descriptorSetAllocInfo.descriptorPool = descriptorPool;
	descriptorSetAllocInfo.pSetLayouts = &descriptorSetLayout;
	descriptorSetAllocInfo.descriptorSetCount = 1;
	VK_CHECK_RESULT(vkAllocateDescriptorSets((VkDevice)*device, &descriptorSetAllocInfo, &descriptorSet));

	VkWriteDescriptorSet writeDescriptorSet{};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	writeDescriptorSet.descriptorCount = 1;
	writeDescriptorSet.dstSet = descriptorSet;
	writeDescriptorSet.dstBinding = 0;
	writeDescriptorSet.pBufferInfo = &VkDescriptorBufferInfo(ubo);
	vkUpdateDescriptorSets((VkDevice)*device, 1, &writeDescriptorSet, 0, nullptr);
}

void Projectile::update(float deltatime)
{
	position += direction * speed * deltatime;
	updated = true;
	if (updated) {
		updateUniformdata();
	}
}

void Projectile::updateUniformdata()
{
	if (updated) {
		uniformData.model = glm::translate(glm::mat4(1.0f), position);
		memcpy(ubo.mapped, &uniformData, sizeof(uniformData));
	}
	updated = false;
}

void Projectile::draw(VkCommandBuffer commandBuffer)
{
	if (model) {
		model->draw(commandBuffer);
	}
}
