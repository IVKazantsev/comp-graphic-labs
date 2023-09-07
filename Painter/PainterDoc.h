// PainterDoc.h : interface of the CPainterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTERDOC_H__F8B9924B_79CF_11D5_BB4A_20804AC10000__INCLUDED_)
#define AFX_PAINTERDOC_H__F8B9924B_79CF_11D5_BB4A_20804AC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TOP			0
#define BOTTOM		1
#define STEPUP		2
#define STEPDOWN	3

class CBasePoint;
class CPainterDoc : public CDocument
{
protected: 
	CPainterDoc();
	DECLARE_DYNCREATE(CPainterDoc)

// ������
public:
	// ������ �����
	WORD m_wSheet_Width;
	// ������ �����
	WORD m_wSheet_Height;
	// ����� �����������
	WORD m_wMap_Mode;

	// ������ ���������� �� �������-������
	CTypedPtrList<CObList, CBasePoint*> m_ShapesList;
	// ��������� �� ��������� ������
	CBasePoint* m_pSelShape;  

	
// ������
public:
	// ������� ������ ��������
	void ClearShapesList();
	// ����� �������� ������
	CBasePoint* SelectShape(CPoint point);
	// ��������� ������� ���������� �������� ������ � ������ �����
	BOOL ChangeOrder(int code);
	// ������� ���������� ������
	BOOL DeleteSelected();

	// ���������� ������ ��� ���������� ������
	void SetPatternForSelected(UINT Pattern_ID);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPainterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPainterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPainterDoc)
	afx_msg void OnFilePageproperty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTERDOC_H__F8B9924B_79CF_11D5_BB4A_20804AC10000__INCLUDED_)
