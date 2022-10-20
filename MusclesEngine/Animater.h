#pragma once
class AnimationClip;
/// <summary>
/// �ִϸ�����~
/// Play�� ���ϴ� �ִϸ��̼� �̸� �־�����~
/// </summary>
class ENGINE_API Animater : public IComponents
{
public:
	Animater(GameObject* _GameObj);
	virtual ~Animater();
private:
	map<string, AnimationClip*> m_AnimClips;
	string m_PlayAnimName;
public:
	void Play(string _AniName);
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
};