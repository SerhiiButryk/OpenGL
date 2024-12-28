#include "Rectangle.h"

namespace xengine {

    Rectangle::Rectangle(Point point, float width, float height) : m_point(point), m_width(width), m_height(height) {
        create();
    }

    Vertex createVertex(Point p, Color c, TextureCoord t, float id) {
        return { p.x, p.y, /* position */
            c.r, c.g, c.b, c.alpha, /* color */
            t.coord_1, t.coord_2,id /* texture information */ };
    }

    void Rectangle::update() {
        create();
    }

    void Rectangle::create() {

        // Default texture coordinates
        TextureCoord c1 = {0.0f, 0.0f};
        TextureCoord c2 = {1.0f, 0.0f};
        TextureCoord c3 = {1.0f, 1.0f};
        TextureCoord c4 = {0.0f, 1.0f};

        float leftBottomX = m_point.x;
        float leftBottomY = m_point.y;

        m_dataBuffer[0] = createVertex({leftBottomX, leftBottomY},
            m_color,
            c1,
            m_textureIndex);

        m_dataBuffer[1] = createVertex({leftBottomX + m_width, leftBottomY},
            m_color,
            c2,
            m_textureIndex);

        m_dataBuffer[2] = createVertex({leftBottomX + m_width, leftBottomY + m_width},
            m_color,
            c3,
            m_textureIndex);

        m_dataBuffer[3] = createVertex({leftBottomX, leftBottomY + m_width},
            m_color,
            c4,
            m_textureIndex);
    }
}
