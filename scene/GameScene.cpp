#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;


}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	//viewProjection_.eye = {0, 0, 10};
	//viewProjection_.target = {10, 0, 0};
	//viewProjection_.up = {cosf(XM_PI / 4.0f), sinf(XM_PI / 4.0f), 0.0f};
	//viewProjection_.fovAngleY = XMConvertToRadians(10.0f);
	//viewProjection_.aspectRatio = 1.0f;
	//viewProjection_.nearZ = 52.0f;
	//viewProjection_.farZ = 53.0f;
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	std::random_device seed_gen;

	std::mt19937_64 engine(seed_gen());

	//for (size_t i = 0; i < _countof(worldTransform_);i++) {
		//worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		//worldTransform_[i].rotation_ = {rotDist(engine), rotDist(engine), rotDist(engine)};
		//worldTransform_[i].translation_ = {posDist(engine), posDist(engine), posDist(engine)};
		//worldTransform_[i].Initialize();
	//}
	 //worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	// worldTransform_.rotation_ = {0.0f, XMConvertToRadians(45.0f), 0.0f};
	//worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	//worldTransform_.translation_ = {0.0f, 10.0f, 0.0f};
	worldTransform_[PartId::Root].Initialize();

	worldTransform_[PartId::Spine].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::Spine].parent_ = &worldTransform_[PartId::Root];
	worldTransform_[PartId::Spine].Initialize();
	                                
	worldTransform_[PartId::Chest].translation_ = {0, 2.6f, 0};
	worldTransform_[PartId::Chest].parent_ = &worldTransform_[PartId::Root];
	worldTransform_[PartId::Chest].Initialize();

	worldTransform_[PartId::Head].translation_ = {0, 2.5f, 0};
	worldTransform_[PartId::Head].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::Head].Initialize();

	worldTransform_[PartId::ArmL].translation_ = {2.5f, 2.5f, 0};
	worldTransform_[PartId::ArmL].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmL].Initialize();
	
	worldTransform_[PartId::ArmR].translation_ = {-2.5f, 2.5f, 0};
	worldTransform_[PartId::ArmR].parent_ = &worldTransform_[PartId::Chest];
	worldTransform_[PartId::ArmR].Initialize();
	
	worldTransform_[PartId::Hip].translation_ = {0, -5.0f, 0};
	worldTransform_[PartId::Hip].parent_ = &worldTransform_[PartId::Spine];
	worldTransform_[PartId::Hip].Initialize();
	
	worldTransform_[PartId::LegL].translation_ = {2.5f, -2.5f, 0};
	worldTransform_[PartId::LegL].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::LegL].Initialize();

	worldTransform_[PartId::LegR].translation_ = {-2.5f, -2.5f, 0};
	worldTransform_[PartId::LegR].parent_ = &worldTransform_[PartId::Hip];
	worldTransform_[PartId::LegR].Initialize();
	
	

	viewProjection_.Initialize();

	

	//std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	//std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
}

void GameScene::Update() {
	// if (input_->PushKey(DIK_W)) {
	//	viewProjection_.fovAngleY += 0.01f;
	//	viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	// } else if (input_->PushKey(DIK_S)) {
	//	viewProjection_.fovAngleY -= 0.01f;
	//	viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	// }
	//
	// viewProjection_.UpdateMatrix();
	//
	// debugText_->SetPos(50, 110);
	// debugText_->Printf("fovAngleY(Degree):%f", XMConvertToDegrees(viewProjection_.fovAngleY));
	//
	//	if (input_->PushKey(DIK_UP)) {
	//	viewProjection_.nearZ += 0.01f;
	// } else if (input_->PushKey(DIK_DOWN)) {
	//	    viewProjection_.nearZ -= 0.01f;
	//
	// }
	// debugText_->SetPos(50, 130);
	// debugText_->Printf("nearZ:%f", viewProjection_.nearZ);

	//{
	//	XMFLOAT3 move = {0, 0, 0};
	//
	//	const float kEyespeed = 0.2f;
	//
	//	if (input_->PushKey(DIK_W)) {
	//		move = {0, 0, kEyespeed};
	//
	//	} else if (input_->PushKey(DIK_S)) {
	//		move = {0, 0, -kEyespeed};
	//	}
	//
	//	viewProjection_.eye.x += move.x;
	//	viewProjection_.eye.y += move.y;
	//	viewProjection_.eye.z += move.z;
	//
	//	viewProjection_.UpdateMatrix();
	//
	//	debugText_->SetPos(50, 50);
	//	debugText_->Printf(
	//	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	//}
	//{
	//	XMFLOAT3 move = {0, 0, 0};
	//
	//	const float kTargetspeed = 0.2f;
	//
	//	if (input_->PushKey(DIK_LEFT)) {
	//		move = {kTargetspeed, 0, 0};
	//
	//	} else if (input_->PushKey(DIK_RIGHT)) {
	//		move = {-kTargetspeed, 0, 0};
	//	}
	//	viewProjection_.target.x += move.x;
	//	viewProjection_.target.y += move.y;
	//	viewProjection_.target.z += move.z;
	//
	//	viewProjection_.UpdateMatrix();
	//
	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf(
	//	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	//	  viewProjection_.target.z);
	//}
	//{
	//
	//
	//	const float kUpRotspeed = 0.05f;
	//
	//	if (input_->PushKey(DIK_SPACE)) {
	//		viewAngle += kUpRotspeed;
	//		viewAngle = fmodf(viewAngle, XM_2PI);
	//	}
	//	viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};
	//
	//	viewProjection_.UpdateMatrix();
	//
	//	debugText_->SetPos(50, 90);
	//	debugText_->Printf(
	//	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	//}
	XMFLOAT3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move = {-kCharacterSpeed, 0, 0};

	} else if (input_->PushKey(DIK_RIGHT)) {
		move = {kCharacterSpeed, 0, 0};
	}
	worldTransform_[0].translation_.x += move.x;
	worldTransform_[0].translation_.y += move.y;
	worldTransform_[0].translation_.z += move.z;

	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_[0].translation_.x += move.x,
	  worldTransform_[0].translation_.y += move.y, worldTransform_[0].translation_.z += move.z);

	worldTransform_[PartId::Root].UpdateMatrix();
	worldTransform_[PartId::Spine].UpdateMatrix();
	worldTransform_[PartId::Chest].UpdateMatrix();
	worldTransform_[PartId::Head].UpdateMatrix();

	worldTransform_[PartId::ArmL].UpdateMatrix();
	worldTransform_[PartId::ArmR].UpdateMatrix();
	worldTransform_[PartId::Hip].UpdateMatrix();
	worldTransform_[PartId::LegL].UpdateMatrix();
	worldTransform_[PartId::LegR].UpdateMatrix();

	const float kChestrot = 0.05;

	if (input_->PushKey(DIK_U)) {
		worldTransform_[PartId::Chest].rotation_.y -= kChestrot;
	} else if (input_->PushKey(DIK_I)) {
		worldTransform_[PartId::Chest].rotation_.y += kChestrot;
	}

	const float kHiprotSpeed = 0.05f;
	if (input_->PushKey(DIK_J)) {
		worldTransform_[PartId::Hip].rotation_.y -= kChestrot;
	} else if (input_->PushKey(DIK_K)) {
		worldTransform_[PartId::Hip].rotation_.y += kHiprotSpeed;
	}
}
	    void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	//for (size_t i = 0; i < _countof(worldTransform_); i++) {
	//	model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	//}
	//model_->Draw(worldTransform_[PartId::Root], viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_[PartId::Spine], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Chest], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Head], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::ArmR], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::Hip], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::LegL], viewProjection_, textureHandle_);
	model_->Draw(worldTransform_[PartId::LegR], viewProjection_, textureHandle_);
	


	//char str[100];
	//sprintf_s(
	//  str, "scale:(%f,%f,%f)", worldTransform_.scale_.x, worldTransform_.scale_.y,
	//  worldTransform_.scale_.z);
	//debugText_->Print(str, 100, 10, 1);
	//
	//char str2[100];
	//sprintf_s(
	//  str2, "rotation:(%f,%f,%f)", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	//  worldTransform_.rotation_.z);
	//debugText_->Print(str2, 100, 40, 1);
	//
	//char str3[100];
	//sprintf_s(
	//  str3, "translation:(%f,%f,%f)", worldTransform_.translation_.x,
	//  worldTransform_.translation_.y, worldTransform_.translation_.z);
	//debugText_->Print(str3, 100, 70, 1);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
