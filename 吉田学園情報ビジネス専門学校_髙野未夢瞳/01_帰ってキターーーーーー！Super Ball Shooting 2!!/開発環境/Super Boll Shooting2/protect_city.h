//--------------------------------------------------------------------------------------
//
// �X
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _PROTECT_CITY_H_
#define _PROTECT_CITY_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"
#include "renderer.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class Cprotect_City : public CObject2D
{
public:
	/*��ԊǗ�*/
	enum CITY_STATE
	{
		STARE_NOMAL = 0,
		STARE_DAMAGE,
		STATE_MAX
	};

	Cprotect_City();																//�R���X�g���N�^
	~Cprotect_City();																//�f�X�g���N�^
	HRESULT Init()override;													//������
	static Cprotect_City * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd);		//�N���G�C�g
	void Update()override;													//�X�V
	void Draw()override;													//�`��
	void Uninit()override;													//�I��
	void Damage(int nDamage);
	void State();
	void SetState(Cprotect_City::CITY_STATE state);
	static int GetLife();

private:
	int m_Damage;									//�_���[�W���擾����ϐ�
	static int m_nLife;									//����
	int m_nColorCount;
	Cprotect_City::CITY_STATE m_nState;
};

#endif // !_PROTECT_CITY_H_
