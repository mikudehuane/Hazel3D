#pragma once

namespace Hazel {

	class Model
	{
	public:
		Model() = delete;
		Model(const std::string& path)
		{
			loadModel(path);
		}
	private:
		void loadModel(const std::string& path);
	};

}
