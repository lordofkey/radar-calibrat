//Date:2016-06-25 
//Author:���
//Description:���ļ�����ֱ������ϵ����Ļ����ϵ�໥ת������
//            ���޸Ĵ��ļ��������±����������ô��ļ���CPP�ļ�
class transformaxis
{
private:
	float ax,bx,ay,by;
public:
//���룺clientrect ������ʾ��hDC��rect    xs-x����ʼλ�� xe-x���ֹλ��  ys-y����ʼλ��  ye - y���ֹλ�� 
	transformaxis(CRect clientrect,float xs,float xe,float ys,float ye)
	{ 
		ax = (float)clientrect.Width()/(xe-xs);
		bx = -xs * ax;
		ay = (float)clientrect.Height()/(ys-ye);
		by = -ay*ye;
	}
//��Ļ����-��ԭʼ����
	float getox(int x)
	{
		return ((float)x-bx)/ax;
	}
	float getoy(int y)
	{
		return ((float)y-by)/ay;
	}
//ԭʼ����-����Ļ����
	int gettx(int x)
	{
		return (int)(ax*(float)x+bx);
	}
	int getty(int y)
	{
		return (int)(ay*(float)y+by);
	}
};