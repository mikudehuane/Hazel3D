#include "hzpch.h"
#include "Light.h"
#include "Hazel/Core/Utils.h"

namespace Hazel {
    void DirectionalLight::Bind(const Ref<Shader>& shader) const
    {
        shader->Bind();  // TODO(islander): may be optimized out
        shader->SetFloat3("u_DirectionalLight.color", GetColor());
        shader->SetFloat3("u_DirectionalLight.direction", GetDirection());
        shader->SetFloat("u_DirectionalLight.ambient", GetAmbientIntensity());
        shader->SetFloat("u_DirectionalLight.diffuse", GetDiffuseIntensity());
        shader->SetFloat("u_DirectionalLight.specular", GetSpecularIntensity());
    }

    void PointLight::Bind(const Ref<Shader>& shader, int index) const
    {
        shader->Bind();  // TODO(islander): may be optimized out
        shader->SetFloat3(string_format("u_PointLights[%d].color", index), GetColor());
        shader->SetFloat3(string_format("u_PointLights[%d].position", index), GetPosition());
        shader->SetFloat(string_format("u_PointLights[%d].ambient", index), GetAmbientIntensity());
        shader->SetFloat(string_format("u_PointLights[%d].diffuse", index), GetDiffuseIntensity());
        shader->SetFloat(string_format("u_PointLights[%d].specular", index), GetSpecularIntensity());
        
        shader->SetFloat(string_format("u_PointLights[%d].constant", index), GetConstant());
        shader->SetFloat(string_format("u_PointLights[%d].linear", index), GetLinear());
        shader->SetFloat(string_format("u_PointLights[%d].quadratic", index), GetQuadratic());
    }

    void SpotLight::Bind(const Ref<Shader>& shader) const
    {
        shader->Bind();  // TODO(islander): may be optimized out
        shader->SetFloat3("u_SpotLight.color", GetColor());
        shader->SetFloat3("u_SpotLight.position", GetPosition());
        shader->SetFloat3("u_SpotLight.direction", GetDirection());
        shader->SetFloat("u_SpotLight.ambient", GetAmbientIntensity());
        shader->SetFloat("u_SpotLight.diffuse", GetDiffuseIntensity());
        shader->SetFloat("u_SpotLight.specular", GetSpecularIntensity());
        shader->SetFloat("u_SpotLight.constant", GetConstant());
        shader->SetFloat("u_SpotLight.linear", GetLinear());
        shader->SetFloat("u_SpotLight.quadratic", GetQuadratic());
        shader->SetFloat("u_SpotLight.cutOff", GetCutOff());
        shader->SetFloat("u_SpotLight.outerCutOff", GetOuterCutOff());
    }
}

