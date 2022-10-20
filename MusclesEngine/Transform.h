#pragma once
#include "IComponents.h"
class ENGINE_API Transform : public IComponents
{
public:
	Transform(GameObject* _GameObject);
	virtual ~Transform();

public:

	// Get/Set world transform position.
	XMFLOAT3 GetPosition() const;
	XMVECTOR GetXMPosition() const;

	void SetPosition(float x, float y, float z);
	void SetPosition(const XMFLOAT3& v);
	void SetPosition(const XMVECTOR& v);

	XMFLOAT3 GetScale() const;
	XMVECTOR GetXMScale() const;

	void SetScale(float x, float y, float z);
	void SetScale(const XMFLOAT3& v);

	// Get transform basis vectors.
	XMFLOAT3 GetRight() const;
	XMFLOAT3 GetUp() const;
	XMFLOAT3 GetLook() const;

	XMVECTOR GetXMRight() const;
	XMVECTOR GetXMUp() const;
	XMVECTOR GetXMLook() const;

	void SetRight(const FXMVECTOR& pos);
	void SetUp(const FXMVECTOR& pos);
	void SetLook(const FXMVECTOR& pos);

	void SetQuaternion(const XMVECTOR& _Quat);
	void SetRight(const XMFLOAT3& right);
	void SetUp(const XMFLOAT3& up);
	void SetLook(const XMFLOAT3& look);

	// Define transform space via LookAt parameters.
	void LookAt(FXMVECTOR target, FXMVECTOR pos);
	void LookAt(const XMFLOAT3& target, const XMFLOAT3& pos);
	void LookAt(const XMFLOAT3& target);
	void LookAt(GameObject* target);

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);
	void WorldUpDown(float d);

	// Rotate the transform.
	void Pitch(float angle);
	void RotateY(float angle);



	void SetXMLocalTM(XMMATRIX _M);
	void SetXMWorldTM(XMMATRIX _M);

	XMMATRIX GetXMLocalTM();
	XMFLOAT4X4 GetLocalTM();

	XMMATRIX GetXMWorldTM();
	XMFLOAT4X4 GetWorldTM();

	void MakeTM();

	const XMMATRIX& GetTranformTM() { return m_T_TM; }
	const XMMATRIX& GetRotateTM() { return m_R_TM; }
	const XMMATRIX& GetScaleTM() { return m_S_TM; }

private:


	// 행렬을 만들기 위한 변수들
	XMFLOAT3 m_Position; // T
	XMFLOAT3 m_Scale; // S

	XMFLOAT3 m_Right; //R
	XMFLOAT3 m_Up;
	XMFLOAT3 m_Look;

	//나중에 스케일 추가하자 S?
	XMFLOAT4X4 m_LocalTM;
	XMFLOAT4X4 m_WorldTM;

	XMMATRIX m_T_TM;
	XMMATRIX m_R_TM;
	XMMATRIX m_S_TM;

public:
	virtual void Start();
	virtual void Update();
	virtual void Render();
};

