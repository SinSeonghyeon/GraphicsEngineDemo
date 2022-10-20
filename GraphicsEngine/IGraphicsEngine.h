#pragma once
#include <windows.h>
#include <string.h>
#include "GlobalFunction.h"


class IMesh;
class DXEngine;

class IGraphicsEngine
{
public:
	IGraphicsEngine();
	virtual ~IGraphicsEngine();
	//
public:
	GRPHICHS_API virtual void Initialize(HWND hWnd, int Width, int height) abstract;
	GRPHICHS_API virtual void BeginRender() abstract;
	GRPHICHS_API virtual void EndRender() abstract;
	GRPHICHS_API virtual void OnResize() abstract;
	GRPHICHS_API virtual void CameraUpdate(const XMMATRIX&& _View, const XMMATRIX&& _Proj, const XMFLOAT3&& _Pos) abstract;
	GRPHICHS_API virtual void ShadowUpdate(const XMMATRIX&& _View, const XMMATRIX&& _Proj) abstract;
	GRPHICHS_API virtual IMesh* GetMeshResource(string _Name) abstract;
	GRPHICHS_API virtual float GetWidth() abstract;
	GRPHICHS_API virtual float GetHeight() abstract;


};
