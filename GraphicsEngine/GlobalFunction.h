#pragma once

#ifdef GRAPHICSENGINE_EXPORTS
#define GRPHICHS_API __declspec(dllexport)
#else
#define GRPHICHS_API __declspec(dllimport)
#endif

class IGraphicsEngine;
class IMesh;
struct GizmoInfo;
// 그래픽스 엔진 생성
extern "C" GRPHICHS_API IGraphicsEngine * CreateDXEngine();
extern "C" GRPHICHS_API void DeleteDXEngine(IGraphicsEngine * _pEngine);

// 이펙트 함수 랩핑.
namespace Wrapping
{
	extern "C" GRPHICHS_API void SetLights(const DirectionalLight & lights);
	extern  GRPHICHS_API void SetLights(const PointLight& lights, int Index);
	extern  GRPHICHS_API void SetLights(const SpotLight& lights);
	extern  GRPHICHS_API void SetLights(int& Count);
	extern  GRPHICHS_API IMesh* CreateGizmoMesh(GizmoInfo* _Info);

}

