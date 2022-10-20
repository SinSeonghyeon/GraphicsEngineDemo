#pragma once
class AnimationKey;

class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();
private:
	float FrameCount;
	bool m_isPlay;
	bool m_isPuase;
	float m_Speed;
public:
	vector<AnimationKey*> m_AnimKeys;

	
	bool GetisPlaying() { return m_isPlay; }
	void Init(GameObject* _GameObj, int _Index);
	void Stop();
	void Pause();
	void Play();
	void Update();

};