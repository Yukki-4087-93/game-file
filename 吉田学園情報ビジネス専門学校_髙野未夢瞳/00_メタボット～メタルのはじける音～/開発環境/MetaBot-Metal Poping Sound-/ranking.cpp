//----------------------------------------------------------------------------------------
//
//ランキング
//Author::TAKANO
//
//----------------------------------------------------------------------------------------

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "application.h"
#include "ranking.h"
#include "bg.h"
#include "score.h"
#include "input.h"
#include "sound.h"
#include "ui.h"
#include <stdio.h>
#include <assert.h>

//--------------------------------------
//マクロ定義
//--------------------------------------
#define RANK_H				(80)					//縦幅
#define RANK_WD				(50)					//横幅

//--------------------------------------
//グローバル変数
//--------------------------------------
CBg *CRanking::m_pBg;
CScore *CRanking::m_pScore;
CUi *CRanking::m_pUi;
int CRanking::m_nBox;

//--------------------------------------
//コンストラクタ
//--------------------------------------
CRanking::CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{//データをクリアする
		m_SortData[i] = {};
		m_pScore = {};
	}

	m_nRankUpdate = 0;		//ランキングを更新するための変数のクリア
}

//--------------------------------------
//デストラクタ
//--------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------
//初期化
//--------------------------------------
HRESULT CRanking::Init()
{
	Load();					//読み込み
	BubbleSort(m_nBox);		//ソートデータ
	Save();					//保存

	//背景の生成
	m_pBg = CBg::Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f, 720.0f, CTexture::TEXTURE::TEXTYRE_RANKING_BG);

	//UIの生成
	m_pUi = CUi::Create(D3DXVECTOR3(360.0f, 383.0f, 0.0f), 80.0f, 600.0f, CTexture::TEXTURE::TEXTURE_RANKING_BUMMBER);

	for (int i = 0; i < MAX_RANKING; i++)
	{//ランキングを表示する
		m_pScore = CScore::Create(D3DXVECTOR3(520.0f + 40.0f * i, 137.0f + 123.0f * i, 0.0f), m_SortData[i]);
	}

	//UIの生成
	m_pUi = CUi::Create(D3DXVECTOR3(980.0f, 107.0f, 0.0f), 200.0f, 400.0f, CTexture::TEXTURE::TEXTURE_RANKING_NOW_UI);

	//取得したスコアを表示する
	m_pScore = CScore::Create(D3DXVECTOR3(920.0f, 157.0f, 0.0f), m_nBox);

	//サウンドの再生
	CApplication::GetSound()->Play(CSound::SOUND_BGM_RANKING);

	return S_OK;
}

//--------------------------------------
//終了
//--------------------------------------
void CRanking::Uninit()
{
	//サウンドの停止
	CApplication::GetSound()->Stop(CSound::SOUND_BGM_RANKING);

	if (m_pBg != nullptr)
	{
		m_pBg = nullptr;
	}

	if (m_pUi != nullptr)
	{
		m_pUi = nullptr;
	}

	if (m_pScore != nullptr)
	{
		for (int i = 0; i < MAX_RANKING; i++)
		{
			m_pScore = nullptr;
		}
	}

	//オブジェクトの解放
	CObject::ReleaseAll();
}

//--------------------------------------
//更新
//--------------------------------------
void CRanking::Update()
{
	//決定キー(ENTER)が押されたかどうか
	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE::MODE_TITLE);
	}
}

//--------------------------------------
//描画
//--------------------------------------
void CRanking::Draw()
{

}

//--------------------------------------
//ランキングの値設定
//--------------------------------------
void CRanking::Set(int nScore)
{
	m_nBox = nScore;
}

//--------------------------------------
//ランキングの情報取得
//--------------------------------------
int CRanking::Get()
{
	return m_nBox;
}

//--------------------------------------
//バブルソート(値入れ替え)
//--------------------------------------
void CRanking::BubbleSort(int nSort)
{
	m_nRankUpdate = -1;		//ソート番号を初期化

	if (nSort >= m_SortData[COMPARE_RANKING])
	{//受け取った値がランキングの値の一番下より大きかったら
		m_SortData[COMPARE_RANKING] = nSort;										//一番下の値に代入する
	}

	for (int nInData = 0; nInData < COMPARE_RANKING; nInData++)						//比較する方
	{
		for (int nChange = nInData + 1; nChange < MAX_RANKING; nChange++)			//比較される方
		{
			if (m_SortData[nInData] < m_SortData[nChange])
			{
				int nBox = m_SortData[nInData];					//変数に入ってきた値を代入
				m_SortData[nInData] = m_SortData[nChange];		//入ってきた値を変更する変数に代入
				m_SortData[nChange] = nBox;						//変更した値を箱の変数に代入
			}
		}
	}

	for (int nComparisonData = 0; nComparisonData < MAX_RANKING; nComparisonData++)
	{//値を比較する
		if (m_SortData[nComparisonData] == nSort)
		{//入れ替えたデータが入った値と同じなら
			m_nRankUpdate = nComparisonData;	//更新データに該当する番号に代入する
		}
	}
}

//--------------------------------------
//外部ファイルに保存
//--------------------------------------
void CRanking::Save()
{
	//ファイルに書き込む
	FILE *pFile;        //ファイルポインタを宣言

						//ファイルを開く
	pFile = fopen(FILE_NAME, "w");

	if (pFile != nullptr)
	{//ファイルが開けたとき
	 //ファイルに数値を書き出す
		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n", CRanking::m_SortData[i]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{//ファイルが開けなかったとき
		assert(false);				//プログラムを止める
	}
}

//--------------------------------------
//外部ファイルを開く
//--------------------------------------
void CRanking::Load()
{
	FILE *pFile;        //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(FILE_NAME, "r");

	if (pFile != nullptr)
	{//ファイルが開けたとき
	 //ファイルに数値を書き出す
		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_SortData[i]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{//ファイルが開けなかったとき
		assert(false);				//プログラムを止める
	}
}
