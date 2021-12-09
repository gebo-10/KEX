#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#pragma  comment(lib,"Psapi.lib")
#pragma  comment(lib,"Userenv.lib")

#pragma comment(lib,"lua_slib.lib")
#pragma comment(lib, "uv_a.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")
#pragma comment(lib , "flatbuffers.lib")
//#pragma comment(lib, "freetype.lib")

#pragma comment(lib, "libzmq.lib")

#pragma comment(lib, "assimp.lib")
#ifdef _DEBUG
    #pragma comment(lib, "zlibstaticd.lib")
#else
    #pragma comment(lib, "zlibstatic.lib")
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <kengine/kengine.h>
kengine::KEngine* engine=nullptr;
int main()
{
    GLFWwindow* window;
    engine = &GetKEngineInstance();
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    //glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        error("glewInit failed");
        return -1;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)->void {engine->on_view_size(width,height); });
    engine->init(1024, 1024);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        engine->update();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    engine->quit();
    glfwTerminate();
    return 0;
}