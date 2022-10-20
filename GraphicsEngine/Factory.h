#pragma once
/// <summary>
/// �޽��� ��� ������ Ŭ����.
/// �����ڸ� ������� �ʰ� ���丮�� ������ ��.
/// �ļ����� ���� �����͸� �� �����ؼ� �˾Ƽ� �������ּ���~
/// </summary>
class Factory
{
public:
	Factory();
	~Factory();

public:
	Mesh* CreateMesh(BulidInfo& _BulidInfo);
	IMesh* CreateGizmoMesh(GizmoInfo& _Info);

	void CreateSpecialMeshs();

private:
	Bulider* m_Bulider;
};

