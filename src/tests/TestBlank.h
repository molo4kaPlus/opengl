#pragma once

#include "Test.h"

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

	};
}
