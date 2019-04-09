#include "test.h"

#include <imgui/imgui.h>

namespace test {

	TestMenu::TestMenu(Test *& current_test_ptr)
		: current_test(current_test_ptr)
	{
	}

	void TestMenu::on_imgui_render()
	{
		for (auto& test : tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				current_test = test.second();
			}
		}
	}
}