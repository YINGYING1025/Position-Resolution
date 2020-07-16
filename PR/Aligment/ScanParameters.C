int ScanParameters(){

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	//++++++++++++++++++++++++ Read the RealEventTree.root +++++++++++++++++++++++++//
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	double px1_cp;
	double py1_cp;
	double px2_cp;
	double py2_cp;
	double px3_cp;
	double py3_cp;
	double entry_cp;

	double x_residual=0.;
	double y_residual=0.;
	const int xAligbinNum=2000;//AllEvent & Aligment 

	TCanvas *c4=new TCanvas("c4","All_Aligment_PR",500,500);
	TH1F *xAlig =new TH1F("xAlig","AllMid AligmentX PR",xAligbinNum,-10,10);
	TH1F *xAlig_cp =new TH1F("xAlig_cp","AllMid AligmentX PR",xAligbinNum,-10,10);
	vector<double>x1;
	vector<double>y1_sTGC;
	vector<double>x2;
	vector<double>y2;
	vector<double>x3;
	vector<double>y3;

	vector<double>X;
	vector<double>Angle;
	vector<double>pr;

	TFile *f =new TFile("./RealEvent/RealEventTree.root");
	TTree *t1 =(TTree*)f->Get("RealEventTreeX");
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
	for(int i=0;i<nentries;i++){
		t1->GetEntry(i);
		x1.push_back(px1_cp);
		y1_sTGC.push_back(py1_cp);
		x2.push_back(px2_cp);
		y2.push_back(py2_cp);
		x3.push_back(px3_cp);
		y3.push_back(py3_cp);
	}

	double x=0.298332;
	double angleSet=-0.2;//angle=[-5,5];
	double angle=angleSet/180.*TMath::Pi();
	//double xStep=0.1;
	double angStep=0.00001;
	int loopN=abs(angle*2)/angStep;
	const int n=698;//n=abs(angle*2)/angStep; 
	//for(int i=0;i<40;i++){
	for(int j=0;j<loopN;j++){
		for(int k=0; k<x2.size(); k++){
			x_residual=(35.3/66.2*x1[k]+30.9/66.2*x3[k])*cos(angle)-(46.1/66.2*y1_sTGC[k]+20.1/66.2*y3[k])*sin(angle)+x-x2[k];
			xAlig->Fill(x_residual);
		}
		xAlig->Fit("gaus");
		TF1 *f1=(TF1 *)xAlig->GetFunction("gaus");
		
		if(f1->GetParameter(2)<0.2){
		xAlig->SetTitle(TString::Format("Gause fit par: deltaX= %f, deltaAngle= %f )",x,angle));
		xAlig->Draw();
		c4->SaveAs(TString::Format("./ScanPar/pr/xFit_deltaX_%f_deltaAngle%f.pdf",x,angle));
		}
		//X.push_back(x);
		Angle.push_back(angle);
		pr.push_back(f1->GetParameter(2));
		angle=angle+angStep;
		xAlig->Reset();
		c4->Update();
	}
	//	x=x+xStep;
	//}
	for(int m=0;m<50;m++)cout<<"*"; cout<<endl;
	cout<<"The number of the pr,Angle: "<<pr.size()<<" "<<Angle.size()<<endl;
	cout<<endl;

	// Draw the sigma_angle
	double ANGLE[n]={0.};
	double PR[n]={0.};
	for(int i=0;i<pr.size();i++){
		ANGLE[i]=Angle[i];
		PR[i]=pr[i];
	}
	TGraph* gr = new TGraph(n,ANGLE,PR);
	auto minPR=min_element(pr.begin(), pr.end());
	int minInd= distance(pr.begin(), minPR);

	for(int m=0;m<50;m++)cout<<"*"; cout<<endl;
	cout<<"The angle range is from "<<angleSet/180.*TMath::Pi()<<" to "<<angle<<";  The angle step is about "<<angStep<<endl;
	cout<<endl;
	cout<<"The smallest pr is  "<<*minPR<<";  The index is  "<<minInd<<";  The delta Angle is "<<Angle[minInd]<<endl;
	for(int m=0;m<50;m++)cout<<"*"; cout<<endl;

	double sita=Angle[minInd];
	double detaX2=x;
	for(int k=0; k<x2.size(); k++){
		x_residual=(35.3/66.2*x1[k]+30.9/66.2*x3[k])*cos(sita)-(46.1/66.2*y1_sTGC[k]+20.1/66.2*y3[k])*sin(sita)+detaX2-x2[k];
		//x_residual=(35.3/66.2*x1[k]+30.9/66.2*x3[k])*cos(2.49273)-(46.1/66.2*y1_sTGC[k]+20.1/66.2*y3[k])*sin(2.49273)-detaX2-x2[k];
		//cout<<x_residual<<endl;
		xAlig->Fill(x_residual);
	}
	xAlig->Fit("gaus");
	xAlig->SetTitle(TString::Format("Gause fit par: deltaX= %f, deltaAngle= %f )",detaX2,sita));
	xAlig->GetXaxis()->SetTitle("mm");
	xAlig->GetYaxis()->SetTitle("event");
	xAlig->Draw();
	c4->SaveAs(TString::Format("./ScanPar/xFit deltaX %f_deltaAngle%f.pdf",detaX2,sita));
	c4->Update();
	TCanvas *c1 = new TCanvas("c1","Sigma_Angle",200,10,500,300);
	c1->SetGrid();
	gr->SetLineWidth(2);
	gr->GetXaxis()->SetTitle("Angle");
	gr->GetYaxis()->SetTitle("Sigma");
	gr->SetTitle(TString::Format("From %f(%f) to %f(%f), AngStep is %f, deltaAngle is %f",angle-n*angStep,angleSet,angle,angle*180./TMath::Pi(),angStep,sita));
	gr->SetMarkerStyle(4);
	gr->SetLineColor(2);
	gr->Draw("APL");
	c1->SaveAs(TString::Format("./ScanPar/Sigma_Angle from %f to %f AngStep %f.pdf",angle-n*angStep,angle,angStep));
	return 0;
}
