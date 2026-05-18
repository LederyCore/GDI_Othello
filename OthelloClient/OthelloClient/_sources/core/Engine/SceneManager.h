#pragma once
class Scene;

class SceneManager
{
public :
	SceneManager();
	virtual ~SceneManager();

	static SceneManager* GetInstance();
	static Scene* GetActiveScene();

	void Initialize();
private :
	static SceneManager* Instance;

	Scene* m_currentActiveScene = nullptr;
};