#pragma once

#include <base/TestCase.h>

namespace test {

    class ShapesComponentUI : public TestCase
    {
    public:

        enum class ShapesUIMode : unsigned short {
            CIRCLE_SHAPE = 1,
            TRIANGLE_SHAPE,
            RECTANGLE_SHAPE,
            INIT
        };

        explicit ShapesComponentUI(Application* app);

        void onAttach() override;
        void onDetach() override;

        void onDraw() override;
        void onDrawUI() override;

    private:

        void addShape(ShapesUIMode shape);
        void submitShape(xengine::Shape* shape, const char* shaderName);

        std::unique_ptr<xengine::Camera> m_camera = std::make_unique<xengine::Camera>(-1.6f, 1.6f, -0.9f, 0.9f);
        std::unique_ptr<xengine::RenderGL> m_renderer = std::make_unique<xengine::RenderGL>();
        std::unique_ptr<xengine::RenderData> m_data = std::make_unique<xengine::RenderData>();

        // Or
        // ... director = new xengine::RenderDirectorDebug();

        ShapesUIMode m_shapesUIModeCurrent = ShapesUIMode::INIT;
        unsigned int m_shapeId = {};

        float* m_color = {};
        float* m_colorTriangle = {};

        glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f};

    };
}
