#include "ShaderTools/DefaultRenderLoop.h"
#include "ShaderTools/RenderPass.h"
#include "ShaderTools/VertexArrayObjects/Quad.h"
#include <array>


// fragment shader taken from: https://www.shadertoy.com/view/ldS3DW
// original shader was "../Moritz_Ba/raytrace.frag"
auto sp = new ShaderProgram({"/Test_ShaderTools/Moritz_Ba/raytrace.vert", "/Test_ShaderTools/Moritz_Ba/raytrace3.frag"});

auto pass = new RenderPass(
    new Quad(), 
    sp
);

//TODO load own spheres / multiple spheres
//TODO avoid horizonatal line / change background?
//TODO make lightsource a fix point?
//TODO getTextures/depth/color  -> multiple passes
//TODO occlusion by other spheres
//TODO spheres with colors?



float size = 0.5;
float lum = 0.5;
glm::vec3 eye;

float lastTime, currentTime;

/*
glm::mat4 viewMat = {
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		0,	0,	0,	1,
};



glm::mat4 viewMat       = glm::lookAt(
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
    glm::vec3(0,0,0), // and looks at the origin
    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
);


glm::mat4 projMat = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

glm::mat4 mvp= projMat * viewMat;
*/

std::vector<glm::vec4> sphereVec;
std::vector<glm::vec3> mesh;

int main(int argc, char *argv[]) {
    sp -> printUniformInfo();
    sp -> printInputInfo();
    sp -> printOutputInfo();

    eye=glm::vec3(0.0,0.0,-3.0);

    sphereVec.push_back(glm::vec4(0.0, 0.25, 0.0, 0.5));
    sphereVec.push_back(glm::vec4(0.5, 0.5, -0.5, 0.5));

    mesh.push_back(glm::vec3(0.1, 0.2, -0.3));
    mesh.push_back(glm::vec3(0.4, 0.5, -0.6));
    mesh.push_back(glm::vec3(0.7, 0.8, -0.9));
    mesh.push_back(glm::vec3(0.10, 0.11, -0.12));
    mesh.push_back(glm::vec3(0.13, 0.14, -0.15));
    mesh.push_back(glm::vec3(0.16, 0.17, -0.18));
    mesh.push_back(glm::vec3(0.19, 0.20, -0.21));
    mesh.push_back(glm::vec3(0.22, 0.23, -0.24));
    mesh.push_back(glm::vec3(0.25, 0.26, -0.27));
    mesh.push_back(glm::vec3(0.28, 0.29, -0.30));
    mesh.push_back(glm::vec3(0.31, 0.32, -0.33));
    mesh.push_back(glm::vec3(0.34, 0.35, -0.36));
    mesh.push_back(glm::vec3(0.37, 0.38, -0.39));
    mesh.push_back(glm::vec3(0.40, 0.41, -0.42));
    mesh.push_back(glm::vec3(0.43, 0.44, -0.45));
    mesh.push_back(glm::vec3(0.46, 0.47, -0.48));
    mesh.push_back(glm::vec3(0.49, 0.50, -0.51));
    mesh.push_back(glm::vec3(0.52, 0.53, -0.54));
    mesh.push_back(glm::vec3(0.55, 0.56, -0.57));
    mesh.push_back(glm::vec3(0.58, 0.59, -0.60));
    mesh.push_back(glm::vec3(0.61, 0.62, -0.63));

    lastTime = glfwGetTime();

    pass -> update("sphereVec[0]", sphereVec);
    pass -> update("mesh[0]", mesh);

    renderLoop([]{
        currentTime = glfwGetTime();
        float deltaT = currentTime - lastTime;
        lastTime = currentTime;


        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) size  = glm::max(size - 0.5 * deltaT, 0.);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) size = glm::min(size + 0.5 * deltaT, 1.);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) lum  = glm::max(lum - 0.5 * deltaT, 0.);
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) lum = glm::min(lum + 0.5 * deltaT, 1.);

        pass
        -> clear(0, 0, 0, 0)
		-> update("iGlobalTime", lastTime)
		-> update("iResolution", glm::vec3(1280, 720, 1))
		-> update("eye", eye)
        -> update("scale", size)
        -> run();
    });
}
