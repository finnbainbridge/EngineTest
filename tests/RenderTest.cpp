#include <iostream>
#include <string>

#include "Engine/DevTools.hpp"
#include "Engine/Element3D.hpp"
#include "Engine/Engine.hpp"
// #include "Engine/DOM.hpp"
// #include "Engine/Threading.hpp"
#include "Engine/Input.hpp"
#include "Engine/Log.hpp"
#include "Engine/Renderer/Models.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Amber.hpp"
#include "Engine/Res.hpp"
#include "glm/fwd.hpp"
#include <memory>
#include <cstdlib>

class TriangleElement3D : public Engine::E3D::ManualMeshElement3D {
    private:
        std::shared_ptr<Engine::Renderer::RenderObject> model;
    public:
        TriangleElement3D(std::shared_ptr<Engine::Document> document);
        ~TriangleElement3D();
        virtual void process(float delta);
        virtual void init();

    protected:
};

TriangleElement3D::TriangleElement3D(std::shared_ptr<Engine::Document> document)
    : Engine::E3D::ManualMeshElement3D(document) {

    setTagName("triangle");
}

TriangleElement3D::~TriangleElement3D() {}
void TriangleElement3D::init()
{
    auto shader = document->renderer->addShaderProgram(Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/basic.vert"),
                Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/basic.frag"));

    setMesh(std::vector<glm::vec3> {glm::vec3(0, 1, 0), glm::vec3(1, -1, 0), glm::vec3(-1, -1, 0)}, 
            std::vector<glm::vec3> {glm::vec3(0, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0)},
            std::vector<glm::vec2> {glm::vec2(0, -1), glm::vec2(1, 1), glm::vec2(-1, 1)},
            std::vector<glm::uint32> {0, 1, 2}, shader);
}

void TriangleElement3D::process(float delta)
{
    rotate(1.5* delta, glm::vec3(0, 1, 0));
}

// Globals

std::shared_ptr<Engine::E3D::CameraElement3D> camera;
std::shared_ptr<Engine::Document> document;

// Render function
void render(float delta)
{
    // LOG_ASSERT(true);
    // Rotate the model
    // std::dynamic_pointer_cast<Engine::E3D::Element3D>(document->body->getElementsByTagName("element3d", true)[1])->rotate(1.5 * delta, glm::vec3(0, 1, 0));

}

int main(int argc, char const* argv[])
{
    LOG_INFO("Running RenderTest...");
    Engine::Res::ResourceManager::start(argc, argv);
    document = Engine::Document::createDocument();
    auto renderer = std::make_shared<Engine::Renderer::Amber>(document);
    renderer->createWindow(1024, 866, "Test");
    LOG_INFO("Window created");

    document->addElement("triangle", std::make_shared<Engine::DOM::ElementClassFactory<TriangleElement3D>>());

    // auto tri_element = std::make_shared<TriangleElement3D>(document);
    // document->body->appendChild(tri_element);
    // // auto shader = document->renderer->addShaderProgram(Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/basic.vert"),
    // //             Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/basic.frag"));

    // // tri_element->setMesh(std::vector<glm::vec3> {glm::vec3(0, 1, 0), glm::vec3(1, -1, 0), glm::vec3(-1, -1, 0)}, 
    // //         std::vector<glm::vec3> {glm::vec3(0, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0)},
    // //         std::vector<glm::vec2> {glm::vec2(0, -1), glm::vec2(1, 1), glm::vec2(-1, 1)},
    // //         std::vector<glm::uint32> {0, 1, 2}, shader);

    // auto tri_element2 = std::make_shared<TriangleElement3D>(document);
    // tri_element->appendChild(tri_element2);

    // auto green_shader = document->renderer->addShaderProgram(Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/basic.vert"),
    //             Engine::Res::ResourceManager::load<Engine::Renderer::ShaderResource>("shaders/green.frag"));

    // // tri_element2->setMesh(std::vector<glm::vec3> {glm::vec3(0, 1, 0), glm::vec3(1, -1, 0), glm::vec3(-1, -1, 0)}, 
    // //         std::vector<glm::vec3> {glm::vec3(0, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0)},
    // //         std::vector<glm::vec2> {glm::vec2(0, -1), glm::vec2(1, 1), glm::vec2(-1, 1)},
    // //         std::vector<glm::uint32> {0, 1, 2}, green_shader);
    // tri_element2->translate(glm::vec3(0,0,-1));
    // tri_element2->scale(glm::vec3(0.5, 0.5, 0.5));

    // auto meshelement = std::make_shared<Engine::E3D::MeshElement3D>(document);
    // meshelement->setResource(Engine::Res::ResourceManager::load<Engine::Models::MeshResource>("assets/green_GreenV2.1_retopo.005.emesh", true));
    // document->body->appendChild(meshelement);

    // Camera
    // camera = std::make_shared<Engine::DevTools::OrbitCamera3D>(document);
    camera = std::make_shared<Engine::E3D::CameraElement3D>(document);
    camera->translate(glm::vec3(0, 0, 5));
    // camera->init();

    document->body->appendChild(camera);

    // tri_element->saveToFile("/shaders/save_test.xml");

    // Test XML loading
    // document->body->appendChild(document->loadFromFile("assets/jmodl.xml"));
    srand (time(NULL));

    for (int i = 0; i < 11; i++)
    {
        LOG_INFO("Creating model "+std::to_string(i+1)+"/11");
        auto ele = std::make_shared<Engine::E3D::Element3D>(document);
        ele->translate(glm::vec3(-15 + i*3, 0, 0));
        if (rand() % 10 + 1 < 6)
        {
            LOG_INFO("Creating a jmodl");
            ele->appendChild(document->loadFromFile("assets/jmodl.xml"));
        }
        else
        {
            LOG_INFO("Creating a green");
            ele->appendChild(document->loadFromFile("assets/green_fixed.xml"));
        }
        
        document->body->appendChild(ele);
        // ele->callChildUpdate();
    }
    LOG_INFO("Models created");

    // Add sun
    // auto sun = std::make_shared<Engine::E3D::LightElement3D>(document);
    // sun->translate(glm::vec3(-20, 20, -20));
    // sun->diffuse = glm::vec3(0.5, 0.5, 0.5);
    // sun->ambient = glm::vec3(0.2, 0.2, 0.2);
    // sun->specular = glm::vec3(0, 0, 0);
    // sun->radius = 500;

    // document->body->appendChild(sun);

    // Add light
    auto light1 = std::make_shared<Engine::E3D::LightElement3D>(document);
    light1->translate(glm::vec3(0, 0, 3));
    light1->diffuse = glm::vec3(0.5, 0.5, 0.5);
    light1->ambient = glm::vec3(0.5, 0.5, 0.5);
    light1->specular = glm::vec3(0.1, 0.1, 0.1);
    light1->radius = 20;
    LOG_INFO("Light created");

    document->body->appendChild(light1);
    renderer->setCamera(camera);

    renderer->setMouseMode(Engine::Input::MouseMode::Free);
    LOG_INFO("Added nodes");
    // renderer->setCursorMode(Engine::Input::CursorMode::Hidden);

    renderer->mainloop(render);
}