// Dndc_manure11.cpp : implementation file
//

#include "stdafx.h"
#include "dndc71.h"
#include "Dndc_main.h"
#include "Dndc_manure11.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int feed_ID[120];
float feed_CM[117]={0.0,0.0,0.0,0.0,90.3,86.9,35.9,84.7,91,90.5,35.5,88.3,87.1,90.2,90.7,89.9,95.2,85.8,90.8,90.2,89.4,86.4,88.1,88.1,88.1,71.8,71.8,89.2,88.5,23.5,35.1,44.2,90.1,89,90.5,95.3,99.8,100,99.8,100,93.3,91.5,92,91.2,20.1,88.1,84,83.8,84.4,36.5,36.2,42,38.7,84.3,87.3,84.7,47.1,44.5,38.5,83.1,85.3,89.7,45.9,44.1,42.8,83.8,84.2,84.3,43.2,43.3,42.9,21.4,87.8,84.2,83.9,83.8,39.1,41.2,42.9,42.6,90.3,93.9,94,77.9,74.3,90,91.9,34.6,92.3,35.4,90.6,29.7,93.5,88.6,88.6,28.8,86.5,28.8,90.9,89.6,50,89.1,89.5,90,91,40.4,92.2,91.8,24.7,32,89.1,89.4,86.8,89.5,33.3,92.7,20.8};//dry matter in feed, %
float feed_CP[117]={0.0,0.0,0.0,0.0,19.2,6.5,7.7,12.5,12.4,20.1,12,10,10.4,95.5,29.2,20.5,11.9,6.9,3,29.7,23.8,65,9.4,9.4,9.4,9.2,9.2,8.6,11.9,9.7,8.8,8.5,23.5,6.2,44.9,0,0,0,0,0,92,85,71.2,68.5,26.5,10.6,18,13.3,10.8,12.8,16.8,16.8,12.7,18.4,17.4,13.3,18,17.6,15.4,19.7,18.4,18.2,20.3,19.1,17.4,20.5,19.1,17.2,20,19,18.3,26.5,20.2,22.8,20.8,17.8,20,23.2,21.9,20.3,32.6,57.6,54.2,8.5,5.8,13.2,9.1,12.9,51.8,10.5,15.5,16.1,29,11.6,11.6,9.1,9.4,10.8,13.9,46.3,27,49.9,53.8,39.2,43,17.4,28.4,19.2,19.3,13.8,17.3,14.2,9.4,18.5,12,4.8,14.6};//crude protein in feed, %
float feed_PP[117]={0.28,0.13,0.14,0.36,0.39,0.51,0.3,0.09,0.27,0.3,0.67,0.68,0.3,0.12,0.06,0.83,1,0.6,0.3,0.3,0.3,0.3,0.3,0.28,0.65,0.24,0.26,0.25,0.6,0.12,1.15,0,0,0,0,0,0.5,0.77,2.69,3.05,0.44,0.23,0.34,0.29,0.26,0.29,0.36,0.36,0.31,0.31,0.36,0.27,0.34,0.36,0.33,0.31,0.32,0.37,0.35,0.35,0.33,0.3,0.3,0.28,0.36,0.34,0.33,0.37,0.26,0.31,0.3,0.28,0.32,0.36,0.35,0.33,0.83,4.2,4.73,0.03,0.1,0.4,0.22,0.31,0.64,0.29,1.78,0.42,0.72,0.35,0.35,0.21,0.2,0.24,0.17,0.66,0.75,0.71,0.7,0.6,0.64,0.37,1,0.51,0.47,0.33,1.18,0.43,0.2,1.02,0.29,0.1,1.04};//P in feed, %

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure11 dialog

Dndc_manure11::Dndc_manure11(CWnd* pParent /*=NULL*/)
	: CDialog(Dndc_manure11::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dndc_manure11)
	m_4 = 0.0f;
	m_10 = 0.0f;
	m_100 = 0.0f;
	m_101 = 0.0f;
	m_102 = 0.0f;
	m_103 = 0.0f;
	m_104 = 0.0f;
	m_105 = 0.0f;
	m_106 = 0.0f;
	m_107 = 0.0f;
	m_108 = 0.0f;
	m_109 = 0.0f;
	m_11 = 0.0f;
	m_110 = 0.0f;
	m_111 = 0.0f;
	m_112 = 0.0f;
	m_113 = 0.0f;
	m_114 = 0.0f;
	m_115 = 0.0f;
	m_116 = 0.0f;
	m_117 = 0.0f;
	m_118 = 0.0f;
	m_119 = 0.0f;
	m_12 = 0.0f;
	m_120 = 0.0f;
	m_127 = 0.0f;
	m_128 = 0.0f;
	m_13 = 0.0f;
	m_14 = 0.0f;
	m_15 = 0.0f;
	m_16 = 0.0f;
	m_17 = 0.0f;
	m_18 = 0.0f;
	m_19 = 0.0f;
	m_20 = 0.0f;
	m_22 = 0.0f;
	m_23 = 0.0f;
	m_24 = 0.0f;
	m_25 = 0.0f;
	m_26 = 0.0f;
	m_27 = 0.0f;
	m_28 = 0.0f;
	m_29 = 0.0f;
	m_3 = 0.0f;
	m_30 = 0.0f;
	m_31 = 0.0f;
	m_32 = 0.0f;
	m_33 = 0.0f;
	m_34 = 0.0f;
	m_35 = 0.0f;
	m_36 = 0.0f;
	m_37 = 0.0f;
	m_38 = 0.0f;
	m_39 = 0.0f;
	m_40 = 0.0f;
	m_41 = 0.0f;
	m_42 = 0.0f;
	m_43 = 0.0f;
	m_44 = 0.0f;
	m_45 = 0.0f;
	m_46 = 0.0f;
	m_47 = 0.0f;
	m_48 = 0.0f;
	m_49 = 0.0f;
	m_5 = 0.0f;
	m_50 = 0.0f;
	m_51 = 0.0f;
	m_52 = 0.0f;
	m_53 = 0.0f;
	m_54 = 0.0f;
	m_55 = 0.0f;
	m_56 = 0.0f;
	m_57 = 0.0f;
	m_58 = 0.0f;
	m_59 = 0.0f;
	m_6 = 0.0f;
	m_60 = 0.0f;
	m_61 = 0.0f;
	m_62 = 0.0f;
	m_63 = 0.0f;
	m_64 = 0.0f;
	m_65 = 0.0f;
	m_66 = 0.0f;
	m_67 = 0.0f;
	m_68 = 0.0f;
	m_69 = 0.0f;
	m_7 = 0.0f;
	m_70 = 0.0f;
	m_71 = 0.0f;
	m_72 = 0.0f;
	m_73 = 0.0f;
	m_74 = 0.0f;
	m_75 = 0.0f;
	m_76 = 0.0f;
	m_77 = 0.0f;
	m_78 = 0.0f;
	m_79 = 0.0f;
	m_8 = 0.0f;
	m_80 = 0.0f;
	m_81 = 0.0f;
	m_82 = 0.0f;
	m_83 = 0.0f;
	m_84 = 0.0f;
	m_85 = 0.0f;
	m_86 = 0.0f;
	m_87 = 0.0f;
	m_88 = 0.0f;
	m_89 = 0.0f;
	m_9 = 0.0f;
	m_90 = 0.0f;
	m_91 = 0.0f;
	m_92 = 0.0f;
	m_93 = 0.0f;
	m_94 = 0.0f;
	m_95 = 0.0f;
	m_96 = 0.0f;
	m_97 = 0.0f;
	m_98 = 0.0f;
	m_99 = 0.0f;
	m_21 = 0.0f;
	m_1 = 0.0f;
	m_unit = 0;
	//}}AFX_DATA_INIT
}


void Dndc_manure11::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dndc_manure11)
	DDX_Text(pDX, IDC_EDIT4, m_4);
	DDX_Text(pDX, IDC_EDIT10, m_10);
	DDX_Text(pDX, IDC_EDIT100, m_100);
	DDX_Text(pDX, IDC_EDIT101, m_101);
	DDX_Text(pDX, IDC_EDIT102, m_102);
	DDX_Text(pDX, IDC_EDIT103, m_103);
	DDX_Text(pDX, IDC_EDIT104, m_104);
	DDX_Text(pDX, IDC_EDIT105, m_105);
	DDX_Text(pDX, IDC_EDIT106, m_106);
	DDX_Text(pDX, IDC_EDIT107, m_107);
	DDX_Text(pDX, IDC_EDIT108, m_108);
	DDX_Text(pDX, IDC_EDIT109, m_109);
	DDX_Text(pDX, IDC_EDIT11, m_11);
	DDX_Text(pDX, IDC_EDIT110, m_110);
	DDX_Text(pDX, IDC_EDIT111, m_111);
	DDX_Text(pDX, IDC_EDIT112, m_112);
	DDX_Text(pDX, IDC_EDIT113, m_113);
	DDX_Text(pDX, IDC_EDIT114, m_114);
	DDX_Text(pDX, IDC_EDIT115, m_115);
	DDX_Text(pDX, IDC_EDIT116, m_116);
	DDX_Text(pDX, IDC_EDIT117, m_117);
	DDX_Text(pDX, IDC_EDIT118, m_118);
	DDX_Text(pDX, IDC_EDIT119, m_119);
	DDX_Text(pDX, IDC_EDIT12, m_12);
	DDX_Text(pDX, IDC_EDIT120, m_120);
	DDX_Text(pDX, IDC_EDIT127, m_127);
	DDX_Text(pDX, IDC_EDIT128, m_128);
	DDX_Text(pDX, IDC_EDIT13, m_13);
	DDX_Text(pDX, IDC_EDIT14, m_14);
	DDX_Text(pDX, IDC_EDIT15, m_15);
	DDX_Text(pDX, IDC_EDIT16, m_16);
	DDX_Text(pDX, IDC_EDIT17, m_17);
	DDX_Text(pDX, IDC_EDIT18, m_18);
	DDX_Text(pDX, IDC_EDIT19, m_19);
	DDX_Text(pDX, IDC_EDIT20, m_20);
	DDX_Text(pDX, IDC_EDIT22, m_22);
	DDX_Text(pDX, IDC_EDIT23, m_23);
	DDX_Text(pDX, IDC_EDIT24, m_24);
	DDX_Text(pDX, IDC_EDIT25, m_25);
	DDX_Text(pDX, IDC_EDIT26, m_26);
	DDX_Text(pDX, IDC_EDIT27, m_27);
	DDX_Text(pDX, IDC_EDIT28, m_28);
	DDX_Text(pDX, IDC_EDIT29, m_29);
	DDX_Text(pDX, IDC_EDIT3, m_3);
	DDX_Text(pDX, IDC_EDIT30, m_30);
	DDX_Text(pDX, IDC_EDIT31, m_31);
	DDX_Text(pDX, IDC_EDIT32, m_32);
	DDX_Text(pDX, IDC_EDIT33, m_33);
	DDX_Text(pDX, IDC_EDIT34, m_34);
	DDX_Text(pDX, IDC_EDIT35, m_35);
	DDX_Text(pDX, IDC_EDIT36, m_36);
	DDX_Text(pDX, IDC_EDIT37, m_37);
	DDX_Text(pDX, IDC_EDIT38, m_38);
	DDX_Text(pDX, IDC_EDIT39, m_39);
	DDX_Text(pDX, IDC_EDIT40, m_40);
	DDX_Text(pDX, IDC_EDIT41, m_41);
	DDX_Text(pDX, IDC_EDIT42, m_42);
	DDX_Text(pDX, IDC_EDIT43, m_43);
	DDX_Text(pDX, IDC_EDIT44, m_44);
	DDX_Text(pDX, IDC_EDIT45, m_45);
	DDX_Text(pDX, IDC_EDIT46, m_46);
	DDX_Text(pDX, IDC_EDIT47, m_47);
	DDX_Text(pDX, IDC_EDIT48, m_48);
	DDX_Text(pDX, IDC_EDIT49, m_49);
	DDX_Text(pDX, IDC_EDIT5, m_5);
	DDX_Text(pDX, IDC_EDIT50, m_50);
	DDX_Text(pDX, IDC_EDIT51, m_51);
	DDX_Text(pDX, IDC_EDIT52, m_52);
	DDX_Text(pDX, IDC_EDIT53, m_53);
	DDX_Text(pDX, IDC_EDIT54, m_54);
	DDX_Text(pDX, IDC_EDIT55, m_55);
	DDX_Text(pDX, IDC_EDIT56, m_56);
	DDX_Text(pDX, IDC_EDIT57, m_57);
	DDX_Text(pDX, IDC_EDIT58, m_58);
	DDX_Text(pDX, IDC_EDIT59, m_59);
	DDX_Text(pDX, IDC_EDIT6, m_6);
	DDX_Text(pDX, IDC_EDIT60, m_60);
	DDX_Text(pDX, IDC_EDIT61, m_61);
	DDX_Text(pDX, IDC_EDIT62, m_62);
	DDX_Text(pDX, IDC_EDIT63, m_63);
	DDX_Text(pDX, IDC_EDIT64, m_64);
	DDX_Text(pDX, IDC_EDIT65, m_65);
	DDX_Text(pDX, IDC_EDIT66, m_66);
	DDX_Text(pDX, IDC_EDIT67, m_67);
	DDX_Text(pDX, IDC_EDIT68, m_68);
	DDX_Text(pDX, IDC_EDIT69, m_69);
	DDX_Text(pDX, IDC_EDIT7, m_7);
	DDX_Text(pDX, IDC_EDIT70, m_70);
	DDX_Text(pDX, IDC_EDIT71, m_71);
	DDX_Text(pDX, IDC_EDIT72, m_72);
	DDX_Text(pDX, IDC_EDIT73, m_73);
	DDX_Text(pDX, IDC_EDIT74, m_74);
	DDX_Text(pDX, IDC_EDIT75, m_75);
	DDX_Text(pDX, IDC_EDIT76, m_76);
	DDX_Text(pDX, IDC_EDIT77, m_77);
	DDX_Text(pDX, IDC_EDIT78, m_78);
	DDX_Text(pDX, IDC_EDIT79, m_79);
	DDX_Text(pDX, IDC_EDIT8, m_8);
	DDX_Text(pDX, IDC_EDIT80, m_80);
	DDX_Text(pDX, IDC_EDIT81, m_81);
	DDX_Text(pDX, IDC_EDIT82, m_82);
	DDX_Text(pDX, IDC_EDIT83, m_83);
	DDX_Text(pDX, IDC_EDIT84, m_84);
	DDX_Text(pDX, IDC_EDIT85, m_85);
	DDX_Text(pDX, IDC_EDIT86, m_86);
	DDX_Text(pDX, IDC_EDIT87, m_87);
	DDX_Text(pDX, IDC_EDIT88, m_88);
	DDX_Text(pDX, IDC_EDIT89, m_89);
	DDX_Text(pDX, IDC_EDIT9, m_9);
	DDX_Text(pDX, IDC_EDIT90, m_90);
	DDX_Text(pDX, IDC_EDIT91, m_91);
	DDX_Text(pDX, IDC_EDIT92, m_92);
	DDX_Text(pDX, IDC_EDIT93, m_93);
	DDX_Text(pDX, IDC_EDIT94, m_94);
	DDX_Text(pDX, IDC_EDIT95, m_95);
	DDX_Text(pDX, IDC_EDIT96, m_96);
	DDX_Text(pDX, IDC_EDIT97, m_97);
	DDX_Text(pDX, IDC_EDIT98, m_98);
	DDX_Text(pDX, IDC_EDIT99, m_99);
	DDX_Text(pDX, IDC_EDIT21, m_21);
	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Radio(pDX, IDC_unit, m_unit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dndc_manure11, CDialog)
	//{{AFX_MSG_MAP(Dndc_manure11)
	ON_BN_CLICKED(IDCANCEL, OnSuan)
	ON_BN_CLICKED(IDC_RADIO2, OnUnit1)
	ON_BN_CLICKED(IDC_unit, Onunit)
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dndc_manure11 message handlers

void Dndc_manure11::OnOK() 
{
	// TODO: Add extra validation here
	CString FRC;
	FILE *frc;

	FRC.Format("%s\\FeedComp", INTER);
	frc=fopen(FRC, "w");
	if(frc==NULL) note(1,FRC);
	fprintf(frc, "%f %f %f", m_128, m_3, m_127);
	fclose(frc);
	
	CDialog::OnOK();
}

void Dndc_manure11::OnSuan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	float FMD=0.0, FCP=0.0, FPP=0.0;
	int i=0, j=0;
	int UF[124]={0,0,0,0,m_4,m_5,m_6,m_7,m_8,m_9,m_10,m_11,m_12,m_13,m_14,m_15,m_16,m_17,m_18,m_19,m_20,
		m_21,m_22,m_23,m_24,m_25,m_26,m_27,m_28,m_29,m_30,m_31,m_32,m_33,m_34,m_35,m_36,m_37,m_38,m_39,m_40,
		m_41,m_42,m_43,m_44,m_45,m_46,m_47,m_48,m_49,m_50,m_51,m_52,m_53,m_54,m_55,m_56,m_57,m_58,m_59,m_60,
		m_61,m_62,m_63,m_64,m_65,m_66,m_67,m_68,m_69,m_70,m_71,m_72,m_73,m_74,m_75,m_76,m_77,m_78,m_79,m_80,
		m_81,m_82,m_83,m_84,m_85,m_86,m_87,m_88,m_89,m_90,m_91,m_92,m_93,m_94,m_95,m_96,m_97,m_98,m_99,m_100,
		m_101,m_102,m_103,m_104,m_105,m_106,m_107,m_108,m_109,m_110,m_111,m_112,m_113,m_114,m_115,m_116,m_117,
		m_118,m_119,m_120};

	float TFF;
	TFF = (m_4+m_5+m_6+m_7+m_8+m_9+m_10+m_11+m_12+m_13+m_14+m_15+m_16+m_17+m_18+m_19+m_20+
		m_21+m_22+m_23+m_24+m_25+m_26+m_27+m_28+m_29+m_30+m_31+m_32+m_33+m_34+m_35+m_36+m_37+m_38+m_39+m_40+
		m_41+m_42+m_43+m_44+m_45+m_46+m_47+m_48+m_49+m_50+m_51+m_52+m_53+m_54+m_55+m_56+m_57+m_58+m_59+m_60+
		m_61+m_62+m_63+m_64+m_65+m_66+m_67+m_68+m_69+m_70+m_71+m_72+m_73+m_74+m_75+m_76+m_77+m_78+m_79+m_80+
		m_81+m_82+m_83+m_84+m_85+m_86+m_87+m_88+m_89+m_90+m_91+m_92+m_93+m_94+m_95+m_96+m_97+m_98+m_99+m_100+
		m_101+m_102+m_103+m_104+m_105+m_106+m_107+m_108+m_109+m_110+m_111+m_112+m_113+m_114+m_115+m_116+m_117+
		m_118+m_119+m_120);
	
	if(TFF!=100.0)
	{
		AfxMessageBox("PLease make sure the sum of the percents to be 100");
		return;
	}

	for(i=4;i<=120; i++)
	{
		if(UF[i]>0.0)
		{
			j++;
			FMD += 0.01 * UF[i] * m_1 * 0.01 * feed_CM[i];
			FCP += 0.01 * UF[i] * feed_CP[i];
			FPP += 0.01 * UF[i] * feed_PP[i];
		}
	}

	m_128 = FMD;
	m_3 = FCP;
	m_127 = FPP;

	UpdateData(FALSE);

	/*m_4=0.0; m_5=0.0; m_6=0.0; m_7=0.0; m_8=0.0; m_9=0.0; m_10=0.0; m_11=0.0; m_12=0.0; m_13=0.0; m_14=0.0; m_15=0.0; m_16=0.0; m_17=0.0; m_18=0.0; m_19=0.0; m_20=0.0; 
		m_21=0.0; m_22=0.0; m_23=0.0; m_24=0.0; m_25=0.0; m_26=0.0; m_27=0.0; m_28=0.0; m_29=0.0; m_30=0.0; m_31=0.0; m_32=0.0; m_33=0.0; m_34=0.0; m_35=0.0; m_36=0.0; m_37=0.0; m_38=0.0; m_39=0.0; m_40=0.0; 
		m_41=0.0; m_42=0.0; m_43=0.0; m_44=0.0; m_45=0.0; m_46=0.0; m_47=0.0; m_48=0.0; m_49=0.0; m_50=0.0; m_51=0.0; m_52=0.0; m_53=0.0; m_54=0.0; m_55=0.0; m_56=0.0; m_57=0.0; m_58=0.0; m_59=0.0; m_60=0.0; 
		m_61=0.0; m_62=0.0; m_63=0.0; m_64=0.0; m_65=0.0; m_66=0.0; m_67=0.0; m_68=0.0; m_69=0.0; m_70=0.0; m_71=0.0; m_72=0.0; m_73=0.0; m_74=0.0; m_75=0.0; m_76=0.0; m_77=0.0; m_78=0.0; m_79=0.0; m_80=0.0; 
		m_81=0.0; m_82=0.0; m_83=0.0; m_84=0.0; m_85=0.0; m_86=0.0; m_87=0.0; m_88=0.0; m_89=0.0; m_90=0.0; m_91=0.0; m_92=0.0; m_93=0.0; m_94=0.0; m_95=0.0; m_96=0.0; m_97=0.0; m_98=0.0; m_99=0.0; m_100=0.0; 
		m_101=0.0; m_102=0.0; m_103=0.0; m_104=0.0; m_105=0.0; m_106=0.0; m_107=0.0; m_108=0.0; m_109=0.0; m_110=0.0; m_111=0.0; m_112=0.0; m_113=0.0; m_114=0.0; m_115=0.0; m_116=0.0; m_117=0.0; m_118=0.0; m_119=0.0; m_120=0.0; 
		m_121=0.0; m_122=0.0; m_123=0.0; m_124=0.0; m_125=0.0; m_126=0.0; m_127=0.0; m_128=0.0; */
}

void Dndc_manure11::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void Dndc_manure11::OnUnit1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate2);
		Edt->EnableWindow(TRUE); 
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate2);
		Edt->EnableWindow(FALSE); 
	}

	UpdateData(FALSE);
}

void Dndc_manure11::Onunit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CEdit *Edt;
	if(m_unit==1)
	{
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate);
		Edt->EnableWindow(FALSE); 
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate2);
		Edt->EnableWindow(TRUE); 
	}
	else
	{
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate2);
		Edt->EnableWindow(FALSE); 
	}

	UpdateData(FALSE);
}

BOOL Dndc_manure11::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CEdit *Edt;
	
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate);
		Edt->EnableWindow(TRUE); 
		Edt=(CEdit *)GetDlgItem(IDC_WFeedRate2);
		Edt->EnableWindow(FALSE); 

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
