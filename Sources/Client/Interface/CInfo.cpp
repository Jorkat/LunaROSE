#include "stdafx.h"
#include ".\cinfo.h"
#include "IO_ImageRes.h"
#include "CTDrawImpl.h"
#include "../../TGameCtrl/ResourceMgr.h"
CInfo::CInfo(void)
{
	Clear();
}

CInfo::~CInfo(void)
{
}
void CInfo::Draw()
{
	int iPosX = m_ptPosition.x;
	int iPosY = m_ptPosition.y;

	std::vector<CInfoStringLine>::iterator iterLine;

	for (iterLine = m_listString.begin();
		iterLine != m_listString.end();
		++iterLine)
	{
		DrawLineImage(
			iPosX,
			iPosY,
			m_iWidth
		);

		std::vector<CInfoStringPart>::iterator iterPart;

		for (iterPart = iterLine->m_Parts.begin();
			iterPart != iterLine->m_Parts.end();
			++iterPart)
		{
			RECT rcDraw =
			{
				2 + iterPart->m_iOffsetX,
				2,
				m_iWidth,
				17
			};

			iterPart->m_String.Draw(rcDraw);
		}

		iPosY += 17;
	}
}

bool CInfo::IsEmpty()
{
	return m_listString.empty();
}

void CInfo::DrawLineImage( int x, int y, int iWidth )
{
	m_iLineImageNo = CResourceMgr::GetInstance()->GetImageNID(IMAGE_RES_UI, "ID_BLACK_PANEL"  );
	g_DrawImpl.Draw( x, y, iWidth, IMAGE_RES_UI, m_iLineImageNo , D3DCOLOR_ARGB( 180,255,255,255) );
}

void CInfo::Clear()
{
	m_iLineImageNo = CResourceMgr::GetInstance()->GetImageNID(IMAGE_RES_UI, "ID_BLACK_PANEL"  );
	m_listString.clear();
//	m_strTitle.clear();
	
	m_iHeight = 0;
	
	m_uMaxSizeString	= 0;
	m_iWidth			= 0;

	m_ptPosition.x		= 0;
	m_ptPosition.y		= 0;
}

void CInfo::SetPosition( POINT pt )
{ 
	m_ptPosition = pt; 
	AdjustPosition();
}	
int	 CInfo::GetWidth(){ return m_iWidth; }
int  CInfo::GetHeight(){ return m_iHeight; }
int	 CInfo::GetMaxSizeString(){ return m_uMaxSizeString; }
void CInfo::AddString(CTString& TString)
{
	AddString(
		TString.m_strText.c_str(),
		TString.m_dwColor,
		TString.m_hFont,
		TString.m_uFormat,
		true
	);
}

void CInfo::AddString(
	const char* pszTxt,
	DWORD color,
	HNODE hFont,
	UINT uFormat,
	bool bColorLabel)
{
	if (pszTxt == NULL)
	{
		Clear();
		return;
	}

	if (bColorLabel &&
		pszTxt[0] != '[')
	{
		const char* pszColon = strchr(pszTxt, ':');

		if (pszColon != NULL)
		{
			const size_t iLabelLength =
				static_cast<size_t>(pszColon - pszTxt) + 1;

			std::string strLabel(
				pszTxt,
				iLabelLength
			);

			std::string strValue =
				pszColon + 1;

			
			if (!strValue.empty() &&
				strValue[0] == ' ')
			{
				strLabel += ' ';
				strValue.erase(0, 1);
			}

			AddSplitString(
				strLabel.c_str(),
				D3DCOLOR_ARGB(255, 166, 202, 240),
				strValue.c_str(),
				color,
				hFont
			);

			return;
		}
	}

	const SIZE sizeString =
		getFontTextExtent(
			hFont,
			pszTxt
		);

	m_iHeight += 18;

	if (m_iWidth < sizeString.cx + 5)
		m_iWidth = sizeString.cx + 5;

	const size_t iTextLength =
		strlen(pszTxt);

	if (iTextLength >
		static_cast<size_t>(m_uMaxSizeString))
	{
		m_uMaxSizeString =
			static_cast<UINT>(iTextLength);
	}

	CInfoStringPart Part;

	Part.m_iOffsetX = 0;
	Part.m_String.SetColor(color);
	Part.m_String.SetString(pszTxt);
	Part.m_String.SetFormat(uFormat);
	Part.m_String.SetFont(hFont);

	CInfoStringLine Line;
	Line.m_Parts.push_back(Part);

	m_listString.push_back(Line);

	AdjustPosition();
}

void CInfo::AddSplitString(
	const char* pszLeft,
	DWORD dwLeftColor,
	const char* pszRight,
	DWORD dwRightColor,
	HNODE hFont)
{
	if (pszLeft == NULL ||
		pszRight == NULL)
	{
		return;
	}

	const SIZE sizeLeft =
		getFontTextExtent(
			hFont,
			pszLeft
		);

	const SIZE sizeRight =
		getFontTextExtent(
			hFont,
			pszRight
		);

	const int iTotalWidth =
		sizeLeft.cx + sizeRight.cx;

	m_iHeight += 18;

	if (m_iWidth < iTotalWidth + 5)
		m_iWidth = iTotalWidth + 5;

	const size_t iTotalCharacters =
		strlen(pszLeft) +
		strlen(pszRight);

	if (iTotalCharacters >
		static_cast<size_t>(m_uMaxSizeString))
	{
		m_uMaxSizeString =
			static_cast<UINT>(iTotalCharacters);
	}

	CInfoStringLine Line;

	CInfoStringPart LeftPart;

	LeftPart.m_iOffsetX = 0;
	LeftPart.m_String.SetColor(dwLeftColor);
	LeftPart.m_String.SetString(pszLeft);
	LeftPart.m_String.SetFormat(DT_LEFT);
	LeftPart.m_String.SetFont(hFont);

	Line.m_Parts.push_back(LeftPart);

	CInfoStringPart RightPart;

	RightPart.m_iOffsetX = sizeLeft.cx;
	RightPart.m_String.SetColor(dwRightColor);
	RightPart.m_String.SetString(pszRight);
	RightPart.m_String.SetFormat(DT_LEFT);
	RightPart.m_String.SetFont(hFont);

	Line.m_Parts.push_back(RightPart);

	m_listString.push_back(Line);

	AdjustPosition();
}

void CInfo::AddMultiColorString(
	const char* pszPart1,
	DWORD dwColor1,
	const char* pszPart2,
	DWORD dwColor2,
	const char* pszPart3,
	DWORD dwColor3,
	const char* pszPart4,
	DWORD dwColor4,
	HNODE hFont)
{
	if (!pszPart1 ||
		!pszPart2 ||
		!pszPart3 ||
		!pszPart4)
	{
		return;
	}

	const SIZE size1 =
		getFontTextExtent(hFont, pszPart1);

	const SIZE size2 =
		getFontTextExtent(hFont, pszPart2);

	const SIZE size3 =
		getFontTextExtent(hFont, pszPart3);

	const SIZE size4 =
		getFontTextExtent(hFont, pszPart4);

	const int iTotalWidth =
		size1.cx +
		size2.cx +
		size3.cx +
		size4.cx;

	m_iHeight += 18;

	if (m_iWidth < iTotalWidth + 5)
		m_iWidth = iTotalWidth + 5;

	const size_t iTotalCharacters =
		strlen(pszPart1) +
		strlen(pszPart2) +
		strlen(pszPart3) +
		strlen(pszPart4);

	if (iTotalCharacters >
		static_cast<size_t>(m_uMaxSizeString))
	{
		m_uMaxSizeString =
			static_cast<UINT>(iTotalCharacters);
	}

	CInfoStringLine Line;

	CInfoStringPart Part1;
	Part1.m_iOffsetX = 0;
	Part1.m_String.SetColor(dwColor1);
	Part1.m_String.SetString(pszPart1);
	Part1.m_String.SetFormat(DT_LEFT);
	Part1.m_String.SetFont(hFont);
	Line.m_Parts.push_back(Part1);

	CInfoStringPart Part2;
	Part2.m_iOffsetX = size1.cx;
	Part2.m_String.SetColor(dwColor2);
	Part2.m_String.SetString(pszPart2);
	Part2.m_String.SetFormat(DT_LEFT);
	Part2.m_String.SetFont(hFont);
	Line.m_Parts.push_back(Part2);

	CInfoStringPart Part3;
	Part3.m_iOffsetX =
		size1.cx +
		size2.cx;

	Part3.m_String.SetColor(dwColor3);
	Part3.m_String.SetString(pszPart3);
	Part3.m_String.SetFormat(DT_LEFT);
	Part3.m_String.SetFont(hFont);
	Line.m_Parts.push_back(Part3);

	CInfoStringPart Part4;
	Part4.m_iOffsetX =
		size1.cx +
		size2.cx +
		size3.cx;

	Part4.m_String.SetColor(dwColor4);
	Part4.m_String.SetString(pszPart4);
	Part4.m_String.SetFormat(DT_LEFT);
	Part4.m_String.SetFont(hFont);
	Line.m_Parts.push_back(Part4);

	m_listString.push_back(Line);

	AdjustPosition();
}

void CInfo::AdjustPosition()
{
	if( m_ptPosition.x < 0 )
		m_ptPosition.x = 0;
	if( m_ptPosition.y < 0 )
		m_ptPosition.y = 0;

	if( m_ptPosition.x + m_iWidth > g_pCApp->GetWIDTH() )
		m_ptPosition.x = g_pCApp->GetWIDTH() - m_iWidth;

	if( m_ptPosition.y + m_iHeight  > g_pCApp->GetHEIGHT() )
		m_ptPosition.y = g_pCApp->GetHEIGHT() - m_iHeight ;

	//if( !m_strTitle.empty() )
	//	SetTitle( (char*)m_strTitle.c_str() ); 
}

//void CInfo::SetTitle( char* pszTitle  )
//{
//	assert( pszTitle );
//	if( pszTitle )
//	{
//		m_strTitle = pszTitle;
//		m_Title.SetDefaultColor( g_dwYELLOW );
//		m_Title.SetDefaultFont( FONT_NORMAL_BOLD );
//		int iStringWidthOnelinePrint = m_Title.SetString( pszTitle, m_iWidth );
//		if( m_iWidth < iStringWidthOnelinePrint )
//			m_iWidth = iStringWidthOnelinePrint;
//	}
//}