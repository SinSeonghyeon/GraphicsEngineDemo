#include "GameEnginePCH.h"
#include "Light.h"

int Light::m_PointCount = 0;
PointLight Light::mPointLight[10];
Light::Light(GameObject* _GameObject) :IComponents(_GameObject), m_Type(), m_isInit(false)
{
}

Light::~Light()
{
}

void Light::Start()
{
}

void Light::Update()
{
	//광원 관련 나중에 옮길것.
	assert(m_isInit);


	Camera* _Camera = MuscleEngine::GetInstance()->GetMainCamera();


	switch (m_Type)
	{
	case CameraTypeEnum::Directional:
	{

		mDirLight.Ambient = m_Ambient;
		mDirLight.Diffuse = m_Diffuse;
		mDirLight.Specular = m_Specular;
		mDirLight.Direction = m_GameObject->GetTransform()->GetLook();
		Wrapping::SetLights(mDirLight);






		Transform* _Transform = m_GameObject->GetTransform();
		XMVECTOR R = _Transform->GetXMRight();
		XMVECTOR U = _Transform->GetXMUp();
		XMVECTOR L = _Transform->GetXMLook();
		XMVECTOR P = _Transform->GetXMPosition();

		// Keep camera's axes orthogonal to each other and of unit length.
		L = XMVector3Normalize(L);
		U = XMVector3Normalize(XMVector3Cross(L, R));

		// U, L already ortho-normal, so no need to normalize cross product.
		R = XMVector3Cross(U, L);

		// Fill in the view matrix entries.
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));
		// 역행렬을 구할 때 이렇게 한다고 한다.. 용책을 다시 확인해보자.

		XMFLOAT3 m_Right = _Transform->GetRight();
		XMFLOAT3 m_Up = _Transform->GetUp();
		XMFLOAT3 m_Look = _Transform->GetLook();

		XMStoreFloat3(&m_Right, R);
		XMStoreFloat3(&m_Up, U);
		XMStoreFloat3(&m_Look, L);
		XMFLOAT4X4 _View;
		_View(0, 0) = m_Right.x;
		_View(1, 0) = m_Right.y;
		_View(2, 0) = m_Right.z;
		_View(3, 0) = x;

		_View(0, 1) = m_Up.x;
		_View(1, 1) = m_Up.y;
		_View(2, 1) = m_Up.z;
		_View(3, 1) = y;

		_View(0, 2) = m_Look.x;
		_View(1, 2) = m_Look.y;
		_View(2, 2) = m_Look.z;
		_View(3, 2) = z;

		_View(0, 3) = 0.0f;
		_View(1, 3) = 0.0f;
		_View(2, 3) = 0.0f;
		_View(3, 3) = 1.0f;

		RECT _rect;
		GetClientRect(MuscleEngine::GetInstance()->GetHWND(), &_rect);
		float Width = _rect.left + _rect.right;
		float Height = _rect.top + _rect.bottom;


		if (Width)
		{
		XMMATRIX _ViewTemp = XMLoadFloat4x4(&_View); // 라이트 뷰
		XMMATRIX _Proj = XMMatrixOrthographicLH(Width, Height, 0.0f, 2000.0f); // 직교투영
		MuscleEngine::GetInstance()->GetGraphicsEngine()->ShadowUpdate(move(_ViewTemp), move(_Proj));
		}



	}


	break;
	case CameraTypeEnum::Point:
		mPointLight[m_PointIndex].Ambient = m_Ambient;
		mPointLight[m_PointIndex].Diffuse = m_Diffuse;
		mPointLight[m_PointIndex].Specular = m_Specular;
		mPointLight[m_PointIndex].Att = m_Att;
		mPointLight[m_PointIndex].Range = Range;
		mPointLight[m_PointIndex].Position = m_GameObject->GetTransform()->GetPosition();
		Wrapping::SetLights(*mPointLight, m_PointIndex);
		break;
	case CameraTypeEnum::Spot:
		mSpotLight.Position = _Camera->GetTransform()->GetPosition();
		mSpotLight.Direction = _Camera->GetTransform()->GetLook();
		mSpotLight.Ambient = m_Ambient;
		mSpotLight.Diffuse = m_Diffuse;
		mSpotLight.Specular = m_Specular;
		mSpotLight.Att = m_Att;
		mSpotLight.Spot = Spot;
		mSpotLight.Range = Range;
		Wrapping::SetLights(mSpotLight);
		break;
	default:
		break;
	}
}

void Light::Render()
{


}

void Light::SetPosition(XMFLOAT3 _Position)
{
	m_GameObject->GetTransform()->SetPosition(_Position);
}

void Light::Initialize(CameraTypeEnum _Type, XMFLOAT4 _Ambient, XMFLOAT4 _Diffuse, XMFLOAT4 _Specular)
{
	m_Type = _Type;
	m_Ambient = _Ambient;
	m_Diffuse = _Diffuse;
	m_Specular = _Specular;

	m_Att = XMFLOAT3(0.0f, 0.0f, 0.003f);

	Range = 50.0f; // 설정 만들어 줘야함.
	Spot = 96.0f; // 설정 만들어 줘야함.


	m_isInit = true;

	switch (m_Type)
	{
	case CameraTypeEnum::Directional:
	{


	}
	break;
	case CameraTypeEnum::Point:
		m_PointIndex = m_PointCount;
		m_PointCount++;
		Wrapping::SetLights(m_PointCount);
		assert(m_PointIndex <= 10);
		break;
	case CameraTypeEnum::Spot:
		break;
	default:
		break;
	}

}
