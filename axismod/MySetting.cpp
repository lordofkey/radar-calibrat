//Date:2016-07-2
//Author:���
//Description:���ļ����������ļ���д�����xmlЭ��
//            ���������밴��˵�������޸�


#include "StdAfx.h"
#include "MySetting.h"
#define f2str(target) sprintf_s(buffer,100,"%.2f",target);
#define i2str(target) sprintf_s(buffer,100,"%d",target);

MySetting::MySetting(void)
{
	pDoc = NULL;
	xmlRoot = NULL;
	pProInstruction = NULL;
	pRootElement = NULL;
	plineElement = NULL;
	pcalitimeElement = NULL;
	szXmlFile  = "setting.xml";

	memset(calipar,0,sizeof(calipar));
	memset(rradar,0,sizeof(rradar));
	memset(lradar,0,sizeof(lradar));
}
MySetting::~MySetting(void)
{
}
//���� �ļ���
//���� �Ƿ��ʼ���ɹ�
bool MySetting::initialdom(void)
{
	HRESULT hr = pDoc.CreateInstance(_uuidof(MSXML2::DOMDocument40));
	if (FAILED(hr))
	{
		::MessageBox(NULL,"�޷�����DOM�ļ����󣬼���Ƿ�װMS XML Parser���п⣡","����",MB_OK);
		return false;
	}

	VARIANT_BOOL bXmlLoad = pDoc->load((_variant_t)szXmlFile);
	if (!bXmlLoad) // ����ʧ��
	{
		if(IDOK == ::MessageBox(NULL,"���������ĵ�ʧ�ܣ����ȷ���������³�ʼ������","����",MB_OKCANCEL))
		{
			pProInstruction = pDoc->createProcessingInstruction((_bstr_t)(char*)"xml", (_bstr_t)(char*)"version=\"1.0\" encoding=\"utf-8\"");
			pDoc->appendChild((MSXML2::IXMLDOMNode*)pProInstruction);
			pRootElement =  pDoc->createElement((_bstr_t)(char*)"lines");   
			pDoc->PutRefdocumentElement(pRootElement); // pXMLDomDoc->documentElement = pRootElement;
			pDoc->save((_variant_t)szXmlFile);
		}
		else
		{
			return false;
		}
	}
	else
	{
		pRootElement = pDoc->GetdocumentElement();
	}
	return true;
}
//���룺��·����
//�������·�ڵ�
int MySetting::checkline(CString linename)
{
	long length = 0;
	MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
	MSXML2::IXMLDOMElementPtr pElement = NULL;
	pNodeList = pDoc->getElementsByTagName((_bstr_t)"Line");
	pNodeList->get_length(&length);
	for(int i = 0;i < length; i++)
	{
		if(strcmp(pNodeList->Getitem(i)->Getattributes()->Getitem(0)->Gettext(),linename) == 0)
		{
			printf("����������·:%s\n",pNodeList->Getitem(i)->Getattributes()->Getitem(0)->Gettext(),linename);
			pElement = pNodeList->Getitem(i);
			break;
		}
	}
	if(pElement == NULL)
	{
		pElement = pDoc->createElement((_bstr_t)"Line");
		pElement->setAttribute((_bstr_t)"name",linename.GetBuffer());
		pRootElement->appendChild(pElement);
	}
	plineElement = pElement;
	return 1;
}
//<lines><line><caltime>
void MySetting::precali(void)
{
	CTime now = CTime::GetCurrentTime();
	MSXML2::IXMLDOMElementPtr pElement = NULL;
	pElement = pDoc ->createElement("caltime");
	pElement->setAttribute((_bstr_t)"time",now.Format("%Y-%m-%d %H:%M:%S: ").GetBuffer());
	pElement->setAttribute((_bstr_t)"version",Mymodfunc::GetInstance()->version.GetBuffer());
	pElement->setAttribute((_bstr_t)"source",Mymodfunc::GetInstance()->source.GetBuffer());
	pcalitimeElement = pElement;
	plineElement->appendChild(this->pcalitimeElement);
}

bool MySetting::writesetting(CString linename)
{
	MSXML2::IXMLDOMElementPtr pPar = NULL, prradar = NULL, plradar = NULL,pcut = NULL,pcar = NULL;
	this->initialdom();
	this->checkline(linename);
	this->precali();
	char buffer[100];


	pPar = pDoc->createElement((_bstr_t)"cali_par");
	f2str(calipar[0])
	pPar->setAttribute((_bstr_t)"roadwidth",buffer);
	f2str(calipar[1])
	pPar->setAttribute((_bstr_t)"radarheight",buffer);
	f2str(calipar[2])
	pPar->setAttribute((_bstr_t)"road_radar_dis",buffer);

	prradar = pDoc->createElement("right_radar");
	f2str(rradar[0])
	prradar->setAttribute((_bstr_t)"delta_x",buffer);
	f2str(rradar[1])
	prradar->setAttribute((_bstr_t)"delta_y",buffer);
	f2str(rradar[2]*57.2958)
	prradar->setAttribute((_bstr_t)"delta_th",buffer);
	f2str(rradar[3])
	prradar->setAttribute((_bstr_t)"score",buffer);
	f2str(rradar[4])
	prradar->setAttribute((_bstr_t)"w1",buffer);
	f2str(rradar[5])
	prradar->setAttribute((_bstr_t)"w2",buffer);


	plradar = pDoc->createElement("left_radar");
	f2str(lradar[0])
	plradar->setAttribute((_bstr_t)"delta_x",buffer);
	f2str(lradar[1])
	plradar->setAttribute((_bstr_t)"delta_y",buffer);
	f2str(lradar[2]*57.2958)
	plradar->setAttribute((_bstr_t)"delta_th",buffer);
	f2str(lradar[3])
	plradar->setAttribute((_bstr_t)"score",buffer);
	f2str(lradar[4])
	plradar->setAttribute((_bstr_t)"w1",buffer);
	f2str(lradar[5])
	plradar->setAttribute((_bstr_t)"w2",buffer);
	pcut = pDoc->createElement("cut");
	i2str(Mymodfunc::GetInstance()->cc);
	pcut->setAttribute((_bstr_t)"number",buffer);
	pcalitimeElement->appendChild(pPar);
	pcalitimeElement->appendChild(prradar);
	pcalitimeElement->appendChild(plradar);
	pcalitimeElement->appendChild(pcut);


	for(int i = 0;i<Mymodfunc::GetInstance()->cc;i++)
	{
		pcar = pDoc->createElement("car");
		i2str(Mymodfunc::GetInstance()->stps[i])
		pcar->setAttribute((_bstr_t)"stpoint",buffer);
		i2str(Mymodfunc::GetInstance()->lens[i])
		pcar->setAttribute((_bstr_t)"length",buffer);
		pcut->appendChild(pcar);
	}

	pDoc->save((_variant_t)szXmlFile);
	return false;
}


int MySetting::ReadLine(CString& str_lines)
{
	initialdom();
	MSXML2::IXMLDOMNodeListPtr pNodeList = NULL;
	str_lines = "";
	this->initialdom();
	long length = 0;
	pNodeList = pDoc->getElementsByTagName((_bstr_t)"Line");
	pNodeList->get_length(&length);
	for(int i = 0;i < length; i++)
	{
		str_lines += (char*)(pNodeList->Getitem(i)->Getattributes()->Getitem(0)->Gettext());
	}
	return 0;
}
