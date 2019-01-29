#pragma once
#include "IComponent.h"

namespace MyDirectX
{
	class ScoreItemPool;
	class PlayScene;

	class ScoreItem :public Component
	{
	public:
		ScoreItem() {};
		~ScoreItem() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
		virtual void OnDisable() override;
		void SetScoreScene(PlayScene* scene) { mPlayScene = scene; }
		void SetScoreItemPool(ScoreItemPool* pool) { mPool = pool; }	
	private:
		PlayScene* mPlayScene;
		ScoreItemPool* mPool;
		float mAddScore = 50;
	};
}


