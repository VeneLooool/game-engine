#include "core.h"

t_shader vec_shader;
t_model lamp;
t_model light;

glm::vec3 lightPos(0.8f, 0.8f, 0.8f);

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = 800 / 2.0;
GLfloat lastY = 600 / 2.0;

int WIDTH = 800, HEIGHT = 600; 
bool keys[1024];

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;
//timer time;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

stack <t_model> stack_of_model;

void main_loop()
{
    init_GL();

    GLFWwindow* window = create_window(WIDTH, HEIGHT, "Engine");

    
    light.curent_shader = 0;
    light.load_obj("res/models/cube.obj");
    light.setup_mesh();
    light.shininess = 32.0f;

    light.spawnPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    light.curentPosition = light.spawnPosition;
	light.do_collis(light.collision_model);
	light.wieght = 500;
	stack_of_model.push(light);

    
    lamp.curent_shader = 0;
    lamp.load_obj("res/models/cube.obj");
    lamp.setup_mesh();
    lamp.pointLight.init_pointLight(lightPos, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.045, 0.0075);

	vec_shader.load_shader("res/shaders/light.vs", "res/shaders/light.frag");
    vec_shader.load_shader("res/shaders/lamp.vs", "res/shaders/lamp.frag");

    light.texture.load_texture("res/materials/united.png");
    light.texture.load_blikMap("res/materials/unitedBlack.png");

    while (!glfwWindowShouldClose(window))
    {
    //  calc_time(time);
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;  
        lastFrame = currentFrame;

        glfwPollEvents();
        do_movement();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vec_shader.vec[0].Use();
        vec_shader.vec[0].setVec3("viewPos", camera.Position);

        //PHYSIC 
        //{

            GLint spawnPosLoc = glGetUniformLocation(vec_shader.vec[0].Program, "spawnPosition");
            glUniform3f(spawnPosLoc, light.spawnPosition.x, light.spawnPosition.y, light.spawnPosition.z);
            GLint biasLoc = glGetUniformLocation(vec_shader.vec[0].Program, "bias");
            glUniform3f(biasLoc, light.curentPosition.x - light.spawnPosition.x, light.curentPosition.y - light.spawnPosition.y, light.curentPosition.z - light.spawnPosition.z);

        //}
        //PHYSIC 
        glm::mat4 view;
        glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        light.draw_model(vec_shader.vec[0], lamp, camera, view, projection);

        vec_shader.vec[1].Use();

        GLint modelLoc = glGetUniformLocation(vec_shader.vec[1].Program, "model");
        GLint viewLoc = glGetUniformLocation(vec_shader.vec[1].Program, "view");
        GLint projLoc = glGetUniformLocation(vec_shader.vec[1].Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(lamp.VAO);
        glDrawElements(GL_TRIANGLES, lamp.tri.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        

        glfwSwapBuffers(window);

		//calc_phys(); // äà ÄÀÀÀÀÀÀÀÀÀ, ñ÷èòàåì ôèçèêó
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
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
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