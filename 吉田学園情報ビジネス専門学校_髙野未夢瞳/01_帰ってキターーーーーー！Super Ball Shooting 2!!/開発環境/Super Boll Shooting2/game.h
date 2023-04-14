//---------------------------------------------------------
//
//�Q�[��
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
class CRenderer;
//class CInput;
class CBg;
class CPlayer;
class CTexture;
class CEnemyManager;
class Cprotect_City;
class CSoundManager;
class CScore;
class CUi;

//----------------------------------------
//�N���X��`
//�}�l�[�W���[
//----------------------------------------
class CGame
{
public:
	CGame();												//�R���X�g���N�^
	~CGame();												//�f�X�g���N�^
	HRESULT Init();											//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	static CPlayer* GetPlayer();							//�v���C���[���̎擾
	static Cprotect_City* GetProtect_City();				//�X�̏��̎擾
	static CUi* GetUi();
	static CScore* GetScore();

private:
	static CPlayer* m_pPlayer;											//�v���C���[�̃|�C���^�[
	static CEnemyManager* m_pEnemyManager;								//�G�l�~�[�̃|�C���^�[
	static Cprotect_City* m_pProtect_City;								//�X�̃|�C���^�[
	static CUi* m_pUi;
	static CScore* m_pScore;
};

#endif // !_GAME_H_
