#pragma once
#include <map>

/// <summary>
/// 미리 이펙트와 메쉬를 생성하고 땡겨쓸듯?
/// </summary>
class CASEParser;
class Mesh;
class Effects;
class Factory;
class ResourceManager
{

public:
	ResourceManager();
	~ResourceManager();
public:
	CASEParser* m_ASEParser;
	void init();
private:
	map<string, IMesh*> m_Mesh;

	Effects* m_Effects;
	Factory* m_Factory;

public:
	Factory* GetFactory() const { return m_Factory; }
	map<string, IMesh*>& GetMeshs() { return m_Mesh; }
};

