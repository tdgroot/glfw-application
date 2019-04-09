#pragma once

#include <vector>
#include <functional>

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void on_update(float delta) {}
		virtual void on_render() {}
		virtual void on_imgui_render() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& current_test_ptr);

		virtual void on_imgui_render() override;

		template<typename T>
		void register_test(const std::string& name)
		{
			printf("Registering test %s \n", name.c_str());

			tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test*& current_test;
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
	};
}