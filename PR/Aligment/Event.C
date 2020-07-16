#include "TH1.h"
#include "TF1.h"

Double_t fitfcn(Double_t *x,Double_t *par){
	Double_t y=x[0];
	Double_t f=par[0] + y*par[1] + pow(y,2)*par[2] + pow(y,3)*par[3] + pow(y,4)*par[4];
	return f;
}

void Event(){
	// To get the realy event in the cosmic ray test.
	// slice the x axis select a range bin and see the y axis projection,
	// the result pic at ./EventQA/

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

	vector<double>x1;
	vector<double>x2;
	vector<double>x3;
	vector<double>y1;
	vector<double>y2;
	vector<double>y3;
	vector<double>MeanX;
	vector<double>MeanXErr;
	vector<double>SigmaX;
	vector<double>SigmaXErr;
	vector<double>MeanY;
	vector<double>MeanYErr;
	vector<double>SigmaY;
	vector<double>SigmaYErr;
	int nxPdfNum=0;
	int nyPdfNum=0;
	int nentries=0;
	int n=0;
	double detaX1=0.;
	double detaX2=0.;
	double detaY1=0.;
	double detaY2=0.;
	int bin=23;
	int binNum=460;

	t1->SetBranchAddress("px1",&px1);
	t1->SetBranchAddress("py1",&py1);
	t1->SetBranchAddress("px2",&px2);
	t1->SetBranchAddress("py2",&py2);
	t1->SetBranchAddress("px3",&px3);
	t1->SetBranchAddress("py3",&py3);
	t1->SetBranchAddress("entry",&entry);

	TCanvas *c3=new TCanvas("c3","Event",1000,500);
	TH2F *h6 =new TH2F("h6","Event_x ",binNum,-bin,bin,binNum,-bin,bin);
	TH2F *h7 =new TH2F("h7","Event_y ",binNum,-bin,bin,binNum,-bin,bin);
	TH1F *h10 =new TH1F("h10","For check the x direction 1-1.5 number event",binNum,0,bin);//detaX
	TH1F *h11 =new TH1F("h11","All the deltaX12 distribution",binNum,0,bin);//detaY
	nentries=(int)t1->GetEntries();
	cout <<nentries<<endl;
	//Get data frome tree.
	for(int i=0;i<nentries;i++){
		t1->GetEntry(i);
		x1.push_back(px1);
		y1.push_back(py1);
		x2.push_back(px2);
		y2.push_back(py2);
		x3.push_back(px3);
		y3.push_back(py3);
	}

	double range=-13;
	double MeanCenter=range+0.25;
	double tems=52;
	const int nx=52;//==tems;  Number of the pdf in x axis.
	const int ny=34;//-10.5-10.5; Number of the pdf in y axis.
	double times=2; 
	//If cange Y range, please also change line=215.
	double ybinlow=-10.1;
	double ybinbig=10.1;
	//X range is -15 to 15; everytime add o.5 and need 60 tems.
	//Y range is -10 to 10;
	cout<<"Check All EVENT= "<<x3.size()<<endl;

	TCanvas *c4=new TCanvas("c4","Event",400,400);
	TH1F *h8 =new TH1F("h8","",binNum,-bin,bin);//detaX
	TH1F *h9 =new TH1F("h9","",binNum,-bin,bin);//detaY

	//***************************************************************//
	//********* Get the slice event distribution *******************//
	//**************************************************************//
	for(int j=0;j<tems;j++){
		//All Event Loop:
		for(int k=0;k<x1.size();k++){
			detaX1=x1[k]-x2[k];
			detaX2=x2[k]-x3[k];
			if(detaX1>range && detaX1<(range+0.5)){
				h8->Fill(detaX2);}

			if(range<ybinbig&&range>ybinlow){
				detaY1=y1[k]-y2[k];
				detaY2=y2[k]-y3[k];
				if(detaY1>range && detaY1<(range+0.5)){
					h9->Fill(detaY2);}
			}
		}
		c4->cd();
		h8->GetXaxis()->SetTitle("deltaX23/mm");
		h8->GetYaxis()->SetTitle("Event");
		h8->Fit("gaus");
		h8->SetTitle(TString::Format("Gause fit for deltaX23 in deltaX12( %f - %f )",range,range+0.5));
		h8->Draw();
		nxPdfNum++;
		//Get the fit result sigma,mean amd their error. 
		TF1 *f1=(TF1 *)h8->GetFunction("gaus");
		MeanX.push_back(f1->GetParameter(1));
		MeanXErr.push_back(f1->GetParError(1));
		SigmaX.push_back(f1->GetParameter(2));
		SigmaXErr.push_back(f1->GetParError(2));
		c4->SaveAs(TString::Format("./EventQA/xFitRange %f-%f.pdf",range,range+0.5));
		h8->Reset();
		c4->Update();
		if(range<ybinbig&&range>ybinlow){	
			c4->cd();
			h9->GetXaxis()->SetTitle("deltaY23/mm");
			h9->GetYaxis()->SetTitle("Event");
			h9->Fit("gaus");
			h9->SetTitle(TString::Format("Gause fit for deltaY23 in deltaX12( %f - %f )",range,range+0.5));
			h9->Draw();
			nyPdfNum++;
			//Get Y direction fit result sigma,mean and their error.
			TF1 *gfit=(TF1 *)h9->GetFunction("gaus");
			MeanY.push_back(gfit->GetParameter(1));
			MeanYErr.push_back(gfit->GetParError(1));
			SigmaY.push_back(gfit->GetParameter(2));
			SigmaYErr.push_back(gfit->GetParError(2));
			c4->SaveAs(TString::Format("./EventQA/yFitRange %f-%f.pdf",range,range+0.5));
			h9->Reset();
			c4->Update();}
		range=range+0.5;
	}

	//Use the ProjiectionX/Y() function.
	/*
	   double rangemin=-20;
	   TCanvas *c4=new TCanvas("c4","Event",400,400);

	   for(int j=0;j<36;j++){
	   range=range+0.5;
	   rangemin=range-0.5;
	//x Three layers
	TH1D *detaX2 = h6->ProjectionX("detaX2", rangemin, range);
	c4->cd();
	detaX2->GetXaxis()->SetTitle("detaX2");
	detaX2->GetYaxis()->SetTitle("Event");
	detaX2->Fit("gaus");
	detaX2->SetTitle(TString::Format("Gause fit for detaX2 in detaX1( %f - %f )",range-0.5,range));
	detaX2->Draw();
	c4->SaveAs(TString::Format("./EventQA/projection/xFitRange %f-%f.pdf",range-0.5,range));
	detaX2->Reset();
	c4->Update();
	//y Three layers
	if(range<10.1){
	TH1D *detaY2 = h7->ProjectionX("detaY2", rangemin, range);
	c4->cd();
	detaY2->GetXaxis()->SetTitle("detaY2");
	detaY2->GetYaxis()->SetTitle("Event");
	detaY2->Fit("gaus");
	detaY2->SetTitle(TString::Format("Gause fit for detaY2 in detaX1( %f - %f )",range-0.5,range));
	detaY2->Draw();
	c4->SaveAs(TString::Format("./EventQA/projection/yFitRange %f-%f.pdf",range-0.5,range));
	detaY2->Reset();
	c4->Update();
	}
	}
	 */


	for( int i=0; i<50; i++)cout<<"="; cout<<endl;
	cout<<"x direction PDF number: "<<nxPdfNum<<"   y direction PDF number:" <<nyPdfNum<<endl;
	for( int i=0; i<50; i++)cout<<"="; cout<<endl;

	//*************************************************************************************************//
	//****************** Draw the Fit result mean, sigma, 3sigma from above histogram ******************// 
	//**************************************************************************************************//
	//const int nx=60;//Here is the number of nxPdfNum; 
	//const int ny=41;//Here is the number of nyPdfNum
	//double times=2; // Get the Event include  N_Sigma times.
	
	//Get the number from vector MeanX,MeanXErr,SigmaX,SigmaXErr,MeanY,MeanYErr,SigmaY,SigmaYErr;
	double meanx[nx]={0.};
	double meanxerr[nx]={0.};
	double sigmax[nx]={0.};
	double sigmaxerr[nx]={0.};
	double meany[ny]={0.};
	double meanyerr[ny]={0.};
	double sigmay[ny]={0.};
	double sigmayerr[ny]={0.};
	double detax12[nx]={0.};
	double detax12err[nx]={0.};
	double detay12[ny]={0.};
	double detay12err[ny]={0.};
	double p3sigmax[nx]={0.};
	double p3sigmaxerr[nx]={0.};
	double n3sigmax[nx]={0.};
	double n3sigmaxerr[nx]={0.};
	double p3sigmay[ny]={0.};
	double p3sigmayerr[ny]={0.};
	double n3sigmay[ny]={0.};
	double n3sigmayerr[ny]={0.};
	for(int i=0; i<nx; i++){
		detax12[i]=MeanCenter+0.5*i;
		if(i<ny) detay12[i]=-10.25+0.5*i;

		//X direction;
		meanx[i]=MeanX[i];
		meanxerr[i]=MeanXErr[i];
		sigmax[i]=SigmaX[i];
		sigmaxerr[i]=SigmaXErr[i];
		p3sigmax[i]=MeanX[i]+times*SigmaX[i];
		p3sigmaxerr[i]=sqrt(pow(MeanXErr[i],2)+pow(times,2)*pow(SigmaXErr[i],2));
		n3sigmax[i]=MeanX[i]-times*SigmaX[i];
		n3sigmaxerr[i]=p3sigmaxerr[i];
		//Y direction
		if(i<ny)
		{
			meany[i]=MeanY[i];
			meanyerr[i]=MeanYErr[i];
			sigmay[i]=SigmaY[i];
			sigmayerr[i]=SigmaYErr[i];
			p3sigmay[i]=MeanY[i]+times*SigmaY[i];
			p3sigmayerr[i]=sqrt(pow(MeanYErr[i],2)+pow(times,2)*pow(SigmaYErr[i],2));
			n3sigmay[i]=MeanY[i]-times*SigmaY[i];
			n3sigmayerr[i]=p3sigmayerr[i];
		}
	}
	TCanvas *c1=new TCanvas("c1","",1600,800);
	TF1* f1 = new TF1("f1","fitfcn",-23,23,5);
	f1->SetParameters(5,0);


	auto grXMean = new TGraphErrors(nx,detax12,meanx,detax12err,meanxerr);
	auto grXSigma = new TGraphErrors(nx,detax12,sigmax,detax12err,sigmaxerr);
	auto grXp3Sigma = new TGraphErrors(nx,detax12,p3sigmax,detax12err,p3sigmaxerr);
	auto grXn3Sigma = new TGraphErrors(nx,detax12,n3sigmax,detax12err,n3sigmaxerr);

	auto grYMean = new TGraphErrors(ny,detay12,meany,detay12err,meanyerr);
	auto grYSigma = new TGraphErrors(ny,detay12,sigmay,detay12err,sigmayerr);
	auto grYp3Sigma = new TGraphErrors(ny,detay12,p3sigmay,detay12err,p3sigmayerr);
	auto grYn3Sigma = new TGraphErrors(ny,detay12,n3sigmay,detay12err,n3sigmayerr);

	grXMean->SetTitle(TString::Format("deltaX23 mean in %f_%f",-range,range));
	grXSigma->SetTitle(TString::Format("deltaX23 sigma in %f_%f",-range,range));
	grXp3Sigma->SetTitle(TString::Format("Fit deltaX23 + %f sigma",times));
	grXn3Sigma->SetTitle(TString::Format("Fit deltaX23 - %f sigma",times));
	grYMean->SetTitle(TString::Format("deltaY23 mean in %d_%d",-10,7));
	grYSigma->SetTitle(TString::Format("deltaY23 sigma in %d_%d",-10,7));
	grYp3Sigma->SetTitle(TString::Format("Fit deltaY23 +%f sigma",times));
	grYn3Sigma->SetTitle(TString::Format("Fit deltaY23 -%f sigma",times));
	grXMean->SetMarkerStyle(4);
	grXSigma->SetMarkerStyle(4);
	grXp3Sigma->SetMarkerStyle(4);	
	grXn3Sigma->SetMarkerStyle(4);
	grYMean->SetMarkerStyle(4);
	grYSigma->SetMarkerStyle(4);
	grYp3Sigma->SetMarkerStyle(4);
	grYn3Sigma->SetMarkerStyle(4);
	grXMean->SetMarkerSize(0.5);
	grXSigma->SetMarkerSize(0.5);
	grXp3Sigma->SetMarkerSize(0.5);
	grXn3Sigma->SetMarkerSize(0.5);
	grYMean->SetMarkerSize(0.5);
	grYSigma->SetMarkerSize(0.5);
	grYp3Sigma->SetMarkerSize(0.5);
	grYn3Sigma->SetMarkerSize(0.5);
	grXMean->SetMarkerColor(4);
	grXSigma->SetMarkerColor(2);
	grXp3Sigma->SetMarkerColor(2);
	grXn3Sigma->SetMarkerColor(2);
	grYMean->SetMarkerColor(4);
	grYSigma->SetMarkerColor(2);
	grYp3Sigma->SetMarkerColor(2);
	grYn3Sigma->SetMarkerColor(2);
	grXMean->GetYaxis()->SetRangeUser(-28,28);
	grXSigma->GetYaxis()->SetRangeUser(0.5,2);
	grYMean->GetYaxis()->SetRangeUser(-28,28);
	grYSigma->GetYaxis()->SetRangeUser(0.5,2);
	grXMean->GetXaxis()->SetTitle("deltaX12/mm");
	grXMean->GetYaxis()->SetTitle("deltaX23 mean");
	grXSigma->GetXaxis()->SetTitle("deltaX12/mm");
	grXSigma->GetYaxis()->SetTitle("deltaX23 sigma");
	grXp3Sigma->GetXaxis()->SetTitle("deltaX12/mm");
	grXp3Sigma->GetYaxis()->SetTitle("deltaX23 +3sigma");
	grXn3Sigma->GetXaxis()->SetTitle("deltaX12/mm");
	grXn3Sigma->GetYaxis()->SetTitle("deltaX23 -3sigma");
	grYMean->GetXaxis()->SetTitle("deltaY12/mm");
	grYMean->GetYaxis()->SetTitle("deltaY23 mean");
	grYSigma->GetXaxis()->SetTitle("deltaY12/mm");
	grYSigma->GetYaxis()->SetTitle("deltaY23 sigma");
	grYp3Sigma->GetXaxis()->SetTitle("deltaY12/mm");
	grYp3Sigma->GetYaxis()->SetTitle("deltaY23 +3sigma");
	grYn3Sigma->GetXaxis()->SetTitle("deltaY12/mm");
	grYn3Sigma->GetYaxis()->SetTitle("deltaY23 -3sigma");
	c1->Divide(4,2);

	c1->cd(1);
	// Fit with Negative binomial distribution.
	grXMean->Fit(f1);
	TF1 *fitxmean = grXMean->GetFunction("f1");
	double a0x=fitxmean->GetParameter(0);
	double a1x=fitxmean->GetParameter(1);
	double a2x=fitxmean->GetParameter(2);
	double a3x=fitxmean->GetParameter(3);
	double a4x=fitxmean->GetParameter(4);
	grXMean->Draw("AP");

	c1->cd(2);
	grXSigma->Draw("AP");

	c1->cd(3);
	grXp3Sigma->Fit(f1);
	TF1 *fitp3sigma = grXp3Sigma->GetFunction("f1");
	double b0x=fitp3sigma->GetParameter(0);
	double b1x=fitp3sigma->GetParameter(1);
	double b2x=fitp3sigma->GetParameter(2);
	double b3x=fitp3sigma->GetParameter(3);
	double b4x=fitp3sigma->GetParameter(4);
	grXp3Sigma->Draw("AP");

	c1->cd(4);
	grXn3Sigma->Fit(f1);
	TF1 *fitn3sigma = grXn3Sigma->GetFunction("f1");
	double c0x=fitn3sigma->GetParameter(0);
	double c1x=fitn3sigma->GetParameter(1);
	double c2x=fitn3sigma->GetParameter(2);
	double c3x=fitn3sigma->GetParameter(3);
	double c4x=fitn3sigma->GetParameter(4);
	grXn3Sigma->Draw("AP");

	c1->cd(5);
	grYMean->Fit(f1);
	TF1 *fitymean = grYMean->GetFunction("f1");
	double a0y=fitymean->GetParameter(0);
	double a1y=fitymean->GetParameter(1);
	double a2y=fitymean->GetParameter(2);
	double a3y=fitymean->GetParameter(3);
	double a4y=fitymean->GetParameter(4);
	grYMean->Draw("AP");

	c1->cd(6);
	grYSigma->Draw("AP");

	c1->cd(7);
	grYp3Sigma->Fit(f1);
	TF1 *fityp3sig = grYp3Sigma->GetFunction("f1");
	double b0y=fityp3sig->GetParameter(0);
	double b1y=fityp3sig->GetParameter(1);
	double b2y=fityp3sig->GetParameter(2);
	double b3y=fityp3sig->GetParameter(3);
	double b4y=fityp3sig->GetParameter(4);
	grYp3Sigma->Draw("AP");

	c1->cd(8);
	grYn3Sigma->Fit(f1);
	TF1 *fityn3sig = grYn3Sigma->GetFunction("f1");
	double c0y=fityn3sig->GetParameter(0);
	double c1y=fityn3sig->GetParameter(1);
	double c2y=fityn3sig->GetParameter(2);
	double c3y=fityn3sig->GetParameter(3);
	double c4y=fityn3sig->GetParameter(4);
	grYn3Sigma->Draw("AP");
	c1->Update();
	
	auto stats1 = (TPaveStats*)grXMean->GetListOfFunctions()->FindObject("stats");
	auto stats2 = (TPaveStats*)grXp3Sigma->GetListOfFunctions()->FindObject("stats");
	auto stats3 = (TPaveStats*)grYMean->GetListOfFunctions()->FindObject("stats");
	auto stats4 = (TPaveStats*)grYp3Sigma->GetListOfFunctions()->FindObject("stats");
	auto stats5 = (TPaveStats*)grXn3Sigma->GetListOfFunctions()->FindObject("stats");
	auto stats6 = (TPaveStats*)grYn3Sigma->GetListOfFunctions()->FindObject("stats");
	stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.45); stats1->SetY1NDC(0.6);
	stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.45); stats2->SetY1NDC(0.6);
	stats3->SetX1NDC(0.12); stats3->SetX2NDC(0.45); stats3->SetY1NDC(0.6);
	stats4->SetX1NDC(0.12); stats4->SetX2NDC(0.45); stats4->SetY1NDC(0.6);
	stats5->SetX1NDC(0.12); stats5->SetX2NDC(0.45); stats5->SetY1NDC(0.6); 
	stats6->SetX1NDC(0.12); stats6->SetX2NDC(0.45); stats6->SetY1NDC(0.6); 
	c1->Modified();
	c1->SaveAs(TString::Format("./EventQA/FitParameters.pdf"));
	c1->Update();
	
	//**************************************************************//
	//****************** Get the 2D Event Pic **********************//
	//***************************************************************//
	
	for(int i=0;i<50;i++)cout<<"*"; cout<<endl;
   	cout<<"Get the N_Sigma Event"<<endl;
        for(int i=0;i<50;i++)cout<<"*"; cout<<endl;
	cout<<"Fit XMean Parameters: a0x= "<<a0x<<"  a1x=  "<<a1x<<"  a2x= "<<a2x<<"  a3x= "<<a3x<<"  a4x= "<<a4x<<endl;
	cout<<"Fit Xp3Sigma Parameters: b0x= "<<b0x<<"  b1x=  "<<b1x<<"  b2x= "<<b2x<<"  b3x= "<<b3x<<"  b4x= "<<b4x<<endl;
	cout<<"Fit Xn3Sigma Parameters: c0x= "<<c0x<<"  c1x=  "<<c1x<<"  c2x= "<<c2x<<"  c3x= "<<c3x<<"  c4x= "<<c4x<<endl;
	cout<<"Fit YMean Parameters: a0y= "<<a0y<<"  a1y=  "<<a1y<<"  a2y= "<<a2y<<"  a3y= "<<a3y<<"  a4y= "<<a4y<<endl;
	cout<<"Fit Yp3Sigma Parameters: b0y= "<<b0y<<"  b1y=  "<<b1y<<"  b2y= "<<b2y<<"  b3y= "<<b3y<<"  b4y= "<<b4y<<endl;
	cout<<"Fit Yn3Sigma Parameters: c0y= "<<c0y<<"  c1y=  "<<c1y<<"  c2y= "<<c2y<<"  c3y= "<<c3y<<"  c4y= "<<c4y<<endl;

	TFile *RealEvent = new TFile("./RealEvent/RealEventTree.root","RECREATE");
        TTree *RealEventTreeX = new TTree("RealEventTreeX","all point");// X direction meet the N_Sigma requirment.
        TTree *RealEventTreeY = new TTree("RealEventTreeY","all point");// Y direction meet the N_Sigma requirment.
        TTree *RealEventTreeXY = new TTree("RealEventTreeXY","all point");// X&&Y direction meet the N_Sigma requirment.
	double px1_cp;
        double py1_cp;
        double px2_cp;
        double py2_cp;
        double px3_cp;
        double py3_cp;
        double entry_cp;
	 //Set the RealEventTree.root x, y, x&y branch.
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

	double Xvalue=0.;
	double Yvalue=0.;
	double xfcnUp=0.;
	double xfcnDown=0.;
	double yfcnUp=0.;
        double yfcnDown=0.;

	for(int i=0;i<x1.size();i++){
                detaX1=x1[i]-x2[i];
                detaX2=x2[i]-x3[i];
                h6->Fill(detaX1,detaX2);

                //check
                if(detaX1<1.5 && detaX1>1.){
                        n++;
                        h10->Fill(detaX2);}// The deltaX2 distri.in the range 1-1.5.
                h11->Fill(detaX2);// All of the deltaX2 distribution.
                detaY1=y1[i]-y2[i];
                detaY2=y2[i]-y3[i];
                h7->Fill(detaY1,detaY2);
		
		//calculate get event;
		Xvalue=detaX1;
		Yvalue=detaY1;
		xfcnUp=b0x + Xvalue*b1x + pow(Xvalue,2)*b2x + pow(Xvalue,3)*b3x + pow(Xvalue,4)*b4x;
		xfcnDown=c0x + Xvalue*c1x + pow(Xvalue,2)*c2x + pow(Xvalue,3)*c3x + pow(Xvalue,4)*c4x;
		yfcnUp=b0y + Yvalue*b1y + pow(Yvalue,2)*b2y + pow(Yvalue,3)*b3y + pow(Yvalue,4)*b4y;
		yfcnDown=c0y + Yvalue*c1y + pow(Yvalue,2)*c2y + pow(Yvalue,3)*c3y + pow(Yvalue,4)*c4y;
		if(detaX2<xfcnUp&&detaX2>xfcnDown){
			px1_cp=x1[i];
                        py1_cp=y1[i];
                        px2_cp=x2[i];
                        py2_cp=y2[i];
                        px3_cp=x3[i];
                        py3_cp=y3[i];
                        RealEventTreeX->Fill();
		
		}
		if(detaY2<yfcnUp&&detaY2>yfcnDown){
			px1_cp=x1[i];
                        py1_cp=y1[i];
                        px2_cp=x2[i];
                        py2_cp=y2[i];
                        px3_cp=x3[i];
                        py3_cp=y3[i];
			RealEventTreeY->Fill();
		}
		if(detaX2<xfcnUp&&detaX2>xfcnDown&&detaY2<yfcnUp&&detaY2>yfcnDown){
			px1_cp=x1[i];
                        py1_cp=y1[i];
                        px2_cp=x2[i];
                        py2_cp=y2[i];
                        px3_cp=x3[i];
                        py3_cp=y3[i];
			RealEventTreeXY->Fill();
		}

        }
	RealEvent->cd();
        RealEventTreeX->Write();
        RealEventTreeY->Write();
        RealEventTreeXY->Write();
	
	
	//Draw the +-N_Sigma curve;
        TF1 *fxm=new TF1("fpol1","pol4(0)",-23,23);
        fxm->SetParameters(a0x,a1x,a2x,a3x,a4x);//XMean
        TF1 *fxps=new TF1("fxps","pol4(0)",-23,23);
        fxps->SetParameters(b0x,b1x,b2x,b3x,b4x);//X3Sigma
        TF1 *fxns=new TF1("fxns","pol4(0)",-23,23);
        fxns->SetParameters(c0x,c1x,c2x,c3x,c4x);//-X3Sigma

        TF1 *fym=new TF1("fym","pol4(0)",-23,23);
        fym->SetParameters(a0y,a1y,a2y,a3y,a4y);//YMean
        TF1 *fyps=new TF1("fyps","pol4(0)",-23,23);
        fyps->SetParameters(b0y,b1y,b2y,b3y,b4y);//Y3Sigma
        TF1 *fyns=new TF1("fyns","pol4(0)",-23,23);
        fyns->SetParameters(c0y,c1y,c2y,c3y,c4y);//-Y3Sigma
	
	//The slice 2D pic;
	c3->Divide(2,1);
	c3->cd(1);
	fxm->SetLineColor(4);
	fxm->SetLineWidth(2);
        fxps->SetLineColor(2);
	fxps->SetLineWidth(2);
        fxns->SetLineColor(2);
	fxns->SetLineWidth(2);
	h6->GetXaxis()->SetTitle("deltaX12/mm");
	h6->GetYaxis()->SetTitle("deltaX23/mm");
	gPad->SetLogz();
	gPad->SetGrid();
	h6->GetXaxis()->SetRangeUser(-16,16);
	h6->Draw("colz");
	fxm->Draw("same");
        fxps->Draw("same");
        fxns->Draw("same");

	c3->cd(2);
	fym->SetLineColor(4);
	fym->SetLineWidth(2);
        fyps->SetLineColor(2);
	fyps->SetLineWidth(2);
        fyns->SetLineColor(2);
	fyns->SetLineWidth(2);
	h7->GetXaxis()->SetTitle("deltaY12/mm");
	h7->GetYaxis()->SetTitle("deltaY23/mm");
	h7->GetXaxis()->SetRangeUser(-16,16);
	h7->Draw("colz");
	fym->Draw("same");
        fyps->Draw("same");
        fyns->Draw("same");
	gPad->SetGrid();
	gPad->SetLogz();
	c3->Update();
	
	auto stats7 = (TPaveStats*)h6->GetListOfFunctions()->FindObject("stats");
        auto stats8 = (TPaveStats*)h7->GetListOfFunctions()->FindObject("stats");
	stats7->SetX1NDC(0.12); stats7->SetX2NDC(0.45); stats7->SetY1NDC(0.6);
        stats8->SetX1NDC(0.12); stats8->SetX2NDC(0.45); stats8->SetY1NDC(0.6);
        c3->Modified();
	c1->Update();
	c3->SaveAs(TString::Format("./EventQA/EventQA.pdf"));

	TCanvas *c5=new TCanvas("c5","Event",800,400);
	c5->Divide(2,1);
	c5->cd(1);
	h10->Draw();
	c5->cd(2);
	h11->Draw();
}

