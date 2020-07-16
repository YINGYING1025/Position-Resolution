#include <TColor.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "TStyle.h"
#include "TFile.h"
#include "TF2.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TDatime.h"
#include "TVirtualFitter.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TTree.h"
#include "TStyle.h"
#include "TString.h"
#include "THStack.h"
#include <THStack.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "TVectorD.h"
#include "TMinuit.h"
#include "TObject.h"
#include <TLine.h>
#include "TLegend.h"

//*********** CH6+S1_CV1_CH2+CH8 all have the signal event number ********************//

string stor;
string stor_map;
string event[11];
string altro[12];
string a;
string b;
string c;

int line_size=0;
int ps=0;
int Event=0;
int ALTRO=0;
int CH=0;
int TB=0;
double ADC=0;
int STRIP=0;
int preTB=0;
int t=0;
double UpsumADC=0;
double UpsumADC_y=0;
double MidsumADC=0;
double MidsumADC_y=0;
double DownsumADC=0;
double DownsumADC_y=0;
int j=0;
int alt=0;
int ch=0;
int Strip_num=0;

int TBcount=0;
int Pulse=0;
int ThisStrip=0;
int UpStripCount=0;
int UpStripCount_y=0;
int MidStripCount=0;
int MidStripCount_y=0;
int DownStripCount=0;
int DownStripCount_y=0;

int altro_map=0;
int ch_map=0;
int strip_map=0;
vector<int>Tb;
vector<double>Adc;
vector<int>Tb_mid;
vector<double>Adc_mid;
vector<double>Upsumadc;
vector<double>Upsumadc_y;
vector<double>Midsumadc;
vector<double>Midsumadc_y;
vector<double>Downsumadc;
vector<double>Downsumadc_y;
vector<int>Upstrip;
vector<int>Upstrip_y;
vector<int>Midstrip;
vector<int>Midstrip_y;
vector<int>Downstrip;
vector<int>Downstrip_y;

//Up position;
double x1=0;
double z1=0;
double Q1=0.;
double WightQ1=0.;

//Mid position;
double x2=0;
double z2=0;
double Q2=0.;
double WightQ2=0.;
double Q2_z=0.;
double WightQ2_z=0.;

//Down position
double x3=0;
double z4=0;
double Q3=0.;
double WightQ3=0.;
double Xresidual_up=0.;
double Xresidual_mid=0.;
double Xresidual_down=0.;
string path1;

void upSumADC();
void midSumADC();
void downSumADC();
int IfSignal(int k);

//************ The Signal Cut Condition **********//
int ADC_Cut=16;
int TB_Cut=3;
int Strip_Cut=3;

// Get signal cosmic ray and don't threshod ADC event.

// file 
int FileBegin=2462;
int FileEnd=2476;

//the ALTRO of different layer.
int upALTROx[6]={42,43,36,37,38,39};
int upALTROy[4]={46,47,44,45};
int midALTROx[6]={50,51,34,35,40,41};
int midALTROy[4]={54,55,58,59};
int downALTROy[8]={48,49,60,61,52,53,56,57};
int downALTROx[4]={31,30,32,33};
//================================================//
double MidxSignal=0;
double MidySignal=0;
double xAllevent=0;
double yAllevent=0;
double xEff=0.;
int AllSigEvent=0;

void efficiency(){
	TH1F *h1 =new TH1F("h1","Event style",5,0,5);
	TLatex *tex[4];

	for(int k=FileBegin;k<FileEnd;k++){
		ifstream data;
		ifstream map;
		path1=Form("/Volumes/shiyy/SourceData/three_Allxz/three_xy/test_%d.txt",k);
		data.open(path1);
		cout<<endl;
		cout<<endl;
		cout <<"**********************  File "<<k<<" is runing ***********************  "<<endl;	
		if(!data){
			continue;}
		while(getline(data,stor,'\n')){
			line_size=stor.size();
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
			ps=stor.find("Event",0);
			if(ps>0){
				
				IfSignal(k);
				allevent++;

				stringstream is(stor);
				while(is>>event[j]){j++;}
				j=0;
				event[2].pop_back();
				Event=atoi(event[2].c_str());
			}
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
			if(line_size==54){
				if(Pulse==1){
					Tb.insert(Tb.end(), Tb_mid.begin(), Tb_mid.end());
					Adc.insert(Adc.end(), Adc_mid.begin(), Adc_mid.end());
					ThisStrip++;
					Pulse = 0;
				}
				if(ThisStrip>0){
					t=Tb.size();
					if(t>0){
						MaxADC=*max_element(begin(Adc),end(Adc));
						if(MaxADC2<MaxADC){
							MaxADC2=MaxADC;}
						upSumADC();
						midSumADC();
						downSumADC();
					}
				}

				ThisStrip=0;
				Tb.clear();
				Adc.clear();
				Tb_mid.clear();
				Adc_mid.clear();
				TBcount = 0;

				// ALTRO CH Strip
				istringstream is(stor);
				while(is>>altro[j]){j++;}
				j=0;
				altro[7].pop_back();
				altro[9].pop_back();
				ALTRO=atoi(altro[7].c_str());
				CH=atoi(altro[9].c_str());
				map.open("../decode/strip_map_2.txt");
				while(getline(map,stor_map,'\n')){
					istringstream is(stor_map);
					is>>alt>>ch>>Strip_num;
					if(ALTRO==alt&&CH==ch){
						STRIP=Strip_num;}
				}
				map.close();
			}
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
			if(line_size==18){
				istringstream is(stor);
				while(is>>a>>TB>>b>>ADC>>c){

					if(TB-preTB!=-1){
						if(Pulse==1){
							Tb.insert(Tb.end(), Tb_mid.begin(), Tb_mid.end());
							Adc.insert(Adc.end(), Adc_mid.begin(), Adc_mid.end());
							ThisStrip++;
							Pulse = 0;
						}
						Tb_mid.clear();
						Adc_mid.clear();
						TBcount = 0;
					}
					if(ADC>ADC_Cut){
						TBcount ++;
					}
					if(ADC<ADC_Cut){
						TBcount = 0;
					}
					if(TBcount>TB_Cut){
						Pulse = 1;
					}

					Tb_mid.push_back(TB);
					Adc_mid.push_back(ADC);
					preTB=TB;
				}
			}
		}
		//****************** Line_size 18 END *******************/
		
		if(ps<0) IfSignal(k);
		data.close();
	}
}
// main function end

int IfSignal(int k){
	if(Pulse==1){
		Tb.insert(Tb.end(), Tb_mid.begin(), Tb_mid.end());
		Adc.insert(Adc.end(), Adc_mid.begin(), Adc_mid.end());
		ThisStrip++;
		Pulse = 0;
	}
	if(ThisStrip>0){
		t=Tb.size();
		if(t>0){
			upSumADC();
			midSumADC();
			downSumADC();
		}
	}

	Event=0;
	// strip sumADC need reset 0;
	Upsumadc.clear();
	Upsumadc_y.clear();
	Midsumadc.clear();
	Midsumadc_y.clear();
	Downsumadc.clear();
	Downsumadc_y.clear();
	Midstrip.clear();
	Midstrip_y.clear();
	Upstrip.clear();
	Upstrip_y.clear();
	Downstrip.clear();
	Downstrip_y.clear();

	UpStripCount=0;
	UpStripCount_y=0;
	MidStripCount=0;
	MidStripCount_y=0;
	DownStripCount=0;
	DownStripCount_y=0;

	ThisStrip=0;
	Tb.clear();
	Adc.clear();
	Tb_mid.clear();
	Adc_mid.clear();
	TBcount = 0;
	return 0;
}

void upSumADC(){
	//the up detector
	//X position
	int tb[t];
	int adc[t];
	if(ALTRO==upALTROx[0]||ALTRO==upALTROx[1]||ALTRO==upALTROx[2]||ALTRO==upALTROx[3]||ALTRO==upALTROx[4]||ALTRO==upALTROx[5]){
		for(int i=0;i<t;i++){
			tb[i]=Tb[i];
			adc[i]=Adc[i];
			if(adc[i]>10){
				UpsumADC=UpsumADC+adc[i];}
		}
		Upsumadc.push_back(UpsumADC);
		Upstrip.push_back(STRIP);
		UpStripCount++;
		UpsumADC=0;
	}
	// Y position
	if(ALTRO==upALTROy[0]||ALTRO==upALTROy[1]||ALTRO==upALTROy[2]||ALTRO==upALTROy[3]){
		for(int i=0;i<t;i++){
			tb[i]=Tb[i];
			adc[i]=Adc[i];
			if(adc[i]>10){
				UpsumADC_y=UpsumADC_y+adc[i];}
		}
		Upsumadc_y.push_back(UpsumADC_y);
		Upstrip_y.push_back(STRIP);
		UpStripCount_y++;
		UpsumADC_y=0;
	}


}

void midSumADC(){
	//the middle detector:
	//X position
	int tb[t];
	int adc[t];
	if(ALTRO==midALTROx[0]||ALTRO==midALTROx[1]||ALTRO==midALTROx[2]||ALTRO==midALTROx[3]||ALTRO==midALTROx[4]||ALTRO==midALTROx[5]){
		for(int i=0;i<t;i++){
			tb[i]=Tb[i];
			adc[i]=Adc[i];
			if(adc[i]>10){
				MidsumADC=MidsumADC+adc[i];}
		}
		Midsumadc.push_back(MidsumADC);
		Midstrip.push_back(STRIP);
		MidStripCount++;
		MidsumADC=0;
	}
	// Y position
	
	   if(ALTRO==midALTROy[0]||ALTRO==midALTROy[1]||ALTRO==midALTROy[2]||ALTRO==midALTROy[3]){
	   for(int i=0;i<t;i++){
	   tb[i]=Tb[i];
	   adc[i]=Adc[i];
	   if(adc[i]>10){
	   MidsumADC_y=MidsumADC_y+adc[i];}
	   }
	   Midsumadc_y.push_back(MidsumADC_y);
	   Midstrip_y.push_back(STRIP);
	   MidStripCount_y++;
	   MidsumADC_y=0;
	   }
}

void downSumADC(){

	// the end detetor
	// X position
	int tb[t];
	int adc[t];
	if(ALTRO==downALTROx[0]||ALTRO==downALTROx[1]||ALTRO==downALTROx[2]||ALTRO==downALTROx[3]){

		for(int i=0;i<t;i++){
			tb[i]=Tb[i];
			adc[i]=Adc[i];
			if(adc[i]>10){
				DownsumADC=DownsumADC+adc[i];}
		}
		Downsumadc.push_back(DownsumADC);
		Downstrip.push_back(STRIP);
		DownStripCount++;
		DownsumADC=0;
	}
	// Y position
	if(ALTRO==downALTROy[0]||ALTRO==downALTROy[1]||ALTRO==downALTROy[2]||ALTRO==downALTROy[3]||ALTRO==downALTROy[4]||ALTRO==downALTROy[5]||ALTRO==downALTROy[6]||ALTRO==downALTROy[7]){
		for(int i=0;i<t;i++){
			tb[i]=Tb[i];
			adc[i]=Adc[i];
			if(adc[i]>10){
				DownsumADC_y=DownsumADC_y+adc[i];}
		}
		Downsumadc_y.push_back(DownsumADC_y);
		Downstrip_y.push_back(STRIP);
		DownStripCount_y++;
		DownsumADC_y=0;
	}

}
void xEfficiency(){
	if(UpStripCount>Strip_Cut&&DownStripCount>Strip_Cut){
	for(int i=0; i<UpStripCount;i++){
                        WeightQ1=((Upstrip[i]*3.2)*Upsumadc[i])+WeightQ1;
                        Q1=Upsumadc[i]+Q1;
                        h1x->SetBinContent(Upstrip[i],Upsumadc[i]);
                }
                x1=WeightQ1/Q1;

		 //the middle detector:X2
                for(int i=0; i<MidStripCount;i++){
                        WeightQ2=((Midstrip[i]*3.2)*Midsumadc[i])+WeightQ2;
                        Q2=Midsumadc[i]+Q2;
                        h2x->SetBinContent(Midstrip[i],Midsumadc[i]);
                }
                x2=WeightQ2/Q2;

		// the down detector:X3
                for(int i=0; i<DownStripCount;i++){
                        WeightQ3=((Downstrip[i]*3.2)*Downsumadc[i])+WeightQ3;
                        Q3=Downsumadc[i]+Q3;
                        h3x->SetBinContent(Downstrip[i],Downsumadc[i]);
                }
                x3=WeightQ3/Q3;
		

}
