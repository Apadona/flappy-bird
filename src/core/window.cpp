#include "window.hpp"

#include <engine_pch.hpp>

Window::Window( std::int16_t size_x, std::int16_t size_y, const std::string_view& title,
                std::int16_t pos_x, std::int16_t pos_y,
                int8_t gl_major_version, int8_t gl_minor_version ) :

                m_width(size_x), m_height(size_y), m_x(pos_x), m_y(pos_y), m_title(title)/*,
                m_gl_context(gl_major_version,gl_minor_version)*/
{
    HandleCreation();
}

Window::Window( const Window& other ) : m_width(other.m_width), m_height( other.m_height ),
                 m_x(other.m_x), m_y(other.m_y), m_title(other.m_title)
{
    HandleCreation();
}

Window::~Window()
{
    glfwDestroyWindow(glfw_window);
}

void Window::SetSize( std::int16_t size_x, std::int16_t size_y )
{
    m_width = size_x, m_height = size_y;
    glfwSetWindowSize(glfw_window,m_width,m_height);
}

void Window::SetPosition( std::int16_t pos_x, std::int16_t pos_y )
{
    m_x = pos_x, m_y = pos_y;
    glfwSetWindowPos(glfw_window,m_x,m_y);
}

void Window::SetTitle( const std::string_view& title )
{
    m_title = title;
    glfwSetWindowTitle(glfw_window,m_title.data());
}

void Window::Hide( bool hide )
{
    if( hide )
        glfwShowWindow(glfw_window);

    else
        glfwHideWindow(glfw_window);
}

void Window::Close()
{
    glfwDestroyWindow(glfw_window);
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(glfw_window);
}

void Window::MakeGLContext( std::int8_t major_version, std::int8_t minor_version )
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,minor_version);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Window::Update() const
{
    if( IsOpen() )
    {
        glfwPollEvents();
        
        return true;
    }

    return false;
}

void Window::ReDraw() const
{
    glfwSwapBuffers(glfw_window);
}

void Window::HandleCreation()
{
    MakeGLContext(3,1);

    glfw_window = glfwCreateWindow(m_width,m_height,m_title.data(),nullptr,nullptr);

    glfwMakeContextCurrent(glfw_window);

    glfwGetWindowPos(glfw_window,(int*)&m_x,(int*)&m_y);

    glfwSetErrorCallback(OnError);
    glfwSetMouseButtonCallback(glfw_window,OnMouseClick);
    glfwSetKeyCallback(glfw_window,OnKeyPressed);
    glfwSetCharCallback(glfw_window,OnCharKeyPressed);
    glfwSetFramebufferSizeCallback(glfw_window,OnWindowResize);
    glfwSetCursorPosCallback(glfw_window,OnMouseMove);
    glfwSetWindowCloseCallback(glfw_window,OnWindowClose);
}

void Window::OnError( int code, const char* error )
{
    std::cerr << "glfw error code occured!\ncode: " << code << "\n error message:" << error << std::endl;
}

void Window::OnKeyPressed( GLFWwindow* window, int key, int scan_code, int action, int modes )
{
}

void Window::OnCharKeyPressed( GLFWwindow* window, unsigned int key )
{
    std::cout << "key " << (char)key << " is pressed!\n";
}

void Window::OnMouseClick( GLFWwindow* window, int button, int action, int mode )
{
    if( action == GLFW_PRESS )
    {
        switch( button )
        {
            case GLFW_MOUSE_BUTTON_1:
                std::cout << "Left mouse button is pressed!\n";
            break;

            case GLFW_MOUSE_BUTTON_2:
                std::cout << "Right mouse button is pressed!\n";
            break;

            case GLFW_MOUSE_BUTTON_3:
                std::cout << "Middle mouse button is pressed!\n";
            break;

            case GLFW_MOUSE_BUTTON_4:
                std::cout << "Up mouse button is pressed!\n";
            break;

            case GLFW_MOUSE_BUTTON_5:
                std::cout << "Down mouse button is pressed!\n";
            break;
        }
    }
        
    if( action == GLFW_RELEASE )
    {
        switch( button )
        {
            case GLFW_MOUSE_BUTTON_1:
                std::cout << "Left mouse button is released!\n";
            break;

            case GLFW_MOUSE_BUTTON_2:
                std::cout << "Right mouse button is released!\n";
            break;

            case GLFW_MOUSE_BUTTON_3:
                std::cout << "Middle mouse button is released!\n";
            break;

            case GLFW_MOUSE_BUTTON_4:
                std::cout << "Up mouse button is released!\n";
            break;

            case GLFW_MOUSE_BUTTON_5:
                std::cout << "Down mouse button is released!\n";
            break;
        }
    }
}

void Window::OnMouseMove( GLFWwindow* window, double x, double y )
{
    //std::cout << "mouse is moved inside the window! with pos_x = " << x 
    //          << " and pos_y = " << y << std::endl;
}

void Window::OnWindowResize( GLFWwindow* window, int width, int height )
{
    std::cout << "Window is resized! new size = width :" << width << " height = "
              << height << std::endl;
    glViewport(0,0,width,height);
}

void Window::OnWindowMove( GLFWwindow* window, int pos_x, int pos_y )
{
    std::cout << "Window has moved! pos_x = " << pos_x << " pos_y = "
              << pos_y << std::endl;
}

void Window::OnWindowClose( GLFWwindow* window )
{
    std::cout << "window close message has been sent to window!\n";
    glfwSetWindowShouldClose(window,GL_TRUE);
}