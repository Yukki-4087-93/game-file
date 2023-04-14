//---------------------------------------------------------
//
// �Q�[���Ǘ�
// Author::TAKANO
//
//---------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>

//----------------------------------------
//�O���錾
//----------------------------------------
class CCamera;
class CLight;
class CPlayer;
class CMeshField;
class CSkybox;
class CScore;
class CUi;
class CEnemyManager;
class CBildingManager;
class CEatDescription;

//----------------------------------------
//�N���X��`
//�Q�[���V�[���𑍊�����N���X
//----------------------------------------
class CGame
{
public:
/*�֐��Q*/
/*��ʊ֐�*/
	CGame();																//�R���X�g���N�^
	~CGame();																//�f�X�g���N�^
	HRESULT Init();															//������
	void Uninit();															//�I��
	void Update();															//�X�V
	void Draw();															//�`��

/*�Q�[���Ŋ֐�����֐�*/
public:
	static CCamera* GetCamera()	{ return m_pCamera; }							//�J�����̏��擾
	static CLight* GetLight() { return m_pLight; }								//���C�g�̏��擾
	static CPlayer* GetPlayer() { return m_pPlayer; }							//�v���C���[�̏��̎擾
	static CMeshField* GetMeshifild() { return m_pMeshifild; }					//���b�V���t�B�[���h�̏��擾
	static CSkybox* GetSkybox() { return m_pSkybox; }							//�X�J�C�{�b�N�X�̏��擾
	static CScore* GetScore() { return m_pScore; }								//�X�R�A�̏��擾
	static CUi* GetUi() { return m_pUi; }										//���[�U�[�C���^�[�t�F�[�X�̏��擾
	static CEnemyManager* GetEnemyManager() { return m_pEnemyManager; }			//�G�l�~�[�}�l�[�W���[�̏��擾
	static CBildingManager* GetBildingManager() { return m_pBildingManager; }	//�����}�l�[�W���[�̏��擾
	static CEatDescription* GetEatDescription() { return m_pEatDescription; }	//���i�����̏��擾

/*�����o�ϐ��Q*/
/*�Q�[���ŊǗ�����ϐ�*/
private:
	static CCamera* m_pCamera;											//�J�����̃|�C���^�[
	static CLight* m_pLight;											//���C�g�̃|�C���^�[
	static CPlayer* m_pPlayer;											//�v���C���[�̃|�C���^�[
	static CMeshField* m_pMeshifild;									//���b�V���t�B�[���h�̃|�C���^�[
	static CSkybox* m_pSkybox;											//�X�J�C�{�b�N�X�̃|�C���^�[
	static CScore* m_pScore;											//�X�R�A�̃|�C���^�[
	static CUi* m_pUi;													//���[�U�[�C���^�[�t�F�[�X�̃|�C���^�[
	static CEnemyManager* m_pEnemyManager;								//�G�l�~�[�W���[�}�l�̃|�C���^�[
	static CBildingManager* m_pBildingManager;							//�����}�[�l�W���̃|�C���^�[
	static CEatDescription* m_pEatDescription;							//���i�����̃|�C���^�[
};

#endif // !_GAME_H_
