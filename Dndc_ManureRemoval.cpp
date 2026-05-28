#include "stdafx.h"
#include "Dndcgo.h"
#include "Source_main.h"
#include "Dndc_tool.h"
#include "math.h"

#ifdef MANURE 
extern class_manure MData;

void class_manure::FeedlotManureRemoval0(int FN, int GN, int q, float rcnrvl, float rcnrl, float rcnrr, float rcnb, float rcnh, float rcnm,
								 float *soc, float *son, float *SIN, float *rcvl, float *rcl, float *rcr, 
								 float *CRB1, float *CRB2, float *crhl, float *crhr, float *dphum, float *doc, 
								 float *nh4, float *no3, float *no2, float *no, float *n2o, float *n2, float *nh3, 
								 float *urea, int jday, float *co2, float *sph, double water[25][250],
								 float *day_wfps, float *temp, float air_temp, int scale, float *sop, 
								 float *OrgP, float *LabP, float *ComP, FILE* fFeedOut)// float *House_to_compost_C, float *House_to_compost_N, float *House_to_compost_H2O)
{
	//In this function, define and record date, destination, C/N/P/H2O amount of each manure component revoved from each barn
	
	float FloorToCompost[24]={0.0,0.0}, FloorToLagoon[24]={0.0,0.0}, FloorToDigester[24]={0.0,0.0}, FloorToField[24]={0.0,0.0};
	float GutterToCompost[24]={0.0,0.0}, GutterToLagoon[24]={0.0,0.0}, GutterToDigester[24]={0.0,0.0}, GutterToField[24]={0.0,0.0};

	float old_FloorN, old_FloorC, new_FloorN, new_FloorC;
	float old_GutterN, old_GutterC, new_GutterN, new_GutterC;
	float old_floor_H2O, new_floor_H2O, old_gutter_H2O, new_gutter_H2O;
	float old_floor_P, new_floor_P, old_gutter_P, new_gutter_P; 
	int CLD, fcc = FN, gcc=q+8, CNN=q+4, LNN=q+5, DNN=q+6, FNN=3;
	float old_N, old_C, old_P, old_H2O;
	float new_N, new_C, new_P, new_H2O;
	float TTrcvl, TTrcl, TTrcr, TTCRB1, TTCRB2, TTcrhl, TTcrhr, TTdphum, TTdoc, TTnh4, TTno3;
	float TTno2, TTno, TTn2o, TTn2, TTnh3, TTurea, TTwater, TTco2, TTOrgP, TTLabP, TTComP;
	float TMM=0.0, WPs=0.0;
	int ToComp=q+4, ToLago=q+5, ToDige=q+6, ToFiel=q+7, ToRema=q+1;//These indexes are what are used to track where inputs are being stored/transferred to. ToComp = Composter , ToLago=Lagoon, ToDige=To Digester, ToField= To Field, ToRema=Remain in faciltity component. 
	
	if(MData.m_ManureRemoveFrequency[fcc]==0.0) CLD=1;
	else CLD = jday%(int)MData.m_ManureRemoveFrequency[fcc];

	if(CLD==0)
	{
		fprintf(fFeedOut, "%d\n", jday);
		
		//Solid phase to compost Note the pools are all being referenced/indexed using the above defined indexes with the remaining Feedlot pools defined using GN? are multiplied at the end. 
		rcvl[ToComp] += (rcvl[GN] * MData.m_FC[fcc]);//resistant very labile C pool get solid C added to it. MData.m_FC is FeedLot inputs?????
		rcl[ToComp] += (rcl[GN] * MData.m_FC[fcc]);
		rcr[ToComp] += (rcr[GN] * MData.m_FC[fcc]);
		CRB1[ToComp] += (CRB1[GN] * MData.m_FC[fcc]);
		CRB2[ToComp] += (CRB2[GN] * MData.m_FC[fcc]);
		crhl[ToComp] += (crhl[GN] * MData.m_FC[fcc]);
		crhr[ToComp] += (crhr[GN] * MData.m_FC[fcc]);
		dphum[ToComp] += (dphum[GN] * MData.m_FC[fcc]);
		OrgP[ToComp] += (OrgP[GN] * MData.m_FC[fcc]);
		LabP[ToComp] += (LabP[GN] * MData.m_FC[fcc]);
		ComP[ToComp] += (ComP[GN] * MData.m_FC[fcc]);				
		//Liquid phase to compost - mostly N portions but also some DOC, CO2 and water
		nh4[ToComp] += (nh4[GN] * MData.m_UC[fcc]);
		no3[ToComp] += (no3[GN] * MData.m_UC[fcc]);
		no2[ToComp] += (no2[GN] * MData.m_UC[fcc]);
		no[ToComp] += (no[GN] * MData.m_UC[fcc]);
		n2o[ToComp] += (n2o[GN] * MData.m_UC[fcc]);
		n2[ToComp] += (n2[GN] * MData.m_UC[fcc]);
		nh3[ToComp] += (nh3[GN] * MData.m_UC[fcc]);
		urea[ToComp] += (urea[GN] * MData.m_UC[fcc]);
		co2[ToComp] += (co2[GN] * MData.m_UC[fcc]);
		doc[ToComp] += (doc[GN] * MData.m_UC[fcc]);
		water[1][ToComp] += (water[1][GN] * MData.m_UC[fcc]);

		fprintf(fFeedOut, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ", 
				rcvl[GN] * MData.m_FC[fcc], rcl[GN] * MData.m_FC[fcc], rcr[GN] * MData.m_FC[fcc], CRB1[GN] * MData.m_FC[fcc], CRB2[GN] * MData.m_FC[fcc],
				crhl[GN] * MData.m_FC[fcc], crhr[GN] * MData.m_FC[fcc], dphum[GN] * MData.m_FC[fcc], OrgP[GN] * MData.m_FC[fcc], LabP[GN] * MData.m_FC[fcc],
				ComP[GN] * MData.m_FC[fcc], nh4[GN] * MData.m_UC[fcc], no3[GN] * MData.m_UC[fcc], no2[GN] * MData.m_UC[fcc], no[GN] * MData.m_UC[fcc],
				n2o[GN] * MData.m_UC[fcc], n2[GN] * MData.m_UC[fcc], nh3[GN] * MData.m_UC[fcc], urea[GN] * MData.m_UC[fcc], co2[GN] * MData.m_UC[fcc],
				doc[GN] * MData.m_UC[fcc], water[1][GN] * MData.m_UC[fcc]);
		fprintf(fFeedOut, "\n");

		MData.House_to_compost_C = rcvl[GN] * MData.m_FC[fcc] + rcl[GN] * MData.m_FC[fcc] + rcr[GN] * MData.m_FC[fcc] + CRB1[GN] * MData.m_FC[fcc] + 
			CRB2[GN] * MData.m_FC[fcc] + crhl[GN] * MData.m_FC[fcc] + crhr[GN] * MData.m_FC[fcc] + dphum[GN] * MData.m_FC[fcc] + 
			co2[GN] * MData.m_UC[fcc] + doc[GN] * MData.m_UC[fcc];//total is 10 items

		MData.House_to_compost_N = rcvl[GN] * MData.m_FC[fcc] /rcnrvl + rcl[GN] * MData.m_FC[fcc]/rcnrl + rcr[GN] * MData.m_FC[fcc]/rcnrr + 
			CRB1[GN] * MData.m_FC[fcc]/rcnb + CRB2[GN] * MData.m_FC[fcc]/rcnb + crhl[GN] * MData.m_FC[fcc]/rcnh + crhr[GN] * MData.m_FC[fcc]/rcnh + 
			dphum[GN] * MData.m_FC[fcc]/rcnm + nh4[GN] * MData.m_UC[fcc] + no3[GN] * MData.m_UC[fcc] + no2[GN] * MData.m_UC[fcc] + no[GN] * MData.m_UC[fcc] + 
			n2o[GN] * MData.m_UC[fcc] + n2[GN] * MData.m_UC[fcc] + nh3[GN] * MData.m_UC[fcc] + urea[GN] * MData.m_UC[fcc];//total is 16 items

		MData.House_to_compost_P = OrgP[GN] * MData.m_FC[fcc] + LabP[GN] * MData.m_FC[fcc] + ComP[GN] * MData.m_FC[fcc];

		MData.House_to_compost_H2O = water[1][GN] * MData.m_UC[fcc];


		//Solid phase to lagoon
		rcvl[ToLago] += (rcvl[GN] * MData.m_FL[fcc]);
		rcl[ToLago] += (rcl[GN] * MData.m_FL[fcc]);
		rcr[ToLago] += (rcr[GN] * MData.m_FL[fcc]);
		CRB1[ToLago] += (CRB1[GN] * MData.m_FL[fcc]);
		CRB2[ToLago] += (CRB2[GN] * MData.m_FL[fcc]);
		crhl[ToLago] += (crhl[GN] * MData.m_FL[fcc]);
		crhr[ToLago] += (crhr[GN] * MData.m_FL[fcc]);
		dphum[ToLago] += (dphum[GN] * MData.m_FL[fcc]);
		OrgP[ToLago] += (OrgP[GN] * MData.m_FL[fcc]);
		LabP[ToLago] += (LabP[GN] * MData.m_FL[fcc]);
		ComP[ToLago] += (ComP[GN] * MData.m_FL[fcc]);				
		//Liquid phase to lagoon
		nh4[ToLago] += (nh4[GN] * MData.m_UL[fcc]);
		no3[ToLago] += (no3[GN] * MData.m_UL[fcc]);
		no2[ToLago] += (no2[GN] * MData.m_UL[fcc]);
		no[ToLago] += (no[GN] * MData.m_UL[fcc]);
		n2o[ToLago] += (n2o[GN] * MData.m_UL[fcc]);
		n2[ToLago] += (n2[GN] * MData.m_UL[fcc]);
		nh3[ToLago] += (nh3[GN] * MData.m_UL[fcc]);
		urea[ToLago] += (urea[GN] * MData.m_UL[fcc]);
		co2[ToLago] += (co2[GN] * MData.m_UL[fcc]);
		doc[ToLago] += (doc[GN] * MData.m_UL[fcc]);
		water[1][ToLago] += (water[1][GN] * MData.m_UL[fcc]);

		fprintf(fFeedOut, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ", 
				rcvl[GN] * MData.m_FL[fcc], rcl[GN] * MData.m_FL[fcc], rcr[GN] * MData.m_FL[fcc], CRB1[GN] * MData.m_FL[fcc], CRB2[GN] * MData.m_FL[fcc],
				crhl[GN] * MData.m_FL[fcc], crhr[GN] * MData.m_FL[fcc], dphum[GN] * MData.m_FL[fcc], OrgP[GN] * MData.m_FL[fcc], LabP[GN] * MData.m_FL[fcc],
				ComP[GN] * MData.m_FL[fcc], nh4[GN] * MData.m_UL[fcc], no3[GN] * MData.m_UL[fcc], no2[GN] * MData.m_UL[fcc], no[GN] * MData.m_UL[fcc],
				n2o[GN] * MData.m_UL[fcc], n2[GN] * MData.m_UL[fcc], nh3[GN] * MData.m_UL[fcc], urea[GN] * MData.m_UL[fcc], co2[GN] * MData.m_UL[fcc],
				doc[GN] * MData.m_UL[fcc], water[1][GN] * MData.m_UL[fcc]);
		fprintf(fFeedOut, "\n");

		MData.House_to_lagoon_C = rcvl[GN] * MData.m_FL[fcc] + rcl[GN] * MData.m_FL[fcc] + rcr[GN] * MData.m_FL[fcc] + CRB1[GN] * MData.m_FL[fcc] + 
			CRB2[GN] * MData.m_FL[fcc] + crhl[GN] * MData.m_FL[fcc] + crhr[GN] * MData.m_FL[fcc] + dphum[GN] * MData.m_FL[fcc] + 
			co2[GN] * MData.m_UL[fcc] + doc[GN] * MData.m_UL[fcc];//total is 10 items

		MData.House_to_lagoon_N = rcvl[GN] * MData.m_FL[fcc] /rcnrvl + rcl[GN] * MData.m_FL[fcc]/rcnrl + rcr[GN] * MData.m_FL[fcc]/rcnrr + 
			CRB1[GN] * MData.m_FL[fcc]/rcnb + CRB2[GN] * MData.m_FL[fcc]/rcnb + crhl[GN] * MData.m_FL[fcc]/rcnh + crhr[GN] * MData.m_FL[fcc]/rcnh + 
			dphum[GN] * MData.m_FL[fcc]/rcnm + nh4[GN] * MData.m_UL[fcc] + no3[GN] * MData.m_UL[fcc] + no2[GN] * MData.m_UL[fcc] + no[GN] * MData.m_UL[fcc] + 
			n2o[GN] * MData.m_UL[fcc] + n2[GN] * MData.m_UL[fcc] + nh3[GN] * MData.m_UL[fcc] + urea[GN] * MData.m_UL[fcc];//total is 16 items

		MData.House_to_lagoon_P = OrgP[GN] * MData.m_FL[fcc] + LabP[GN] * MData.m_FL[fcc] + ComP[GN] * MData.m_FL[fcc];

		MData.House_to_lagoon_H2O = water[1][GN] * MData.m_UL[fcc];

		//Solid phase to digester
		rcvl[ToDige] += (rcvl[GN] * MData.m_FD[fcc]);
		rcl[ToDige] += (rcl[GN] * MData.m_FD[fcc]);
		rcr[ToDige] += (rcr[GN] * MData.m_FD[fcc]);
		CRB1[ToDige] += (CRB1[GN] * MData.m_FD[fcc]);
		CRB2[ToDige] += (CRB2[GN] * MData.m_FD[fcc]);
		crhl[ToDige] += (crhl[GN] * MData.m_FD[fcc]);
		crhr[ToDige] += (crhr[GN] * MData.m_FD[fcc]);
		dphum[ToDige] += (dphum[GN] * MData.m_FD[fcc]);
		OrgP[ToDige] += (OrgP[GN] * MData.m_FD[fcc]);
		LabP[ToDige] += (LabP[GN] * MData.m_FD[fcc]);
		ComP[ToDige] += (ComP[GN] * MData.m_FD[fcc]);				
		//Liquid phase to digester
		nh4[ToDige] += (nh4[GN] * MData.m_UD[fcc]);
		no3[ToDige] += (no3[GN] * MData.m_UD[fcc]);
		no2[ToDige] += (no2[GN] * MData.m_UD[fcc]);
		no[ToDige] += (no[GN] * MData.m_UD[fcc]);
		n2o[ToDige] += (n2o[GN] * MData.m_UD[fcc]);
		n2[ToDige] += (n2[GN] * MData.m_UD[fcc]);
		nh3[ToDige] += (nh3[GN] * MData.m_UD[fcc]);
		urea[ToDige] += (urea[GN] * MData.m_UD[fcc]);
		co2[ToDige] += (co2[GN] * MData.m_UD[fcc]);
		doc[ToDige] += (doc[GN] * MData.m_UD[fcc]);
		water[1][ToDige] += (water[1][GN] * MData.m_UD[fcc]);

		fprintf(fFeedOut, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ", 
				rcvl[GN] * MData.m_FD[fcc], rcl[GN] * MData.m_FD[fcc], rcr[GN] * MData.m_FD[fcc], CRB1[GN] * MData.m_FD[fcc], CRB2[GN] * MData.m_FD[fcc],
				crhl[GN] * MData.m_FD[fcc], crhr[GN] * MData.m_FD[fcc], dphum[GN] * MData.m_FD[fcc], OrgP[GN] * MData.m_FD[fcc], LabP[GN] * MData.m_FD[fcc],
				ComP[GN] * MData.m_FD[fcc], nh4[GN] * MData.m_UD[fcc], no3[GN] * MData.m_UD[fcc], no2[GN] * MData.m_UD[fcc], no[GN] * MData.m_UD[fcc],
				n2o[GN] * MData.m_UD[fcc], n2[GN] * MData.m_UD[fcc], nh3[GN] * MData.m_UD[fcc], urea[GN] * MData.m_UD[fcc], co2[GN] * MData.m_UD[fcc],
				doc[GN] * MData.m_UD[fcc], water[1][GN] * MData.m_UD[fcc]);
		fprintf(fFeedOut, "\n");

		MData.House_to_digester_C = rcvl[GN] * MData.m_FD[fcc] + rcl[GN] * MData.m_FD[fcc] + rcr[GN] * MData.m_FD[fcc] + CRB1[GN] * MData.m_FD[fcc] + 
			CRB2[GN] * MData.m_FD[fcc] + crhl[GN] * MData.m_FD[fcc] + crhr[GN] * MData.m_FD[fcc] + dphum[GN] * MData.m_FD[fcc] + 
			co2[GN] * MData.m_UD[fcc] + doc[GN] * MData.m_UD[fcc];//total is 10 items

		MData.House_to_digester_N = rcvl[GN] * MData.m_FD[fcc] /rcnrvl + rcl[GN] * MData.m_FD[fcc]/rcnrl + rcr[GN] * MData.m_FD[fcc]/rcnrr + 
			CRB1[GN] * MData.m_FD[fcc]/rcnb + CRB2[GN] * MData.m_FD[fcc]/rcnb + crhl[GN] * MData.m_FD[fcc]/rcnh + crhr[GN] * MData.m_FD[fcc]/rcnh + 
			dphum[GN] * MData.m_FD[fcc]/rcnm + nh4[GN] * MData.m_UD[fcc] + no3[GN] * MData.m_UD[fcc] + no2[GN] * MData.m_UD[fcc] + no[GN] * MData.m_UD[fcc] + 
			n2o[GN] * MData.m_UD[fcc] + n2[GN] * MData.m_UD[fcc] + nh3[GN] * MData.m_UD[fcc] + urea[GN] * MData.m_UD[fcc];//total is 16 items

		MData.House_to_digester_P = OrgP[GN] * MData.m_FD[fcc] + LabP[GN] * MData.m_FD[fcc] + ComP[GN] * MData.m_FD[fcc];

		MData.House_to_digester_H2O = water[1][GN] * MData.m_UD[fcc];

		//Solid phase to field
		rcvl[ToFiel] += (rcvl[GN] * MData.m_FF[fcc]);
		rcl[ToFiel] += (rcl[GN] * MData.m_FF[fcc]);
		rcr[ToFiel] += (rcr[GN] * MData.m_FF[fcc]);
		CRB1[ToFiel] += (CRB1[GN] * MData.m_FF[fcc]);
		CRB2[ToFiel] += (CRB2[GN] * MData.m_FF[fcc]);
		crhl[ToFiel] += (crhl[GN] * MData.m_FF[fcc]);
		crhr[ToFiel] += (crhr[GN] * MData.m_FF[fcc]);
		dphum[ToFiel] += (dphum[GN] * MData.m_FF[fcc]);
		OrgP[ToFiel] += (OrgP[GN] * MData.m_FF[fcc]);
		LabP[ToFiel] += (LabP[GN] * MData.m_FF[fcc]);
		ComP[ToFiel] += (ComP[GN] * MData.m_FF[fcc]);				
		//Liquid phase to field
		nh4[ToFiel] += (nh4[GN] * MData.m_UF[fcc]);
		no3[ToFiel] += (no3[GN] * MData.m_UF[fcc]);
		no2[ToFiel] += (no2[GN] * MData.m_UF[fcc]);
		no[ToFiel] += (no[GN] * MData.m_UF[fcc]);
		n2o[ToFiel] += (n2o[GN] * MData.m_UF[fcc]);
		n2[ToFiel] += (n2[GN] * MData.m_UF[fcc]);
		nh3[ToFiel] += (nh3[GN] * MData.m_UF[fcc]);
		urea[ToFiel] += (urea[GN] * MData.m_UF[fcc]);
		co2[ToFiel] += (co2[GN] * MData.m_UF[fcc]);
		doc[ToFiel] += (doc[GN] * MData.m_UF[fcc]);
		water[1][ToFiel] += (water[1][GN] * MData.m_UF[fcc]);

		fprintf(fFeedOut, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ", 
				rcvl[GN] * MData.m_FF[fcc], rcl[GN] * MData.m_FF[fcc], rcr[GN] * MData.m_FF[fcc], CRB1[GN] * MData.m_FF[fcc], CRB2[GN] * MData.m_FF[fcc],
				crhl[GN] * MData.m_FF[fcc], crhr[GN] * MData.m_FF[fcc], dphum[GN] * MData.m_FF[fcc], OrgP[GN] * MData.m_FF[fcc], LabP[GN] * MData.m_FF[fcc],
				ComP[GN] * MData.m_FF[fcc], nh4[GN] * MData.m_UF[fcc], no3[GN] * MData.m_UF[fcc], no2[GN] * MData.m_UF[fcc], no[GN] * MData.m_UF[fcc],
				n2o[GN] * MData.m_UF[fcc], n2[GN] * MData.m_UF[fcc], nh3[GN] * MData.m_UF[fcc], urea[GN] * MData.m_UF[fcc], co2[GN] * MData.m_UF[fcc],
				doc[GN] * MData.m_UF[fcc], water[1][GN] * MData.m_UF[fcc]);
		fprintf(fFeedOut, "\n");

		MData.House_to_field_C = rcvl[GN] * MData.m_FF[fcc] + rcl[GN] * MData.m_FF[fcc] + rcr[GN] * MData.m_FF[fcc] + CRB1[GN] * MData.m_FF[fcc] + 
			CRB2[GN] * MData.m_FF[fcc] + crhl[GN] * MData.m_FF[fcc] + crhr[GN] * MData.m_FF[fcc] + dphum[GN] * MData.m_FF[fcc] + 
			co2[GN] * MData.m_UF[fcc] + doc[GN] * MData.m_UF[fcc];//total is 10 items

		MData.House_to_field_N = rcvl[GN] * MData.m_FF[fcc] /rcnrvl + rcl[GN] * MData.m_FF[fcc]/rcnrl + rcr[GN] * MData.m_FF[fcc]/rcnrr + 
			CRB1[GN] * MData.m_FF[fcc]/rcnb + CRB2[GN] * MData.m_FF[fcc]/rcnb + crhl[GN] * MData.m_FF[fcc]/rcnh + crhr[GN] * MData.m_FF[fcc]/rcnh + 
			dphum[GN] * MData.m_FF[fcc]/rcnm + nh4[GN] * MData.m_UF[fcc] + no3[GN] * MData.m_UF[fcc] + no2[GN] * MData.m_UF[fcc] + no[GN] * MData.m_UF[fcc] + 
			n2o[GN] * MData.m_UF[fcc] + n2[GN] * MData.m_UF[fcc] + nh3[GN] * MData.m_UF[fcc] + urea[GN] * MData.m_UF[fcc];//total is 16 items

		MData.House_to_field_P = OrgP[GN] * MData.m_FF[fcc] + LabP[GN] * MData.m_FF[fcc] + ComP[GN] * MData.m_FF[fcc];

		MData.House_to_field_H2O = water[1][GN] * MData.m_UF[fcc];

		//Solid phase to remain
		rcvl[GN] = (rcvl[GN] * MData.m_FR[fcc]);
		rcl[GN] = (rcl[GN] * MData.m_FR[fcc]);
		rcr[GN] = (rcr[GN] * MData.m_FR[fcc]);
		CRB1[GN] = (CRB1[GN] * MData.m_FR[fcc]);
		CRB2[GN] = (CRB2[GN] * MData.m_FR[fcc]);
		crhl[GN] = (crhl[GN] * MData.m_FR[fcc]);
		crhr[GN] = (crhr[GN] * MData.m_FR[fcc]);
		dphum[GN] = (dphum[GN] * MData.m_FR[fcc]);
		OrgP[GN] = (OrgP[GN] * MData.m_FR[fcc]);
		LabP[GN] = (LabP[GN] * MData.m_FR[fcc]);
		ComP[GN] = (ComP[GN] * MData.m_FR[fcc]);				
		//Liquid phase to remain
		nh4[GN] = (nh4[GN] * MData.m_UR[fcc]);
		no3[GN] = (no3[GN] * MData.m_UR[fcc]);
		no2[GN] = (no2[GN] * MData.m_UR[fcc]);
		no[GN] = (no[GN] * MData.m_UR[fcc]);
		n2o[GN] = (n2o[GN] * MData.m_UR[fcc]);
		n2[GN] = (n2[GN] * MData.m_UR[fcc]);
		nh3[GN] = (nh3[GN] * MData.m_UR[fcc]);
		urea[GN] = (urea[GN] * MData.m_UR[fcc]);
		co2[GN] = (co2[GN] * MData.m_UR[fcc]);
		doc[GN] = (doc[GN] * MData.m_UR[fcc]);
		water[1][GN] = (water[1][GN] * MData.m_UR[fcc]);	

		MData.yr_House_to_compost_C += MData.House_to_compost_C;
		MData.yr_House_to_compost_N += MData.House_to_compost_N;
		MData.yr_House_to_compost_P += MData.House_to_compost_P;
		MData.yr_House_to_compost_H2O += MData.House_to_compost_H2O;

		MData.yr_House_to_lagoon_C += MData.House_to_lagoon_C;
		MData.yr_House_to_lagoon_N += MData.House_to_lagoon_N;
		MData.yr_House_to_lagoon_P += MData.House_to_lagoon_P;
		MData.yr_House_to_lagoon_H2O += MData.House_to_lagoon_H2O;

		MData.yr_House_to_digester_C += MData.House_to_digester_C;
		MData.yr_House_to_digester_N += MData.House_to_digester_N;
		MData.yr_House_to_digester_P += MData.House_to_digester_P;
		MData.yr_House_to_digester_H2O += MData.House_to_digester_H2O;
		
		MData.yr_House_to_field_C += MData.House_to_field_C;
		MData.yr_House_to_field_N += MData.House_to_field_N;
		MData.yr_House_to_field_P += MData.House_to_field_P;
		MData.yr_House_to_field_H2O += MData.House_to_field_H2O;

		MData.House_floor_removedC = MData.House_to_compost_C + MData.House_to_lagoon_C + 
									MData.House_to_digester_C + MData.House_to_field_C;

		MData.House_floor_removedN = MData.House_to_compost_N + MData.House_to_lagoon_N + 
									MData.House_to_digester_N + MData.House_to_field_N;

		MData.House_floor_removedP = MData.House_to_compost_P + MData.House_to_lagoon_P + 
									MData.House_to_digester_P + MData.House_to_field_P;

		MData.House_floor_removedH2O = MData.House_to_compost_H2O + MData.House_to_lagoon_H2O + 
									MData.House_to_digester_H2O + MData.House_to_field_H2O;


		}	
		else
		{
			fprintf(fFeedOut, "%d\n", jday);
			for(int i6=1; i6<=22; i6++) fprintf(fFeedOut, "%f ", 0.0);
			fprintf(fFeedOut, "\n");
			for(int i7=1; i7<=22; i7++) fprintf(fFeedOut, "%f ", 0.0);
			fprintf(fFeedOut, "\n");
			for(int i8=1; i8<=22; i8++) fprintf(fFeedOut, "%f ", 0.0);
			fprintf(fFeedOut, "\n");
			for(int i9=1; i9<=22; i9++) fprintf(fFeedOut, "%f ", 0.0);
			fprintf(fFeedOut, "\n");

			MData.House_floor_removedN = 0.0; 
			MData.House_floor_removedC = 0.0; 
			MData.House_floor_removedP = 0.0;
			MData.House_floor_removedH2O = 0.0;
			
		}
}

#endif