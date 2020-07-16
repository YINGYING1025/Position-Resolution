#include "TH1.h"
#include "TF1.h"
void pr(){

	TFile *f =new TFile("../RealEvent/RealEventTree.root");
	TTree *t1 =(TTree*)f->Get("RealEventTreeXY");
	gStyle->SetOptFit(1101);	
	double px1_cp;
	double py1_cp;
	double px2_cp;
	double py2_cp;
	double px3_cp;
	double py3_cp;
	double entry_cp;

	int nentries=0;
	int n=0;
	double x_residual=0.;
	double y_residual=0.;
	//==================================================//
	//=============== Set x and y Angle ================//
	double xAngleDownSet=89.9;//" 89.4。"
	double yAngle0=0.;//"。"
	double xAngleUpSet=0;
	//=============== Structure is close sandwich =======//
	double high13=77.0;//"mm"
	double high23=41.7;//"mm"
	string xfitresult;
	string yfitresult;
	const int xbinNum=1600;
	const int ybinNum=1700;

	//==================================================//

	double TanAlpha=0.;//"X cosmicray tan angle"
	double TanGamma=0.;//"Y cosmicray tan angle "
	double y2=0.;
	double x2=0.;

	double y_min=196.;
	double y_max=197.;//mm
	double x_min=248.;
	double x_max=256.;//mm

	double xAngleDown=0;	
	double yAngle=0.;
	double xAngleUp=0;
	xAngleDown=xAngleDownSet/180.*TMath::Pi();
	yAngle=yAngle0/180.*TMath::Pi();
	xAngleUp=xAngleUpSet/180.*TMath::Pi();

	 // Get the data tree
        t1->SetBranchAddress("px1_cp",&px1_cp);
        t1->SetBranchAddress("py1_cp",&py1_cp);
        t1->SetBranchAddress("px2_cp",&px2_cp);
        t1->SetBranchAddress("py2_cp",&py2_cp);
        t1->SetBranchAddress("px3_cp",&px3_cp);
        t1->SetBranchAddress("py3_cp",&py3_cp);
        t1->SetBranchAddress("entry_cp",&entry_cp);

	//	cout <<"X angle tan:"<<TMath::Tan(xAngle)<<endl;
	//	cout <<"Y angle tan:"<<TMath::Tan(yAngle)<<endl;

	TCanvas *c1=new TCanvas("c1","PR",1200,500);
	TCanvas *c2=new TCanvas("c2","PR",1000,500);
	TH1F *h1 =new TH1F("h1","Mid X Position Resolution",xbinNum,-50,50);
	TH2F *h2 =new TH2F("h2","UP XY Position ",310,0,310,310,0,310);
	TH2F *h4 =new TH2F("h4","DOWN XY Position ",310,0,310,310,0,310);
	TH2F *h3 =new TH2F("h3","Mid XY Position ",310,0,310,310,0,310);
	TH1F *h5 =new TH1F("h5","Mid Y Position Resolution",ybinNum,-50,50);
	nentries=(int)t1->GetEntries();
	cout <<nentries<<endl;
	for(int i=0;i<nentries;i++){
		t1->GetEntry(i);


		//Get the point of every layer.
			h2->Fill(px1_cp,py1_cp);
			h4->Fill(px3_cp,py3_cp);
			h3->Fill(px2_cp,py2_cp);

		//cout<<"Event: "<<i+1<<endl;	
		//y2=py3+(41.7/high13)*(py1-py3);
		//x2=px3+(41.7/high13)*(px1-px3);
		//y2=py2-(3.2/77)*(py1-py3);

		// The x_residual and angle.		
		//x_residual=px2-x2;
		//y_residual=py2-y2;


		x_residual=px2_cp-(px1_cp+px3_cp)/2;
		y_residual=py2_cp-(py1_cp+py3_cp)/2;
		TanAlpha=abs(high13/(px3_cp-px1_cp));
		TanGamma=abs(high13/(py3_cp-py1_cp));
		//if(TanAlpha>TMath::Tan(xAngleDown)&&TanAlpha<TMath::Tan(xAngleUp)&&TanGamma>TMath::Tan(yAngle)){
		if(TanAlpha>TMath::Tan(xAngleDown)&&TanGamma>TMath::Tan(yAngle)){	
		cout<<x_residual<<endl;
			h5->Fill(y_residual);//*(sqrt(2./3))
			n++;
			h1->Fill(x_residual);
		}

	}
	c2->Divide(2,1);
	cout <<n<<endl;

	c2->cd(1);	

	// X signal gaus fit
	h1->GetXaxis()->SetTitle("mm");
	h1->GetYaxis()->SetTitle("event");
	h1->GetXaxis()->SetRangeUser(-3,3);
	h1->Fit("gaus","","",-0.4,0.4);//0.09-0.34
	h1->Draw();
	xfitresult=Form("./result/%d.C",xbinNum);
	h1->SaveAs("fitresult");


	/*
	// X doublr gaus fit
	Double_t par[6]; 
	TF1 *g1 = new TF1("g1","gaus",-0.25,0.4); 
	TF1 *g2 = new TF1("g2","gaus",-3,3);
	TF1 *total = new TF1("total","gaus(0)+gaus(3)",-3,3);
	g1->SetLineColor(0);

	g2->SetLineColor(0);
	h1->GetXaxis()->SetTitle("mm");
	h1->GetYaxis()->SetTitle("event");
	h1->GetXaxis()->SetRangeUser(-3,3);
	//h1->Fit("gaus","","",-0.09,0.38);//0.09,0.38
	gStyle->SetOptFit(1);
	h1->Fit(g1,"R");
	h1->Fit(g2,"R+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	h1->Fit(total,"R");
	h1->Draw();
	 */


	c2->cd(2);
	// Y double gaus fit
	/*		
			Double_t par[6]; 
			TF1 *g1 = new TF1("g1","gaus",-0.09,0.38); 
			TF1 *g2 = new TF1("g2","gaus",-3,3);
			TF1 *total = new TF1("total","gaus(0)+gaus(3)",-3,3);
			g1->SetLineColor(0);

			g2->SetLineColor(0);
			h5->GetXaxis()->SetTitle("mm");
			h5->GetYaxis()->SetTitle("event");
			h5->GetXaxis()->SetRangeUser(-3,3);
	//h5->Fit("gaus","","",-0.09,0.38);//0.09,0.38
	gStyle->SetOptFit(1);
	h5->Fit(g1,"R");
	h5->Fit(g2,"R+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	h5->Fit(total,"R");
	h5->Draw();
	yfitresult=Form("./result/%d.C",ybinNum);
	h5->SaveAs("fitresult");
	 */


	// Y signal gaus fit
	h5->GetXaxis()->SetTitle("mm");
	h5->GetYaxis()->SetTitle("event");
	h5->GetXaxis()->SetRangeUser(-3,3);
	h5->Fit("gaus","","",-0.4,0.4);//0.09-0.34
	h5->Draw();
	yfitresult=Form("./result/%d.C",ybinNum);
	h5->SaveAs("fitresult");




	// data point
	c1->Divide(3,1);
	c1->cd(1);
	h2->SetMarkerStyle(3);
	h2->SetMarkerColor(2);
	h2->GetXaxis()->SetTitle("x");
	h2->GetYaxis()->SetTitle("y");
	h2->Draw();
	h3->SetMarkerStyle(2);
	h3->SetMarkerColor(3);
	h3->GetXaxis()->SetTitle("x");
	h3->GetYaxis()->SetTitle("y");
	c1->cd(2);
	h3->Draw();
	h4->SetMarkerStyle(5);
	h4->SetMarkerColor(4);
	h4->GetXaxis()->SetTitle("x");
	h4->GetYaxis()->SetTitle("y");
	c1->cd(3);
	h4->Draw();
	}
