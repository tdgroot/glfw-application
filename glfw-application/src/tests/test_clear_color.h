#pragma once

#include "test.h"

namespace test {
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();
		
		void on_update(float delta) override;
		void on_render() override;
		void on_imgui_render() override;
	private:
		float clear_color[4];
	};
}
