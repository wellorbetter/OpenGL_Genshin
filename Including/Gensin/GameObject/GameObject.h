#pragma once
class GameObject {
public:
	virtual void Update() = 0;
	virtual void Awake() = 0;
	virtual void Start() = 0;

	virtual void Destroy() = 0;
};
