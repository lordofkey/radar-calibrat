#pragma once

class Mymodfunc
{

#pragma region single cls //ʵ�ֵ�������
private:
	class Deleter
	{
	public:
		~Deleter()
		{
			if (Mymodfunc::m_pInstance != NULL)
			{
				delete Mymodfunc::m_pInstance;
				Mymodfunc::m_pInstance = NULL;
			}
		}
	};
	static Mymodfunc* m_pInstance;
	Mymodfunc(void);
	virtual ~Mymodfunc();   
public:
	HWND h_view;//��ͼ���ھ��
	HWND h_viewm; //У�������ͼ���
	HWND h_form;//���������
	static Mymodfunc *Mymodfunc::GetInstance();

#pragma endregion

public:
	// ��ȡ�����ļ�
	bool readfile(CString filename,CString path);
	// ��ȡ��n����Ƭ������
	bool Getpiecen(int n, int** x, int** y);
	bool Getpiecenmod(int n, int** x, int** y);
	bool Getpiecenmodr(int n, int** x, int** y);
	bool Getpiecenmod2(int n, int** x, int** y);
	bool Getpiecenmodr2(int n, int** x, int** y);
	bool firstmod(float height, float width, float distan,int carst ,int caren);//// ��һ��У������
	bool seconmod(float width, float height,int carst ,int caren);// ����У��
	bool traincut();//�Զ��г�


	// �ܲ���
	int totallayer;
	short *lpdata;//�״�����
	float sint[360];//�Ƕȶ�Ӧsinֵ
	float cost[360];//�Ƕȶ�Ӧcosֵ


	float lroix_min,lroix_max,lroiy_min,lroiy_max,rroix_min,rroix_max,rroiy_min,rroiy_max;//����궨����
	float mroix_min,mroix_max,mroiy_min,mroiy_max;//��׼���궨����


	CString inifilename;


	float sinm[360];//�Ƕȶ�Ӧsinֵ
	float cosm[360];//�Ƕȶ�Ӧcosֵ
	///һ��У�����
	float ang_delta[2]; 
	float x_delta[2];
	float y_delta[2];
	// һ��У��
	bool isfirmod[2];
	float w1[2];
	float w2[2];
	bool issecmod[2];//һ��У���Ƿ����
	int islr;//����У�����״�

	int stps[200];//�г���ʼλ��
	int lens[200];//����
	int cc;//�г����

	CString source;

	CString *pstr;//��Ϣ����

	CString version;
};
