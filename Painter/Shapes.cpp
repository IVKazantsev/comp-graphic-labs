// ���� Shapes.cpp

#include "stdafx.h"
#include "shapes.h"
#include "global.h"
#include <math.h>
#include "Painter.h"


CBasePoint::CBasePoint(): CPoint(0, 0)
{
	m_wSize=1;
	
	m_iPenStyle=PS_SOLID;
	m_iPenWidth=1;
	m_rgbPenColor=RGB(0,0,0);
	m_iBrushStyle=-1;
	m_rgbBrushColor=RGB(0,0,0);
	m_dwPattern_ID=0;
};

CBasePoint::CBasePoint(int x, int y, WORD s):CPoint(x, y)
{
	m_wSize=s;

	m_iPenStyle=PS_SOLID;
	m_iPenWidth=1;
	m_rgbPenColor=RGB(0,0,0);
	m_iBrushStyle=-1;
	m_rgbBrushColor=RGB(0,0,0);
	m_dwPattern_ID=0;
};

IMPLEMENT_SERIAL(CBasePoint, CObject , VERSIONABLE_SCHEMA|1)
void CBasePoint::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<x;
		ar<<y;
		ar<<m_wSize;
		ar<<m_iPenStyle;
		ar<<m_iPenWidth;
		ar<<m_rgbPenColor;
		ar<<m_iBrushStyle;
		ar<<m_rgbBrushColor;
		ar<<m_dwPattern_ID;
	}
	else
	{
		int Version=ar.GetObjectSchema();
		ar>>x;
		ar>>y;
		ar>>m_wSize;
		ar>>m_iPenStyle;
		ar>>m_iPenWidth;
		ar>>m_rgbPenColor;
		ar>>m_iBrushStyle;
		ar>>m_rgbBrushColor;
		ar>>m_dwPattern_ID;

		SetPen(m_rgbPenColor, m_iPenWidth, m_iPenStyle);
		SetBrush(m_rgbBrushColor, m_dwPattern_ID, m_iBrushStyle );
	}
};
BOOL CBasePoint::SetPen(COLORREF color, int width /*=1*/, int style/*=PS_SOLID*/)
{
	m_iPenStyle=style;
	m_iPenWidth=width;
	m_rgbPenColor=color;
	if(HPEN(m_Pen)!=NULL)
		if(!m_Pen.DeleteObject()) return FALSE;
	return m_Pen.CreatePen( m_iPenStyle, m_iPenWidth, m_rgbPenColor);
};
BOOL CBasePoint::SetBrush(COLORREF color, DWORD pattern /*=0*/, int style/*=-1*/)
{
	m_iBrushStyle=style;
	m_dwPattern_ID= pattern;
	m_rgbBrushColor=color;
	int res=1;
	if(HBRUSH(m_Brush)!=NULL)
		if(!m_Brush.DeleteObject()) return FALSE;
	if(m_dwPattern_ID>0)
	{
		CBitmap Pattern;
		if(!Pattern.LoadBitmap(m_dwPattern_ID)) return FALSE;
		return m_Brush.CreatePatternBrush(&Pattern);
	}
	if(m_iBrushStyle>=0)
		return m_Brush.CreateHatchBrush( m_iBrushStyle, m_rgbBrushColor);
	return m_Brush.CreateSolidBrush(m_rgbBrushColor);
};



BOOL CBasePoint::PrepareDC(CDC *pDC)
{
	if(!pDC->SaveDC()) return FALSE;
	if(HPEN(m_Pen)!=NULL)
		pDC->SelectObject(&m_Pen);
	if(HBRUSH(m_Brush)!=NULL)
		pDC->SelectObject(&m_Brush);
	return TRUE;
};

BOOL CBasePoint::RestoreDC(CDC *pDC)
{
	return pDC->RestoreDC(-1);
};

void CBasePoint::Show(CDC* pDC) 
{
	PrepareDC(pDC);
	/// //////////////////////////////////////////////////////////////
	CBitmap brushBitmap;
	brushBitmap.LoadBitmap(IDB_BITMAP1);
	CBrush patternBrush;
	patternBrush.CreatePatternBrush(&brushBitmap);
	CBrush* pBrush = pDC->SelectObject(&patternBrush);
	/// //////////////////////////////////////////////////////////////
	pDC->Ellipse(x-m_wSize, y-m_wSize, x+m_wSize, y+m_wSize);
	RestoreDC(pDC);
} 

void CBasePoint::GetRegion(CRgn &Rgn)
{
	Rgn.CreateEllipticRgn(x-m_wSize, y-m_wSize, x+m_wSize, y+m_wSize);
}

void CBasePoint::Transform(const CPoint &point0, double ang, int a, int b)
{
	CPoint res=::Transform(CPoint(x, y), CPoint(0,0), 0, a, b);
	 x=res.x; y=res.y;
};

BOOL CBasePoint::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags, UINT nMyFlags) 
{
	BOOL res=TRUE;
	if(nMyFlags & SHIFT_HOLD)
		switch(nChar)
		{
			case 37: 
				Transform(CPoint(0,0), -ROTATE_STEP, 0, 0);
				break;
			case 39:
				Transform(CPoint(0,0), ROTATE_STEP, 0, 0);
				break;
			default:
				res=FALSE;
		}
	else
		switch(nChar)
		{
			case 38:
				Transform(CPoint(0,0), 0, 0, MOVE_STEP);
				break; 
			case 40:
				Transform(CPoint(0,0), 0, 0, -MOVE_STEP); 
				break;
			case 37:
				Transform(CPoint(0,0), 0, -MOVE_STEP, 0);
				break;
			case 39:
				Transform(CPoint(0,0), 0, MOVE_STEP, 0);
				break;
			default:
				res=FALSE;
		}	
	return res;
}

CSquare::CSquare(int x, int y, WORD s): CBasePoint(x, y, s)
{
	m_wSize=s;
} 

CSquare::CSquare(): CBasePoint()
{
	m_wSize=40;
} 

IMPLEMENT_SERIAL(CSquare, CObject, 1)
void CSquare::Serialize(CArchive &ar)
{
	CBasePoint::Serialize(ar);
}
void CSquare::Show(CDC* pDC) 
{
	int s=m_wSize/2;
	PrepareDC(pDC);
	pDC->Rectangle(x-s, y-s, x+s, y+s);
	RestoreDC(pDC);
} 

void CSquare::GetRegion(CRgn &Rgn)
{
	int s=m_wSize/2;
	Rgn.CreateRectRgn(x-s, y-s, x+s, y+s);
}

CEllipse::CEllipse(int x, int y, WORD s, int finishX, int finishY): CBasePoint(x, y, s)
{
	secondPointX = finishX;
	secondPointY = finishY;
}

CEllipse::CEllipse(): CBasePoint()
{
	m_wSize = 40;
}

IMPLEMENT_SERIAL(CEllipse, CObject, 1)

void CEllipse::Serialize(CArchive& ar)
{
	CBasePoint::Serialize(ar);
}

void CEllipse::Show(CDC* pDC)
{
	int s = m_wSize;
	PrepareDC(pDC);
	pDC->Ellipse(x, y, secondPointX, secondPointY);
	RestoreDC(pDC);
}

void CEllipse::GetRegion(CRgn& Rgn)
{
	int s = m_wSize;
	Rgn.CreateEllipticRgn(x, y, secondPointX, secondPointY);
}

CPng::CPng(int x, int y, WORD s) : CBasePoint(x, y, s)
{
	m_wSize = s;
}

CPng::CPng() : CBasePoint()
{
	m_wSize = 40;
}

IMPLEMENT_SERIAL(CPng, CObject, 1)

void CPng::Serialize(CArchive& ar)
{
	CBasePoint::Serialize(ar);
}

void CPng::Show(CDC* pDC)
{
	int s = m_wSize / 2;
	PrepareDC(pDC);

	// Рисуем квадрат
	pDC->Rectangle(x - s, y - s, x + s, y + s);

	// Создаем объект CBitmap и загружаем BMP изображение
	CBitmap bmp;
	if (bmp.LoadBitmap(IDB_BITMAP1)) { 
		// Создаем объект CDC для BMP
		CDC cDC;
		cDC.CreateCompatibleDC(pDC);
		cDC.SelectObject(bmp);

		// Налагаем изображение на квадрат
		pDC->StretchBlt(x - s, y - s, s * 2, s * 2, &cDC, 0, 512, 512, -512, SRCCOPY);
	}

	RestoreDC(pDC);
}

void CPng::GetRegion(CRgn& Rgn)
{
	int s = m_wSize / 2;
	Rgn.CreateRectRgn(x - s, y - s, x + s, y + s);
}
 
CPolygon::CPolygon(): CBasePoint()
{
	m_wSize=0;
	m_bPolygon=FALSE;
} 

CPolygon::~CPolygon()
{
	m_PointsArray.RemoveAll( );
} 


IMPLEMENT_SERIAL(CPolygon, CObject, 1)
void CPolygon::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<m_bPolygon;
	}
	else
	{
		int Version=ar.GetObjectSchema();
		ar>>m_bPolygon;
	}	
	m_PointsArray.Serialize(ar);
	CBasePoint::Serialize(ar);
}
void CPolygon::Show(CDC* pDC) 
{
	PrepareDC(pDC);
	if (m_bPolygon) {
		pDC->Polygon(m_PointsArray.GetData(), 4);
	}
	else
		pDC->Polyline( m_PointsArray.GetData(), 4);
	RestoreDC(pDC);
} 

void CPolygon::GetRegion(CRgn &Rgn)
{
	Rgn. CreatePolygonRgn(m_PointsArray.GetData(), m_PointsArray.GetSize(), ALTERNATE);
}

void CPolygon::Transform(const CPoint &point0, double ang, int a, int b)
{
	for(int i=0; i<m_PointsArray.GetSize(); i++)
		m_PointsArray[i]=::Transform(m_PointsArray[i], m_PointsArray[0], ang, a, b);
};





CBezier::CBezier() : CPolygon()
{
	m_wSize = 0;
	m_bPolygon = TRUE;
}

CBezier::~CBezier()
{
	m_PointsArray.RemoveAll();
}


IMPLEMENT_SERIAL(CBezier, CObject, 1)
void CBezier::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bPolygon;
	}
	else
	{
		int Version = ar.GetObjectSchema();
		ar >> m_bPolygon;
	}
	m_PointsArray.Serialize(ar);
	CBasePoint::Serialize(ar);
}
void CBezier::Show(CDC* pDC)
{
	PrepareDC(pDC);
	if (m_bPolygon) {
		m_PointsArray;
		CPen myPen(PS_SOLID, 2, RGB(255, 0, 0)); // Создаем красную кисть
		pDC->SelectObject(&myPen); // Выбираем эту кисть
		// Задаем управляющие точки для полибезье
		POINT points[13];
		points[0] = { m_PointsArray[0].x, m_PointsArray[0].y };
		points[1] = { m_PointsArray[0].x + 1000, m_PointsArray[0].y };
		points[2] = { m_PointsArray[1].x,  m_PointsArray[1].y + 1000 };
		points[3] = { m_PointsArray[1].x, m_PointsArray[1].y };

		points[4] = { m_PointsArray[1].x, m_PointsArray[1].y - 1000 };
		points[5] = { m_PointsArray[2].x + 1000,  m_PointsArray[2].y };
		points[6] = { m_PointsArray[2].x, m_PointsArray[2].y };

		points[7] = { m_PointsArray[2].x - 1000, m_PointsArray[2].y };
		points[8] = { m_PointsArray[3].x,  m_PointsArray[3].y - 1000 };
		points[9] = { m_PointsArray[3].x, m_PointsArray[3].y };

		points[10] = { m_PointsArray[3].x, m_PointsArray[3].y + 1000 };
		points[11] = { m_PointsArray[0].x - 1000,  m_PointsArray[0].y };
		points[12] = { m_PointsArray[0].x, m_PointsArray[0].y };

		// Создаем полибезье
		pDC->PolyBezier(points, 13);
	}
	else
		pDC->Polyline(m_PointsArray.GetData(), 10);
	RestoreDC(pDC);
}

void CBezier::GetRegion(CRgn& Rgn)
{
	Rgn.CreatePolygonRgn(m_PointsArray.GetData(), m_PointsArray.GetSize(), ALTERNATE);
}








IMPLEMENT_SERIAL(C3DPolygon, CPolygon, -1)
void C3DPolygon::Serialize(CArchive &ar)
{
	CPolygon::Serialize(ar);
	
	if(ar.IsStoring())
	{
	}
	else
	{
	}
	m_3DPointsArray.Serialize(ar);
	
};

void C3DPolygon::MakeProjection(Perspective P)
{
	P.theta=P.theta*atan(1.0)/45.0; P.phi=P.phi*atan(1.0)/45.0;

	double  st=sin(P.theta), ct=cos(P.theta), sp=sin(P.phi), cp=cos(P.phi),
	v11=-st,	v12=-cp*ct,	v13=-sp*ct,
	v21=ct,		v22=-cp*st,	v23=-sp*st,
				v32=sp,		v33=-cp,
	v41=P.dx,	v42=P.dy,	v43=P.rho;
	double x, y, z;
	double TempZ=0;
	 m_PointsArray.SetSize(m_3DPointsArray.GetSize());
	for(int i=0; i<m_3DPointsArray.GetSize(); i++)
	{
		x=m_3DPointsArray[i].x-P.O.x;
		y=m_3DPointsArray[i].y-P.O.y;
		z=m_3DPointsArray[i].z-P.O.z;

		TempZ=v13*x+v23*y+v33*z+v43;
		m_PointsArray[i].x=(LONG)(v11*x+v21*y+v41+0.5);
		m_PointsArray[i].y=(LONG)(v12*x+v22*y+v32*z+v42+0.5);

		if(P.with_perspective)
		{
			m_PointsArray[i].x=(LONG)(P.d*m_PointsArray[i].x/TempZ +0.5);
			m_PointsArray[i].y=(LONG)(P.d*m_PointsArray[i].y/TempZ +0.5);
		}
		
		m_PointsArray[i].x+=(LONG)(P.O.x +0.5);
		m_PointsArray[i].y+=(LONG)(P.O.y +0.5);
	}
};

C3DShape::C3DShape(): CBasePoint()
{
	m_Percpective.O.x=0;
	m_Percpective.O.y=0;
	m_Percpective.O.z=0;
	m_Percpective.rho=50000;
	m_Percpective.theta=30;  
	m_Percpective.phi=30;
	m_Percpective.d=25000;
	m_Percpective.with_perspective=TRUE;
	m_Percpective.dx=0;
	m_Percpective.dy=0;
}

C3DShape::~C3DShape()
{
	while(m_PtrPolygonList.GetCount()>0)
		delete m_PtrPolygonList.RemoveHead();
	
};

IMPLEMENT_SERIAL(C3DShape, CBasePoint, -1)
void C3DShape::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar << m_Percpective.O.x;
		ar << m_Percpective.O.y;
		ar << m_Percpective.O.z;
		ar << m_Percpective.rho;
		ar << m_Percpective.theta;
		ar << m_Percpective.phi;
		ar << m_Percpective.d;
		ar << m_Percpective.with_perspective;
		ar << m_Percpective.dx;
		ar << m_Percpective.dy;
	}
	else
	{
		ar >> m_Percpective.O.x;
		ar >> m_Percpective.O.y;
		ar >> m_Percpective.O.z;
		ar >> m_Percpective.rho;
		ar >> m_Percpective.theta;
		ar >> m_Percpective.phi;
		ar >> m_Percpective.d;
		ar >> m_Percpective.with_perspective;
		ar >> m_Percpective.dx;
		ar >> m_Percpective.dy;

	}
	m_PtrPolygonList.Serialize(ar);
};

void C3DShape::Show(CDC *pDC)
{
	POSITION Pos=NULL;
	if(m_PtrPolygonList.GetCount()>0)
		Pos=m_PtrPolygonList.GetHeadPosition();
	
	while(Pos!=NULL)
		m_PtrPolygonList.GetNext(Pos)->Show(pDC);
};


void C3DShape::GetRegion(CRgn &Rgn)
{
	CRect Frame;
	POSITION Pos=NULL;
	int i=0;
	CPolygon *pPolygon=NULL;
	if(m_PtrPolygonList.GetCount()>0)
		Pos=m_PtrPolygonList.GetHeadPosition();
	if(Pos!=NULL && (pPolygon=m_PtrPolygonList.GetAt(Pos))!=NULL && pPolygon->m_PointsArray.GetSize()>0)
	{
		Frame.left=Frame.right=pPolygon->m_PointsArray[0].x;
		Frame.top=Frame.bottom=pPolygon->m_PointsArray[0].y;
	}
	else return;
	while(Pos!=NULL)
	{
		pPolygon=m_PtrPolygonList.GetNext(Pos);
		for(i=0; i<pPolygon->m_PointsArray.GetSize(); i++)
		{
			if(pPolygon->m_PointsArray[i].x<Frame.left) Frame.left=pPolygon->m_PointsArray[i].x;
			if(pPolygon->m_PointsArray[i].x>Frame.right) Frame.right=pPolygon->m_PointsArray[i].x;
			if(pPolygon->m_PointsArray[i].y>Frame.bottom) Frame.bottom=pPolygon->m_PointsArray[i].y;
			if(pPolygon->m_PointsArray[i].y<Frame.top) Frame.top=pPolygon->m_PointsArray[i].y;
		};
	}
	Rgn.CreateRectRgn(Frame.left, Frame.top, Frame.right, Frame.bottom);
}

	
void C3DShape::AddPolygon(C3DPolygon *pPolygon)
{
	m_PtrPolygonList.AddTail(pPolygon);
	POSITION Pos=NULL;
	C3DPolygon* pCurPolygon=NULL;
	WORD Count=0, i=0;
	if(m_PtrPolygonList.GetCount()>0)
		Pos=m_PtrPolygonList.GetHeadPosition();
	while(Pos!=NULL)
	{
		pCurPolygon=(C3DPolygon*)m_PtrPolygonList.GetNext(Pos);
		for(i=0; i<pCurPolygon->m_3DPointsArray.GetSize(); i++)
		{
			m_Percpective.O.x+=pCurPolygon->m_3DPointsArray[i].x;	
			m_Percpective.O.y+=pCurPolygon->m_3DPointsArray[i].y;	
			m_Percpective.O.z+=pCurPolygon->m_3DPointsArray[i].z;	
		}
		Count+=i;
	}
	m_Percpective.O.x/=Count;
	m_Percpective.O.y/=Count;
	m_Percpective.O.z/=Count;
};


void C3DShape::MakeProjection()
{
	POSITION Pos=NULL;
	if(m_PtrPolygonList.GetCount()>0)
		Pos=m_PtrPolygonList.GetHeadPosition();
	while(Pos!=NULL)
		((C3DPolygon*)m_PtrPolygonList.GetNext(Pos))->MakeProjection(m_Percpective);
};

BOOL C3DShape::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags, UINT nMyFlags)
{
	
	BOOL res=TRUE;
	if(nMyFlags & SHIFT_HOLD)
	switch(nChar)
	{
		case 38: m_Percpective.phi-=ROTATE_STEP; break;	//Up
		case 40: m_Percpective.phi+=ROTATE_STEP; break;	//Down
		case 37: m_Percpective.theta-=ROTATE_STEP; break; //Left
		case 39: m_Percpective.theta+=ROTATE_STEP; break; //Right
		default: res=FALSE;
	}
	else
	if(nMyFlags & CTRL_HOLD)	 
	switch(nChar)
	{
		case 38: m_Percpective.d+=MOVE_STEP; break; //Up
		case 40: m_Percpective.d-=MOVE_STEP; break; //Down
		default: res=FALSE;
	}
	else
	{
		switch(nChar)
		{
			case 38:	m_Percpective.dy+= MOVE_STEP; break;
			case 40: 	m_Percpective.dy-= MOVE_STEP; break;
			case 37: 	m_Percpective.dx-= MOVE_STEP; break;
			case 39:    m_Percpective.dx+= MOVE_STEP; break;
			case 80:    m_Percpective.with_perspective=!m_Percpective.with_perspective;
						break; 
			default:	res=FALSE;
		}	
	}
	if(res)
		MakeProjection();
	return res;
};

int AddRsection(C3DShape *pShape, POINT3D *pSur, int x_size, int y_size, double level, COLORREF color)
{
	if(x_size<2 || y_size<2) return 0;
	C3DPolygon *pTempPolygon=new C3DPolygon();
	if(pTempPolygon==NULL) return 0; 
	for(int x=0, y=0; y<y_size-1; y++)
		for(int x=0;  x<x_size-1; x++)
		{
			AddTriangleSection(pTempPolygon, &pSur[y*x_size+x], &pSur[(y+1)*x_size+x+1], &pSur[y*x_size+x+1], level);
			AddTriangleSection(pTempPolygon, &pSur[y*x_size+x], &pSur[(y+1)*x_size+x], &pSur[(y+1)*x_size+x+1], level);
		}
	CArray <POINT3D, POINT3D> &TempPointsArray=pTempPolygon->m_3DPointsArray;
	
	int pos=0, posmin=0;
	POINT3D EndSegPoint;
	double D=0, dcur=0, dmin=0;
	C3DPolygon *pSeg;
	BOOL fContinueSeg=TRUE;
	POINT3D P1=pSur[0], P2=pSur[x_size+1];	P1.z=P2.z=0;
	D=Dist(&P1, &P2);
	while(TempPointsArray.GetSize()-1>0)
	{
		// ����� ������� - �������
		pSeg=new C3DPolygon();	fContinueSeg=TRUE;
		if(pSeg==NULL) return 0;
		// ��������� ����
		pSeg->SetPen(color);
		// ������ �����-������ � ����� ��������
		pSeg->AddPoint(TempPointsArray[0]);
		EndSegPoint=TempPointsArray[0];
		// ������� ����� �� ������ ������� �����
		TempPointsArray.RemoveAt(0);
		// ���������� �������
		while(fContinueSeg )
		{	
			posmin=0;
			dmin=D*2;
			// � ������ �������
			// �������� ��������� � ����� �������� ����� 
			for(pos=0; pos<TempPointsArray.GetSize(); pos++)
			{
			  dcur=Dist(&EndSegPoint, &TempPointsArray[pos]);
			  if(dcur<dmin) 
			    {dmin=dcur; posmin=pos;}//���������� �������(�����) ��������� �����
			}
			if(dmin<=D) //���������� �� ��������� ����� ������ ����������,
			{	
				//�� ���-���� ����� �� ��������� � ������ ��������,
				//������� ������� �� � �������
				if(dmin>D/1000) 
				{
					//��������� ���� � �������
					pSeg->AddPoint(TempPointsArray[posmin]);
					//����� ����� ����������� ������ ��������
					EndSegPoint=TempPointsArray[posmin];
				}

				//������� ��� �����
				TempPointsArray.RemoveAt(posmin);
			}
			else //�� ����� ������� � ����� �����- ��������� �������
				fContinueSeg=FALSE;
		} ;
		//��������, ����� ����� �������� �������
		if(pSeg->m_3DPointsArray.GetSize()>2)
			if(Dist(&pSeg->m_3DPointsArray[0], &pSeg->m_3DPointsArray[pSeg->m_3DPointsArray.GetSize()-1])<D)
				pSeg->AddPoint(pSeg->m_3DPointsArray[0]);
		
			
		//��������� ������� � ������ 
		pShape->AddPolygon(pSeg);
	} 	
	//��������� ������� ��� ������ �� �����
	delete pTempPolygon;
	return 1;
}



void AddTriangleSection(C3DPolygon *p3DPolygon, POINT3D *pP1, POINT3D *pP2, POINT3D *pP3, double level)
{
	int  f1,f2,f3;
	double x1,x2,x3,y1,y2,y3;
	POINT3D P1, P2;
	if(	!((pP1->z==level)&&(pP2->z==level)&&(pP3->z==level)) && //����������� � ���������
   		!((pP1->z>level)&&(pP2->z>level)&&(pP3->z>level)) &&   //����������� � ��������� �� ������������
		!((pP1->z<level)&&(pP2->z<level)&&(pP3->z<level)) )	   //����������� � ��������� �� ������������

   	if((pP1->z==level)&&(pP2->z==level))	//������� � ��������� - ���������
   	{
		p3DPolygon->AddPoint(*pP1);
		p3DPolygon->AddPoint(*pP2);
   	}
	else
		if((pP2->z==level)&&(pP3->z==level)) //������� � ��������� - ���������
   		{ 
   			p3DPolygon->AddPoint(*pP2);
			p3DPolygon->AddPoint(*pP3);
		}
   		else
   			if((pP3->z==level)&&(pP1->z==level)) //������� � ��������� - ���������
   		    { 
	   			p3DPolygon->AddPoint(*pP3);
				p3DPolygon->AddPoint(*pP1);
			}
   			else
   			{	// ������� 	����������� ������ ������� ������������ � ����������
				 f1=CutCross(level,pP1, pP2, x1, y1); 
				 f2=CutCross(level,pP2, pP3, x2, y2);
				 f3=CutCross(level,pP3, pP1, x3, y3);
				 if(f1&&f2) 
				 { 
					P1.x=x1; P1.y=y1; P1.z=level; 
					P2.x=x2; P2.y=y2; P2.z=level; 
					p3DPolygon->AddPoint(P1);
					p3DPolygon->AddPoint(P2);
			     }
				 if(f2&&f3)
				 { 
					P1.x=x2; P1.y=y2; P1.z=level; 
					P2.x=x3; P2.y=y3; P2.z=level; 
					p3DPolygon->AddPoint(P1);
					p3DPolygon->AddPoint(P2);
				 }
				 if(f1&&f3)
				 { 
					P1.x=x1; P1.y=y1; P1.z=level; 
					P2.x=x3; P2.y=y3; P2.z=level; 
					p3DPolygon->AddPoint(P1);
					p3DPolygon->AddPoint(P2);
				 }
   }//~else
}

int CutCross(double level, POINT3D *pP1, POINT3D *pP2, double &x, double &y)
{ if( (pP1->z<level && pP2->z<level) || //������� ��� ���������� level
      (pP1->z>level && pP2->z>level) ||	//������� ��� ���������� level
	  (pP1->z==pP2->z)  ) 	 //������� � ��������� level
		{x=pP1->x; y=pP1->y; return 0;} 
  else
    {
	 x=pP2->x-(pP1->x-pP2->x)*(level-pP2->z)/(pP2->z-pP1->z);
	 y=pP2->y-(pP1->y-pP2->y)*(level-pP2->z)/(pP2->z-pP1->z);
	 return 1;
	}
}

double Dist(POINT3D *pP1, POINT3D* pP2)
{
	if(pP1==NULL||pP2==NULL) return 0;
	return sqrt(pow(pP1->x-pP2->x, 2)+pow(pP1->y-pP2->y, 2)+pow(pP1->z-pP2->z, 2));
};