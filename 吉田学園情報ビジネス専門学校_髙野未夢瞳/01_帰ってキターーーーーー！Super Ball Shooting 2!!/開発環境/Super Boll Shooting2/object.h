//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "renderer.h"
//�J�b�gand�y�[�X�g�ŃN���X�w��

//--------------------------------------
//�}�N����`
//--------------------------------------
#define HI_SIZE		(100.0f)
#define WD_SIZE		(400.0f)
#define MAX_OBJ		(3280)

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CObject
{
public:
	enum ObjType
	{//�I�u�W�F�N�g�^�C�v
		OBJTYPE_NONE = 0,		//�g�p���Ă��Ȃ����
		OBJTYPE_PLAYER,			//�v���C���[
		OBJTYPE_ENEMY,				//�G�l�~�[
		OBJTYPE_BOSS,
		OBJTYPE_BULLET,				//�e
		OBJTYPE_EFFECT,				//�G�t�F�N�g
		OBJTYPE_EXPLOSION,			//����
		OBJTYPE_BG,					//�w�i
		OBJTYPE_PROTECT,			//�X
		OBJTYPE_LIFE,				//���C�t
		OBJTYPE_SCORE,
		OBJTYPE_UI,
		OBJTYPE_MAX				//�ő�
	};

	CObject();											//�R���X�g���N�^
	virtual ~CObject();									//�f�X�g���N�^
	virtual HRESULT Init() = 0;							//������
	virtual void Uninit() = 0;							//�I��
	virtual void Update() = 0;							//�X�V
	virtual void Draw() = 0;							//�`��
	virtual void Setpos(D3DXVECTOR3 pos) = 0;			//�ʒu�̐ݒ�
	D3DXVECTOR3 Getpos();								//�ʒu�̎擾
	static void ReleaseAll();							//�S�J��
	static void UpdateAll();							//�S�X�V
	static void DrawAll();								//�S�`��
	void Release();										//�ꕔ�J��
	CObject* Getobject(int nID);						//�I�u�W�F�N�g�̏��擾
	void SetObjectType(ObjType objtype);				//�I�u�W�F�N�g�̐ݒ�
	ObjType GetObjectType();							//�I�u�W�F�N�g�^�C�v�̎擾

protected:
	static CObject *m_apObject[MAX_OBJ];				//�I�u�W�F�N�g�N���X�̃|�C���^
	D3DXVECTOR3 m_pos;									//�ʒu
	int m_nID;											//�I�u�W�F�N�g�ؑ֗p��ID
	ObjType m_objType;									//�I�u�W�F�N�g�^�C�v�̗񋓂��g�p���邽�߂̕ϐ�
};

#endif // !_OBJECT_H_
