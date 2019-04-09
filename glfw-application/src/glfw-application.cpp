#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "pch.h"

#include "callback.h"
#include "renderer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbuffer_layout.h"
#include "indexbuffer.h"
#include "shader.h"
#include "texture.h"

#include "tests/test_clear_color.h"
#include "tests/test_texture.h"
#include "tests/test_object_renderer.h"

int main()
{
    std::cout << "Hello World!\n";
	std::cout << "Perhaps we should use mathlib https://github.com/g-truc/glm \n";

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "GLFW App", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// Enable gl options.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	bool test_menu_active = true;

	test::Test* current_test = nullptr;
	test::TestMenu* test_menu = new test::TestMenu(current_test);
	test::TestObjectRenderer* object_renderer = new test::TestObjectRenderer();
	current_test = object_renderer; 

	test_menu->register_test<test::TestClearColor>("Clear Color");
	test_menu->register_test<test::TestTexture>("Texture");
	test_menu->register_test<test::TestObjectRenderer>("Object Renderer");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		renderer.clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (current_test)
		{
			current_test->on_update(0.0f);
			current_test->on_render();
			ImGui::Begin("Test");
			if (current_test != test_menu && ImGui::Button("<-"))
			{
				delete current_test;
				current_test = test_menu;
			}
			current_test->on_imgui_render();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	delete current_test;
	if (current_test != test_menu)
		delete test_menu;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
