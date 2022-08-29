#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace Hazel
{
	// do not subclass
	// wrapper over a vector of layers
	class HAZEL_API LayerStack final
	{
	public:
		LayerStack();
		// layers are managed outside, but when destruct (usually called when application ends), all layers will be deleted
		~LayerStack();
		
		// layers are pushed to the first half
		// overlays are pushed to the second half
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		// the popped layer will not be deleted
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;  // the index to insert overlay (the number of bottom layers)
	};
}

