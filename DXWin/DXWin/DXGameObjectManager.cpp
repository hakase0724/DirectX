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
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPS�J�E���^�[�𐶐�
	mFPSCountor = std::make_unique<FPSCountor>();
	//�e�Ǘ��N���X�𐶐�
	mBulletManager = std::make_unique<BulletManager>(this);
	mBulletManager->CreatePreBullets();
}

//�Q�[���Ɏn�߂��炢��I�u�W�F�N�g�𐶐�
void DXGameObjectManager::CreateGameObject()
{
	/*auto test = Instantiate();
	test->SetName("MoveObject");
	test->SetTag(Tag::PlayerTag);
	test->AddComponent<Mover>();
	auto col = test->AddComponent<SquareCollider2D>();
	col->SetOneSide(col->GetOneSide() / 30.0f);
	auto player = test->AddComponent<Player>();
	test->AddComponent<DXSquare>();

	auto test3 = Instantiate();
	test3->SetName("NotMoveObject2");
	auto transfrom2 = test3->GetTransform();
	transfrom2.Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	test3->SetTransform(&transfrom2);
	test3->SetTag(Tag::EnemyTag);
	test3->AddComponent<SquareCollider2D>();
	test3->AddComponent<DXSquare>();*/

	auto test4 = Instantiate();
	auto tex = test4->AddComponent<DXTexture>();
	tex->SetTexture();
	test4->SetTag(Tag::PlayerTag);
	test4->AddComponent<Mover>();
	test4->AddComponent<Player>();
	auto col = test4->AddComponent<SquareCollider2D>();
	col->SetOneSide(col->GetOneSide() / 30.0f);


	auto texture2 = Instantiate();
	texture2->SetTag(Tag::EnemyTag);
	auto tex2 = texture2->AddComponent<DXTexture>();
	tex2->SetTexture(_T("Texture/Bullet3.png"));
	auto texPos = texture2->GetTransform();
	texPos->Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	texture2->AddComponent<SquareCollider2D>();
	texture2->GetComponent<MeshRenderer>()->SetDefaultColor(0, 1, 0, 1);
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


