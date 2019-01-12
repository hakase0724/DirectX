#pragma once
#include "EnemyBase.h"

namespace MyDirectX
{
	class NormalEnemy :public EnemyBase
	{
	public:
		NormalEnemy() {};
		~NormalEnemy() {};
		virtual void Initialize(DXGameObject* gameObject) override { EnemyBase::Initialize(gameObject); }
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void OnDisable() override;
	};
}


