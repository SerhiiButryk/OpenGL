#pragma once

#include "Layer.h"

#include <vector>
#include <cstddef>

namespace xengine {

    /**
     * A layer stack is an ordered list which we hold during runtime.
     * It could be changed dynamically. It has stuff that we render at any given moment.
     *
     * An example of layers:
     * 1) Our scene where we have all objects
     * 2) Some debug graphics which we can enable dynamically
     */
    class LayerStack final
    {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        Layer* operator[](size_t index)
        {
            return m_Layers[index];
        }

        const Layer* operator[](size_t index) const
        {
            return m_Layers[index];
        }

        size_t size() const { return m_Layers.size(); }

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

}
