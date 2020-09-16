#include "core.h"

t_scene scene;

glm::vec3 lightPos(0.8f, 0.8f, 0.8f);

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = 800 / 2.0;
GLfloat lastY = 600 / 2.0;

int WIDTH = 800, HEIGHT = 600; 
bool keys[1024];

timer time;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
unsigned int loadCubemap(vector<std::string> faces);

stack <t_model> stack_of_model;
stack <t_model> stack_of_moving_model;

void main_loop()
{
    init_GL();

    GLFWwindow* window = create_window(WIDTH, HEIGHT, "Engine");
    
//	light.collision_model = light.do_collis(light.curentPosition);
//	stack_of_model.push(light);

//	light.physical_properties.wieght = 500.0;

    scene.Model.add_3d_model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), "res/models/cube.obj", 32.0f, -1,
        "res/shaders/light.vs", "res/shaders/light.frag", scene.Shaders, "res/materials/united.png", "res/materials/unitedBlack.png");
    scene.Model.add_3d_model(glm::vec3(-0.8f, 0.8f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), "res/models/cube.obj", 0.0f, -1,
        "res/shaders/lamp.vs", "res/shaders/lamp.frag", scene.Shaders, "", "");

    scene.Light.add_dirLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.2f, -1.0f, -0.3f), 
        glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
    scene.Light.add_pointLight(glm::vec3(-0.8f, 0.8f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.05f, 0.05f, 0.05f), 
        glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.045, 0.0075);

    scene.SkyBox.addSkybox("res/shaders/skybox.vs","res/shaders/skybox.frag","res/maps/skybox/right.jpg", "res/maps/skybox/left.jpg", "res/maps/skybox/top.jpg", "res/maps/skybox/bottom.jpg", "res/maps/skybox/front.jpg", "res/maps/skybox/back.jpg");

    while (!glfwWindowShouldClose(window))
    {
        time.calc_time();

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		light.collision_model = light.do_collis(light.curentPosition);

        scene.draw_scene(camera, WIDTH, HEIGHT);

        glfwSwapBuffers(window);
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, time.delta_sec);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, time.delta_sec);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, time.delta_sec);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, time.delta_sec);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}