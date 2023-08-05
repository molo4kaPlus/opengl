#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "texture.h"

#include <memory>

namespace test
{
	class TestCircle : public Test
	{
	public:
		TestCircle();
		~TestCircle();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		int numberOfVertices;
		float radius;
		float color[4];

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::vec3 m_translation;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::vec2 position;
	};
}
