#include "Core.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

float vertices[] = {
	// позиции       // текстурные координаты
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // верхний правый угол
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // нижний правый угол
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // нижний левый угол
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // верхний левый угол
};

unsigned int indices[] = {
	0, 1, 3, // первый треугольник
	1, 2, 3  // второй треугольник
};
unsigned int shaderProgram;
unsigned int VBO, VAO, EBO;

namespace Core
{
	Core::Core()
	{
		glfwInit();
		glewExperimental = GL_TRUE;

		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorContentScale(primary_monitor, &sysdata.monitor_scaleX, &sysdata.monitor_scaleY);
		settings.monitory_scaleX = sysdata.monitor_scaleX;
		settings.monitory_scaleY = sysdata.monitor_scaleY;

		sysdata.video_mode = glfwGetVideoMode(primary_monitor);
		settings.video_mode = sysdata.video_mode;

		gl_window = glfwCreateWindow(settings.video_mode->width, settings.video_mode->height, "Trido", NULL, NULL);
		glfwMakeContextCurrent(gl_window);
		glewInit();
		glfwSwapInterval(1);

		glfwSetWindowUserPointer(gl_window, this);
		glfwSetKeyCallback(gl_window, Core::KeyCallback);
		glfwSetMouseButtonCallback(gl_window, Core::MouseCallback);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Атрибуты вершин
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Атрибуты текстурных координат
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        void main() {
            gl_Position = vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
    )";

		const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;

        uniform sampler2D texture1;

        void main() {
            FragColor = texture(texture1, TexCoord);
        }
    )";
		shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

		stbi_set_flip_vertically_on_load(true);
		res.Load();
		windows.push_back(Window([&]() {this->RenderMainWindow(); }, [&](GLFWwindow* window) {
			this->InputMainWindow(window); }, [&]() { this->EventMainWindow(); }));
		logger.print(Log_type::INFO, "Core run");
	}

	void Core::RenderMainWindow()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindTexture(GL_TEXTURE_2D, res.textures[0].tex_id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	void Core::InputMainWindow(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
	void Core::EventMainWindow()
	{

	}
	void Core::KeyCallback(GLFWwindow* gl_window, int key, int scancode, int action, int mod)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(gl_window));
		if (core) {
			// first input topper window
			std::vector<Window>&windows = core->windows;
			for (auto window = windows.rbegin(); window != windows.rend(); window++)
			{
				window->InputCallback(gl_window);
				if (window->LockInput == Window::ALLOW_ALL)
					continue;
				// stop accept input from lower windows
				else break;
			}
		}
	}
	void Core::MouseCallback(GLFWwindow* gl_window, int button, int action, int mod)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(gl_window));
		if (core) {
			// first input topper window
			std::vector<Window>& windows = core->windows;
			for (auto window = windows.rbegin(); window != windows.rend(); window++)
			{
				window->InputCallback(gl_window);
				if (window->LockInput == Window::ALLOW_ALL || window->LockInput == Window::ALLOW_MOUSE)
					continue;
				// stop accept input from lower windows
				else break;
			}
		}
	}
	void Core::Loop()
	{
		while (!glfwWindowShouldClose(gl_window))
			Pipeline();
		Exit();
	}
	void Core::Pipeline()
	{
		Render();
		glfwSwapBuffers(gl_window);
		glfwPollEvents();
	}
	void Core::Render()
	{
		// first render lower window
		for (Window& window : windows)
			window.RenderCallback();
	}
	void Core::Exit()
	{
		glfwTerminate();
	}

	Resources::Resources()
	{

	}
	void Resources::Load()
	{
		int textures_count = 1;
		textures.reserve(textures_count);
		for (int i = 0; i < textures_count; i++)
		{
			// handling xml data
		}
		Resources::Texture tex1;
		if (LoadTextureFromFile("textures/tex1.png", &tex1))
			textures.push_back(tex1);
	}
	bool Resources::LoadTextureFromFile(const char* filename, Texture* texture)
	{
		// Load from file
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create a OpenGL texture identifier
		GLuint image_texture;
		glGenTextures(1, &image_texture);
 		glBindTexture(GL_TEXTURE_2D, image_texture);

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

		// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		texture->tex_id = image_texture;
		texture->width = image_width;
		texture->height = image_height;
		texture->channels = 4;
	}
	unsigned int compileShader(unsigned int type, const char* source) {
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Проверка на ошибки
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "Shader compilaton error: " << infoLog << std::endl;
		}
		return shader;
	}

	// Функция для создания программы
	unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
		// Компиляция шейдеров
		unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		// Создание шейдерной программы
		unsigned int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		// Проверка на ошибки линковки
		int success;
		char infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << "Linker error: " << infoLog << std::endl;
		}

		// Удаляем шейдеры после линковки
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}
}