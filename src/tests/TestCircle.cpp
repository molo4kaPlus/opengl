#include "TestCircle.h"

#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <math.h>

namespace test 
{
	TestCircle::TestCircle()
		: numberOfVertices (32), radius (50.5f), color { 1.0f, 0.0f, 0.0f, 0.0f }, position(glm::vec2(50.0f, 50.f)),
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_translation(200, 200, 0)
	{
		float PI = 3.14159265359f;
		float TwicePI = 2.0f * PI;
		float x = position[0];
		float y = position[1];

		float possitions[32 * 2] = {x, y};
		for (int i = 1; i < numberOfVertices; i++)
		{
			possitions[i * 2] = (x + (radius * cos(i * TwicePI / numberOfVertices)));
			possitions[i * 2 + 1] = (y + (radius * sin(i * TwicePI / numberOfVertices)));
		}
		
		unsigned int indices[3 * 32] = {};
		for (int i = 0; i < 3; i++)
		{
			if (i % 3 == 0) { indices[i] = 0; }
			if (i % 3 == 1) { indices[i] = i; }
			if (i % 3 == 2) { indices[i] = i + 1; }
		}

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(possitions, 32 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 32 * 3);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		m_Shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/textures/end.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestCircle::~TestCircle()
	{

	}

	void TestCircle::OnUpdate(float deltaTime)
	{

	}

	void TestCircle::OnRender()
	{
		GLCall(glClearColor(0.0f, 1.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestCircle::OnImGuiRender()
	{
		ImGui::SliderFloat2("position", &m_translation.x, 0.0f, 960.0f);
		ImGui::SliderInt("N vertices", &numberOfVertices, 3, 100);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}