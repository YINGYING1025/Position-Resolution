#include "TH1.h"
#include "TF1.h"
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


double px1_cp;
double py1_cp;
double px2_cp;
double py2_cp;
double px3_cp;
double py3_cp;
double entry_cp;

double x_residual=0.;
double y_residual=0.;
const int xAligbinNum=1600;//AllEvent & Aligment 
const int yAligbinNum=1100;

TCanvas *c4=new TCanvas("c4","Verticle_Aligment_PR",500,500);
TH1F *xAlig =new TH1F("xAlig","VerticleMid AligmentX PR",xAligbinNum,-50,50);
TH1F *yAlig =new TH1F("yAlig","AllMid AligmentY PR",yAligbinNum,-50,50);

vector<double>x1;
vector<double>y1_sTGC;
vector<double>x2;
vector<double>y2;
vector<double>x3;
vector<double>y3;

void fcn12x3(int &npar, double *gin, double &chi2, double *par, int iflag){
	//Calculate log-likelihood
	double angle = par[0];
	double detaX = par[1];
	double detaZ = par[2];
	chi2=0;
	for(int j=0; j<x2.size(); j++){
		//chi2+=pow((35.3/66.2*x1[j]+30.9/66.2*x3[j])*cos(angle)-(46.1/66.2*y1_sTGC[j]+20.1/66.2*y3[j])*sin(angle)+detaX-x2[j],2);
		if(x1[j]!=x3[j]){
			chi2+=pow((35.3/66.2*x1[j]+30.9/66.2*x3[j])*cos(angle)-(46.1/66.2*y1_sTGC[j]+20.1/66.2*y3[j])*sin(angle)+detaX-x2[j]-77*detaZ/(x1[j]-x3[j]),2);
		}
	}
	chi2 *=2;

}

//=============== select verticle cosmic ray ================//
double xAngleSet=89.4;//" 89.4。"
double yAngleSet=0;//"。"
double xAngle=0.;
double yAngle=0.;
double TanAlpha=0.;//"X cosmicray tan angle"
double TanGamma=0.;//"Y cosmicray tan angle "
double high13=77.;//mm

void Select_Verticle_Event(){
	xAngle=xAngleSet/180.*TMath::Pi();//tansfer the degree to pi.
	yAngle=yAngleSet/180.*TMath::Pi();
	//*** This VerticleEvent cosmic ray angle is:
	TanAlpha=abs(high13/(px3_cp-px1_cp));
	TanGamma=abs(high13/(py3_cp-py1_cp));
}

int main_ver(){
	//ReadFile

	TFile *f =new TFile("./RealEvent/RealEventTree.root");
	TTree *t1 =(TTree*)f->Get("RealEventTreeY");
	gStyle->SetOptFit(1101);

	// Get the data tree
	t1->SetBranchAddress("px1_cp",&px1_cp);
	t1->SetBranchAddress("py1_cp",&py1_cp);
	t1->SetBranchAddress("px2_cp",&px2_cp);
	t1->SetBranchAddress("py2_cp",&py2_cp);
	t1->SetBranchAddress("px3_cp",&px3_cp);
	t1->SetBranchAddress("py3_cp",&py3_cp);
	t1->SetBranchAddress("entry_cp",&entry_cp);
	const int nentries=(int)t1->GetEntries();
	cout<<"The All Event is: "<<nentries<<endl;

	//Get data point
	cout<<endl<<"Get data point"<<endl;
	for( int i=0; i<20; i++)cout<<"*"; cout<<endl;

	//Get_input_data();
	for(int i=8000;i<nentries;i++){
		t1->GetEntry(i);//loop the all event x and y position.
		//if((px3>px2&&px2<px1)||(px3<px2&&px2>px1)||(py3>py2&&py2<py1)||(py3<py2&&py2>py1)) continue;
		//Remove some event that the measurement point is not a line.
		
		Select_Verticle_Event();
		if(TanAlpha>TMath::Tan(xAngle)&&TanGamma>TMath::Tan(yAngle)){

			//*** Get_All_Event_data for Aligment
			x1.push_back(px1_cp);
			y1_sTGC.push_back(py1_cp);
			x2.push_back(px2_cp);
			y2.push_back(py2_cp);
			x3.push_back(px3_cp);
			y3.push_back(py3_cp);
		}
	}

/*
	//prepare for fit
	cout<<endl<<"Define the Minuit facility"<<endl;
	for( int i=0; i<50; i++)cout<<"="; cout<<endl;

	const int npar=3;
	TMinuit * gMinuit= new TMinuit(npar);

	cout<<"set the fitting fucntion"<<endl;
	for( int i=0; i<50; i++)cout<<"="; cout<<endl;
	gMinuit->SetFCN(fcn12x3);

	//cout<<"start the minimization"<<endl;
	//for( int i=0; i<50; i++)cout<<"="; cout<<endl;
	//	gMinuit->SetErrorDef(0.5);

	double arglist[10];
	int ierflg=0;
	//	arglist[0]=2;
	arglist[0]=1;
	gMinuit->mnexcm("SET STR",arglist,1,ierflg);
	//gMinuit->mnexcm("SET ERR", arglist,1,ierflg);
	//Set starting values and step sizes for parameters
	double vstart[npar] = {0, 0, 0};
	double step[npar] = {0.00001, 0.01, 0.1};
	gMinuit->mnparm(0, "angle_Mid_x", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "detaX_Mid_x", vstart[1], step[1], 0, 0, ierflg);
	gMinuit->mnparm(2, "detaZ_Mid_x", vstart[2], step[2], 0, 0, ierflg);

	//Now ready for minimization step
	cout<<"Minimization step: "<<endl;
	for( int i=0; i<50; i++)cout<<"="; cout<<endl;
	arglist[0] = 500;// 500->5000
	arglist[1] = 1.;
	//gMinuit->mnexcm("SIMPLEX", arglist,0,ierflg);
	gMinuit->mnexcm("MIGRAD", arglist,2,ierflg);
	//gMinuit->mnexcm("HESSE", arglist,0,ierflg);

	//Print Calculate Result
	double fmin, fedm, errdef, covmat[npar][npar];
	double  detaX_err, detaZ_err, angle_err, detaX, detaZ, angle;
	int nvpar, nparx, icstat;
	gMinuit->mnstat(fmin, fedm, errdef, nvpar, nparx, icstat);
	gMinuit->GetParameter(0, angle, angle_err);
	gMinuit->GetParameter(1, detaX, detaX_err);
	gMinuit->GetParameter(2, detaZ, detaZ_err);
	cout<<endl<<endl<<"detaX_Mid_x= "<<detaX<<" +/- "<<detaX_err<<endl;
	cout<<endl<<endl<<"detaZ_Mid_z= "<<detaZ<<" +/- "<<detaZ_err<<endl;
	cout<<"angle_Mid_x= "<<angle<<" +/- "<<angle_err<<endl<<endl<<endl;

	cout<<"log_l = "<<-0.5*fmin<<endl;
	double val = 0;
	


	*/
	double angle = -0.000321;
	double detaY = 0.298332;
	
	/*
	for(int j=0; j<x2.size(); j++){
		val+=pow((35.3/66.2*x1[j]+30.9/66.2*x3[j])*cos(angle)-(46.1/66.2*y1_sTGC[j]+20.1/66.2*y3[j])*sin(angle)+detaX-x2[j]-77*detaZ/(x1[j]-x3[j]),2);
	}
	cout<<"the manual fcn value = "<<val<<endl;*/

	for(int j=0; j<x2.size(); j++){
		x_residual=(41.7/66.2*x3[j]+24.5/66.2*x1[j])*sin(angle)+(35.3/66.2*y1_sTGC[j]+30.9/66.2*y3[j])*cos(angle)+detaY-y2[j];
		//x_residual=(35.3/66.2*x1[j]+30.9/66.2*x3[j])*cos(angle)-(46.1/66.2*y1_sTGC[j]+20.1/66.2*y3[j])*sin(angle)+detaX-x2[j]-77*detaZ/(x1[j]-x3[j]);
		xAlig->Fill(x_residual);

	}
	//TGraph* gr = new TGraph(n,EventNum,Residual);
	delete gMinuit;


	xAlig->GetXaxis()->SetTitle("mm");
	xAlig->GetYaxis()->SetTitle("event");
	xAlig->GetXaxis()->SetRangeUser(-3,3);
	xAlig->Fit("gaus","","",0,0.7);
	xAlig->Draw();

	return 0;
}
