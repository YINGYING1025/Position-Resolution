void GetEventData2(){
	int eventNum=0;
	int fileNum=0;
	int line_size=0;
	string stor;
	string str;
	int ps=0;
	int pss=0;
	int GetThisEvent=0;
	string a;
	string event[12];
	int world=0;
	int Event=0;
	string path1;
	string path2;
	vector<int>eventnum;
	vector<int>filenum;
	int size=0;
	int j=0;
	int n=0;
	string b;
	//======= File out ====//
	ofstream out;
	out.open("./data_All.txt");

	// ATATION: Please See This!

	// !!!!!!!! Remenber change the data.txt name !!!!!!//
	// it can be replace with new file, only run this file!!!!!


	//====== File in =======//
	ifstream even;
	even.open("./signalEvent_2549_2814.txt");//signalEvent_2475_2487.txt signalEvent_2549_2814.txt 
	while(getline(even,str,'\n')){
		istringstream is(str);
		is>>a>>fileNum>>b>>eventNum;
		filenum.push_back(fileNum);
		eventnum.push_back(eventNum);
	}
	size=eventnum.size();
	cout << "AllEvent: "<<size<<" filenum size: "<<filenum.size()<<endl;
	even.close();
	int FileBegin=2549;
	int FileEnd=2815;
	ifstream in;
	for(int i=FileBegin;i<FileEnd;i++){
		path2=Form("/Volumes/shiyy/SourceData/three_xy/test_%d.txt",i);
		in.open(path2);
		cout <<"filenum[i]: "<<filenum[j]<<" i: "<<i<<endl;

		if(filenum[j]==i){	
			//Get the Event content.
			while(getline(in,stor,'\n')){
				line_size=stor.size();
				ps=stor.find("Event ",0);
				if(ps>0){
					istringstream is(stor);
					while(is>>event[world]){world++;}
					event[2].pop_back();
					Event=atoi(event[2].c_str());
					world=0;

					if(eventnum[j]==Event){
						j++;
					//cout <<"j: "<<j<<" "<<eventnum[j]<<" "<<Event<<endl;
					}
				}
				if(j-1<0){
					continue;}

				if(eventnum[j-1]==Event){
					if(ps>0){
						//cout <<"j: "<<j-1<<" "<<eventnum[j-1]<<" "<<Event<<endl;
						n++;
						cout <<" n: "<<n<<" File: "<<filenum[j-1]<<" j: "<<j<<" Event: "<<Event<<" eventnum: "<<eventnum[j-1]<<endl;

						out <<event[0]<<" "<<event[1]<<" "<<j<<","<<" "<<event[3]<<" "<<event[4]<<" "<<event[5]<<" "<<event[6]<<" "<<event[7]<<" "<<event[8]<<" "<<event[9]<<" "<<event[10]<<" "<<event[11]<<endl;
					}
					if(ps<0){
						//cout <<"j: "<<j-1<<" "<<eventnum[j-1]<<" "<<Event<<endl;
						out << stor <<endl;}

				}

			}
			eventnum[j-1]=eventnum[j];
		}
		in.close();

	}
	out.close();
}
