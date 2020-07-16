//*********************** ADC change with tb in strip of MaxADC in all event *************************//


#include <iostream> 
#include <iterator>
#include <algorithm>
void TB_ADC(){
	string path;
	int line_size=0;
	int ps=0;
	int alt=0;
	int ch=0;
	int Strip=0;
	int STRIP=0;
	int ALTRO=0;
	int CH=0;
	int Event=0;
	int MaxADC=0;
	int MaxADC_index=0;
	int world=0;
	int TB=0;
	int ADC=0;
	int strip_num=0;
	int adc_num=0;
	int x_strip[470]={0};
	int y_adc[470]={0};
	int x_tb[470]={0};
	int j=0;
	int h=0;
	int EVENT=0;
	int strip_max=0;
	int real_strip[30]={0};
	int real_adc[30]={0};
	vector<int>adc;
	vector<int>tb;
	vector<int>strip;

	int n=0;
	string a;
	string b;
	string c;
	string stor;
	string stor_map;
	string event[11];
	string altro[12];
	TCanvas *c1 = new TCanvas("c1","ADC_TB",800,500);
	TFile *file = new TFile("ADC_TB.root","RECREATE");
	TGraph *g[10000];
	TMultiGraph *mg = new TMultiGraph();

	//**********************************//
	//========== All the File ==========//
	//*********************************//
	/*	int FileBegin=1909;
		int FileEnd=1920;
		for(int k=FileBegin;k<FileEnd;k++){
		ifstream data;
		path=Form("/Users/yingyingshi/shiyy/sTGC_Test/sTGC_analysis/Station1/CH2/Efficiency/test6/test6_%d.txt",k);
		data.open(path);
		if(!data){
		continue;}
	 */	 
	ifstream data;
	data.open("./4.txt");
	ifstream map;

	//cout << " dhfkjsnfjdslkvndkfnv" << endl;
	while(getline(data,stor,'\n')){
		line_size=stor.size();

		ps=stor.find("Event",0);
		if(ps>0){
			if(adc.size()>0){
				EVENT++;
				// The MaxADC,TB and index of this EVENT.
				MaxADC=*max_element(begin(adc),end(adc));
				MaxADC_index=std::distance(begin(adc),std::max_element(begin(adc),end(adc)));
				TB=tb[MaxADC_index];
				strip_max=strip[MaxADC_index];
				cout <<strip_max<<endl;
				//cout<<"TB: "<<TB<<" MaxADC: "<<MaxADC<<" Index: "<<MaxADC_index<<endl;
			
				for(int i=-4;i<5;i++){
				
					for(int j=0;j<strip.size();j++){
						if(strip[j]==strip_max+i){
							x_tb[h]=tb[j];
							y_adc[h]=adc[j];
							h++;
								cout <<strip[j]<<"  "<<strip_max+i<<"  "<<x_tb[h] << "  "<< y_adc[h]<<" "<< h<<endl;
						}
					}
					g[n] = new TGraph(h,x_tb,y_adc);
					g[n]->SetMarkerStyle(8);
					g[n]->SetMarkerColor(1);
					g[n]->SetMarkerSize(0.5);
					g[n]->SetLineColor(4);
					g[n]->SetLineWidth(3);
					g[n]->SetTitle("TB");
					//g[n]->GetXaxis()->SetRangeUser(-15,15);
					g[n]->GetXaxis()->SetTitle("TB");
					g[n]->GetYaxis()->SetTitle("ADC");
					//g[n]->Fit("gaus","","",-15,15);
					mg->Add(g[n]);
					h=0;
					n++;
				}

				file->cd();
				mg->Write();


				memset(x_tb,0,sizeof x_strip);
				memset(y_adc,0,sizeof y_adc);
				memset(real_strip,0,sizeof real_strip);
				memset(real_adc,0,sizeof real_adc);
				tb.clear();
				adc.clear();
				strip.clear();
				h=0;
			}
			cout << "The Evnet is : " << EVENT <<endl;

			
			istringstream is(stor);
			while(is>>event[world]){world++;}
			event[2].pop_back();
			Event=atoi(event[2].c_str());
			world=0;
		}

		if(line_size==54){
			istringstream is(stor);
			while(is>>altro[world]){world++;}
			world=0;
			altro[7].pop_back();//ALTRO
			ALTRO=atoi(altro[7].c_str());
			altro[9].pop_back();//CH
			CH=atoi(altro[9].c_str());

			//cout <<ALTRO<<"  "<<CH<<endl;
			map.open("./decode/strip_map_3.txt");
			while(getline(map,stor_map,'\n')){
				istringstream is(stor_map);
				is>>alt>>ch>>Strip;

				if(ALTRO==alt&&CH==ch){
					STRIP=Strip;
				}
			}
			map.close();
			//cout<<"ALTRO:  " <<ALTRO<<" CH: "<<CH<<" Strip:  "<<STRIP<<endl;
		}

		if(line_size==18){
			istringstream is(stor);
			while(is>>a>>TB>>b>>ADC>>c){
				tb.push_back(TB);
				adc.push_back(ADC);
				strip.push_back(STRIP);		
			}
		}

	}

	//	}
	cout << "All the Evnet: " << EVENT <<endl;
	mg->SetTitle("ADC_TB");
	mg->GetXaxis()->SetTitle("TB");
	mg->GetYaxis()->SetTitle("ADC");
	//mg->GetXaxis()->SetRangeUser(-15,15);
	mg->Draw("apc");
}
