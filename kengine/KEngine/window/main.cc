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
//#pragma comment(lib, "assimpd.lib")
#pragma comment(lib, "zlibstaticd.lib")
//#pragma comment(lib, "Effekseerd.lib")
//#pragma comment(lib, "EffekseerRendererGL.lib")
#else

#pragma comment(lib, "zlibstatic.lib")
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <kengine/kengine.h>
kengine::KEngine* engine=nullptr;
//#include <Effekseer/Effekseer.h>
//#include <EffekseerRendererGL/EffekseerRendererGL.h>


void init_imgui(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void destory_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


int main()
{
    GLFWwindow* window;
    engine = &GetKEngineInstance();
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    //glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    //glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    
    glfwMakeContextCurrent(window);

    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        error("glewInit failed");
        return -1;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)->void {engine->on_view_size(width,height); });
    init_imgui(window);
    engine->init(1024, 1024);
    

    while (!glfwWindowShouldClose(window))
    {
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glClearColor(0, 0, 0, 0);
        //glClearDepth(1.0);
        //glEnable(GL_STENCIL_TEST);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

        engine->update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    engine->quit();
    destory_imgui();
    glfwTerminate();
    return 0;
}