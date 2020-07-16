//*************** sumADC is the MaxADC and ADC at tb of MaxADC at different event ***************//

#include <iostream> 
#include <iterator>
#include <algorithm>
//ADC_strip3 
void sumADC_strip(){
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
	int signal=0;

	gStyle->SetOptStat(1);
	TCanvas *c1 = new TCanvas("c1","ADC_strip",800,500);
	TFile *file = new TFile("ADC_strip.root","RECREATE");
	TGraph *g[10000];
	TMultiGraph *mg = new TMultiGraph();


	int fill=0;
	int real_strip_num=0;
	map<int,int> mymap;
	TCanvas *c2 = new TCanvas("c2","ADC_strip",800,500);
	TH1F * h1=new TH1F("h1","sumADC at each strip",32,-16,16);
	gStyle->SetOptStat(1);

	for(int i=-15;i<16;i++){
		mymap[i]=0;}
#if 1
	//**********************************//
	//========== All the File ==========//
	//*********************************//
	int FileBegin=2415;
	int FileEnd=2416;
	for(int k=FileBegin;k<FileEnd;k++){
		ifstream data;
		path=Form("../test_%d.txt",k);
		data.open(path);
		if(!data){
			continue;}
#endif
//		ifstream data;
//		data.open("./4.txt");
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
					//cout<<"TB: "<<TB<<" MaxADC: "<<MaxADC<<" Index: "<<MaxADC_index<<endl;
					//Get the TB; Get the ADC of EVENt in TB.
					if(MaxADC>60){
					for(int i=0;i<tb.size();i++){
						if(tb[i]==TB){
							strip_num=strip[i];
							adc_num=adc[i];
							if(adc_num>10){
								x_strip[j]=strip_num-strip_max;
								y_adc[j]=adc_num;
								j++;
								//		cout << strip_num<< " "<< adc_num<< " x_strip  "<<j<<"  "<<x_strip[j]<<"y_adc  "<<y_adc[j]<<endl;
							}
						}
					}
					//x_strip,y_adc is the all information of one event
					for(int i=-15;i<16;i++){
						for(int m=0;m<j;m++){
							if(x_strip[m]==i){
								real_strip[h]=i;
								real_adc[h]=y_adc[m];
								//mymap[i]=mymap[i]+real_adc[h];
								//cout << real_strip[h]<< "  " << real_adc[h]<<" "<<h<<endl;
								h++;
								continue;
							}	

						}
					}
					for(int i=0;i<h;i++){
						real_strip_num=real_strip[i];
						mymap[real_strip_num]=mymap[real_strip_num]+real_adc[i];
						//cout << "mymap strip "<< mymap[real_strip_num]<<endl;
					}

						g[n] = new TGraph(h,real_strip,real_adc);
					//	g[n] = new TGraph(j-1,x_strip,y_adc);
					g[n]->SetMarkerStyle(8);
					g[n]->SetMarkerColor(1);
					g[n]->SetMarkerSize(0.5);
					g[n]->SetLineColor(4);
					g[n]->SetLineWidth(3);
					g[n]->SetTitle("Strip");
					g[n]->GetXaxis()->SetRangeUser(-15,15);
					g[n]->GetXaxis()->SetTitle("STRIP");
					g[n]->GetYaxis()->SetTitle("ADC");
					//g[n]->Fit("gaus","","",-15,15);
					mg->Add(g[n]);
					//g[n]->Draw("ap");

					//file->cd();
					//g[n]->Write();
				
					}
					 
					memset(x_strip,0,sizeof x_strip);
					memset(y_adc,0,sizeof y_adc);
					memset(real_strip,0,sizeof real_strip);
					memset(real_adc,0,sizeof real_adc);
					tb.clear();
					adc.clear();
					strip.clear();
					j=0;
					h=0;
				}
				//cout << "The Evnet is : " << EVENT <<endl;

				n++;
				istringstream is(stor);
				while(is>>event[world]){world++;}
				event[2].pop_back();
				Event=atoi(event[2].c_str());
				world=0;
			if(Event%1000==0){
				cout << "This event is: "<<Event<<endl;}
			if(Event==500){	
				break;}
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
				map.open("../decode/strip_map_2.txt");
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
	 if(ALTRO==50||ALTRO==51||ALTRO==34||ALTRO==35||ALTRO==40||ALTRO==41){
	//		if(ALTRO==42||ALTRO==43||ALTRO==37||ALTRO==36||ALTRO==39||ALTRO==38){
		//if(ALTRO==32||ALTRO==33||ALTRO==30||ALTRO==31){
			if(line_size==18){
				istringstream is(stor);
				while(is>>a>>TB>>b>>ADC>>c){
					tb.push_back(TB);
					adc.push_back(ADC);
					strip.push_back(STRIP);		
				}
			}
	 }

		}

			}
			c1->cd();
			cout << "All the Evnet: " << EVENT <<endl;
			mg->SetTitle("ADC_Strip");
			mg->GetXaxis()->SetTitle("STRIP");
			mg->GetYaxis()->SetTitle("ADC");
			mg->GetXaxis()->SetRangeUser(-15,15);
			mg->Draw("apc");
			c2->cd();
		for(int i=-15;i<16;i++){
			fill=mymap[i];
			cout <<i<<" "<<fill<<endl;
			h1->SetBinContent(i+16,fill);
		}
		h1->GetXaxis()->SetTitle("STRIP");
                h1->GetYaxis()->SetTitle("sumADC");
		h1->Fit("gaus");
		h1->Draw("PLC PMC");
		cout<<"signal"<<signal<<endl;
}
