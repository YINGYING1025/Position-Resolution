//****************************** 整体思路*******************************************//
// Tb.mid and Adc.mid 是筛子，将信号挑出来，杂质每次都清空。
// Tb and Adc 是一个干净的暂时存放的台子，将一个干净纯粹的信号，安放的地方。 将这个信号装进袋子之后，就将自己清空，以方便迎接下一个新主人
// tb and adc 是一个袋子，每次接受一个干净的信号，for循环去了解信号的具体特点，将他们一个一个消化，投出到最终目的地。
//
// ************************* 信号挑选 ********************************************//
// 1. 只要TB 不连续， 判断是信号的条件变量就要归零。
// 2. 只要ADC 数值不大于设定值，判断是信号的条件变零就要归零。
// 注意： 判断完signal变量，最后signal归零。
void Pluse(){

	string path;
	int line_size=0;
	string stor;
	int ps=0;
	int i=0;
	string event[11];
	int Event=0;
	string altro[12];
	int ALTRO=0;
	int CH=0;
	int TB=0;
	int ADC=0;
	string a;
	string b;
	string c;
	int preTB=0;
	int TBcount=0;
	int SignalCount=0;
	int Pulse = 0;
	int ThisStrip=0;
	vector<int>Tb;
	vector<int>Adc;
	vector<int>Tb_mid;
	vector<int>Adc_mid;
	int j=0;
	int t=0;
	int StripCount=0;

	int ADC_Cut=16;
	int TB_Cut=3;
	int Strip_Cut=3;
	TCanvas *c1= new TCanvas("c1","Signal Pluse",700,600);
	c1->SetGrid();
	gStyle->SetOptFit();
//	TCanvas *c2= new TCanvas("c2","Signal Pluse",800,600);

	gStyle->SetOptTitle(kFALSE);
   gStyle->SetPalette(kSolar);
	TGraph *g[32];
	TMultiGraph *mg = new TMultiGraph();
#if 0	//**********************************//
	//========== All the File ==========//
	//*********************************//
	int FileBegin=1909;
	int FileEnd=1910;//1998
	for(int i=FileBegin;i<FileEnd;i++){
		ifstream data;
		path=Form("/Users/yingyingshi/shiyy/sTGC_Test/sTGC_analysis/Station1/CH2/Efficiency/test6/test6_%d.txt",i);
		data.open(path);
#endif
		ifstream data;
		data.open("./data/data_All.txt");
		// The first event of the file 1909 as for a example.
		while(getline(data,stor,'\n')){
			line_size=stor.size();

			ps=stor.find("Event",0);
			if(ps>0){
				if(StripCount>Strip_Cut){
					SignalCount++;
					cout << "Event is: " << Event << "   Signal is: " << SignalCount << endl;
				}
				StripCount=0;
				stringstream is(stor);
				while(is>>event[i]){i++;}
				i=0;
				event[2].pop_back();
				Event=atoi(event[2].c_str());}
			if(Event<23){
				continue;}
			if(Event==25){
				break;}

			if(line_size==54){
				if (Pulse==1){
					Tb.insert(Tb.end(), Tb_mid.begin(), Tb_mid.end());
					Adc.insert(Adc.end(), Adc_mid.begin(), Adc_mid.end());
					ThisStrip++;
					Pulse=0;
				}
				//if don't think have the two signal. ThisStrip number = Strip respond

				if(ThisStrip>0){
					cout<<endl;
					StripCount++;
					j++;
					t=Tb.size();
					if(t>0){
						int tb[t];
						int adc[t];
						for(int i=0;i<t;i++){
						//	if(adc[i]>30){
							tb[i]=Tb[i];
							adc[i]=Adc[i];
						//}
						}
						//cout << "adc size: " << sizeof(adc)/sizeof(adc[0]) << endl;
						g[j] = new TGraph(t,tb,adc);
						g[j]->SetMarkerStyle();
						
						//Up detector:
						//X:
						if(ALTRO==42||ALTRO==43||ALTRO==36||ALTRO==37||ALTRO==38||ALTRO==39){
						g[j]->SetLineColor(1);}//black
						g[j]->SetMarkerColor(1);
						g[j]->SetTitle("Up sTGC CH8");
						//Y:
						if(ALTRO==46||ALTRO==47||ALTRO==44||ALTRO==45){
                                                g[j]->SetLineColor(1);}// light black
                                                g[j]->SetMarkerColor(1);
                                                g[j]->SetTitle("Up sTGC CV3");
						
						//Middle
						//X: 
						if(ALTRO==34||ALTRO==35||ALTRO==40||ALTRO==41||ALTRO==50||ALTRO==51){
                                                g[j]->SetLineColor(2);}//g2 red
						g[j]->SetMarkerColor(2);
						g[j]->SetTitle("Middle sTGC CV1");
						//Y:
						if(ALTRO==54||ALTRO==55||ALTRO==58||ALTRO==59){
                                                g[j]->SetLineColor(2);}//g2 pale red
                                                g[j]->SetMarkerColor(2);
                                                g[j]->SetTitle("Middle sTGC CH2");
						
						//Down
						//X:
						if(ALTRO==31||ALTRO==30||ALTRO==32||ALTRO==33){
                                                g[j]->SetLineColor(3);}//g3 green
						g[j]->SetMarkerColor(1);
						 g[j]->SetTitle("Down sTGC CH8");
						 //Y:
						 if(ALTRO==48||ALTRO==49||ALTRO==60||ALTRO==61||ALTRO==52||ALTRO==53||ALTRO==56||ALTRO==57){
                                                g[j]->SetLineColor(3);}//g3 pale green
                                                g[j]->SetMarkerColor(1);
                                                 g[j]->SetTitle("Down sTGC CV3");

						g[j]->SetLineWidth(3);
						g[j]->SetMarkerStyle();
						g[j]->SetMarkerSize(1);
						g[j]->SetFillStyle(3004);
						mg->Add(g[j]);
					}
					ThisStrip=0;
				}
				TBcount=0;
				Tb.clear();
				Tb_mid.clear();
				Adc.clear();
				Adc_mid.clear();

				istringstream is(stor);
				while(is>>altro[i]){i++;}
				i=0;
				altro[7].pop_back();
				altro[9].pop_back();
				ALTRO=atoi(altro[7].c_str());
				CH=atoi(altro[9].c_str());}


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

			//*******************line_size=18 End *****************//

		}
		if(ps<0){
			if(StripCount>Strip_Cut){
				SignalCount++;
				cout << "Event is: " << Event << "   Signal is: " << SignalCount << endl;
			}
			StripCount=0;
		}


		//	}
		mg->SetTitle("Signal Pulse");
		mg->GetXaxis()->SetTitle("Timebin");
		mg->GetYaxis()->SetTitle("ADC");
		mg->GetXaxis()->SetRangeUser(0,40);
		mg->Draw("acp");
		




}
