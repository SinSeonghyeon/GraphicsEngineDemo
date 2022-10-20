#pragma once
enum class CameraTypeEnum
{
	Directional,
	Point,
	Spot
};

class ENGINE_API Light : public IComponents
{
public:
	Light(GameObject* _GameObject);
	~Light();
public:
	virtual void Start() override;
	virtual void Update() override; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render() override; // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더

public:
	const CameraTypeEnum& GetType() { return m_Type; }
	const XMFLOAT4& GetAmbient() { return m_Ambient; } // 주변광
	const XMFLOAT4& GetDiffuse() { return m_Diffuse; } // N dot L
	const XMFLOAT4& GetSpecular() { return m_Specular; } //반사광
	const XMFLOAT3& GetAtt() { return m_Att; } // 거리에 따른 감솧량

	void SetType(CameraTypeEnum _Type) { m_Type = _Type; }
	void SetAmbient(XMFLOAT4 _Ambient) { m_Ambient = _Ambient; } // 주변광
	void SetDiffuse(XMFLOAT4 _Diffuse) { m_Diffuse = _Diffuse; } // N dot L
	void SetSpecular(XMFLOAT4 _Specular) { m_Specular = _Specular; } //반사광
	void SetPosition(XMFLOAT3 _Position);// 위치
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); } // 위치
	void SetAtt(XMFLOAT3 _Att) { m_Att = _Att; } // 거리에 따른 감솧량

private:
	CameraTypeEnum m_Type;

	XMFLOAT4 m_Ambient; // 주변광
	XMFLOAT4 m_Diffuse; // N dot L
	XMFLOAT4 m_Specular; //반사광



	XMFLOAT3 m_Att; // 거리에 따른 감솧량

	float Range;
	float Spot;

	bool m_isInit;

	static int m_PointCount; // fx 파일에 넘겨주기 위함.
	int m_PointIndex; // 내가 몇번째 포인트 라이트인지.

	DirectionalLight mDirLight;
	static PointLight mPointLight[10];
	SpotLight mSpotLight;
public:
	void Initialize(CameraTypeEnum _Type, XMFLOAT4 _Ambient, XMFLOAT4 _Diffuse, XMFLOAT4 _Specular);

};

