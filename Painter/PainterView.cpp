// PainterView.cpp : implementation of the CPainterView class
//

#include "stdafx.h"
#include "Painter.h"

#include "PainterDoc.h"
#include "PainterView.h"
#include "Shapes.h"
#include "Global.h"
#include "savebmp.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPainterView

IMPLEMENT_DYNCREATE(CPainterView, CScrollView)

BEGIN_MESSAGE_MAP(CPainterView, CScrollView)
	//{{AFX_MSG_MAP(CPainterView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_ADDSHAPE_POINT, OnEditAddshapePoint)
	ON_COMMAND(ID_EDIT_ADDSHAPE_CIRCLE, OnEditAddshapeCircle)
	ON_COMMAND(ID_EDIT_ADDSHAPE_SQUARE, OnEditAddshapeSquare)
	ON_COMMAND(ID_EDIT_ADDSHAPE_ELLIPSE, OnEditAddshapeEllipse)
	ON_COMMAND(ID_EDIT_ADDSHAPE_PNG, OnEditAddshapePng)
	ON_COMMAND(ID_EDIT_SELECT, OnEditSelect)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_ADDSHAPE_POLYLINE, OnEditAddshapePolyline)
	ON_COMMAND(ID_EDIT_ADDSHAPE_POLYGON, OnEditAddshapePolygon)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_EDIT_CHANGEORDER_TOP, OnEditChangeorderTop)
	ON_COMMAND(ID_EDIT_CHANGEORDER_STEPUP, OnEditChangeorderStepup)
	ON_COMMAND(ID_EDIT_CHANGEORDER_STEPDOWN, OnEditChangeorderStepdown)
	ON_COMMAND(ID_EDIT_CHANGEORDER_BOTTOM, OnEditChangeorderBottom)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_ADDSHAPE_SURFACE, OnEditAddshapeSurface)
	ON_COMMAND(ID_EDIT_ADDSHAPE_BEZIER, OnEditAddshapeBezier)
	ON_WM_CREATE()
	ON_COMMAND(ID_SAVE_BMP, OnSaveBmp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPainterView construction/destruction

CPainterView::CPainterView()
{
	// TODO: add construction code here
	m_CurOper=OP_NOOPER;
	m_nMyFlags=0;

	m_hcurCircle=AfxGetApp()->LoadCursor(IDC_CURSOR_CIRCLE);
	m_hcurSquare=AfxGetApp()->LoadCursor(IDC_CURSOR_SQUARE);
	m_hcurPolygon=AfxGetApp()->LoadCursor(IDC_CURSOR_POLYGON);
	m_hcurSurface=AfxGetApp()->LoadCursor(IDC_CURSOR_SURFACE);
	m_hcurEllipse = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	m_hcurPng = AfxGetApp()->LoadCursor(IDC_CURSOR_SQUARE);
}

CPainterView::~CPainterView()
{
}

BOOL CPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPainterView drawing

void CPainterView::OnDraw(CDC* pDC)
{
	CPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	// ������� ��� ������, ���������� � ������
	POSITION pos=NULL;
	CBasePoint* pShape=NULL;
	// ���� � ������ ���� �������
	if(pDoc->m_ShapesList.GetCount()>0)
		// ������� ������� ������� �������
		pos=pDoc->m_ShapesList.GetHeadPosition(); 
	while(pos!=NULL)
	{
		// ������� ��������� �� ������ ������
		pShape=pDoc->m_ShapesList.GetNext(pos);
		// �������� ������
		if(pShape!=NULL) pShape->Show(pDC);
	}
	// �������� �������� ������
	if(m_CurOper==OP_SELECT)	MarkSelectedShape(pDC);
}

void CPainterView::DrawMoveLine(CPoint first_point, CPoint second_point)
{
	// ������� ������ � ��������� ����������
	CClientDC dc(this);
	// ���������� �������� ���������� 
	OnPrepareDC(&dc); 	
	// ��������� ����� ��������� ��������� ������
	int OldMode=dc.SetROP2(R2_NOT);
	// ������ ������ ����� ����� �������
   	dc.MoveTo(first_point);	dc.LineTo(second_point);
	// ��������������� ������� ����� ���������
	dc.SetROP2(OldMode);
}

/////////////////////////////////////////////////////////////////////////////
// CPainterView printing

BOOL CPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPainterView diagnostics

#ifdef _DEBUG
void CPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPainterDoc* CPainterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPainterDoc)));
	return (CPainterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPainterView message handlers

void CPainterView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Получили указатель на объект-документ
	CPainterDoc* pDoc = GetDocument();
	CPoint	LogPoint = point;

	// Получим контекст устройства, на котором рисуем
	CDC* pDC = GetDC();
	// Подготовим контекст устройства 
	OnPrepareDC(pDC);

	// Переведем физические координаты точки в логические
	pDC->DPtoLP(&LogPoint);
	// Освободим контекст устройства
	ReleaseDC(pDC);

	// Запоминаем точку
	m_CurMovePoint = m_FirstPoint = LogPoint;
	if (m_CurOper == OP_LINE) {
		((CPolygon*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(LogPoint);
		((CPolygon*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x + 4000, LogPoint.y - 4000));
		((CPolygon*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x, LogPoint.y - 8000));
		((CPolygon*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x - 4000, LogPoint.y - 4000));
		// Указываем, что окно надо перерисовать
		m_CurOper = OP_NOOPER;
		Invalidate();
		//break;
	}

	if (m_CurOper == OP_BEZIER) {
		((CBezier*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(LogPoint);
		((CBezier*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x + 4000, LogPoint.y - 4000));
		((CBezier*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x, LogPoint.y - 8000));
		((CBezier*)pDoc->m_ShapesList.GetTail())->m_PointsArray.Add(CPoint(LogPoint.x - 4000, LogPoint.y - 4000));
		// Указываем, что окно надо перерисовать
		m_CurOper = OP_NOOPER;
		Invalidate();
		//break;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CPainterView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CPainterDoc *pDoc=GetDocument();
	CPoint	LogPoint=point;
	CDC *pDC=GetDC();
	OnPrepareDC(pDC); 
	pDC->DPtoLP(&LogPoint);
	ReleaseDC(pDC);
	switch(m_CurOper)
	{
	case OP_POINT:
	case OP_CIRCLE:
	case OP_SQUARE:
	case OP_ELLIPSE:
	case OP_PNG:
	case OP_SURFACE:
		AddShape(m_CurOper, m_FirstPoint, LogPoint);
		Invalidate();
	break;
	case OP_SELECT:
		pDoc->SelectShape(LogPoint);
		Invalidate();
	break;
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CPainterView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPainterDoc *pDoc=GetDocument();
	CPoint	LogPoint=point;
	
	CDC *pDC=GetDC();
	OnPrepareDC(pDC); 
	pDC->DPtoLP(&LogPoint);
	ReleaseDC(pDC);
	
	switch(m_CurOper)
	{
		case OP_LINE:
			if(((CPolygon*)pDoc->m_ShapesList.GetTail())->
				m_PointsArray.GetSize()<=0) break;
			DrawMoveLine(m_FirstPoint, m_CurMovePoint);
			m_CurMovePoint=LogPoint;
			DrawMoveLine(m_FirstPoint, m_CurMovePoint);
		break;
		case OP_BEZIER:
			if (((CPolygon*)pDoc->m_ShapesList.GetTail())->
				m_PointsArray.GetSize() <= 0) break;
			DrawMoveLine(m_FirstPoint, m_CurMovePoint);
			m_CurMovePoint = LogPoint;
			DrawMoveLine(m_FirstPoint, m_CurMovePoint);
		break;
		case OP_POINT:
		case OP_CIRCLE:
		case OP_SQUARE:
		case OP_ELLIPSE:
		case OP_PNG:
		case OP_SURFACE:
			if(nFlags==MK_LBUTTON) DrawMoveLine(m_FirstPoint, m_CurMovePoint);
			m_CurMovePoint=LogPoint;
			if(nFlags==MK_LBUTTON) DrawMoveLine(m_FirstPoint, m_CurMovePoint);
		break;
		default:
			::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurDefault);
	}
	CScrollView::OnMouseMove(nFlags, point);
}
void CPainterView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	switch(m_CurOper)
	{
	case OP_LINE:
		m_CurOper=OP_NOOPER;
	break;
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CPainterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CPainterDoc *pDoc=GetDocument();
	CSize sizeTotal;
	sizeTotal.cx = pDoc->m_wSheet_Width;
	sizeTotal.cy = pDoc->m_wSheet_Height;
	SetScrollSizes(pDoc->m_wMap_Mode, sizeTotal);
	CScrollView::OnUpdate(pSender, lHint, pHint); 
}

void CPainterView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	CPainterDoc *pDoc=GetDocument();
	CPoint OriginPoint(0, -pDoc->m_wSheet_Height);
	pDC->LPtoDP(&OriginPoint); 
	pDC->SetViewportOrg(OriginPoint);
	pDC->IntersectClipRect( 0,0, pDoc->m_wSheet_Width, pDoc->m_wSheet_Height);
}

BOOL CPainterView::OnEraseBkgnd(CDC* pDC) 
{
    BOOL Res=CScrollView::OnEraseBkgnd(pDC);
	CBrush br( GetSysColor( COLOR_GRAYTEXT ) ); 
    FillOutsideRect( pDC, &br );
	return Res;
}


void CPainterView::AddShape(int shape, CPoint first_point, CPoint second_point) 
{
	CPainterDoc *pDoc=GetDocument();
	CBasePoint *pShape=NULL;
	int size=0;
	size=(int) floor( sqrt((second_point.x-first_point.x)*(second_point.x-first_point.x)+
				(second_point.y-first_point.y)*(second_point.y-first_point.y)) +0.5);

	switch(shape)
	{
	case OP_LINE:
	break;
	case OP_POINT:
		pShape=new CBasePoint(second_point.x, second_point.y, 100);
		pShape->SetBrush(RGB(200,200,200));
	break;
	case OP_CIRCLE:
		pShape=new CBasePoint(first_point.x, first_point.y, size);
		pShape->SetPen(RGB(0,0,0), 200, PS_GEOMETRIC);
		pShape->SetBrush(RGB(100,100,100));
	break;
	case OP_SQUARE:
		pShape=new CSquare(first_point.x, first_point.y, size*2);
		pShape->SetPen(RGB(200,0,0), 100, PS_GEOMETRIC);
		pShape->SetBrush(RGB(100,100,100),0,HS_DIAGCROSS);
	break;
	case OP_ELLIPSE:
		pShape = new CEllipse(first_point.x, first_point.y, size, second_point.x, second_point.y);
		pShape->SetPen(RGB(0, 0, 0), 200, PS_GEOMETRIC);
		pShape->SetBrush(RGB(255, 0, 0));
	break;
	case OP_PNG:
		pShape = new CPng(first_point.x, first_point.y, size * 2);
		pShape->SetPen(RGB(200, 0, 0), 100, PS_GEOMETRIC);
		pShape->SetBrush(RGB(100, 100, 100), 0, HS_DIAGCROSS);
		break;
	case OP_SURFACE:
		pShape=AddSurface(first_point, size);
	break;
	}
	if(pShape!=NULL)
	{
		pDoc->m_ShapesList.AddTail(pShape);
		pDoc->m_pSelShape=pShape;
		pDoc->SetModifiedFlag();
	}
}

void CPainterView::OnEditAddshapePoint() 
{
	m_CurOper=OP_POINT;	
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurCircle);
}

void CPainterView::OnEditAddshapeCircle() 
{
	m_CurOper=OP_CIRCLE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurCircle);
}

void CPainterView::OnEditAddshapeSquare() 
{
	m_CurOper=OP_SQUARE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurSquare);
}

void CPainterView::OnEditAddshapeEllipse()
{
	// TODO: добавьте свой код обработчика команд
	m_CurOper = OP_ELLIPSE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurCircle);
}

void CPainterView::OnEditAddshapePng()
{
	// TODO: добавьте свой код обработчика команд
	m_CurOper = OP_PNG;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurCircle);
}


void CPainterView::OnEditAddshapePolyline() 
{
	CBasePoint *pShape=new CPolygon;
	// ������ ����� ������� 0.5 ��
	pShape->SetPen(RGB(0,0,0), 50, PS_GEOMETRIC);
	
	CPainterDoc *pDoc=GetDocument();
	// ��������� � ����� ������
	pDoc->m_ShapesList.AddTail(pShape);
	// ��������� ������ ���������� ��������
	pDoc->m_pSelShape=pShape;
	// ���������, ��� �������� �������
	pDoc->SetModifiedFlag();

	m_CurOper=OP_LINE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurPolygon);
}

void CPainterView::OnEditAddshapePolygon() 
{
	CBasePoint *pShape=new CPolygon;
	// �����-������� �������
	pShape->SetBrush(RGB(0,100,0));
	// ������ ����� ������� 0.5 ��
	pShape->SetPen(RGB(0,0,0), 50, PS_GEOMETRIC);

	// ��� ��� pShape ��������� �� CBasePoint,
	// � ����� SetPolygon() ������� ������ � ������ CPolygon,
	// ��������� �������������� ���� ���������
	((CPolygon*)pShape)->SetPolygon(TRUE);

	CPainterDoc *pDoc=GetDocument();
	// ��������� � ����� ������
	pDoc->m_ShapesList.AddTail(pShape);
	// ��������� ������ ���������� ��������
	pDoc->m_pSelShape=pShape;
	// ���������, ��� �������� �������
	pDoc->SetModifiedFlag();
	
	m_CurOper=OP_LINE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurPolygon);
}

void CPainterView::OnEditAddshapeBezier()
{
	CBasePoint* pShape = new CBezier;
	// �����-������� �������
	pShape->SetBrush(RGB(0, 100, 0));
	// ������ ����� ������� 0.5 ��
	pShape->SetPen(RGB(0, 0, 0), 50, PS_GEOMETRIC);

	// ��� ��� pShape ��������� �� CBasePoint,
	// � ����� SetPolygon() ������� ������ � ������ CPolygon,
	// ��������� �������������� ���� ���������
	((CPolygon*)pShape)->SetPolygon(TRUE);

	CPainterDoc* pDoc = GetDocument();
	// ��������� � ����� ������
	pDoc->m_ShapesList.AddTail(pShape);
	// ��������� ������ ���������� ��������
	pDoc->m_pSelShape = pShape;
	// ���������, ��� �������� �������
	pDoc->SetModifiedFlag();

	m_CurOper = OP_BEZIER;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurPolygon);
}


void CPainterView::OnEditAddshapeSurface() 
{
	m_CurOper=OP_SURFACE;
	::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (LONG)m_hcurSurface);
}

const int _GRID_DENSITY=30;
const int _LEVELS_DENSITY=5;
CBasePoint* CPainterView::AddSurface(CPoint first_point, int size)
{
	C3DShape *pShape=NULL;
	pShape=new C3DShape();
	
	// ������������ ����������� � �������� �������
	// dx, dy - ��� �����
	double	dx=(double)size*2/_GRID_DENSITY,
			dy=(double)size*2/_GRID_DENSITY;
	// ������ ����� ����������� ������������ ��� ���������� ��������
	POINT3D point3d[_GRID_DENSITY*_GRID_DENSITY];
	

	// ������� 3D ������ - �����������, ��� ����� 3D ���������
	C3DPolygon *p3DPolygon=NULL;
	// ��������� "����������" ����� ��� Y 
	for(int i=0, j=0; i<_GRID_DENSITY; i++)
	{
		p3DPolygon=new C3DPolygon();
		for(j=0; j<_GRID_DENSITY; j++)
		{
			point3d[j*_GRID_DENSITY+i].x=first_point.x+dx*i - size;
			point3d[j*_GRID_DENSITY+i].y=first_point.y+dy*j - size;
			point3d[j*_GRID_DENSITY+i].z=ZFunction(	fabs(first_point.x-point3d[j*_GRID_DENSITY+i].x),
													fabs(first_point.y-point3d[j*_GRID_DENSITY+i].y));
			p3DPolygon->AddPoint(point3d[j*_GRID_DENSITY+i]);
		}
		pShape->AddPolygon(p3DPolygon);
	}
	double minz=point3d[0].z, maxz=point3d[0].z;
	// ��������� "����������" ����� ��� X 
	for(int j=0; j<_GRID_DENSITY; j++)
	{
		p3DPolygon=new C3DPolygon();
		for(int  i=0; i<_GRID_DENSITY; i++)
		{
			p3DPolygon->AddPoint(point3d[j*_GRID_DENSITY+i]);
			// ���������� ������� ��������� Z 
			if(point3d[j*_GRID_DENSITY+i].z<minz) minz=point3d[j*_GRID_DENSITY+i].z; 
			if(point3d[j*_GRID_DENSITY+i].z>maxz) maxz=point3d[j*_GRID_DENSITY+i].z; 
		}
		pShape->AddPolygon(p3DPolygon);
	}

	// ������ ����� ������
	double l_step=(maxz-minz)/_LEVELS_DENSITY;
	int color_step=200/_LEVELS_DENSITY; //��������� �����
	for(int i=0; i<_LEVELS_DENSITY; i++)
		AddRsection(pShape, point3d, _GRID_DENSITY, _GRID_DENSITY,
					minz + l_step/2 + l_step*i, RGB(0,0, 55+color_step*i));
			
	// ���������� �������� �� �����
	pShape->MakeProjection();
	return pShape;
};


void CPainterView::OnEditSelect() 
{
	m_CurOper=OP_SELECT;
}

void CPainterView::MarkSelectedShape(CDC *pDC)
{
	CPainterDoc *pDoc=GetDocument();
	CRgn Rgn;
	if(pDoc->m_pSelShape==NULL) return;

	pDoc->m_pSelShape->GetRegion(Rgn);
	// ������� �������� �������������, ����������� ������
	CRect Rect;
	int res=Rgn.GetRgnBox(&Rect);
	if(res!= ERROR && res!=NULLREGION)
		pDC-> InvertRect(&Rect);
}

void CPainterView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPainterDoc *pDoc=GetDocument();
	BOOL modified=FALSE;

	if(pDoc->m_pSelShape!=NULL)
		modified=pDoc->m_pSelShape->OnKeyDown(nChar, nRepCnt, nFlags, m_nMyFlags);
		
	switch(nChar)
	{
		case 16: m_nMyFlags=m_nMyFlags|SHIFT_HOLD; break; // Shift
		case 17: m_nMyFlags=m_nMyFlags|CTRL_HOLD; break; // Ctrl
	}	
		
	if(modified)
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPainterView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		case 16: m_nMyFlags=m_nMyFlags^SHIFT_HOLD;	break; // Shift
		case 17: m_nMyFlags=m_nMyFlags^CTRL_HOLD;	break; // Ctrl
	}	
	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CPainterView::OnEditChangeorderTop() 
{
	CPainterDoc *pDoc=GetDocument();
	if(pDoc->ChangeOrder(TOP))
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
}

void CPainterView::OnEditChangeorderStepup() 
{
	CPainterDoc *pDoc=GetDocument();
	if(pDoc->ChangeOrder(STEPUP))
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
}

void CPainterView::OnEditChangeorderStepdown() 
{
	CPainterDoc *pDoc=GetDocument();
	if(pDoc->ChangeOrder(STEPDOWN))
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
}

void CPainterView::OnEditChangeorderBottom() 
{
	CPainterDoc *pDoc=GetDocument();
	if(pDoc->ChangeOrder(BOTTOM))
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
}

void CPainterView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	CPainterDoc *pDoc=GetDocument();
	if(pDoc->DeleteSelected())
	{
		// ���������, ��� �������� �������
		pDoc->SetModifiedFlag();
		// ���������, ��� ���� ���� ������������
		Invalidate();
	}
}


int CPainterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hcurDefault=(HCURSOR)::GetClassLong(GetSafeHwnd(), GCL_HCURSOR);
	return 0;
}


void CPainterView::SaveBMP(CString &FileName)
{
	// ������� �������� ����������, �� ������� ������
	CDC *pwDC=GetDC();
	// ���������� �������� ���������� 
	OnPrepareDC(pwDC); 

	// �������� ������� ������� ���������
	CPoint ScrollPos=GetScrollPosition();
	// ��������� ������� ��������� � ������, ����� ������������ ��� ��������
	ScrollToPosition(CPoint(0,0));

	
	// �������� ���������� ��� ������, � ������� ����� ����������� �����
	CDC MemDC; 
	// �������� �������� ���������� ����������� � �������
	MemDC.CreateCompatibleDC(pwDC);
	// ���������� ��������.
	// ���� ����� ��������� ����� �����������, � ������� �� ��������.
	OnPrepareDC(&MemDC); 
	
	// ������ ���������� � ���������� ������� �������
	// �������� ��������� �� ������-��������
	CPainterDoc *pDoc=GetDocument();
	CSize	SizeTotal,	// ��� ���������� ������
			SizeBMP;	// ��� ���������� ������	
	SizeTotal.cx = pDoc->m_wSheet_Width; // ������
	SizeTotal.cy = pDoc->m_wSheet_Height; // ������
	SizeBMP=SizeTotal;
	MemDC.LPtoDP(&SizeBMP); // ������� ����������� ������� � ����������

	// �������� ��������� "���������", �� ������� ����� ��������
	CBitmap BMP;
	BMP.CreateCompatibleBitmap(pwDC, SizeBMP.cx, SizeBMP.cy);
	// ��������� ��������� � �������� ������
	MemDC.SelectObject(&BMP);
 
	// ����� ���
	CBrush brush;
	CBrush *pBrushOld;
	if(brush.CreateSolidBrush(RGB(255,255,255)))
	{
 		pBrushOld=MemDC.SelectObject(&brush);
 		MemDC.PatBlt(0, 0, SizeTotal.cx, SizeTotal.cy, PATCOPY);
		MemDC.SelectObject(pBrushOld);
	}

	// ����� ������� � �������� ������
	OnDraw(&MemDC);
 
	// ������ ������� ���������� ��������� �������� � ����
	SaveBitmapToBMPFile(FileName, BMP, MemDC);
	
	// �������� ������ ������ �� �����
	ReleaseDC(pwDC);
	// ������ ������� ���������
	ScrollToPosition(ScrollPos);
}


void CPainterView::OnSaveBmp() 
{
	CPainterDoc *pDoc=GetDocument();
	// �� �������� �������� ��������� ��� �����
	CString FileName=pDoc->GetTitle();
	if(FileName.ReverseFind('.')>-1)
		FileName=FileName.Left(FileName.ReverseFind('.'));
	// ������ ������
	CString Filter="BMP File (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CString DefExt="BMP";
	CFileDialog SaveDlg(FALSE, (LPCSTR)DefExt, (LPCSTR)FileName,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						(LPCSTR)Filter, this);
	if(SaveDlg.DoModal()==IDCANCEL) return;
	SaveBMP(SaveDlg.GetPathName());
}