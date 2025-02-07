#pragma once
#include <windows.h>
#include <DirectXMath.h>
using namespace DirectX;

class Camera;
class Mouse {

private:

	static Mouse m_Instance;

	Mouse() {}	;
	~Mouse() {};

	Mouse(const Mouse&) = delete;				//コピーコンストラクタ
	Mouse& operator=(const Mouse&) = delete;	//コピーアサインメントオペレーター

	//マウスカーソルの現時点のポジション
	int m_CurX = 0.0f;
	int m_CurY = 0.0f;
	//マウスカーソルの前１フレームのポジション
	int m_PreX = 0.0f;
	int m_PreY = 0.0f;

	float m_WheelDelta = 0.0f;	//ウィールの移動量

	bool m_LDown = false;	// 左押し
	bool m_RDown = false;	// 右押し
	bool m_WDown = false;	// ウィール押し

	bool m_LClick = false;	// 左クリック
	bool m_RClick = false;	// 右クリック
	bool m_WClick = false;	// ウィールクリック

	//bool m_LClickHandled = true;	// 左クリックが終わったかどうかを判断する用変数
	//bool m_RClickHandled = true;	// 右クリックが終わったかどうかを判断する用変数
	//bool m_WClickHandled = true;	// ウィールクリックが終わったかどうかを判断する用変数

public:

	void Init();
	void Update();

	void SetCam(Camera* cam);
	
	static Mouse& GetInstance() { return m_Instance; };

	int GetCurX() const { return m_CurX; };
	int GetCurY() const { return m_CurY; };
	int GetPreX() const { return m_PreX; };
	int GetPreY() const { return m_PreY; };

	void SetCurX(int x) { m_CurX = x; };
	void SetCurY(int y) { m_CurY = y; };

	bool IsLDown() const { return m_LDown; };
	bool IsRDown() const { return m_RDown; };

	void OnLDown() { m_LDown = true; }
	void OnRDown() { m_RDown = true; }
	void OnLUp() { m_LDown = false; }
	void OnRUp() { m_RDown = false; }

	void ResetLClickFlag()
	{
		m_LClick = false;
	}

	void ResetRClickFlag()
	{
		m_LClick = false;
	}


	//カーソル移動量の計算
	XMFLOAT2 MoveCal()
	{
		XMFLOAT2 xy = {};
		xy.x = m_CurX-m_PreX;
		xy.y = m_CurY-m_PreY;
		return xy;
	}

	

};

