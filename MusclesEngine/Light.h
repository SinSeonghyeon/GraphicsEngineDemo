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
	virtual void Update() override; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render() override; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

public:
	const CameraTypeEnum& GetType() { return m_Type; }
	const XMFLOAT4& GetAmbient() { return m_Ambient; } // �ֺ���
	const XMFLOAT4& GetDiffuse() { return m_Diffuse; } // N dot L
	const XMFLOAT4& GetSpecular() { return m_Specular; } //�ݻ籤
	const XMFLOAT3& GetAtt() { return m_Att; } // �Ÿ��� ���� ������

	void SetType(CameraTypeEnum _Type) { m_Type = _Type; }
	void SetAmbient(XMFLOAT4 _Ambient) { m_Ambient = _Ambient; } // �ֺ���
	void SetDiffuse(XMFLOAT4 _Diffuse) { m_Diffuse = _Diffuse; } // N dot L
	void SetSpecular(XMFLOAT4 _Specular) { m_Specular = _Specular; } //�ݻ籤
	void SetPosition(XMFLOAT3 _Position);// ��ġ
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); } // ��ġ
	void SetAtt(XMFLOAT3 _Att) { m_Att = _Att; } // �Ÿ��� ���� ������

private:
	CameraTypeEnum m_Type;

	XMFLOAT4 m_Ambient; // �ֺ���
	XMFLOAT4 m_Diffuse; // N dot L
	XMFLOAT4 m_Specular; //�ݻ籤



	XMFLOAT3 m_Att; // �Ÿ��� ���� ������

	float Range;
	float Spot;

	bool m_isInit;

	static int m_PointCount; // fx ���Ͽ� �Ѱ��ֱ� ����.
	int m_PointIndex; // ���� ���° ����Ʈ ����Ʈ����.

	DirectionalLight mDirLight;
	static PointLight mPointLight[10];
	SpotLight mSpotLight;
public:
	void Initialize(CameraTypeEnum _Type, XMFLOAT4 _Ambient, XMFLOAT4 _Diffuse, XMFLOAT4 _Specular);

};

