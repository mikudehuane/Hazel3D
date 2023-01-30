#include "Sandbox3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numeric>

Sandbox3D::Sandbox3D(): 
	m_CameraController(
		true, (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT
	), Layer("Sandbox3D")
{
	float aspectRatio = (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT;
}

void Sandbox3D::OnAttach()
{
	// box
	// vertices buffer
	float boxVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};
	// material
	Hazel::Ref<Hazel::Material> material = Hazel::CreateRef<Hazel::Material>(
		Hazel::Texture2D::Create("Sandbox/assets/textures/Container2.png"),
		Hazel::Texture2D::Create("Sandbox/assets/textures/Container2Specular.png"),
		nullptr,
		//Hazel::Texture2D::Create("Sandbox/assets/textures/Matrix.jpg"),
		m_BoxShininess
	);
	std::vector<Hazel::Vertex> boxVerticesVec;
	boxVerticesVec.reserve(36);
	for (int i = 0; i < 36; ++i)
	{
		boxVerticesVec.emplace_back(
			Hazel::Vertex{
				glm::vec3(boxVertices[i * 8 + 0], boxVertices[i * 8 + 1], boxVertices[i * 8 + 2]),
				glm::vec3(boxVertices[i * 8 + 5], boxVertices[i * 8 + 6], boxVertices[i * 8 + 7]),
				glm::vec2(boxVertices[i * 8 + 3], boxVertices[i * 8 + 4])
			}
		);
	}
	std::vector<uint32_t> boxIndicesVec = {
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35
	};
	m_BoxMesh = Hazel::CreateRef<Hazel::Mesh>(boxVerticesVec, boxIndicesVec, material);

	// *********************** light source

	// directional light
	m_DirectionalLight = Hazel::CreateRef<Hazel::DirectionalLight>(
		m_DirectionalLightProp.color, m_DirectionalLightProp.direction,
		m_DirectionalLightProp.ambient, m_DirectionalLightProp.diffuse, m_DirectionalLightProp.specular
	);

	// point light
	float lightVertices[] = {
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,

		-0.1f, -0.1f,  0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,

		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,

		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,

		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,

		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f,
		 0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f
	};
	Hazel::Ref<Hazel::VertexBuffer> pointLightVB = Hazel::VertexBuffer::Create(lightVertices, sizeof(lightVertices));
	pointLightVB->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position" }
		});
	// vertices array
	m_PointLightVA = Hazel::VertexArray::Create();
	m_PointLightVA->AddVertexBuffer(pointLightVB);
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	for (int i = 0; i < 4; ++i)
	{
		// TODO(islander): casual code, redundant copy
		PointLightProps prop = PointLightProps();
		prop.position = pointLightPositions[i];
		m_PointLightProps.push_back(prop);
		
		m_PointLights.push_back(Hazel::CreateRef<Hazel::PointLight>(
			prop.color, prop.position,
			prop.ambient, prop.diffuse, prop.specular,
			prop.constant, prop.linear, prop.quadratic
		));
	}

	// spot light
	m_SpotLight = Hazel::CreateRef<Hazel::SpotLight>(
		m_SpotLightProp.color, m_CameraController.GetCamera().GetPosition(), -m_CameraController.GetCamera().GetZAxis(),
		m_SpotLightProp.ambient, m_SpotLightProp.diffuse, m_SpotLightProp.specular,
		m_SpotLightProp.constant, m_SpotLightProp.linear, m_SpotLightProp.quadratic,
		glm::cos(glm::radians(m_SpotLightProp.cutOff)), glm::cos(glm::radians(m_SpotLightProp.cutOff + m_SpotLightProp.epsilon))
	);

	// view phong illumination clearly
	m_CameraController.SetPosition({ 0.0f, 0.0f, 5.0f });
	//m_CameraController.SetRotation(glm::normalize(glm::quat(1.0f, 0.09f, 0.04f, 0.0f)));
}

void Sandbox3D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	m_CameraController.SetPerspective(m_isPerspective);

	m_DirectionalLight->SetColor(m_DirectionalLightProp.color);
	m_DirectionalLight->SetDirection(m_DirectionalLightProp.direction);
	m_DirectionalLight->SetIntensity(
		m_DirectionalLightProp.ambient,
		m_DirectionalLightProp.diffuse,
		m_DirectionalLightProp.specular
	);

	for (int i = 0; i < m_PointLights.size(); ++i)
	{
		m_PointLights[i]->SetColor(m_PointLightProps[i].color);
		m_PointLights[i]->SetPosition(m_PointLightProps[i].position);
		m_PointLights[i]->SetIntensity(
			m_PointLightProps[i].ambient,
			m_PointLightProps[i].diffuse,
			m_PointLightProps[i].specular
		);
		m_PointLights[i]->SetAttenuation(
			m_PointLightProps[i].constant,
			m_PointLightProps[i].linear,
			m_PointLightProps[i].quadratic
		);
	}

	m_SpotLight->SetColor(m_SpotLightProp.color);
	m_SpotLight->SetPosition(m_CameraController.GetCamera().GetPosition());
	m_SpotLight->SetDirection(-m_CameraController.GetCamera().GetZAxis());
	m_SpotLight->SetIntensity(
		m_SpotLightProp.ambient,
		m_SpotLightProp.diffuse,
		m_SpotLightProp.specular
	);
	m_SpotLight->SetAttenuation(
		m_SpotLightProp.constant,
		m_SpotLightProp.linear,
		m_SpotLightProp.quadratic
	);
	m_SpotLight->SetCutOffs(
		glm::cos(glm::radians(m_SpotLightProp.cutOff)),
		glm::cos(glm::radians(m_SpotLightProp.cutOff + m_SpotLightProp.epsilon))
	);

	m_BoxMesh->GetMaterial()->SetShininess(m_BoxShininess);

	Hazel::Renderer::BeginScene(
		m_CameraController.GetCamera(),
		m_DirectionalLight, m_PointLights, m_SpotLight
	);
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_BoxPos);
		modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
		float angle = 20.0f * i;
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		Hazel::Renderer::Submit(
			m_BoxMesh, modelMatrix
		);
	}
	for (int i = 0; i < m_PointLights.size(); ++i)
	{
		Hazel::Renderer::Submit(
			m_PointLightVA, m_PointLights[i],
			glm::translate(glm::mat4(1.0f), m_PointLightProps[i].position)
		);
	}
	Hazel::Renderer::EndScene();
}

void Sandbox3D::OnDetach()
{
	m_BoxMesh.reset();

	m_DirectionalLight.reset();
	
	m_PointLightVA.reset();
	m_PointLights.clear();
	m_PointLightProps.clear();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Box Settings");
	ImGui::DragFloat3("Box Position", glm::value_ptr(m_BoxPos), 0.1f);
	ImGui::SliderFloat("Box Shininess", &m_BoxShininess, 0.0f, 256.0f);
	ImGui::End();

	ImGui::Begin("Directional Light");
	ImGui::DragFloat3("Direction", glm::value_ptr(m_DirectionalLightProp.direction), 0.1f);
	ImGui::SliderFloat3("Color", glm::value_ptr(m_DirectionalLightProp.color), 0.0f, 1.0f);
	ImGui::SliderFloat3("Intensity (a/d/s)", &(m_DirectionalLightProp.ambient), 0.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("Point Lights");
	for (int i = 0; i < m_PointLights.size(); ++i)
	{
		std::string hint = std::to_string(i);
		ImGui::RadioButton(hint.c_str(), &m_PointLightActivated, i);
		if (i < m_PointLights.size() - 1)
		{
			ImGui::SameLine();
		}
	}
	ImGui::DragFloat3("Position", glm::value_ptr(m_PointLightProps[m_PointLightActivated].position), 0.1f);
	ImGui::SliderFloat3("Color", glm::value_ptr(m_PointLightProps[m_PointLightActivated].color), 0.0f, 1.0f);
	ImGui::SliderFloat3("Intensity (a/d/s)", &(m_PointLightProps[m_PointLightActivated].ambient), 0.0f, 1.0f);
	ImGui::SliderFloat3("Attenuation", &(m_PointLightProps[m_PointLightActivated].constant), 0.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("Spot Light");
	ImGui::SliderFloat3("Color", glm::value_ptr(m_SpotLightProp.color), 0.0f, 1.0f);
	ImGui::SliderFloat3("Intensity (a/d/s)", &(m_SpotLightProp.ambient), 0.0f, 1.0f);
	ImGui::SliderFloat3("Attenuation", &(m_SpotLightProp.constant), 0.0f, 1.0f);
	ImGui::SliderFloat("Light CutOff", &m_SpotLightProp.cutOff, 0.0f, 90.0f);
	ImGui::SliderFloat("Light CutOff Epsilon", &m_SpotLightProp.epsilon, 0, 90.0f - m_SpotLightProp.cutOff);
	ImGui::End();

	ImGui::Begin("Camera Status");
	ImGui::Checkbox("Perspective", &m_isPerspective);
	// show the current camera state
	const glm::vec3& cameraPos = m_CameraController.GetCamera().GetPosition();
	ImGui::Text("Position: (%.1f, %.1f, %.1f)", cameraPos.x, cameraPos.y, cameraPos.z);
	ImGui::Text("AspectRatio: %.2f, Fovy: %.1f, Zoom: %.1f", m_CameraController.GetAspectRatio(), m_CameraController.GetFovy(), m_CameraController.GetZoomLevel());
	const glm::quat& cameraRotation = m_CameraController.GetCamera().GetRotation();
	ImGui::Text("Rotation: %.2f + %.2fi + %.2fj + %.2fk (Norm: %.2f)", cameraRotation.w, cameraRotation.x, cameraRotation.y, cameraRotation.z, glm::length(cameraRotation));
	const glm::vec3& cameraX = m_CameraController.GetCamera().GetXAxis();
	ImGui::Text("X: (%.2f, %.2f, %.2f)", cameraX.x, cameraX.y, cameraX.z);
	const glm::vec3& cameraY = m_CameraController.GetCamera().GetYAxis();
	ImGui::Text("Y: (%.2f, %.2f, %.2f)", cameraY.x, cameraY.y, cameraY.z);
	const glm::vec3& cameraZ = m_CameraController.GetCamera().GetZAxis();
	ImGui::Text("Z: (%.2f, %.2f, %.2f)", cameraZ.x, cameraZ.y, cameraZ.z);
	ImGui::End();
}

void Sandbox3D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
