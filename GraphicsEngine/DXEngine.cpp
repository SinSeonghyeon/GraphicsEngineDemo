#include "pch.h"
#include "DXEngine.h"

DXEngine* DXEngine::m_Instance = nullptr;

DXEngine::DXEngine() : IGraphicsEngine(),
m_MainWnd(nullptr),
m_RasterizerState(nullptr)
{
	if (m_Instance)
		delete m_Instance;

	m_Instance = this;
}

DXEngine::~DXEngine()
{
	delete m_ResourceManager;
	delete m_RasterizerState;
	delete m_Device;
	delete m_Camera;
	delete m_RenderTarget;
	delete m_DepthStencil;
}

void DXEngine::Initialize(HWND hWnd, int Width, int height)
{
	m_MainWnd = hWnd;
	m_Device = new Device();
	m_Device->Initialize(hWnd, Width, height);

	m_Camera = new Camera();

	m_DepthStencil = new DepthStencil();
	m_RenderTarget = new RenderTarget();

	m_RasterizerState = new RasterizerState();
	m_ResourceManager = new ResourceManager();
	m_ResourceManager->init();

	// ���� �Ʒ��δ� OnReSzie �Լ��� �ٽ� �����.
	// ���� ��� ���� ����
	// �� ���ۿ� ���� ���� ��� �� ����.

	OnResize();
}


DXEngine* DXEngine::GetInstance()
{
	return m_Instance;
}

ResourceManager* DXEngine::GetResourceManager()
{
	return m_ResourceManager;
}

ID3D11Device* DXEngine::GetD3dDevice()
{
	return m_Device->GetDevice();
}

ID3D11DeviceContext* DXEngine::Getd3dImmediateContext()
{
	return m_Device->GetDeviceContext();
}

IDXGISwapChain* DXEngine::GetSwapChain()
{
	return m_Device->GetSwapChain();
}

DepthStencil* DXEngine::GetDepthStencil()
{
	return m_DepthStencil;
}

RenderTarget* DXEngine::GetRenderTarget()
{
	return m_RenderTarget;
}

Camera* DXEngine::GetCamera()
{
	return m_Camera;
}

void DXEngine::CameraUpdate(const XMMATRIX&& _View, const XMMATRIX&& _Proj, const XMFLOAT3&& _Pos)
{
	m_Camera->CameraUpdate(_View, _Proj, _Pos);
}

void DXEngine::ShadowUpdate(const XMMATRIX&& _View, const XMMATRIX&& _Proj)
{
	m_Camera->ShadowUpdate(_View, _Proj);
}

DirectX::XMMATRIX DXEngine::GetCameraView()
{
	return m_Camera->GetCameraView();
}

DirectX::XMMATRIX DXEngine::GetCameraProj()
{
	return m_Camera->GetCameraProj();
}

void DXEngine::BeginRender()
{
	m_RenderTarget->BeginRender();
	m_DepthStencil->Clear();
	Effects::TextureRenderFX->SetCurrentViewProj(GetCamera()->GetCurrentViewProj());
	Effects::TextureRenderFX->SetPrevViewProj(GetCamera()->GetPrevViewProj());
}

void DXEngine::EndRender()
{
	m_RenderTarget->EndRender();
	//// ��ü ���� �ؽ��Ŀ� �׸���!!
	//RenderToTexture();
	//// ����� â�� �׸���.
	//RenderDebugWindow();
	// presenting (����) - �ĸ� ���۸� ���� ���ۿ� ��ȯ�ؼ� ȭ�鿡 ǥ�õǰ� �ϴ� ��.
	// ����� �ĸ��� �����͸� ��ü�ϴ� ��.
	GetSwapChain()->Present(1, 0);
}

void DXEngine::OnResize()
{

	ATLTRACE("OnResize ����.\n");
	RECT _rect;
	GetClientRect(m_MainWnd, &_rect);
	// cache properties
	m_ClientWidth = float(_rect.right - _rect.left);
	m_ClientHeight = float(_rect.bottom - _rect.top);
	m_RenderTarget->OnResize();
	m_DepthStencil->OnResize();

}

IMesh* DXEngine::GetMeshResource(string _Name)
{
	return m_ResourceManager->GetMeshs()[_Name];
}

