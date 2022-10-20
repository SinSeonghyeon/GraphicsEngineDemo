#pragma once
class ENGINE_API BoxVolume : public IComponents
{
public:
	BoxVolume(GameObject* _GameObj); //�θ� ���� ������Ʈ�� ���ڷ� �ް� �ʱ�ȭ
	virtual ~BoxVolume();

private:
	XMFLOAT3 m_VertexPos[8];
public:
	XMFLOAT3* GetVertexPos() { return m_VertexPos; }
	virtual void Start() override;
	virtual void Update() override; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render() override; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
};

