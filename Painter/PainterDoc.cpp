// PainterDoc.cpp : implementation of the CPainterDoc class
//

#include "stdafx.h"
#include "Painter.h"

#include "PainterDoc.h"
#include "PainterView.h"
#include "PagePropertyDlg.h"
#include "Shapes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPainterDoc

IMPLEMENT_DYNCREATE(CPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(CPainterDoc, CDocument)
	//{{AFX_MSG_MAP(CPainterDoc)
	ON_COMMAND(ID_FILE_PAGEPROPERTY, OnFilePageproperty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPainterDoc construction/destruction

CPainterDoc::CPainterDoc()
{
	// ����� ����������� 1 ���. ��. = 0.01 ��
	m_wMap_Mode = MM_HIMETRIC;
	// ������ ����� ������� �4
	m_wSheet_Width = 21000;
	m_wSheet_Height = 29700;
	// ��� ��������� ������
	m_pSelShape=NULL;
}

CPainterDoc::~CPainterDoc()
{
	// �������� ������ �����
	ClearShapesList();
}

BOOL CPainterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	// ��� ��������� ������
	m_pSelShape=NULL;

	// �������� ������ �����
	ClearShapesList();
	// ������������
	UpdateAllViews(NULL);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPainterDoc serialization

void CPainterDoc::Serialize(CArchive& ar)
{
	CString version;
	// ���������� �����
	WORD Index=0, i=0, version_n=0; 
	CPoint point;

	CBasePoint *pPolygon=NULL; 
	if (ar.IsStoring()) // ��������� 
	{
		// ������ ������� ����� ��������
		version_n=3;
		version.Format("pr%d", version_n);
		ar << version;
		// ����� ����������� 
		ar << m_wMap_Mode;
		// ������ ����� 
		ar << m_wSheet_Width;
		ar << m_wSheet_Height;
	}
	else // ���������
	{
		// ������ �������
		ar >> version;
		version_n=atoi((LPCTSTR)version.Right(1));
		switch(version_n) // � ����������� �� ������ ������� 
		{
			case 2:
				pPolygon=new CPolygon;
				pPolygon->SetPen(RGB(0,0,0), 50, PS_GEOMETRIC);
				ar >> Index;
				// ��������� �������� ��������� �����
				for(i=0; i<Index; i++)
				{
					ar >> point;
					((CPolygon*)pPolygon)->m_PointsArray.Add(point);
				}
			case 3:
				// ����� ����������� 
				ar >> m_wMap_Mode;
				// ������ ����� 
				ar >> m_wSheet_Width;
				ar >> m_wSheet_Height;
				break;
			default: 
				AfxMessageBox("����������� ������", MB_OK);
				return;
		}//switch(version)
	}
	
	// ��������� ������������ ������ �����
	m_ShapesList.Serialize(ar); 
	// ��������� ������-������� � ������ ������
	if(pPolygon!=NULL)
		m_ShapesList.AddHead(pPolygon);
}



/////////////////////////////////////////////////////////////////////////////
// CPainterDoc diagnostics

#ifdef _DEBUG
void CPainterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPainterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPainterDoc commands

BOOL CPainterDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// ��� ��������� ������
	m_pSelShape=NULL;
	// �������� ������ �����
	ClearShapesList();

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}


void CPainterDoc::OnFilePageproperty() 
{
	// TODO: Add your command handler code here
	//������� ������ - ������ ������� �����
	CPagePropertyDlg PPDlg;
	//�������������� ��������� ������� �������� ����������
	//����� �� 100, �.�. � ������� ������� � ��
	PPDlg.m_uWidth=m_wSheet_Width/100;
	PPDlg.m_uHeight=m_wSheet_Height/100;
	//�������� ������
	if(PPDlg.DoModal()==IDOK)
	{	//���������� ����� ��������
		//�������� �� 100, �.�. 1 ���. ��. = 0.01 �� 
		m_wSheet_Width=PPDlg.m_uWidth*100;
		m_wSheet_Height=PPDlg.m_uHeight*100;
		//��������� �����
		UpdateAllViews(NULL);
	}
	
}

void CPainterDoc::ClearShapesList()
{
	// �������� ������ ��������
	POSITION pos=NULL;
	while(m_ShapesList.GetCount()>0) //���� � ������ ���� ������
		delete m_ShapesList.RemoveHead();//������� ������ �� ���
}

CBasePoint* CPainterDoc::SelectShape(CPoint point)
{
	// ������-�������
	CRgn Rgn;
	// ��������� �� ������� ������
	POSITION pos=NULL;
	// ������� � ������ ������
	if(m_ShapesList.GetCount()>0) pos=m_ShapesList.GetTailPosition();
	// �������� �������� �� ����� point � ����-���� �� �����
	while(pos!=NULL) 
	{
		m_pSelShape=m_ShapesList.GetPrev(pos);
		// ������� ������ - �������
		Rgn.DeleteObject();
		m_pSelShape->GetRegion(Rgn);
		// ����� �������� � ������ - ���������� ��������� �� ������
		if(Rgn.PtInRegion(point) ) return m_pSelShape;
	}
	// ���� ��������� �� ����� �����, ������, �� ������ �� � ����� ������
	return (m_pSelShape=NULL);
};

BOOL CPainterDoc::ChangeOrder(int code)
{
	if(m_pSelShape==NULL) return FALSE;
	CBasePoint *pShape=NULL;
	// ��������� �� ������� ������
	POSITION pos=NULL, pastpos=NULL;
	// ������ ����� � ������ ������
	if(m_ShapesList.GetCount()>0) pos=m_ShapesList.GetTailPosition();
	// ������ ������� ������� � ������
	while(pos!=NULL) 
	{
		if(m_pSelShape==m_ShapesList.GetAt(pos)) break;
		m_ShapesList.GetPrev(pos);
	}
	if(pos==NULL) return FALSE;
	// ����� ������� � ���������� �� ���������� ������
	// ������ ������� �������� � ������ 
	switch(code)
	{
		case TOP:
			m_ShapesList.RemoveAt(pos);
			m_ShapesList.AddTail(m_pSelShape);
			break;
		case BOTTOM:
			m_ShapesList.RemoveAt(pos);
			m_ShapesList.AddHead(m_pSelShape);
			break;
		case STEPUP:
			pastpos=pos;
			m_ShapesList.GetNext(pos);
			if(pos!=NULL)
			{
				m_ShapesList.RemoveAt(pastpos);
				m_ShapesList.InsertAfter(pos, m_pSelShape);
			}
			break;
		case STEPDOWN:
			pastpos=pos;
			m_ShapesList.GetPrev(pos);
			if(pos!=NULL)
			{
				m_ShapesList.RemoveAt(pastpos);
				m_ShapesList.InsertBefore(pos, m_pSelShape);
			}
			break;
	}

	return TRUE;				
};

BOOL CPainterDoc::DeleteSelected()
{
	if(m_pSelShape==NULL) return FALSE;
	CBasePoint *pShape=NULL;
	// ��������� �� ������� ������
	POSITION pos=NULL, pastpos=NULL;
	// ������� � ������ ������
	if(m_ShapesList.GetCount()>0) pos=m_ShapesList.GetTailPosition();
	// ������ ������� ������� � ������
	while(pos!=NULL) 
	{
		if(m_pSelShape==m_ShapesList.GetAt(pos)) break;
		m_ShapesList.GetPrev(pos);
	}
	if(pos!=NULL) // ����� ��� �������
	{
		m_ShapesList.RemoveAt(pos);
		delete m_pSelShape;
		m_pSelShape=NULL;
		return TRUE;
	}
	return FALSE;
};

void CPainterDoc::SetPatternForSelected(UINT Pattern_ID)
{
	if(m_pSelShape==NULL) return;
	m_pSelShape->SetBrush(RGB(0,0,0), Pattern_ID);
};

