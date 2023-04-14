//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include <d3dx9.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const int MAX_OBJ = 264;

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CObject
{
public:
	enum ObjType
	{//�I�u�W�F�N�g�^�C�v
		OBJTYPE_NONE = -1,												//�g�p���Ă��Ȃ����
		OBJTYPE_PLAYER = 0,												//�v���C���[
	/*�G�l�~�[�Y*/
		OBJTYPE_ENEMY_NORMAL,											//�ʏ�̃G�l�~�[
		OBJTYPE_ENEMY_ATTACKER,											//�Ἠ}�V�}�V�G�l�~�[
		OBJTYPE_ENEMY_SPEEDER,											//���x�}�V�}�V�G�l�~�[
		OBJTYPE_ENEMY_DOCTOR,											//�h�N�^�[�G�l�~�[
		OBJTYPE_ENEMY_MULTI,											//���������G�l�~�[
		OBJTYPE_ENEMY_BOSS,												//�{�X�G�l�~�[
	/*�r���_�[�Y*/
		OBJTYPE_BILDING_HELLOWARK,										//�n���[���[�N
		OBJTYPE_BILDING_LANDMARKTOWER,									//�����h�}�[�N�^���[
		OBJTYPE_BILDING_THUMBSUP,										//�T���Y�A�b�v
		OBJTYPE_BILDING_DTHUMBSUP,										//�_�u���T���Y�A�b�v
		OBJTYPE_BILDING_TEMPLE,											//��
		OBJTYPE_BILDING_APOSTLE,										//�g�k
		OBJTYPE_SPOWN_BILDING,											//�o���ʒu
	/*�E�H�[���Y*/
		OBJTYPE_WALL_WIDE,												//��
		OBJTYPE_WALL_HIGHT,												//��
		OBJTYPE_WALL_LONGLONG_WILD,										//��(LongVer.)
		OBJTYPE_WALL_LONGLONG_HIGHT,									//��(LongVer.)
		OBJTYPE_WALL_OUTSIDE_WIDE,										//�O��
		OBJTYPE_WALL_OUTSIDE_HIGHT,										//�O��
	/*�t�F���X�I�u�K�C�A*/
		OBJTYPE_FENCE_WIDE,												//�t�F���X
		OBJTYPE_FENCE_HIGHT,											//�t�F���X
	/*�A�E�^�[�Y*/
		OBJTYPE_MESHFIELD,												//���b�V���t�B�[���h
		OBJTYPE_SCORE,													//�X�R�A
		OBJTYPE_EFFECT,													//�G�t�F�N�g
		OBJTYPE_BG,														//�w�i
		OBJTYPE_UI,														//���[�U�[�C���^�[�t�F�[�X
		OBJTYPE_DESCRIPTION,											//�H�ׂ��Ȃ�����
		OBJTYPE_EAT_DESCRIPTION,										//�H�ׂ������
		OBJTYPE_EAT_DESCRIPTION_DENGER,									//�H�ׂ���l
		OBJTYPE_MAX														//�ő�
	};

	CObject();															//�R���X�g���N�^
	virtual ~CObject();													//�f�X�g���N�^
	virtual HRESULT Init() = 0;											//������
	virtual void Uninit() = 0;											//�I��
	virtual void Update() = 0;											//�X�V
	virtual void Draw() = 0;											//�`��
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }				//�ʒu�̐ݒ�
	D3DXVECTOR3 Getpos() { return m_pos; }								//�ʒu�̎擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						//�p�x�̐ݒ�
	D3DXVECTOR3 GetRot() { return m_rot; }								//�p�x�̈ʒu���̎擾
	static void ReleaseAll();											//�S�J��
	static void UpdateAll();											//�S�X�V
	static void DrawAll();												//�S�`��
	void Release();														//�ꕔ�J��
	static CObject* Getobject(int nID) { return m_apObject[nID]; }		//�I�u�W�F�N�g�̏��擾
	void SetObjectType(ObjType objtype) { m_objType = objtype; }		//�I�u�W�F�N�g�̐ݒ�
	ObjType GetObjectType() { return m_objType; }						//�I�u�W�F�N�g�^�C�v�̎擾

protected:
	static CObject *m_apObject[MAX_OBJ];								//�I�u�W�F�N�g�N���X�̃|�C���^
	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_rot;													//�p�x
	int m_nID;															//�I�u�W�F�N�g�ؑ֗p��ID
	ObjType m_objType;													//�I�u�W�F�N�g�^�C�v�̗񋓂��g�p���邽�߂̕ϐ�
};

#endif // !_OBJECT_H_
