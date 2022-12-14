#include "pch.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture() :m_RenderTargetTexture(nullptr), m_RenderTargetView(nullptr), m_ShaderResourceView(nullptr)
{

}

RenderTexture::~RenderTexture()
{
	Release();
}

bool RenderTexture::Initialize(int _Width, int _Height)
{
	Release();

	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ID3D11Device* device = DXEngine::GetInstance()->GetD3dDevice();

	// RTT 디스크립션을 초기화합니다.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// RTT 디스크립션을 세팅합니다.
	textureDesc.Width = _Width;
	textureDesc.Height = _Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// RTT를 생성합니다.
	result = device->CreateTexture2D(&textureDesc, NULL, &m_RenderTargetTexture);
	if (FAILED(result))
	{
		return false;
	}

	// 렌더 타겟 뷰에 대한 디스크립션을 설정합니다.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;
	
	// 렌더 타겟 뷰를 생성합니다.
	result = device->CreateRenderTargetView(m_RenderTargetTexture, &renderTargetViewDesc, &m_RenderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	// 셰이더 리소스 뷰에 대한 디스크립션을 설정합니다.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// 셰이더 리소스 뷰를 생성합니다.
	result = device->CreateShaderResourceView(m_RenderTargetTexture, &shaderResourceViewDesc, &m_ShaderResourceView);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void RenderTexture::Release()
{
	ReleaseCOM(m_RenderTargetTexture);
	ReleaseCOM(m_RenderTargetView);
	ReleaseCOM(m_ShaderResourceView);
}

void RenderTexture::ClearRenderTarget()
{
	// ClearRenderTarget함수는 BeginScene함수와 같으나 백버퍼가 아닌 
	// m_renderTargetView에 클리어가 이루어진다는 점이 다릅니다.
	// 이 함수는 매 프레임 RTT가 일어나기 전에 호출해 주어야 합니다.

	ID3D11DeviceContext* deviceContext = DXEngine::GetInstance()->Getd3dImmediateContext();
	float color[4];
	// 버퍼를 초기화할 색상을 지정합니다.
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;

	// Rendertarget을 초기화 합니다~~
	deviceContext->ClearRenderTargetView(m_RenderTargetView, color);
}

ID3D11RenderTargetView* RenderTexture::GetRenderTargetView()
{
	return m_RenderTargetView;

}

ID3D11ShaderResourceView* RenderTexture::GetSRV()
{
	return m_ShaderResourceView;
}
