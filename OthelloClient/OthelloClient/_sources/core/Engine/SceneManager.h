#pragma once
class IScene;

class SceneManager
{
public :
	SceneManager() = default;
	virtual ~SceneManager();

	IScene* GetActiveScene() const;
private :
	IScene* m_currentActiveScene = nullptr;
};