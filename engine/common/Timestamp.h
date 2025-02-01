#pragma once

namespace xengine {

    /**
     * Helper class for timestamp representation
     */
    class Timestamp final
    {
    public:
        Timestamp() = default;
        Timestamp(float time);

        auto getSeconds() const { return m_Time; }
        auto getMilliseconds() const { return m_Time * 1000.0f; }

        operator float() const { return m_Time; }

    private:
        float m_Time = 0.0f;
    };

}