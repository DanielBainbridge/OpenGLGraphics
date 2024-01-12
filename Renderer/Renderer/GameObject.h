#pragma once
#include "Graphics.h"
#include "Application.h"

class Animator;
class Mesh;
class Model;
class ShaderProgram;
class Scene;
class GameObject {
public:
	GameObject() {};
	GameObject(glm::mat4 transform, Model* model, ShaderProgram* shaderProgram);
	void SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale);
	void SetPosition(glm::vec3 position);
	void SetRotationEuler(glm::vec3 eulerAngles);
	void SetScale(glm::vec3 scale);
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetRotation() { return rotation; }
	glm::vec3 GetScale() { return scale; }


	void SetParent(GameObject* gameObject) {
		if (gameObject != this) { transformDirty = true; parent = gameObject; gameObject->AddChild(this); }
	}
	void SetDirtyTransform(bool isDirty) { transformDirty = isDirty; if (children.size() > 0) { SetAllChildrenDirty(); } }
	void SetDirtyUI(bool isDirty) { objectInUIHeirarchyDirty = isDirty; }
	GameObject* GetParent() { return parent; }
	std::vector<GameObject*> GetChildren() { return children; }
	void AddChild(GameObject* gameObject);
	glm::mat4 GetTransform();
	void Update(float deltaTime);
	void Draw(Scene* scene);
	void DrawIMGUI(Scene* scene);
	void DrawIMGUIWindow();
	std::string name;
	ShaderProgram* shader;
	Model* model = nullptr;
protected:
	glm::mat4 globalTransform = glm::mat4(1);
	glm::mat4 localTransform = glm::mat4(1);
	bool transformDirty = true;
	bool objectInUIHeirarchyDirty = true;
	glm::vec3 position, rotation, scale;
	int displayBoneIndex = 0;
	int currentAnimationNumber = 0;
	GameObject* parent;
	std::vector<GameObject*> children;
	void SetAllChildrenDirty();
};