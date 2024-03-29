#pragma once
#include<d3d12.h>
#include <DirectXMath.h>
#include <wrl.h>

class Light
{
private://エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData {
		XMVECTOR lightv;
		XMFLOAT3 lightcolor;
	};

private://静的メンバ変数
	//デバイス
	static ID3D12Device* device;

public://静的メンバ関数
	static void StaticInitilaize(ID3D12Device* device);

	static Light* Create();

public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initilaize();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	void SetLightDir(const XMVECTOR& lightdir);

/// <summary>
/// ライト色をセット
/// </summary>
	void SetLightColor(const XMFLOAT3& lightcolor);

/// <summary>
/// 更新
/// </summary>
	void Update();

/// <summary>
/// 描画
/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

private: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向（単位ベクトル）
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
};

