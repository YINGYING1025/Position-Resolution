#include <fstream>
#include <iostream>
void SetThereDataToOne(){
	string stor;
	int ps=0;
	int EventCount=0;
	int n=0;
	string event[12];
	int world=0;
	int DataFileBegin=7;
	int DataFileEnd=9;
	string fileRe;
	string fileWr=Form("./ThereEventAll.txt");

	ofstream dataWr;
	dataWr.open(fileWr);

	ifstream dataRe;

	for(int file=DataFileBegin;file<DataFileEnd;file++){

		fileRe=Form("./data_pr%d.txt",file);
		dataRe.open(fileRe);
		cout<<"***************** File "<<fileRe<<" is runing **************"<<endl;
		if(!dataRe) continue;
		//n=0;

		while(getline(dataRe,stor,'\n')){
		 	ps=stor.find("Event",0);
			if(ps>0){
			EventCount++;
			//n++;
			istringstream is(stor);
                         while(is>>event[world]){world++;}
			world=0;
			 dataWr<<event[0]<<" "<<event[1]<<" "<<EventCount<<","<<" "<<event[3]<<" "<<event[4]<<" "<<event[5]<<" "<<event[6]<<" "<<event[7]<<" "<<event[8]<<" "<<event[9]<<" "<<event[10]<<" "<<event[11]<<endl;
			 //cout<<n<<endl;
			//if(n==2) break;
			if(EventCount%1000==0){
			cout <<"File is: "<<fileRe<<" EventCount: "<<EventCount<<endl;}
			}
			if(ps<0){
			dataWr<<stor<<endl;}
		}
		cout <<"File is: "<<fileRe<<" EventCount: "<<EventCount<<endl;

	dataRe.close();
	}
	dataWr.close();
}
