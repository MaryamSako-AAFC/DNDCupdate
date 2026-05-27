#if !defined(AFX_REGIONINPUT_H__47F0B088_8C28_4FD5_AFB9_D5C3B5CF4F69__INCLUDED_)
#define AFX_REGIONINPUT_H__47F0B088_8C28_4FD5_AFB9_D5C3B5CF4F69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegionInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegionInput dialog

class RegionInput : public CDialog
{
// Construction
public:
	RegionInput(CWnd* pParent = NULL);   // standard constructor
	//CCreateThreadDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(RegionInput)
	enum { IDD = IDD_RegionInputSet };
	CComboBox	m_SimuMode;
	CProgressCtrl	m_ConvertGo;
	CComboBox	m_MajorTarget;
	CComboBox	m_DailyItem;
	CListBox	m_GisFileName;
	int		m_StartGridID;
	CString	m_ScenarioName;
	int		m_SimuYears;
	int		m_StartYear;
	CString	m_RegionName;
	int		m_TotalCells;
	int		m_SimulatedCells;
	int		m_DataFormat;
	CProgressCtrl	m_progress3;
	CProgressCtrl	m_progress2;
	CProgressCtrl	m_progress1;
	int		m_Drought;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegionInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RegionInput)
	afx_msg void OnSelGisFile();
	afx_msg void OnFarmFile();
	afx_msg void OnFarmFile2();
	afx_msg void Onyr1();
	afx_msg void Onyr2();
	afx_msg void Onyr3();
	afx_msg void Onyr4();
	afx_msg void Onyr5();
	afx_msg void Onyr6();
	afx_msg void Onyr7();
	afx_msg void Onyr8();
	afx_msg void Onyr9();
	afx_msg void Onyr10();
	afx_msg void Onyr11();
	afx_msg void Onyr12();
	afx_msg void Onyr13();
	afx_msg void Onyr14();
	afx_msg void Onyr15();
	afx_msg void Onyr16();
	afx_msg void Onyr17();
	afx_msg void Onyr18();
	afx_msg void Onyr19();
	afx_msg void Onyr20();
	afx_msg void Onyr21();
	afx_msg void Onyr22();
	afx_msg void Onyr23();
	afx_msg void Onyr24();
	afx_msg void Onyr25();
	afx_msg void Onyr26();
	afx_msg void Onyr27();
	afx_msg void Onyr28();
	afx_msg void Onyr29();
	afx_msg void Onyr30();
	afx_msg void Onyr31();
	afx_msg void Onyr32();
	afx_msg void Onyr33();
	afx_msg void Onyr34();
	afx_msg void Onyr35();
	afx_msg void Onyr36();
	afx_msg void Onyr37();
	afx_msg void Onyr38();
	afx_msg void Onyr39();
	afx_msg void Onyr40();
	afx_msg void OnDblclkGisFileList();
	virtual void OnOK();
	afx_msg void OnKillfocusSimuYears();
	afx_msg void OnSetfocusRegionName();
	afx_msg void OnSaveregion();
	afx_msg void OnAccept();
	afx_msg void OnOpenregion();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusMajorTarget();
	afx_msg void OnKillfocusRegionName();
	afx_msg void OnFarming();
	afx_msg void OnChangeStartGridID();
	afx_msg void OnButton1();
	afx_msg void OnDataConversion();
	afx_msg void Onyr41();
	afx_msg void Onyr42();
	afx_msg void Onyr43();
	afx_msg void Onyr44();
	afx_msg void Onyr45();
	afx_msg void Onyr46();
	afx_msg void Onyr47();
	afx_msg void Onyr48();
	afx_msg void Onyr49();
	afx_msg void Onyr50();
	afx_msg void Onyr51();
	afx_msg void Onyr52();
	afx_msg void Onyr53();
	afx_msg void Onyr54();
	afx_msg void Onyr55();
	afx_msg void Onyr56();
	afx_msg void Onyr57();
	afx_msg void OnDoubleclickedyr58();
	afx_msg void Onyr59();
	afx_msg void Onyr60();
	afx_msg void Onyr61();
	afx_msg void Onyr62();
	afx_msg void Onyr63();
	afx_msg void Onyr64();
	afx_msg void Onyr65();
	afx_msg void Onyr66();
	afx_msg void Onyr67();
	afx_msg void Onyr68();
	afx_msg void Onyr69();
	afx_msg void Onyr70();
	afx_msg void Onyr71();
	afx_msg void Onyr72();
	afx_msg void Onyr73();
	afx_msg void Onyr74();
	afx_msg void Onyr75();
	afx_msg void Onyr76();
	afx_msg void Onyr77();
	afx_msg void Onyr78();
	afx_msg void Onyr79();
	afx_msg void Onyr80();
	afx_msg void Onyr81();
	afx_msg void Onyr82();
	afx_msg void Onyr83();
	afx_msg void Onyr84();
	afx_msg void Onyr85();
	afx_msg void Onyr86();
	afx_msg void Onyr87();
	afx_msg void Onyr88();
	afx_msg void Onyr89();
	afx_msg void Onyr90();
	afx_msg void Onyr91();
	afx_msg void Onyr92();
	afx_msg void Onyr93();
	afx_msg void Onyr94();
	afx_msg void Onyr95();
	afx_msg void Onyr96();
	afx_msg void Onyr97();
	afx_msg void Onyr98();
	afx_msg void Onyr99();
	afx_msg void Onyr100();
	afx_msg void Onyr58();
	afx_msg void OnDrought2();
	afx_msg void OnDrought1();
	afx_msg void OnSelchangeDailyRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONINPUT_H__47F0B088_8C28_4FD5_AFB9_D5C3B5CF4F69__INCLUDED_)
