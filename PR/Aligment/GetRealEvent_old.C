#include "TH1.h"
#include "TF1.h"
void GetRealEvent(){

	TFile *f =new TFile("./XYposition.root");
	TTree *t1 =(TTree*)f->Get("tree");
	gStyle->SetOptFit(1101);
	TFile *RealEvent = new TFile("./RealEvent/RealEventTree.root","RECREATE");
	TTree *RealEventTreeX = new TTree("RealEventTreeX","all point");
	TTree *RealEventTreeY = new TTree("RealEventTreeY","all point");
	TTree *RealEventTreeXY = new TTree("RealEventTreeXY","all point");
	double px1, px1_cp;
	double py1, py1_cp;
	double px2, px2_cp;
	double py2, py2_cp;
	double px3, px3_cp;
	double py3, py3_cp;
	double entry, entry_cp;

	int nentries=0;
	int n=0;
	double x_residual=0.;
	double y_residual=0.;
	//==================================================//
	//=============== Set x and y Angle ================//
	double xAngleDownSet=0;//" 89.4。"
	double yAngle0=0.;//"。"
	double xAngleUpSet=0;
	//=============== Structure is close sandwich =======//
	double high13=77.0;//"mm"
	double high23=41.7;//"mm"
	const int xbinNum=1600;
	const int ybinNum=1700;

	//==================================================//

	double TanAlpha=0.;//"X cosmicray tan angle"
	double TanGamma=0.;//"Y cosmicray tan angle "
	double y2=0.;
	double x2=0.;

	double xAngleDown=0.;	
	double yAngle=0.;
	double xAngleUp=0.;
	double detaX1=0.;
	double detaX2=0.;
	double detaY1=0.;
	double detaY2=0.;
	const double detaXX=1;
	const double detaYY=1;
	int bin=60;
	int binNum=60;

	xAngleDown=xAngleDownSet/180.*TMath::Pi();
	yAngle=yAngle0/180.*TMath::Pi();
	xAngleUp=xAngleUpSet/180.*TMath::Pi();

	t1->SetBranchAddress("px1",&px1);
	t1->SetBranchAddress("py1",&py1);
	t1->SetBranchAddress("px2",&px2);
	t1->SetBranchAddress("py2",&py2);
	t1->SetBranchAddress("px3",&px3);
	t1->SetBranchAddress("py3",&py3);
	t1->SetBranchAddress("entry",&entry);

	//Set the RealEventTree x y position branch.
	RealEventTreeX->Branch("px1_cp",&px1_cp,"px1_cp/D");
	RealEventTreeX->Branch("py1_cp",&py1_cp,"py1_cp/D");
	RealEventTreeX->Branch("px2_cp",&px2_cp,"px2_cp/D");
	RealEventTreeX->Branch("py2_cp",&py2_cp,"py2_cp/D");
	RealEventTreeX->Branch("px3_cp",&px3_cp,"px3_cp/D");
	RealEventTreeX->Branch("py3_cp",&py3_cp,"py3_cp/D");
	RealEventTreeX->Branch("entry_cp",&entry_cp,"entry_cp/D");
	RealEventTreeY->Branch("px1_cp",&px1_cp,"px1_cp/D");
	RealEventTreeY->Branch("py1_cp",&py1_cp,"py1_cp/D");
	RealEventTreeY->Branch("px2_cp",&px2_cp,"px2_cp/D");
	RealEventTreeY->Branch("py2_cp",&py2_cp,"py2_cp/D");
	RealEventTreeY->Branch("px3_cp",&px3_cp,"px3_cp/D");
	RealEventTreeY->Branch("py3_cp",&py3_cp,"py3_cp/D");
	RealEventTreeY->Branch("entry_cp",&entry_cp,"entry_cp/D");
	RealEventTreeXY->Branch("px1_cp",&px1_cp,"px1_cp/D");
	RealEventTreeXY->Branch("py1_cp",&py1_cp,"py1_cp/D");
	RealEventTreeXY->Branch("px2_cp",&px2_cp,"px2_cp/D");
	RealEventTreeXY->Branch("py2_cp",&py2_cp,"py2_cp/D");
	RealEventTreeXY->Branch("px3_cp",&px3_cp,"px3_cp/D");
	RealEventTreeXY->Branch("py3_cp",&py3_cp,"py3_cp/D");
	RealEventTreeXY->Branch("entry_cp",&entry_cp,"entry_cp/D");
	//	cout <<"X angle tan:"<<TMath::Tan(xAngle)<<endl;
	//	cout <<"Y angle tan:"<<TMath::Tan(yAngle)<<endl;

	TCanvas *c1=new TCanvas("c1","PR",1200,500);
	TCanvas *c2=new TCanvas("c2","PR",1000,500);
	TCanvas *c3=new TCanvas("c3","Event",1600,400);
	TH1F *h1 =new TH1F("h1","Mid X Position Resolution",xbinNum,-50,50);
	TH2F *h2 =new TH2F("h2","UP XY Position ",310,0,310,310,0,310);
	TH2F *h4 =new TH2F("h4","DOWN XY Position ",310,0,310,310,0,310);
	TH2F *h3 =new TH2F("h3","Mid XY Position ",310,0,310,310,0,310);
	TH1F *h5 =new TH1F("h5","Mid Y Position Resolution",ybinNum,-50,50);
	string title1,title2;
	title1=Form("Event_x less %f",detaXX);
	title2=Form("Event_y less %f",detaYY);
	TH2F *h6 =new TH2F("h6","", binNum,0,bin,binNum,0,bin);
	TH2F *h7 =new TH2F("h7","", binNum,0,bin,binNum,0,bin);
	TH2F *h8 =new TH2F("h8","Event_x(x&y<1)", binNum,0,bin,binNum,0,bin);
	TH2F *h9 =new TH2F("h9","Event_y(x&y<1)", binNum,0,bin,binNum,0,bin);
	TH1F *h10 =new TH1F("h10","Get 3 sigma",1000,-50,50);
	nentries=(int)t1->GetEntries();
	cout<<"All Event: "<<nentries<<endl;
	for(int i=0;i<nentries;i++){
		t1->GetEntry(i);
		
		// Get all the three point;
		//cout <<"up: "<<px1<<" "<<py1<<" mid: "<<px2<<" "<<py2<<" down: "<<px3<<" "<<py3<<" Event: "<< i<<endl;
		//h2->Fill(px1,py1);
		//h4->Fill(px3,py3);
		//h3->Fill(px2,py2);
		
		detaX1=abs(px1-px2);
		detaX2=abs(px2-px3);
		if(abs(detaX1-detaX2)<detaXX){
			h6->Fill(detaX1,detaX2);
			px1_cp=px1;
			py1_cp=py1;
			px2_cp=px2;
			py2_cp=py2;
			px3_cp=px3;
			py3_cp=py3;
			RealEventTreeX->Fill();
		}

		detaY1=abs(py1-py2);
		detaY2=abs(py2-py3);
		if(abs(detaY1-detaY2)<detaYY){
			h7->Fill(detaY1,detaY2);
			px1_cp=px1;
			py1_cp=py1;
			px2_cp=px2;
			py2_cp=py2;
			px3_cp=px3;
			py3_cp=py3;
			RealEventTreeY->Fill();
		}
		
		if((abs(detaX1-detaX2)<detaXX) && (abs(detaY1-detaY2)<detaYY)){
			h8->Fill(detaX1,detaX2);
			h9->Fill(detaY1,detaY2);
			px1_cp=px1;
			py1_cp=py1;
			px2_cp=px2;
			py2_cp=py2;
			px3_cp=px3;
			py3_cp=py3;
			RealEventTreeXY->Fill();
			h2->Fill(px1,py1);
                h4->Fill(px3,py3);
                h3->Fill(px2,py2);
			 x_residual=px2-(px3+px1)/2.;
                        y_residual=py2-(py3+py1)/2.;
			h5->Fill(y_residual);
                        h1->Fill(x_residual);
		}
		/*
		TanAlpha=abs(high13/(px3-px1));
		TanGamma=abs(high13/(py3-py1));
		if(TanAlpha>TMath::Tan(xAngleDown)&&TanAlpha<TMath::Tan(xAngleUp)&&TanGamma>TMath::Tan(yAngle)){
			h5->Fill(y_residual);
			h1->Fill(x_residual);
		}
		*/
	}
	
	c2->Divide(2,1);
	c2->cd(1);	
	// X signal gaus fit
	h1->GetXaxis()->SetTitle("mm");
	h1->GetYaxis()->SetTitle("event");
	h1->GetXaxis()->SetRangeUser(-3,3);
	h1->Fit("gaus","","",-3,3);//0.09-0.34
	h1->Draw();

	c2->cd(2);
	// Y signal gaus fit
	h5->GetXaxis()->SetTitle("mm");
	h5->GetYaxis()->SetTitle("event");
	h5->GetXaxis()->SetRangeUser(-3,3);
	h5->Fit("gaus","","",-3,3);//0.09-0.34
	h5->Draw();

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

	//Get Real Event 
	c3->Divide(4,1);
	c3->cd(1);
	RealEvent->cd();
	RealEventTreeX->Write();
	RealEventTreeY->Write();
	RealEventTreeXY->Write();
	string Event_x;
	Event_x=Form("Event_x less %f",detaXX);
	h6->SetTitle("Event_x");
	h6->GetXaxis()->SetTitle("detaX12");
	h6->GetYaxis()->SetTitle("detaX23");
	h6->Draw("colz");

	c3->cd(3);
	h8->Draw("colz");
	
	c3->cd(2);
	string Event_y;
        Event_y=Form("Event_y less %f",detaYY);
        h7->SetTitle("Event_y");
	h7->GetXaxis()->SetTitle("detaY12");
	h7->GetYaxis()->SetTitle("detaY23");
	h7->Draw("colz");
	
	c3->cd(4);
	h9->Draw("colz");
	string c3title;
	c3title=Form("./EventPdf/EventDetaXYLess %f.pdf",detaXX);
	c3->SaveAs("c3title");
	}
