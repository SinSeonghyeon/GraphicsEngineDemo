#include "GameEnginePCH.h"
#include "Transform.h"

Transform::Transform(GameObject* _GameObject) :IComponents(_GameObject),
m_Position(0.0f, 0.0f, 0.0f),
m_Right(1.0f, 0.0f, 0.0f),
m_Up(0.0f, 1.0f, 0.0f),
m_Look(0.0f, 0.0f, 1.0f),
m_Scale(1.0f, 1.0f, 1.0f),
m_LocalTM(),
m_WorldTM()
{
	MakeTM();
}

Transform::~Transform()
{
}

DirectX::XMFLOAT3 Transform::GetPosition() const
{
	return m_Position;
}

XMVECTOR Transform::GetXMPosition() const
{
	return XMLoadFloat3(&m_Position);
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
	MakeTM();
}

void Transform::SetPosition(const XMFLOAT3& v)
{
	m_Position = v;
	MakeTM();
}

void Transform::SetPosition(const XMVECTOR& v)
{
	SetPosition(v.m128_f32[0], v.m128_f32[1], v.m128_f32[2]);
}

XMFLOAT3 Transform::GetScale() const
{
	return m_Scale;
}

XMVECTOR Transform::GetXMScale() const
{
	return XMLoadFloat3(&m_Scale);
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
	MakeTM();
}

void Transform::SetScale(const XMFLOAT3& v)
{
	m_Scale = v;
	MakeTM();
}

DirectX::XMFLOAT3 Transform::GetRight() const
{
	return m_Right;
}

XMFLOAT3 Transform::GetUp() const
{
	return m_Up;
}

DirectX::XMFLOAT3 Transform::GetLook() const
{
	return m_Look;
}

XMVECTOR Transform::GetXMRight() const
{
	return XMLoadFloat3(&m_Right);
}

XMVECTOR Transform::GetXMUp() const
{
	return XMLoadFloat3(&m_Up);
}

XMVECTOR Transform::GetXMLook() const
{
	return XMLoadFloat3(&m_Look);
}

void Transform::SetRight(const FXMVECTOR& pos)
{
	XMStoreFloat3(&m_Right, pos);
	MakeTM();
}

void Transform::SetUp(const FXMVECTOR& pos)
{
	XMStoreFloat3(&m_Up, pos);
	MakeTM();
}

void Transform::SetLook(const FXMVECTOR& pos)
{
	XMStoreFloat3(&m_Look, pos);
	MakeTM();
}

void Transform::SetQuaternion(const XMVECTOR& _Quat)
{
	//XMQuaternionMultiply()
	XMMATRIX _R = XMMatrixRotationQuaternion(_Quat);

	m_R_TM = _R;

	m_Right.x = 1;	m_Up.x = 0;	m_Look.x = 0;
	m_Right.y = 0;	m_Up.y = 1;	m_Look.y = 0;
	m_Right.z = 0;	m_Up.z = 0;	m_Look.z = 1;
	XMStoreFloat3(&m_Right, XMVector3TransformNormal(XMLoadFloat3(&m_Right), _R));
	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), _R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), _R));
	MakeTM();

	//XMMATRIX SRT = m_S_MT * m_R_MT * m_T_MT;
	//SetXMLocalMT(SRT);
}

void Transform::SetRight(const XMFLOAT3& right)
{
	SetRight(XMLoadFloat3(&right));
	MakeTM();
}

void Transform::SetUp(const XMFLOAT3& up)
{
	SetUp(XMLoadFloat3(&up));
	MakeTM();
}

void Transform::SetLook(const XMFLOAT3& look)
{
	SetLook(XMLoadFloat3(&look));
	MakeTM();
}


void Transform::LookAt(FXMVECTOR target, FXMVECTOR pos)
{
	/// <summary>
	/// target - Pos
	/// 월드 업 (외적) LookVector 
	/// LookVector (외적) RightVector 
	/// </summary>
	XMFLOAT3 _floatUp(0.0f, 1.0f, 0.0f);
	FXMVECTOR _WorldUp = XMLoadFloat3(&_floatUp);

	XMVECTOR Z = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR X = XMVector3Normalize(XMVector3Cross(_WorldUp, Z));
	XMVECTOR Y = XMVector3Cross(Z, X);


	XMStoreFloat3(&m_Position, pos);
	XMStoreFloat3(&m_Look, Z);
	XMStoreFloat3(&m_Right, X);
	XMStoreFloat3(&m_Up, Y);
	MakeTM();
}

void Transform::LookAt(const XMFLOAT3& target, const XMFLOAT3& pos)
{
	XMVECTOR Pos = XMLoadFloat3(&pos);
	XMVECTOR Tartget = XMLoadFloat3(&target);

	LookAt(Tartget, Pos);
	MakeTM();
}

void Transform::LookAt(const XMFLOAT3& target)
{
	XMVECTOR Pos = XMLoadFloat3(&m_Position);
	XMVECTOR Tartget = XMLoadFloat3(&target);

	LookAt(Tartget, Pos);
	MakeTM();
}

void Transform::LookAt(GameObject* target)
{
	LookAt(target->GetTransform()->GetPosition());
}

void Transform::Strafe(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&m_Right);
	XMVECTOR p = XMLoadFloat3(&m_Position);
	XMStoreFloat3(&m_Position, XMVectorMultiplyAdd(s, r, p));
	MakeTM();
}

void Transform::Walk(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&m_Look);
	XMVECTOR p = XMLoadFloat3(&m_Position);
	XMStoreFloat3(&m_Position, XMVectorMultiplyAdd(s, l, p));
	MakeTM();
}

void Transform::WorldUpDown(float d)
{
	// mPosition += d * mUp
	XMVECTOR scale = XMVectorReplicate(d);
	XMVECTOR up = XMLoadFloat3(&m_Up);
	XMVECTOR position = XMLoadFloat3(&m_Position);
	XMStoreFloat3(&m_Position, XMVectorMultiplyAdd(scale, up, position));
	MakeTM();
}

void Transform::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_Right), angle);

	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), R));
	MakeTM();
}

void Transform::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&m_Right, XMVector3TransformNormal(XMLoadFloat3(&m_Right), R));
	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), R));
	MakeTM();
}

void Transform::SetXMLocalTM(XMMATRIX _M)
{
	XMStoreFloat4x4(&m_LocalTM, _M);
	XMVECTOR _Scale, _Transform, _Rotate;
	XMMatrixDecompose(&_Scale, &_Rotate, &_Transform, _M);

	XMMATRIX _R = XMMatrixRotationQuaternion(_Rotate); // 쿼터니언 너무 어려워~

	XMStoreFloat3(&m_Position, _Transform);
	XMStoreFloat3(&m_Scale, _Scale);

	m_Right.x = 1;	m_Up.x = 0;	m_Look.x = 0;
	m_Right.y = 0;	m_Up.y = 1;	m_Look.y = 0;
	m_Right.z = 0;	m_Up.z = 0;	m_Look.z = 1;
	XMStoreFloat3(&m_Right, XMVector3TransformNormal(XMLoadFloat3(&m_Right), _R));
	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), _R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), _R));

	MakeTM();
}

void Transform::SetXMWorldTM(XMMATRIX _M)
{
	if (m_GameObject->GetParent())
	{
		// WorldTM * ParentWorldTM-1 //Local 구하기.. 맞는듯 O 
		XMMATRIX _XMLocalTM = _M * MathHelper::Inverse(m_GameObject->GetParent()->GetTransform()->GetXMWorldTM());
		SetXMLocalTM(_XMLocalTM);
	}
	else
		SetXMLocalTM(_M);
}

XMMATRIX Transform::GetXMLocalTM()
{
	return XMLoadFloat4x4(&m_LocalTM);
}

XMFLOAT4X4 Transform::GetLocalTM()
{
	return m_LocalTM;
}

XMMATRIX Transform::GetXMWorldTM()
{
	if (m_GameObject->GetParent())
	{
		Transform* _Parent = m_GameObject->GetParent()->GetTransform();
		return GetXMLocalTM() * _Parent->GetXMWorldTM();
	}
	else
	{
		return GetXMLocalTM();
	}
}

XMFLOAT4X4 Transform::GetWorldTM()
{
	XMStoreFloat4x4(&m_WorldTM, GetXMWorldTM());
	return m_WorldTM;
}

void Transform::MakeTM()
{
	//일단 최적화 무시!
	XMMATRIX _S_TM = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);;

	XMMATRIX _T_TM = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);


	XMFLOAT4X4 _R_TM;

	_R_TM._11 = m_Right.x;	_R_TM._12 = m_Right.y;	_R_TM._13 = m_Right.z;	_R_TM._14 = 0;
	_R_TM._21 = m_Up.x;		_R_TM._22 = m_Up.y;		_R_TM._23 = m_Up.z;		_R_TM._24 = 0;
	_R_TM._31 = m_Look.x;	_R_TM._32 = m_Look.y;	_R_TM._33 = m_Look.z;	_R_TM._34 = 0;
	_R_TM._41 = 0;			_R_TM._42 = 0;			_R_TM._43 = 0;			_R_TM._44 = 1.0f;



	m_T_TM = _T_TM;
	m_R_TM = XMLoadFloat4x4(&_R_TM);
	m_S_TM = _S_TM;

	XMMATRIX SRT = m_S_TM * m_R_TM * m_T_TM;
	XMStoreFloat4x4(&m_LocalTM, SRT);

}

void Transform::Start()
{
}

void Transform::Update()
{
}

void Transform::Render()
{
}
