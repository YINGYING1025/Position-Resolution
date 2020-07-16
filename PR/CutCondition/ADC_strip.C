
#include <iostream> 
#include <iterator>
#include <algorithm>
void ADC_strip(){
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
	int j=0;
	int strip_max=0;
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
	TCanvas *c1 = new TCanvas("c1","adc_strip",800,500);
	TFile *file = new TFile("adc_strip.root","RECREATE");
	TGraph *g[10000];
	TMultiGraph *mg = new TMultiGraph();
#if 1
	//**********************************//
	//========== All the File ==========//
	//*********************************//
	int FileBegin=1909;
	int FileEnd=1910;
	for(int k=FileBegin;k<FileEnd;k++){
		ifstream data;
		path=Form("../data/data_pr1.txt");
		data.open(path);
		if(!data){
			continue;}
#endif
		//		ifstream data;
		//		data.open("./1.txt");
		ifstream map;

		while(getline(data,stor,'\n')){
			line_size=stor.size();

			ps=stor.find("Event",0);
			if(ps>0){
				if(adc.size()>0){
					// The MaxADC,TB and index of this EVENT.
					MaxADC=*max_element(begin(adc),end(adc));
					MaxADC_index=std::distance(begin(adc),std::max_element(begin(adc),end(adc)));
					TB=tb[MaxADC_index];
					strip_max=strip[MaxADC_index];
					//cout<<"TB: "<<TB<<" MaxADC: "<<MaxADC<<" Index: "<<MaxADC_index<<endl;
					//Get the TB; Get the ADC of EVENt in TB.

					for(int i=0;i<tb.size();i++){
						if(tb[i]==TB){
							strip_num=strip[i];
							adc_num=adc[i];
							x_strip[j]=strip_num-strip_max;
							if(adc_num>10){
								y_adc[j]=adc_num;}
							j++;
						}
					}

					g[n] = new TGraph(j-1,x_strip,y_adc);
					g[n]->SetMarkerStyle(3);
					g[n]->SetMarkerColor(2);
					g[n]->SetMarkerSize(1);
					g[n]->SetLineColor(2);
					g[n]->SetLineWidth(3);
					g[n]->SetTitle("ADC changes with Strip in one Event");
					g[n]->GetXaxis()->SetRangeUser(-15,15);
					g[n]->GetXaxis()->SetTitle("STRIP");
					g[n]->GetYaxis()->SetTitle("ADC");
					mg->Add(g[n]);

					file->cd();
					g[n]->Write();


					memset(x_strip,0,sizeof x_strip);
					memset(y_adc,0,sizeof y_adc);
					tb.clear();
					adc.clear();
					strip.clear();
					j=0;
				}

				n++;
				istringstream is(stor);
				while(is>>event[world]){world++;}
				event[2].pop_back();
				Event=atoi(event[2].c_str());
				world=0;
				cout <<"Event: " << Event << endl;
			
	}
			if(Event>10) break;

			if(line_size==54){
				istringstream is(stor);
				while(is>>altro[world]){world++;}
				world=0;
				altro[7].pop_back();//ALTRO
				ALTRO=atoi(altro[7].c_str());
				altro[9].pop_back();//CH
				CH=atoi(altro[9].c_str());

				map.open("../decode/strip_map_2.txt");
				while(getline(map,stor_map,'\n')){
					istringstream is(stor_map);
					is>>alt>>ch>>Strip;

					if(ALTRO==alt&&CH==ch){
						STRIP=Strip;
					}
				}
				map.close();
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

	}// file end
	mg->SetTitle("ADC_Strip");
	mg->GetXaxis()->SetTitle("STRIP");
	mg->GetYaxis()->SetTitle("ADC");
	mg->GetXaxis()->SetRangeUser(-15,15);
	mg->Draw("ap");
}
