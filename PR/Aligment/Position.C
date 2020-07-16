#include <TColor.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "TStyle.h"
#include "TFile.h"
#include "TF2.h"
#include "TH1.h"
#include "TH2.h"
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
double y1_up=0;
double Q1=0.;
double Q1_y=0.;
double WeightQ1=0.;
double WeightQ1_y=0.;

//Mid position;
double x2=0;
double y2=0;
double Q2=0.;
double WeightQ2=0.;
double Q2_y=0.;
double WeightQ2_y=0.;

//Down position
double x3=0;
double y3=0;
double Q3=0.;
double Q3_y=0.;
double WeightQ3=0.;
double WeightQ3_y=0.;

double Xresidual_mid=0.;
double Yresidual_mid=0.;
int MaxADC=0;
int MaxADC2=0;
// the branch of the position;
double px1;
double py1;
double px2;
double py2;
double px3;
double py3;
double entry;

void upSumADC();
void midSumADC();
void downSumADC();
void IfSignal();
void position();
void SetInitialize();
void FillSumADC();
//==================================================//
//************ The Signal Cut Condition **********//
int ADC_Cut=16;
int TB_Cut=3;
int Strip_Cut=3;

//the ALTRO of different layer.
int upALTROx[6]={42,43,36,37,38,39};
int upALTROy[4]={46,47,44,45};
int midALTROx[6]={50,51,34,35,40,41};
int midALTROy[4]={54,55,58,59};
int downALTROy[8]={48,49,60,61,52,53,56,57};
int downALTROx[4]={31,30,32,33};



//================================================//
int AllSigEvent=0;


TFile *file1 = new TFile("ThreeSumADC.root","RECREATE");
TH1F *h1x = new TH1F("h1x","Up S1_x_CH2",95,0,95);
TH1F *h2x = new TH1F("h2x","Middle S3_x_CH6",95,0,95);
TH1F *h3x = new TH1F("h3x","Down S2_x_CH8",95,0,95);
TH1F *h1y = new TH1F("h1y","Up S1_y_CV1",95,0,95);
TH1F *h2y = new TH1F("h2y","Middle S3_y_CV7",95,0,95);
TH1F *h3y = new TH1F("h3y","Down S2_y_CV3",95,0,95);


void Position(){
	TFile *file = new TFile("XYposition.root","RECREATE");
	TTree *tree = new TTree("tree","Midxy position");
	TH1F *h5 =new TH1F("h5","x_Pr",10000,-50,50);
	TH1F *h6 =new TH1F("h6","y_Pr",10000,-50,50);
	TCanvas *c1=new TCanvas("c1","",10,10,1600,600);
	//Set the position branch.
	tree->Branch("px1",&px1,"px1/D");
	tree->Branch("py1",&py1,"py1/D");
	tree->Branch("px2",&px2,"px2/D");
	tree->Branch("py2",&py2,"py2/D");
	tree->Branch("px3",&px3,"px3/D");
	tree->Branch("py3",&py3,"py3/D");
	tree->Branch("entry",&entry,"entry/D");

	ifstream data;
	data.open("../data/dataAll.txt");
	ifstream map;
	while(getline(data,stor,'\n')){
		line_size=stor.size();
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
		ps=stor.find("Event",0);
		if(ps>0){
			IfSignal();
			position();
			FillSumADC();
			if(Event%1000==0){
			cout <<"Event: "<<Event<<" x1: "<<x1<<" y1: "<<y1_up<<" x2: "<<x2<<" y2: "<<y2<<" x3: "<<x3<<" y3: "<<y3<<endl;
			cout<<endl;}

			// Fill the the position;
			entry=Event;
			px1=x1;
			py1=y1_up;
			px2=x2;
			py2=y2;
			px3=x3;
			py3=y3;
			tree->Fill();

			//pr
			Xresidual_mid=x2-(x1+x3)/2;
			h5->Fill(Xresidual_mid);
			
			Yresidual_mid=y2-(y1+y3)/2;
                        h6->Fill(Yresidual_mid);

			SetInitialize();

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
					if(STRIP>0){
						upSumADC();
						midSumADC();
						downSumADC();
					}
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
	if(ps<0){
	IfSignal();
	 position();
                        FillSumADC();
                        // Fill the the position;
                        entry=Event;
                        px1=x1;
                        py1=y1_up;
                        px2=x2;
                        py2=y2;
                        px3=x3;
                        py3=y3;
                        tree->Fill();

                        //pr
                        Xresidual_mid=x2-(x1+x3)/2;
                        h5->Fill(Xresidual_mid);
                        Yresidual_mid=y2-(y1+y3)/2;
                        h6->Fill(Yresidual_mid);
			SetInitialize();
	}
	//file end;
        
	file->cd();
	tree->Write();
	c1->Divide(1,2);
	c1->cd(1);
	h5->Draw();
	c1->cd(2);
	h6->Draw();

	data.close();
}
// main function end

void IfSignal(){
	if(Pulse==1){
		Tb.insert(Tb.end(), Tb_mid.begin(), Tb_mid.end());
		Adc.insert(Adc.end(), Adc_mid.begin(), Adc_mid.end());
		ThisStrip++;
		Pulse = 0;
	}
	if(ThisStrip>0){
		t=Tb.size();
		if(t>0){
			if(STRIP>0){
				upSumADC();
				midSumADC();
				downSumADC();}
		}
	}
	if(Event%1000==0){
	cout <<Event<<" Up_x: "<< UpStripCount <<" Up_y: "<<UpStripCount_y<< " Mid_x:  " << MidStripCount<< " Mid_y: "<< MidStripCount_y<<" Down_x: "<< DownStripCount<<" Down_y: "<<DownStripCount_y<< endl;
	}

}


void position(){
	if(UpStripCount>Strip_Cut&&UpStripCount_y>Strip_Cut&&MidStripCount>Strip_Cut&&MidStripCount_y>Strip_Cut&&DownStripCount>Strip_Cut&&DownStripCount_y>Strip_Cut){      
		//the up detector: X1
		for(int i=0; i<UpStripCount;i++){
			WeightQ1=((Upstrip[i]*3.2)*Upsumadc[i])+WeightQ1;
			Q1=Upsumadc[i]+Q1;
			h1x->SetBinContent(Upstrip[i],Upsumadc[i]);
		}
		x1=WeightQ1/Q1;
		//Y1
		for(int i=0; i<UpStripCount_y;i++){
			WeightQ1_y=((Upstrip_y[i]*3.2)*Upsumadc_y[i])+WeightQ1_y;
			Q1_y=Upsumadc_y[i]+Q1_y;
			h1y->SetBinContent(Upstrip_y[i],Upsumadc_y[i]);
		}
		y1_up=WeightQ1_y/Q1_y;


		//the middle detector:X2
		for(int i=0; i<MidStripCount;i++){
			WeightQ2=((Midstrip[i]*3.2)*Midsumadc[i])+WeightQ2;
			Q2=Midsumadc[i]+Q2;
			h2x->SetBinContent(Midstrip[i],Midsumadc[i]);
		}
		x2=WeightQ2/Q2;
		//Y2

		for(int i=0; i<MidStripCount_y;i++){
			WeightQ2_y=((Midstrip_y[i]*3.2)*Midsumadc_y[i])+WeightQ2_y;
			Q2_y=Midsumadc_y[i]+Q2_y;
			h2y->SetBinContent(Midstrip_y[i],Midsumadc_y[i]);
		}
		y2=WeightQ2_y/Q2_y;

		// the down detector:X3
		for(int i=0; i<DownStripCount;i++){
			WeightQ3=((Downstrip[i]*3.2)*Downsumadc[i])+WeightQ3;
			Q3=Downsumadc[i]+Q3;
			h3x->SetBinContent(Downstrip[i],Downsumadc[i]);
		}
		x3=WeightQ3/Q3;
		//Y3:
		for(int i=0; i<DownStripCount_y;i++){
			WeightQ3_y=((Downstrip_y[i]*3.2)*Downsumadc_y[i])+WeightQ3_y;
			Q3_y=Downsumadc_y[i]+Q3_y;
			h3y->SetBinContent(Downstrip_y[i],Downsumadc_y[i]);
		}
		y3=WeightQ3_y/Q3_y;


	}
}
void FillSumADC(){
	h1x->GetXaxis()->SetTitle("Strip");
	h1x->GetYaxis()->SetTitle("SumADC");
	h1y->GetXaxis()->SetTitle("Strip");
	h1y->GetYaxis()->SetTitle("SumADC");
	h2x->GetXaxis()->SetTitle("Strip");
	h2x->GetYaxis()->SetTitle("SumADC");
	h2y->GetXaxis()->SetTitle("Strip");
	h2y->GetYaxis()->SetTitle("SumADC");
	h3x->GetXaxis()->SetTitle("Strip");
	h3x->GetYaxis()->SetTitle("SumADC");
	h3y->GetXaxis()->SetTitle("Strip");
	h3y->GetYaxis()->SetTitle("SumADC");
	file1->cd();
	h1x->Write();
	h2x->Write();
	h3x->Write();
	h1y->Write();
	h2y->Write();
	h3y->Write();

}

void SetInitialize(){
	//The histogram need reset ;
	h1x->Reset();
	h2x->Reset();
	h3x->Reset();
	h1y->Reset();
	h2y->Reset();
	h3y->Reset();
	// the weight q and the q should be reset to 0 .
	WeightQ1 = 0;
	WeightQ1_y = 0;
	WeightQ2 = 0;
	WeightQ2_y= 0;
	WeightQ3 = 0;
	WeightQ3_y = 0;
	x1=0;
	y1_up=0;
	x2=0;
	y2=0;
	x3=0;
	y3=0;
	Q1 = 0;
	Q1_y=0;
	Q2 = 0;
	Q2_y = 0;
	Q3 = 0;
	Q3_y=0;


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

	// StripCount need reset 0;
	UpStripCount=0;
	UpStripCount_y=0;
	MidStripCount=0;
	MidStripCount_y=0;
	DownStripCount=0;
	DownStripCount_y=0;

	// clear vector and set the signal condition (ThisStrip=0)
	ThisStrip=0;
	Tb.clear();
	Adc.clear();
	Tb_mid.clear();
	Adc_mid.clear();
	TBcount = 0;
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
		//cout << "UpsumADC  " << UpsumADC << "  strip  " << STRIP <<" count " << UpStripCount << endl;
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
