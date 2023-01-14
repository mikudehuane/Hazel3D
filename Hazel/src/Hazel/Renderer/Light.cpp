#include "hzpch.h"
#include "Light.h"

namespace Hazel {
    void DirectionalLight::Bind(const Ref<Shader>& shader)
    {
        shader->Bind();  // TODO(islander): may be optimized out
        shader->SetFloat3("u_DirectionalLight.color", GetColor());
        shader->SetFloat3("u_DirectionalLight.direction", GetDirection());
        shader->SetFloat("u_DirectionalLight.ambient", GetAmbientIntensity());
        shader->SetFloat("u_DirectionalLight.diffuse", GetDiffuseIntensity());
        shader->SetFloat("u_DirectionalLight.specular", GetSpecularIntensity());
    }
}

