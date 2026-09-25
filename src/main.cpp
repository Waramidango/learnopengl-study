#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": "
              << description << std::endl;
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

    if (!glfwInit()) {
        std::cerr << "glfwInit() failed" << std::endl;
        return -1;
    }

    int platform = glfwGetPlatform();
    std::cout << "GLFW platform: " << platform << std::endl;
    std::cout << "GLFW initialized successfully" << std::endl;

    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "LearnOpenGL Study",
        nullptr,
        nullptr
    );

    if (!window) {
        const char* description = nullptr;
        int error = glfwGetError(&description);

        std::cerr << "glfwCreateWindow() failed\n";
        std::cerr << "Error: " << error << "\n";
        std::cerr << "Description: "
                  << (description ? description : "unknown")
                  << std::endl;

        glfwTerminate();
        return -1;
    }

    std::cout << "Window created successfully!" << std::endl;

    // ウィンドウを表示する
    glfwShowWindow(window);

    // OpenGLコンテキストをこのウィンドウに設定
    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;

        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL version: "
              << glGetString(GL_VERSION)
              << std::endl;

    // ウィンドウが閉じられるまで待つ
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // 後片付け
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}