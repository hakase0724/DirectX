#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "DXManager.h"
#include <sstream>

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	mDXSound = std::make_unique<DXSound>(hwnd);
	
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPS�J�E���^�[�𐶐�
	mFPSCountor = std::make_unique<FPSCountor>();
	//�e�Ǘ��N���X�𐶐�
	mBulletManager = std::make_unique<BulletManager>(this);
	mBulletManager->CreatePreBullets(1000);
	mBackGround = std::make_unique<BackGround>();
	mDXSound->Play();
}

//�Q�[���Ɏn�߂��炢��I�u�W�F�N�g�𐶐�
void DXGameObjectManager::CreateGameObject()
{
	//���@
	auto player = Instantiate();
	auto playerTex = player->AddComponent<DXTexture>();
	playerTex->SetTexture();
	player->SetTag(Tag::PlayerTag);
	player->AddComponent<Mover>();
	player->AddComponent<Player>();
	auto playerCol = player->AddComponent<SquareCollider2D>();
	playerCol->SetOneSide(playerCol->GetOneSide() / 30.0f);

	//�G
	auto enemy = Instantiate();
	enemy->SetTag(Tag::EnemyTag);
	auto enemyTex = enemy->AddComponent<DXTexture>();
	enemyTex->SetTexture(_T("Texture/Enemy.png"));
	auto texPos = enemy->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	auto enemyCol = enemy->AddComponent<SquareCollider2D>();
	enemyCol->SetOneSide(enemyCol->GetOneSide() / 2.0f);
	auto enemyCom = enemy->AddComponent<Enemy>();
	enemyCom->SetPlayer(player);

	//�w�i�p�摜1
	auto back = Instantiate();
	auto texBack = back->AddComponent<DXTexture>();
	texBack->SetTexture(_T("Texture/background.png"));
	auto backTransform = back->GetTransform();
	backTransform->Position.z = 2.0f;
	backTransform->Scale.x = 5.0f;
	backTransform->Scale.y = 5.0f;

	//�w�i�p�摜2
	auto back2 = Instantiate();
	auto texBack2 = back2->AddComponent<DXTexture>();
	texBack2->SetTexture(_T("Texture/background.png"));
	auto backTransform2 = back2->GetTransform();
	backTransform2->Position.y = 5.0f;
	backTransform2->Position.z = 2.0f;
	backTransform2->Scale.x = 5.0f;
	backTransform2->Scale.y = 5.0f;

	//�������w�i���Z�b�g
	mBackGround->SetBackGrounds(back, back2);

	//�E�̍���
	auto black = Instantiate();
	auto blackBack = black->AddComponent<DXTexture>();
	blackBack->SetTexture(_T("Texture/black.png"));
	auto blackTransform = black->GetTransform();
	blackTransform->Position.z = -1.0f;
	blackTransform->Position.x = 1.63f;
	blackTransform->Scale.y = 3.0f;

	//���̍���
	auto black2 = Instantiate();
	auto blackBack2 = black2->AddComponent<DXTexture>();
	blackBack2->SetTexture(_T("Texture/black.png"));
	auto blackTransform2 = black2->GetTransform();
	blackTransform2->Position.z = -1.0f;
	blackTransform2->Position.x = -1.63f;
	blackTransform2->Scale.y = 3.0f;
}

//�����Ă���R���C�_�[���擾
void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		//�A�N�e�B�u�łȂ���Ζ�������
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		//�R���C�_�[���Ȃ���Ζ�������
		if (com == nullptr) continue;
		auto tag = game->GetTag();
		//�L�����N�^�[
		if(tag == Tag::PlayerTag || tag == Tag::EnemyTag)
		{
			mShooterCollider2DList.push_back(com);
		}
		//�e
		else if(tag == Tag::PlayerBullet || tag == Tag::EnemyBullet)
		{
			mBulletCollider2DList.push_back(com);
		}
	}
}

bool DXGameObjectManager::IsCollisionJudge(Tag tag1, Tag tag2)
{
	//�����^�O�Ȃ画�肵�Ȃ�
	if (tag1 == tag2) return false;
	//���@�Ǝ��@�̒e�͔��肵�Ȃ�
	if (tag1 == Tag::PlayerTag && tag2 == Tag::PlayerBullet) return false;
	if (tag1 == Tag::PlayerBullet && tag2 == Tag::PlayerTag) return false;
	//�G�@�ƓG�@�̒e�͔��肵�Ȃ�
	if (tag1 == Tag::EnemyTag && tag2 == Tag::EnemyBullet) return false;
	if (tag1 == Tag::EnemyBullet && tag2 == Tag::EnemyTag) return false;
	//�e���m�͔��肵�Ȃ�
	if (tag1 == Tag::PlayerBullet && tag2 == Tag::EnemyBullet) return false;
	return true;
}

//�Q�[���I�u�W�F�N�g�����z��Ɋi�[�A������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
DXGameObject * DXGameObjectManager::Instantiate()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get(), this));
	mGameObjectCounter++;
	auto game = mTempGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->SetEnable(true);
	//�e�X�g���₷�����邽�ߎl�p�`�\���R���|�[�l���g��t���Ă���
	//�s�v�ɂȂ莟�����
	//game->AddComponent<DXSquare>();
	return game;
}

BOOL DXGameObjectManager::Update()
{
	//FPS���v�Z���f�o�b�O�E�B���h�E�ɏo�͂���
	auto fps = mFPSCountor.get()->GetFPS();
	std::stringstream stream;
	stream << fps << std::endl;
	OutputDebugStringA(stream.str().c_str());
	//�w�i�ړ�
	mBackGround->UpdateBackGrounds();

	//���݂̓��͏�Ԃ��擾
	mDXManager->GetDXInput()->SetInputState();
	mShooterCollider2DList.clear();
	mBulletCollider2DList.clear();
	StoreCollider2D();
	//���������I�u�W�F�N�g�̍X�V����
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();++itr)
	{
		auto game = itr->get();
		if(game->GetEnable()) itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::LateUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->LateUpdate();
	}
	
	//�����蔻��
	for(auto shooter:mShooterCollider2DList)
	{
		auto shooterTag = shooter->GetTag();
		//�L�����N�^�[���m�̓����蔻��
		for(auto shooter2:mShooterCollider2DList)
		{
			auto shooter2Tag = shooter2->GetTag();
			if (!IsCollisionJudge(shooterTag, shooter2Tag)) continue;
			shooter->IsCollision(shooter2);
			shooter2->IsCollision(shooter);
		}
		//�L�����N�^�[�ƒe�̓����蔻��
		for(auto bullet:mBulletCollider2DList)
		{
			auto bulletTag = bullet->GetTag();
			if (!IsCollisionJudge(shooterTag, bulletTag)) continue;
			shooter->IsCollision(bullet);
			bullet->IsCollision(shooter);
		}
	}

	//�L�����N�^�[�̏Փˉ���
	for(auto shooter:mShooterCollider2DList)
	{
		//�Փ˂��Ă�����
		if(shooter->IsCollided()) shooter->OnCollision();
	}
	//�e�̏Փˉ���
	for (auto bullet : mBulletCollider2DList)
	{
		//�Փ˂��Ă�����
		if (bullet->IsCollided()) bullet->OnCollision();
	}

}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	//���������I�u�W�F�N�g�̃����_�����O����
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->Render();
	}

	//��ʕ\��
	mDXManager->EndScene();

	//1�t���[�����ɒǉ��������ꂽ���̂�����ΊǗ����X�g�ɒǉ�����
	for (auto itr = mTempGameObjectsList.begin(); itr != mTempGameObjectsList.end(); ++itr)
	{
		//���g�̂Ȃ����̂͒ǉ����Ȃ�
		if (*itr == nullptr) continue;
		mGameObjectsList.push_back(std::move(*itr));
	}

	//���t���[���p�Ɉꎞ�z��̃N���A�Ɠ��͏󋵂̎擾
	mTempGameObjectsList.clear();
	mDXManager->GetDXInput()->SetPreBuffer();
}

//�w�肵��ID�̃Q�[���I�u�W�F�N�g�̃A�N�e�B�u���擾
bool DXGameObjectManager::IsEnable(UINT id)
{
	bool result = false;
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetID() != id) continue;
		if(game->GetEnable())
		{
			result = true;
			break;
		}
	}
	return result;
}

//ID���L�[�ɃQ�[���I�u�W�F�N�g��T��
DXGameObject * DXGameObjectManager::GetDXGameObjectWithID(UINT id)
{
	DXGameObject* pGame = nullptr;
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetID() != id) continue;
		pGame = game;
		break;
	}
	return pGame;
}


