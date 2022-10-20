#include "pch.h"
#include "GlobalFunction.h"


GRPHICHS_API IGraphicsEngine* CreateDXEngine()
{
	return new DXEngine();
}

GRPHICHS_API void DeleteDXEngine(IGraphicsEngine* _pEngine)
{
	delete _pEngine;
}

GRPHICHS_API void Wrapping::SetLights(const DirectionalLight& lights)
{
	Effects::TextureRenderFX->SetLights(lights);
}


GRPHICHS_API void Wrapping::SetLights(const PointLight& lights, int Index)
{
	Effects::TextureRenderFX->SetLights(lights, Index);
}

GRPHICHS_API void Wrapping::SetLights(const SpotLight& lights)
{
	Effects::TextureRenderFX->SetLights(lights);
}

GRPHICHS_API void Wrapping::SetLights(int& Count)
{
	Effects::TextureRenderFX->SetPointCount(Count);
}

GRPHICHS_API IMesh* Wrapping::CreateGizmoMesh(GizmoInfo* _Info)
{
	return DXEngine::GetInstance()->GetResourceManager()->GetFactory()->CreateGizmoMesh(*_Info);
}
