#include "core.h"

t_scene scene;

glm::vec3 lightPos(0.8f, 0.8f, 0.8f);

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = 800 / 2.0;
GLfloat lastY = 600 / 2.0;

int WIDTH = 800, HEIGHT = 600; 
bool keys[1024];

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    scene.Model.add_3d_model(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.2f, 20.0f), "res/models/plane.obj", 32.0f, -1,
        "res/shaders/shadow_mapping.vs", "res/shaders/shadow_mapping.frag", scene.Shaders, "res/materials/united.png", "");

    scene.Light.add_dirLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.2f, -1.0f, -0.3f), 
        glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
    scene.Light.add_pointLight(glm::vec3(-0.8f, 0.8f, -0.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.05f, 0.05f, 0.05f), 
        glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.045, 0.0075);

    scene.SkyBox.addSkybox("res/shaders/skybox.vs","res/shaders/skybox.frag","res/maps/skybox/right.jpg", "res/maps/skybox/left.jpg", "res/maps/skybox/top.jpg", "res/maps/skybox/bottom.jpg", "res/maps/skybox/front.jpg", "res/maps/skybox/back.jpg");

    int suc;
    //Shader shader("res/shaders/shadow_mapping.vs", "res/shaders/shadow_mapping.fs", suc);
    Shader simpleDepthShader("res/shaders/shadow_mapping_depth.vs", "res/shaders/shadow_mapping_depth.frag", suc); // убрать это нужно для дебага лишь

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //shader.Use();
    //shader.setInt("diffuseTexture", 0);
    //shader.setInt("shadowMap", 1);ц
    //debugDepthQuad.use();
    //debugDepthQuad.setInt("depthMap", 0);

    // lighting info
    // -------------
    //glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

    while (!glfwWindowShouldClose(window))
    {
        time.calc_time();

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		light.collision_model = light.do_collis(light.curentPosition);

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view

        simpleDepthShader.Use();
        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        model = glm::translate(model, scene.Model.model_3d[0].transform.position);
        model = glm::scale(model, scene.Model.model_3d[0].transform.scale);
        simpleDepthShader.setMat4("model", model);
        glm::mat4 model1(1.0f);
        model1 = glm::translate(model1, scene.Model.model_3d[1].transform.position);
        model1 = glm::scale(model1, scene.Model.model_3d[1].transform.scale);
        simpleDepthShader.setMat4("model", model1);
        glm::mat4 model2(1.0f);
        model2 = glm::translate(model2, scene.Model.model_3d[2].transform.position);
        model2 = glm::scale(model2, scene.Model.model_3d[2].transform.scale);
        simpleDepthShader.setMat4("model", model2);

        //нужно все модели передать в simpleDepthShader
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.draw_scene(camera, WIDTH, HEIGHT, depthMap);

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