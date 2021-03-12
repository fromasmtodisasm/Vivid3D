#include "pch.h"
#include "Application.h"
#include "UI.h"
#include <cstdlib>
#include <thread>
#include <mutex>
Application::Application() {

	Window = NULL;
	states.empty();
	Main = this;
};

AppState* Application::InitialState = NULL;

static void cursor_callback(GLFWwindow* win, double xpos, double ypos)
{

	UI::SetMouse((int)xpos, (int)ypos, 0);

}

static void key_callback(GLFWwindow* win, int key, int scan, int act, int mods) {

	bool on = true;
	bool shift = false;
	if (mods == GLFW_MOD_SHIFT) {

		shift = true;
	}

	if (!act == GLFW_PRESS) {
		on = false;
	}

	if (act != GLFW_RELEASE) {

		UI::CallKey(key);
		UI::SetShift(shift);

	}

	UI::SetKey(key, on);
	UI::SetShift(shift);
}

void Application::Resized(int w, int h) {

	//WinWidth = w;
	//WinHeight = h;
	RenW = w;
	RenH = h;
	WinW = w;
	WinH = h;
	Main->SetSize(w, h);
	




}

void Application::SetSize(int w, int h) {

	WinWidth = w;
	WinHeight = h;
	auto state = GetState();
	if (state != NULL) {
		state->Resized(w, h);
	}

}


void resize_callback(GLFWwindow* window, int width, int height) {

	Application::Resized(width, height);

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	bool lb, rb, mb;
	lb = false;
	rb = false;
	mb = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT) {

		if (action == GLFW_PRESS) {
			lb = true;
		}
		else {
			lb = false;
		}

		UI::SetMouseBut(0, lb);

	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		if (action == GLFW_PRESS) {
			lb = true;
		}
		else {
			lb = false;
		}
		UI::SetMouseBut(2, lb);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {


		if (action == GLFW_PRESS) {
			lb = true;
		}
		else {
			lb = false;
		}
	
		UI::SetMouseBut(1, lb);

	}


}

void Application::CrWindow(int w, int h, const char* title) {

	
	glfwInit();

	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	Window = glfwCreateWindow(w, h, title, NULL, NULL);

	glfwMakeContextCurrent(Window);
	
	glViewport(0, 0, w, h);
	glDisable(GL_BLEND);
	//glDisable(GL_SCISSOR_TEST);
		
	glewExperimental = GL_TRUE;

	glewInit();

	WinWidth = w;
	WinHeight = h;
	RenW = w;
	RenH = h;
	WinW = w;
	WinH = h;

	glfwSetCursorPosCallback(Window, cursor_callback);
	//glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(Window, key_callback);
	glfwSetMouseButtonCallback(Window, mouse_button_callback);
	glfwSetWindowSizeCallback(Window, resize_callback);
	glfwSwapInterval(0);
	glEnable(GL_MULTISAMPLE);
	glDisable(GL_SCISSOR_TEST);
	//glScissor(0, 0, WinW, WinH);
};

 int Application::RenW = 0;
 int Application::RenH = 0;
 int Application::WinW = 0;
 int Application::WinH = 0;


 void Application::SetRen(int w, int h) {

	 RenW = w;
	 RenH = h;

 };

 void Application::ResetRen() {

	 RenW = WinW;
	 RenH = WinH;

 }

int Application::Width() {
	return WinWidth;
}

int Application::Height() {
	return WinHeight;
}

Application* Application::Main = NULL;

void Application::Run() {

	Init();

	glClearColor(0, 0,0, 1.0f);

	double prev_time = glfwGetTime();
	int framec = 0;
	int fps=0;
	//glfwSwapInterval(0);

	//SEngine = new SoundEngine();

	if (InitialState != NULL) {
		PushState(InitialState);
	}


	while (true) {

		double cur_time = glfwGetTime();
		framec++;
		if ((cur_time - prev_time) >= 1.0)
		{
			fps = framec;
			framec = 0;
			prev_time = cur_time;
			printf("FPS:%d \n", fps);
		}

		Update();

		auto state = GetState();
		if (state != NULL) {
			state->Update();
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();
		if (state!= NULL) {
			state->Render();
		}

		glFlush();
		glfwSwapBuffers(Window);
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(3));

	}

}

void Application::InitCL() {

	if (CLInit) return;

	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
	clPlatform = default_platform;
	clDevice = default_device;

	clContext = cl::Context(clDevice);



}


const char * pLen(const char* path) {

	char* str = (char *)malloc(512);


	strcpy(str, Application::ContentPath);
	
	strcat(str, path);

	return str;

}

const char * Application::GetPath(const char* content) {



	return pLen(content);

}

void Application::PushState(AppState* state) {

	states.push(state);
	state->Init();

}

void Application::PopState() {

	states.pop();

}

const char* Application::ContentPath = "";
