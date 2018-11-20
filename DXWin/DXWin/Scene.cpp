#include "stdafx.h"
#include "Scene.h"

using namespace MyDirectX;

DXGameObject * Scene::Instantiate()
{
	auto game = mDXRescourceManager->Instantiate();
	game->SetScene(this);
	std::unique_ptr<DXGameObject> pGame;
	pGame.reset(game);
	mGameObjectsList.push_back(std::move(pGame));
	return mGameObjectsList.back().get();
}
