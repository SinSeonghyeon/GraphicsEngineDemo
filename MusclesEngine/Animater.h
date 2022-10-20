#pragma once
class AnimationClip;
/// <summary>
/// 애니메이터~
/// Play로 원하는 애니메이션 이름 넣어주자~
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