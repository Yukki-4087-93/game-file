//-----------------------------------------------------------------------------------------------------------
//
//�G�l�~�[
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _ENEMY_H_												//���̃}�N����`���Ȃ���Ȃ�������
#define _ENEMY_H_												//��d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"

//----------------------------------------
//�O���錾
//----------------------------------------
class CModel;

//----------------------------------------
//�}�N����`
//----------------------------------------
#define KEY_MAX			(3)										//�L�[�̍ő吔
#define PARTS_MAX		(2)										//�L�[�̍ő吔
#define MOTION_KYE		(10)									//���[�V�����L�[�̍ő�l

//----------------------------------------
//�N���X��`
//�v���C���[�֘A
//----------------------------------------
class CEnemy : public CObject
{
public:
/*�\����*/

	//���[�V�����̎��
	enum MOTION_TYPE
	{//���[�V�����̐ݒ�
		TYPE_NONE = -1,						//���[�V�������g�p���Ă��Ȃ�
		TYPE_IDLE = 0,						//�A�C�h�����[�V����(�����s�����Ă��Ȃ��Ƃ��Ɏg�p)
		TYPE_WARK,							//�������[�V����(�ړ��̂Ƃ��Ɏg�p)
		TYPE_MAX							//�^�C�v�̍ő�l
	};

	//�L�[�\����
	struct KEY
	{
		float fPosX;						//�ʒuX
		float fPosY;						//�ʒuY
		float fPosZ;						//�ʒuZ
		float fRotX;						//�p�xX
		float fRotY;						//�p�xY
		float fRotZ;						//�p�xZ
	};

	//�L�[�̏��
	struct KEY_INFO
	{
		float fFrame;						//�t���[����
		KEY aKeyData[KEY_MAX];				//�L�[�̍ő吔
	};

	//���[�V�����\����
	struct MOTION_INFO
	{
		bool bMotion;						//���[�V�������Đ������ǂ���
		int nKeymax;						//�L�[�̍ő吔
		KEY_INFO aKeyInfo[MOTION_KYE];		//���[�V�����L�[�̍ő吔
	};

/*���J�����o�֐�*/
public:
	CEnemy();																	//�R���X�g���N�^
	~CEnemy();																	//�f�X�g���N�^
	static CEnemy * Create(const char* pfileParent,const char* pfileSon,D3DXVECTOR3 pos ,ObjType type,int nLife);		//�N���G�C�g
	HRESULT Init() override;													//������
	void Uninit() override;														//�I��
	void Update() override;														//�X�V
	void Draw() override;														//�`��
	D3DXVECTOR3 GetPos() { return m_pos; }										//�G�l�~�[�̏��擾
	void PlayMotion();															//���[�V����
	void HitNormal(int nCombo);													//�G�l�~�[�̓����蔻��
	void HitAttacker(int nCombo);												//�Η͂̍����G�l�~�[�ւ̓����蔻��
	void HitSpeeder(int nCombo);												//���x�̍����G�l�~�[�ւ̓����蔻��
	void HitCure(int nCombo);													//�񕜂�����G�l�~�[�ւ̓����蔻��
	void HitMulti(int nCombo);													//�����\�͎����G�l�~�[�ւ̓����蔻��
	void HitBoss(int nCombo);													//�{�X�N���X�ւ̓����蔻��
	void SetLife(int nLife) { m_nLife = nLife; }								//���C�t�̐ݒ�
	int GetLife() { return m_nLife; }											//���C�t�̎擾
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }							//���x�̐ݒ�
	float GetSpeed() { return m_fSpeed; }										//���x�̎擾
	void SubLife(int nSub);														//���C�t�̌��Z
	void SetScale(float fScale);												//�X�P�[���̐ݒ�
	D3DXVECTOR3 GetScale() { return m_Scale; }									//�X�P�[���̏��擾
	void SetNumber(int nNum) { m_nNumber = nNum; }								//�ԍ��̐ݒ�
	int GetNumber() { return m_nNumber; }										//�ԍ����擾	

/*����J�����o�֐�*/
private:
	void Command();												//�G�l�~�[�̑���Ɋ֘A������̗p�֐�
	void NormalizationRotation();								//�p�x�̐��K���p�֐�
	void MoveCalculation();										//�ړ��̌����ʂȂǂ��Ǘ�����֐�
	void Collision();											//�G�l�~�[�̓����蔻��Ɋ֘A������̂��܂Ƃ߂��֐�
	void MotionManager(MOTION_TYPE type);						//���[�V�������Ǘ�����֐��N
	void Chase();												//�Ǐ]�̐ݒ�
	void Run();													//������ݒ�
	void SelectAction();										//�e��G�l�~�[�̔��f�ݒ�

/*��ʃ����o�ϐ�*/
private:
	CModel* m_pParts[PARTS_MAX] = {};							//�G�l�~�[�̃p�[�c�̃|�C���^
	MOTION_TYPE m_motionType;									//���[�V�����^�C�v�������p�ϐ�
	D3DXVECTOR3 m_posOld;										//���_
	D3DXVECTOR3 m_move;											//�ړ���
	D3DXVECTOR3 m_Scale;										//�T�C�Y�A�b�v�p�ϐ�
	D3DXVECTOR3 m_rotDest;										//�ړI�̊p�x

	D3DXVECTOR3 m_VecPos;										//�Ǐ]���邽�߂̈ʒu�����߂�ϐ�
	D3DXVECTOR3 m_VecRot;										//�Ǐ]���邽�߂̌��������߂�ϐ�

	D3DXMATRIX m_mtxWorld;										//�}�g���b�N�X���[���h
	DWORD m_nNumMat;											//�}�e���A�����̐�
	LPD3DXBUFFER m_BuffMat;										//�}�e���A�����
	LPD3DXMESH m_Mesh;											//���b�V�����
	MOTION_INFO m_MotionInfo;									//���[�V�����̏��
	MOTION_TYPE m_Type;											//���[�V�����^�C�v���

	float m_fMotionCounter;										//���[�V�����J�E���^�[�ϐ�
	float m_fScaleSeter;										//�X�P�[���̐ݒ�ϐ�
	float m_fSpeed;												//�X�s�[�h�������ϐ�
	int m_nNumModel;											//���f����
	int m_nNumKey;												//���݂̃L�[�̔ԍ�
	int m_nRand;												//�G�l�~�[�̍s���Ɏg�p����ϐ�
	int m_nRandCount;											//�ړ��̃����_�����Ɏg�p����ϐ�
	int m_nLife;												//�G�l�~�[�̐�����
	int m_HitCount;												//�����蔻��œG�ɓ������Ă��鎞�Ԃ��v��ϐ�
	int m_nNumber;												//�G�l�~�[�̊e�i���o�[��ݒ肷��ϐ�
	int m_nRand_Up_Multi;										//ATTRIBUTE_MULTI�Ŏg�p����ϐ�
};

#endif // !_ENEMY_H_
