#include "GameEnginePCH.h"
#include "GizmoRenderer.h"
#include "..\GraphicsEngine\IMesh.h"

GizmoRenderer::GizmoRenderer(GameObject* _GameObject) :IComponents(_GameObject), m_Mesh(nullptr), m_isInit(false)
{

}

GizmoRenderer::~GizmoRenderer()
{
	finalize();
}

void GizmoRenderer::Start()
{

}

void GizmoRenderer::Update()
{
}

void GizmoRenderer::Render()
{
	XMFLOAT4X4 _Temp = m_GameObject->GetTransform()->GetWorldTM();
	XMMATRIX WorldMt = XMLoadFloat4x4(&_Temp);
	m_Mesh->DrawMesh(WorldMt);
}

void GizmoRenderer::OnEnterCollision(Collider* _Other)
{

}

void GizmoRenderer::OnStayCollision(Collider* _Other)
{
	SetColor(XMFLOAT4(1.0f, 0, 0, 1.0f));
}

void GizmoRenderer::OnExitCollision(Collider* _Other)
{
	SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
}

void GizmoRenderer::Initialize(GizmoInfo* _GizmoInfo)
{
	finalize();
	m_Mesh = Wrapping::CreateGizmoMesh(_GizmoInfo);
	m_isInit = true;
}

IMesh* GizmoRenderer::GetMesh()
{
	return m_Mesh;
}

void GizmoRenderer::SetColor(XMFLOAT4 _Color)
{
	m_Mesh->SetColor(_Color);
}

void GizmoRenderer::finalize()
{
	if (m_Mesh)
	{
		delete m_Mesh;
		m_Mesh = nullptr;
	}
}
