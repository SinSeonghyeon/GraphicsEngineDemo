#pragma once
class ENGINE_API BoxVolume : public IComponents
{
public:
	BoxVolume(GameObject* _GameObj); //부모를 게임 오브젝트를 인자로 받고 초기화
	virtual ~BoxVolume();

private:
	XMFLOAT3 m_VertexPos[8];
public:
	XMFLOAT3* GetVertexPos() { return m_VertexPos; }
	virtual void Start() override;
	virtual void Update() override; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render() override; // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
};

