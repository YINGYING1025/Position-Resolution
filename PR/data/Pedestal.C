
void Pedestal(){

	int count = 0;
	double FEE = 0.0;
	double CH = 0.0;
	int  TB = 0.0;
	double RMS = 0.0;
	double ADC = 0.0;
	double MeanADC = 0.0;
	string tmp;
	string HistName;
	TH1D *his1 = new TH1D("his1","The ADC of FEE",500,0,500);	
	TH2D *his2 = new TH2D("his2","ADC - Ped distribution",95,0,95,200,0,100);
	TH2D *his3 = new TH2D("his3","RMS - Ped distribution",64,0,64,100,0,10);
	ofstream outFile;
//	outFile.open("./pedestals_s01_r3-2.txt");
		ifstream inFile;
//		inFile.open("../Data/25-26readout/pedestals_s01_r3-800.txt");
                inFile.open("./pedestals_s01_r3.txt");
		while(getline(inFile,tmp,'\n')){
			count ++;
			if(count == 6){
				break;
			}	
		}
		count = 0;
		while(inFile>>FEE>>CH>>TB>>ADC>>RMS){	
		//	ADC = 0;
		//	RMS = 0;
			count ++;
		//	if(FEE==2){
		//	CH =CH + 32; }
			if(TB<435){
				his1->Fill(ADC);
				his2->Fill(TB,ADC);
				his3->Fill(CH,RMS);
			//	his1->Draw();
			//	his2->Draw();
			//	his3->Draw();
			}
			//if(count%512 == 0){
				MeanADC = his1->GetMean();
				outFile<<FEE<<"\t"<<CH<<"\t"<<TB<<"\t"<<ADC<<"\t"<<RMS<<endl;
				his1->Reset();
	//		}
		
		}
	his2->Draw("COLZ");
	his2->GetXaxis()->SetTitle("Timebin");
        his2->GetYaxis()->SetTitle("ADC");
//	his3->Draw("COLZ");
//	his3->GetXaxis()->SetTitle("Channel");
//	his3->GetYaxis()->SetTitle("RMS");	
}
