#include "TH1.h"
#include "TF1.h"
void prAligment(){

	TFile *f =new TFile("./XYposition.root");
	TTree *t1 =(TTree*)f->Get("tree");
	gStyle->SetOptFit(1101);
	double px1;
	double py1;
	double px2;
	double py2;
	double px3;
	double py3;
	double entry;

	int nentries=0;
	int n=0;
	double x_residual=0.;
	double y_residual=0.;


	//=============== select verticle cosmic ray ================//
	double xAngle0=85;//" 89.4。"
	double yAngle0=85;//"。"
	double xAngle=0.;
	double yAngle=0.;
	xAngle=xAngle0/180.*TMath::Pi();//tansfer the degree to pi.
	yAngle=yAngle0/180.*TMath::Pi();
	cout <<"X angle tan:"<<TMath::Tan(xAngle)<<endl;
	cout <<"Y angle tan:"<<TMath::Tan(yAngle)<<endl;
	double TanAlpha=0.;//"X cosmicray tan angle"
	double TanGamma=0.;//"Y cosmicray tan angle "	
	//=============== Structure is close sandwich =======//
	double high13=77.0;//"mm"

	//======= set the binNum =========//
	const int xbinNum=1050; //VerticleEvent & NoAligment
	const int ybinNum=1100;
	const int AllxbinNum=1050;//AllEvent & NoAligment
	const int AllybinNum=1100;
	const int xAligbinNum=1050;//AllEvent & Aligment 
	const int yAligbinNum=1100;

	//************** START *********************//
	TCanvas *c3=new TCanvas("c3","Data point in three layers",1000,500);
	TH2F *h2 =new TH2F("h2","UP XY Position ",310,0,310,310,0,310);
	TH2F *h4 =new TH2F("h4","DOWN XY Position ",310,0,310,310,0,310);
	TH2F *h3 =new TH2F("h3","Mid XY Position ",310,0,310,310,0,310);
	TCanvas *c2=new TCanvas("c2","Verticle_PR",1000,500);
	TH1F *h1 =new TH1F("h1","VerMid X Position Resolution",xbinNum,-50,50);
	TH1F *h5 =new TH1F("h5","VerMid Y Position Resolution",ybinNum,-50,50);
	TCanvas *c1=new TCanvas("c1","All_PR",1000,500);	
	TH1F *h6 =new TH1F("h6","AllMid x Position Resolution",AllxbinNum,-50,50);
	TH1F *h7 =new TH1F("h7","AllMid y Position Resolution",AllybinNum,-50,50);
	TCanvas *c4=new TCanvas("c4","All_Aligment_PR",1000,500);
	TH1F *xAlig =new TH1F("xAlig","AllMid AligmentX PR",xAligbinNum,-50,50);
	TH1F *yAlig =new TH1F("yAlig","AllMid AligmentY PR",yAligbinNum,-50,50);

	// Get the data tree
	t1->SetBranchAddress("px1",&px1);
	t1->SetBranchAddress("py1",&py1);
	t1->SetBranchAddress("px2",&px2);
	t1->SetBranchAddress("py2",&py2);
	t1->SetBranchAddress("px3",&px3);
	t1->SetBranchAddress("py3",&py3);
	t1->SetBranchAddress("entry",&entry);
	nentries=(int)t1->GetEntries();
	cout <<"The All Event is: "<<nentries<<endl;

	for(int i=0;i<nentries;i++){
		t1->GetEntry(i);//loop the all event x and y position.

		if((px3>px2&&px2<px1)||(px3<px2&&px2>px1)||(py3>py2&&py2<py1)||(py3<py2&&py2>py1)) continue;
		//Remove some event that the measurement point is not a line.


		//*** Get the point of every layer, And fill the histogram.
		h2->Fill(px1,py1);
		h4->Fill(px3,py3);
		h3->Fill(px2,py2);

		//*** NoAligment ALlEvent result in x and y direction.
		x_residual=px2-(px1+px3)/2;
		y_residual=py2-(py1+py3)/2;
		h6->Fill(x_residual);
		h7->Fill(y_residual);

		//*** This VerticleEvent cosmic ray angle is:
		TanAlpha=abs(high13/(px3-px1));
		TanGamma=abs(high13/(py3-py1));
		// X||Y 
		if(TanAlpha>TMath::Tan(xAngle)) h1->Fill(x_residual);
		if(TanGamma>TMath::Tan(yAngle)) h5->Fill(y_residual);	
		/*
		// X && Y
		if(TanAlpha>TMath::Tan(xAngle)&&TanGamma>TMath::Tan(yAngle)){
		h5->Fill(y_residual); //(sqrt(2./3))
		h1->Fill(x_residual);} */

	}
	
	//================ END==================//
	//*************** data point *********************//
	c3->Divide(3,1);
	c3->cd(1);
	h2->SetMarkerStyle(3);
	h2->SetMarkerColor(2);
	h2->GetXaxis()->SetTitle("x");
	h2->GetYaxis()->SetTitle("y");
	h2->Draw();
	h3->SetMarkerStyle(2);
	h3->SetMarkerColor(3);
	h3->GetXaxis()->SetTitle("x");
	h3->GetYaxis()->SetTitle("y");
	c3->cd(2);
	h3->Draw();
	h4->SetMarkerStyle(5);
	h4->SetMarkerColor(4);
	h4->GetXaxis()->SetTitle("x");
	h4->GetYaxis()->SetTitle("y");
	c3->cd(3);
	h4->Draw();

	//************* Verticle Event pr in x and y ***************//
	c2->Divide(2,1);
	c2->cd(1);	
	// X signal gaus fit
	h1->GetXaxis()->SetTitle("mm");
	h1->GetYaxis()->SetTitle("event");
	h1->GetXaxis()->SetRangeUser(-3,3);
	h1->Fit("gaus","","",-0.2,0.22);//0.09-0.34
	h1->Draw();

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
	/*
	// Y double gaus fit		
	Double_t par2[6]; 
	TF1 *g3 = new TF1("g3","gaus",-0.09,0.38); 
	TF1 *g4 = new TF1("g4","gaus",-3,3);
	TF1 *total2 = new TF1("total2","gaus(0)+gaus(3)",-3,3);
	g3->SetLineColor(0);
	g4->SetLineColor(0);
	h5->GetXaxis()->SetTitle("mm");
	h5->GetYaxis()->SetTitle("event");
	h5->GetXaxis()->SetRangeUser(-3,3);
	gStyle->SetOptFit(1);
	h5->Fit(g3,"R");
	h5->Fit(g4,"R+");
	g3->GetParameters(&par[0]);
	g4->GetParameters(&par[3]);
	total2->SetParameters(par2);
	h5->Fit(total2,"R");
	h5->Draw();
	 */

	// Y signal gaus fit
	h5->GetXaxis()->SetTitle("mm");
	h5->GetYaxis()->SetTitle("event");
	h5->GetXaxis()->SetRangeUser(-3,3);
	h5->Fit("gaus","","",-0.2,0.4);//0.09-0.34
	h5->Draw();

	//************** All Event pr ****************//
	c1->Divide(2,1);
	c1->cd(1);
	// X pr:
	h6->GetXaxis()->SetTitle("mm");
	h6->GetYaxis()->SetTitle("event");
	h6->GetXaxis()->SetRangeUser(-3,3);
	h6->Fit("gaus","","",-0.2,0.4);//0.09-0.34
	h6->Draw();
	// Y pr:
	c1->cd(2);
	h7->GetXaxis()->SetTitle("mm");
	h7->GetYaxis()->SetTitle("event");
	h7->GetXaxis()->SetRangeUser(-3,3);
	h7->Fit("gaus","","",-0.2,0.4);//0.09-0.34
	h7->Draw();
	
	//************* ALL Aligment PR ***************//
	double xFitMin=-0.3;
	double xFitMax=0.3;
	double yFitMin=-0.3;
	double yFitMax=0.3;

	c4->Divide(2,1);
        c4->cd(1);
	xAlig->GetXaxis()->SetTitle("mm");
        xAlig->GetYaxis()->SetTitle("event");
        xAlig->GetXaxis()->SetRangeUser(-3,3);
        xAlig->Fit("gaus","","",xFitMin,xFitMax);
        xAlig->Draw();
        // Y pr:
        c1->cd(2);
        yAlig->GetXaxis()->SetTitle("mm");
        yAlig->GetYaxis()->SetTitle("event");
        yAlig->GetXaxis()->SetRangeUser(-3,3);
        yAlig->Fit("gaus","","",yFitMin,yFitMax);
        yAlig->Draw();



}
