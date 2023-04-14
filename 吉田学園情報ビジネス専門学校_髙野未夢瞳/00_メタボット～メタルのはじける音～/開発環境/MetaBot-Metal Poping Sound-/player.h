//-----------------------------------------------------------------------------------------------------------
//
//�v���C���[	
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _PLAYER_H_													//��d�C���N���[�h�h�~�̃}�N����`

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
class CPlayer : public CObject
{
public:
/*�\����*/
	//���[�V�����̎��
	enum MOTION_TYPE
	{
		TYPE_NONE = -1,											//���[�V�������g�p���Ă��Ȃ�
		TYPE_IDLE = 0,											//�A�C�h�����[�V����(�����s�����Ă��Ȃ��Ƃ��Ɏg�p)
		TYPE_WARK,												//�������[�V����(�ړ��̂Ƃ��Ɏg�p)
		TYPE_HIGH_MEGA_CANNON,									//�n�C�E���K�E�L���m��!!!!
		TYPE_MAX												//�^�C�v�̍ő�l
	};

	//�L�[�\����
	struct KEY
	{
		float fPosX;											//�ʒuX
		float fPosY;											//�ʒuY
		float fPosZ;											//�ʒuZ
		float fRotX;											//�p�xX
		float fRotY;											//�p�xY
		float fRotZ;											//�p�xZ
	};

	//�L�[�̏��
	struct KEY_INFO
	{
		float fFrame;											//�t���[����
		KEY aKeyData[KEY_MAX];									//�L�[�̍ő吔
	};

	//���[�V�����\����
	struct MOTION_INFO
	{
		bool bMotion;											//���[�V�������Đ������ǂ���
		int nKeymax;											//�L�[�̍ő吔
		KEY_INFO aKeyInfo[MOTION_KYE];							//���[�V�����L�[�̍ő吔
	};

/*�����o�֐�*/
public:
	CPlayer();													//�R���X�g���N�^
	~CPlayer();													//�f�X�g���N�^
	static CPlayer * Create(D3DXVECTOR3 pos);					//�N���G�C�g
	HRESULT Init() override;									//������
	void Uninit() override;										//�I��
	void Update() override;										//�X�V
	void Draw() override;										//�`��
	D3DXVECTOR3 GetPos() { return m_pos; }						//�v���C���[�̏��擾
	D3DXVECTOR3 GetPosOld() { return m_posOld; }				//�v���C���[�̌Â����擾
	D3DXVECTOR3 GetMove() { return m_move; };					//�v���C���[�̈ړ��ʂ̎擾
	void PlayMotion();											//���[�V����
	int GetPlayerLife() { return m_nLife; }						//���C�t���擾
	void AddLife(int nAdd);										//���C�t�̉��Z
	void SubLife(int nSub);										//���C�t�̌��Z
	void AddAttack(float nAddAtc) { m_fAttack += nAddAtc; }		//�Η͂̉��Z
	void SubAttack(float nSubAtc) { m_fAttack -= nSubAtc; }		//�Η͂̉��Z
	void AddInertia(float fAddIr) { m_fInertia += fAddIr; }		//���x�̉��Z
	void SubInertia(float fSubIr) { m_fInertia += fSubIr; }		//���x�̌��Z
	void UpScale(float fScale);									//�X�P�[���A�b�v�֐�
	void SetScale(float fScale);
	D3DXVECTOR3 GetScale() { return m_Scale; }
	int GetCombo() { return m_nComboCounter; }
	void ResetCombo();

private:
	void DethPlayer(int nLifeChacker);							//�v���C���[�̎��S���̏���
	void Command();												//�v���C���[�̑���Ɋ֘A������̗p�֐�
	void MoveCalculation();										//�ړ��ʂ̌v�Z
	void NormalizRotation();									//�p�x�̐��K��
	void MotionManager(MOTION_TYPE type);						//���[�V�������Ǘ�����֐��N
	void CollisionManager();									//�����蔻��Ɋ֌W������̂��܂Ƃ߂�֐�

/*�����o�ϐ�*/
private:
	CModel* m_pParts[PARTS_MAX] = {};							//�v���C���[�̃p�[�c�̃|�C���^
	MOTION_TYPE m_motionType;									//���[�V�����^�C�v�������p�ϐ�
	D3DXVECTOR3 m_posOld;										//�ߋ��̈ʒu
	D3DXVECTOR3 m_rotDest;										//�ړI�̊p�x
	D3DXVECTOR3 m_move;											//�ړ���
	D3DXVECTOR3 m_Scale;										//�T�C�Y�A�b�v�p�ϐ�
	D3DXMATRIX m_mtxWorld;										//�}�g���b�N�X���[���h
	DWORD m_nNumMat;											//�}�e���A�����̐�
	LPD3DXBUFFER m_BuffMat;										//�}�e���A�����
	LPD3DXMESH m_Mesh;											//���b�V�����
	MOTION_INFO m_MotionInfo;									//���[�V�����̏��
	MOTION_TYPE m_Type;											//���[�V�����^�C�v���
	float m_fMotionCounter;										//���[�V�����J�E���^�[�ϐ�
	int m_nNumModel;											//���f����
	int m_nNumKey;												//���݂̃L�[�̔ԍ�

private:
	int m_nLife;												//�v���C���[�̐�����
	float m_fAttack;											//�v���C���[�̉Η�
	float m_fInertia;											//�v���C���[�̊���
	int m_nComboCounter;										//���j����ăX�R�A�����Z����Ƃ��̃R���{�Ɏg�p����ϐ�
	int m_nCountCombo;
	bool m_bDenger;
};

#endif // !PLAYER_H_
