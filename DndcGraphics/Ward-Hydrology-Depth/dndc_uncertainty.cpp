#include "stdafx.h"
#include "dndc71.h"
#include "graphexDoc.h"
#include "graphexView.h"
#include "SitePara.h"
#include "dndc_main.h"
//#include "region.h"
#include <errno.h>

int w1=100,w2=150,w3=180;
int q1=0,q2=30,q3=0;
void landuse_color(float ha, int *c1, int *c2, int *c3);
float find_ha(long int CountyID, int cropID);

void CGraphexView::read_scale(int stateID)
{
	switch (stateID)
	{
	case 0:	X1 = 133.0;
			X2 = 14;
			Y1 = 52.0;
			Y2 = 18;
			break;
	case 6:	X1 = 133.0;
			X2 = 45;
			Y1 = 43.0;
			Y2 = 58;
			break;

	}
	
}

void CGraphexView::draw_county1(CGraphexDoc *pDoc, int stateID)
{
	int pairs=0, oldStateID, i;
	long int MapID;
	float Da, Db, longitude, latitude;

	CString js;

	CPoint map_data[50000];

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (0,0); 
	art.SetViewportExt(1500, 3000);	

	CBrush Brush1(RGB(w1,w2,w3));		//define a brush

	art.FillRect(rectClient, &Brush1);

	Brush1.DeleteObject();

	FILE *Fcounty;
	CString StateName;	

	StateName.Format("%s\\Database\\USA\\Map\\US_county_map.txt", ROOTDIR);
	Fcounty = fopen(StateName, "r");
	if(Fcounty==NULL)
	{
		CString note;
		note.Format("Can not open file %s", StateName);
		AfxMessageBox(note);
		exit(0); 
	}

	read_scale(0);

	CPen *pOldPen = NULL;				
	CPen Pen1(PS_SOLID, 1, RGB(255,255,255));	
	pOldPen = art.SelectObject(&Pen1);

	//CString mmm;
	//mmm.Format("center.txt");
	//FILE* mm1;
	//mm1=fopen(mmm, "w");

	oldStateID=0;
	for(;;)
	{
		if(fscanf(Fcounty, "%ld %f %f", &MapID, &longitude, &latitude)!=3) 
			break;
		else
		{
			//if(MapID>0) fprintf(mm1, "%ld  %f %f\n", MapID, longitude, latitude);

			i = -1;
			pairs=0;
			for(;;)
			{
				
				if(fscanf(Fcounty, "%f", &Da)!=1)
				{
					fscanf(Fcounty, "%s", js);
					break;
				}
				else
				{
					i++;
					pairs++;

					fscanf(Fcounty, "%f", &Db);
				
					map_data[i].x  = (int)((X1 + Da) * X2);
					map_data[i].y = (int)((Y1 - Db) * Y2);
				}
			}
				
			art.Polyline(map_data, i);
			/*CBrush *pOldBrush = NULL;			//create a point for brush 
					CBrush Brush2(RGB(0,100,0));
					pOldBrush = art.SelectObject(&Brush2);  //select the brush into brush point
					
					art.Polygon(map_data, pairs);				//draw poligon with the pen and brush
				
					art.SelectObject(pOldBrush);		//return original brush into brush point	
					Brush2.DeleteObject();
			*/
		}
	}
				
	art.SelectObject(pOldPen);			
	Pen1.DeleteObject();

	fclose(Fcounty);
	//fclose(mm1);
	
	draw_states(pDoc);


}


void CGraphexView::draw_states(CGraphexDoc *pDoc)
{
	int pairs=0, j, i;
	long int map_id;
	float Da, Db;

	CPoint map_data[50000];

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);

	read_scale(0);

	for(j=1; j<=56; j++)
	{
			CString RF;
			FILE *ref;
			RF.Format("%s\\Database\\USA\\Map\\p-0%d.txt", ROOTDIR, j);
			ref = fopen(RF, "r");
			if(ref==NULL)
			{
				
			}
			else
			{
				if(fscanf(ref, "%ld %d", &map_id, &pairs)!=2) 
				{
				}
				else
				{
					for(i=0; i<pairs; i++)
					{
						fscanf(ref, "%f %f", &Da, &Db);
					
						{
							map_data[i].x  = (int)((X1 + Da) * X2);
							map_data[i].y = (int)((Y1 - Db) * Y2);
						}
					}

					CPen *pOldPen = NULL;				
					CPen Pen2(PS_SOLID, 1, RGB(0,0,0));	
					pOldPen = art.SelectObject(&Pen2);
					
					art.Polyline(map_data, pairs);
					
					art.SelectObject(pOldPen);			
					Pen2.DeleteObject();
					

					
				}
				fclose(ref);
			} 
		}	

}

void CGraphexView::draw_a_state(CGraphexDoc *pDoc, int stateID)
{
	int pairs=0, oldStateID, i;
	long int MapID;
	float Da, Db;
	
	int mID;
	
	CString js, countyID;

	CPoint map_data[50000];

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (0,0); 
	art.SetViewportExt(1500, 3000);	

	CBrush Brush1(RGB(w1,w2,w3));		//define a brush

	art.FillRect(rectClient, &Brush1);

	Brush1.DeleteObject();

	FILE *Fcounty;
	CString StateName;	

	if(stateID==6) StateName.Format("%s\\Database\\California\\GIS\\CA_5.txt", ROOTDIR);
	Fcounty = fopen(StateName, "r");
	if(Fcounty==NULL)
	{
		CString note;
		note.Format("Can not open file %s", StateName);
		AfxMessageBox(note);
		exit(0); 
	}

	read_scale(stateID);

	CPen *pOldPen = NULL;				
	CPen Pen1(PS_SOLID, 1, RGB(255,255,255));	
	pOldPen = art.SelectObject(&Pen1);

	//CString mmm;
	//mmm.Format("center.txt");
	//FILE* mm1;
	//mm1=fopen(mmm, "w");

	oldStateID=0;
	for(;;)
	{
		if(fscanf(Fcounty, "%s %d", countyID, &MapID)!=2) 
			break;
		else
		{
			CString MF;
			FILE* mf;
			MF.Format("%s\\Database\\California\\lib_map\\%d", ROOTDIR,MapID);
			mf=fopen(MF, "r");
			if(mf==NULL)
			{
				CString note;
				note.Format("Can not open file %s", MF);
				AfxMessageBox(note);
				exit(0); 
			}
			fscanf(mf, "%d %d", &mID, &pairs); 


			//i = -1;
			//pairs=0;
			for(i=0; i<pairs; i++)
			{
				
				if(fscanf(mf, "%f", &Da)!=1)
				{
					//fscanf(Fcounty, "%s", js);
					break;
				}
				else
				{
					//i++;
					//pairs++;

					fscanf(mf, "%f", &Db);
				
					map_data[i].x  = (int)((X1 + Da) * X2);
					map_data[i].y = (int)((Y1 - Db) * Y2);
				}
			}
			fclose(mf);

			art.Polyline(map_data, pairs);
			/*CBrush *pOldBrush = NULL;			//create a point for brush 
					CBrush Brush2(RGB(0,100,0));
					pOldBrush = art.SelectObject(&Brush2);  //select the brush into brush point
					
					art.Polygon(map_data, pairs);				//draw poligon with the pen and brush
				
					art.SelectObject(pOldBrush);		//return original brush into brush point	
					Brush2.DeleteObject();
			*/
		}
	}
				
	art.SelectObject(pOldPen);			
	Pen1.DeleteObject();

	fclose(Fcounty);
	//fclose(mm1);
	
	//draw_states(pDoc);

}

void CGraphexView::Find_Grid(int point_x, int point_y, int ScaleID, int SSL)
{
	int XX1, XX2, YY1, YY2, IntX, IntY;
	int d=5;
	int GridID, SelectedID=0, CountyID, MapID;
	float GridX, GridY;
	double W_log, W_lat;
	//int stateID=0;
	int i;
	CString Land;
	FILE* ld;

	read_scale(ScaleID);

	W_log = (double)point_x / (double)X2 - (double)X1; 
	W_lat = -((double)point_y / (double)Y2 - (double)Y1);

	if(SSL==1)
	{
		CString LL;
		FILE *lonlat;

		LL.Format("%s\\Inter\\SiteLocation.txt", OUTPUT);
		lonlat = fopen(LL, "w");
		if(lonlat==NULL)
			{
				CString note;
				note.Format("1. Can not create file %s", LL);
				AfxMessageBox(note);
				exit(0); 
			}
		fprintf(lonlat, "%f  %f", W_log, W_lat);
		fclose(lonlat);
	}

	int year_count = 1;
	int start_year = 1990;

	char qq[200];
	sprintf(qq, "%d %d %f %f", year_count, start_year, W_lat, W_log);

	XX1 = point_x - d;
	XX2 = point_x + d;
	YY1 = point_y - d;
	YY2 = point_y + d;

	CString RF;
	FILE *ref;
	RF.Format("%s\\Database\\USA\\Map\\County_center.txt", ROOTDIR);
	ref = fopen(RF, "r");
	if(ref==NULL)
		{
			CString note;
			note.Format("Sorry, I failed to follow. Please move a little bit slowly.");
			AfxMessageBox(note);
			exit(0); 
		}

	for(i=1; i<= 10000; i++)
	{
		if(fscanf(ref, "%ld %f %f", &GridID, &GridX, &GridY)!=3)
		{
			SelectedID = 0;
			goto tt;
			//break;
		}
		else
		{
			IntX = (int)((X1 + GridX) * X2);
			IntY = (int)((Y1 - GridY) * Y2);

			if(IntX>=XX1 && IntX<XX2)
			{
				if(IntY>=YY1 && IntY<YY2)
				{
					SelectedID = GridID;
					
					goto tt;
				}
			}
		}

	}
tt:
	fclose(ref);

	
	if(SelectedID==0)
	{
		CountyID=0;
		WizardCountyID=0;
	}
	else
	{
		Land.Format("%s\\Database\\USA\\Map\\CountyID_MapID.txt", ROOTDIR);
		ld=fopen(Land, "r");
		if(ld==NULL)
		{
			CString note;
			note.Format("Can not open file %s", Land);
			AfxMessageBox(note);
			exit(0);
		}
		else
		{
			for(;;)
			{
				if(fscanf(ld, "%d %ld", &WizardCountyID, &MapID)!=2)
				{				
					goto ttt;
				}
				else
				{
					if(MapID==SelectedID)
						goto ttt;
				}
			}
			CString note;
			note.Format("Map %ld is not found", SelectedID);
			AfxMessageBox(note);
			exit(0);
		}
ttt:
	fclose(ld);
	}

	//CString note;
	//note.Format("County %ld, Map %ld", CountyID, SelectedID);
	//AfxMessageBox(note);

	//return(CountyID);
}

void CGraphexView::draw_a_county(CGraphexDoc *pDoc, int WizardCountyID)
{
	int pairs=0, i, k;
	int MapID, map_id;
	float Da, Db;
	int c1, c2, c3;

	int oldState_ID;
	int CID, CountyID;
	int oldCountyID;
	
	CString junk;

	CPoint map_data[50000];

	POSITION pos = pDoc->GetFirstViewPosition();
	CView* pDC = pDoc->GetNextView( pos );
	CClientDC art(pDC);
	
	art.SetMapMode(MM_ANISOTROPIC);//);MM_ISOTROPIC
	art.SetWindowExt(1500, 3000);
	
	CRect rectClient;
	pDC->GetClientRect(rectClient);

	art.SetBkMode(TRANSPARENT);	

	art.SetViewportOrg (0,0); 
	art.SetViewportExt(1500, 3000);	

	CString IDfile;
	FILE *fid;
	
	IDfile.Format("%s\\inter\\WizardSite.txt", OUTPUT);
	fid = fopen(IDfile, "r");
	if ( fid == NULL )
	{

		return;
	}
	else
	{
		fscanf(fid, "%d %d", &oldState_ID, &oldCountyID);
		fclose(fid);
	}

	CString StateName;
	FILE* Fcounty;

	for(k=1; k<=2; k++)
	{
		StateName.Format("%s\\Database\\USA\\Map\\CountyID_MapID.txt", ROOTDIR);
		Fcounty = fopen(StateName, "r");
		if(Fcounty==NULL)
		{
			CString note;
			note.Format("Can not open file %s", StateName);
			AfxMessageBox(note);
			exit(0); 
		}

		read_scale(0);//stateID);

		for(;;)
		{
			if(fscanf(Fcounty, "%d %ld", &CountyID, &MapID)!=2) 
				break;
			else
			{
				if(k==1) CID=oldCountyID;
				else CID=WizardCountyID;

				if(CountyID==CID)
				{
					CString RF;
					FILE *ref;

					RF.Format("%s\\Database\\USA\\Map\\%ld", ROOTDIR, MapID);
					ref = fopen(RF, "r");
					if(ref==NULL)
					{
						CString note;
						note.Format("Can not find file %s", RF);
						AfxMessageBox(note);
						exit(0);
					}
					else
					{
						fscanf(ref, "%ld %d", &map_id, &pairs); 
						for(i=0; i<pairs; i++)
							{
								fscanf(ref, "%f %f", &Da, &Db);
							
								{
									map_data[i].x  = (int)((X1 + Da) * X2);
									map_data[i].y = (int)((Y1 - Db) * Y2);
								}
							}
							
							CPen *pOldPen = NULL;	
							
							if(k==1) 
							{
								c1 = w1; c2=w2; c3=w3;
							}
							else
							{
								c1 = 255; c2=200; c3=0;
							}
							CPen Pen1(PS_SOLID, 1, RGB(255,255,255));	
							pOldPen = art.SelectObject(&Pen1);	

							CBrush *pOldBrush = NULL;
							CBrush Brush1(RGB(c1,c2,c3));
							pOldBrush = art.SelectObject(&Brush1);  //select the brush into brush point
						
							art.Polygon(map_data, pairs);				//draw poligon with the pen and brush
					
							art.SelectObject(pOldBrush);		//return original brush into brush point	
							Brush1.DeleteObject();
						
							art.SelectObject(pOldPen);			
							Pen1.DeleteObject();

						}
						fclose(ref);
					}
				break;
			}

			;
		}//end of for{}
		
		fclose(Fcounty);
	}
	
	//draw_states(pDoc);

}

