#pragma once

#include <base/TestCase.h>

namespace test {

    class ShapesComponentUI : public TestCase
    {
    public:

        enum class ShapeSelected : unsigned short {
            CIRCLE_SHAPE = 1,
            TRIANGLE_SHAPE,
            RECTANGLE_SHAPE
        };

        explicit ShapesComponentUI(Application* app);

        void onAttach() override;
        void onDetach() override;

        void onDraw() override;
        void onDrawUI() override;

    private:

        void addShape();
        void submitShape(xengine::Shape* shape, const char* shaderName);

        std::unique_ptr<xengine::Camera> m_camera = std::make_unique<xengine::Camera>(-1.6f, 1.6f, -0.9f, 0.9f);
        std::unique_ptr<xengine::RenderGL> m_renderer = std::make_unique<xengine::RenderGL>();
        std::unique_ptr<xengine::RenderData> m_data = std::make_unique<xengine::RenderData>();

        // Or
        // ... director = new xengine::RenderDirectorDebug();

        ShapeSelected m_shapeSelected = ShapeSelected::TRIANGLE_SHAPE;

        glm::vec4 m_color = { 1.0f, 0.0f, 0.0f, 1.0f};

        glm::vec3 p1 = {-0.5f, -0.5f, 0.0f};
        glm::vec3 p2 = {0.5f, -0.5f, 0.0f};
        glm::vec3 p3 = {0.0f, 0.5f, 0.0f};

        glm::vec3 center = { 0.0f, 0.0f, 0.0f };
        float textIndex = -1.0f;

        glm::vec2 widthAndHeight = { 1.0f, 1.0f };

    };
}
