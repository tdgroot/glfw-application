#include <glad/glad.h>
#include <imgui/imgui.h>

#include "test_clear_color.h"

namespace test {
	TestClearColor::TestClearColor()
		: clear_color{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::on_update(float delta)
	{
	}

	void TestClearColor::on_render()
	{
		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::on_imgui_render()
	{
		ImGui::ColorEdit4("Clear Color", clear_color);
	}
}