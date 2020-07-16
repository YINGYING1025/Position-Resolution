// The chamber have 1-32 all the address. that can be used.

void GetDecode2(){
	// ALTRO of each layer.
	int altroUpx[6]={42,43,36,37,38,39};
	int altroUpy[4]={47,46,45,44};

	int altroMidx[6]={51,50,35,34,41,40};
	int altroMidy[4]={54,55,58,59};

	int altroDownx[4]={33,32,31,30};
	int altroDowny[8]={48,49,56,57,52,53,60,61};

	//the ALTRO CH;
	int A[16]={0,1,2,3,4,5,6,7,15,14,13,12,11,10,9,8};//33,31,50,34,40,46,44
	int B[16]={1,0,3,2,5,4,7,6,14,15,12,13,10,11,8,9};//32,30,35,41,45,
	int C[16]={9,8,11,10,13,12,15,14,6,7,4,5,2,3,0,1};//49,57,53,61,58,36,38
	int D[16]={8,9,10,11,12,13,14,15,7,6,5,4,3,2,1,0};//48,56,52,60,55,59,43,37,39
	int E[14]={11,10,13,12,15,14,6,7,4,5,2,3,0,1};	  //54,42,
	int F[14]={3,2,5,4,7,6,14,15,12,13,10,11,8,9};	  //51,47,

	ofstream out;
	out.open("./strip_map_2.txt");
	int i=0;

	//Up sTGC CV7 (22,23)
	//Y:
	i=0;
	for(int j=0;j<4;j++){
		if(altroUpy[j]==47){
			for(int k=0;k<14;k++){
				i++;
				//F:47,
				out << altroUpy[j] <<" "<<F[k]<<"  "<<i<<endl;
			}
			continue;
		}

		for(int k=0;k<16;k++){
			i++;
			//A:44,46
			if(altroUpy[j]==44||altroUpy[j]==46){	
				out << altroUpy[j] <<" "<<A[k]<<"  "<<i<<endl;
			}

			//B:45
			if(altroUpy[j]==45){
				out << altroUpy[j] <<" "<<B[k]<<"  "<<i<<endl;
			}
		}
	}

	//X:CH6(19,20,21)
	i=0;

	for(int j=0;j<6;j++){

		if(altroUpx[j]==42){
			for(int k=0;k<14;k++){
				i++;
				//E:42,
				out << altroUpx[j] <<" "<<E[k]<<"  "<<i<<endl;
			}
			continue;
		}

		cout<<i<<endl;	
		for(int k=0;k<16;k++){
			i++;
			//C:36,38,
			if(altroUpx[j]==38||altroUpx[j]==36){
				out << altroUpx[j] <<" "<<C[k]<<"  "<<i<<endl;
			}

			//D:43,37,39
			if(altroUpx[j]==43||altroUpx[j]==37||altroUpx[j]==39){
				out << altroUpx[j] <<" "<<D[k]<<"  "<<i<<endl;
			}
		}
	}
	cout<<endl;

	//Mid sTGC CV1 (25,17,185)
	//X:
	i=0;
	for(int j=0;j<6;j++){

		if(altroMidx[j]==51){
			for(int k=0;k<14;k++){
				i++;
				//F:51,
				out << altroMidx[j] <<" "<<F[k]<<"  "<<i<<endl;
			}
			continue;
		}

		for(int k=0;k<16;k++){
			i++;
			//A:50,34,40
			if(altroMidx[j]==50||altroMidx[j]==34||altroMidx[j]==40){
				out << altroMidx[j] <<" "<<A[k]<<"  "<<i<<endl;
			}

			//B:35,41
			if(altroMidx[j]==35||altroMidx[j]==41){
				out << altroMidx[j] <<" "<<B[k]<<"  "<<i<<endl;
			}

		}
	}
	cout<<endl;

	//Y:sTGC CH2(27,29)
	i=0;
	for(int j=0;j<4;j++){
		if(altroMidy[j]==54){
			for(int k=0;k<14;k++){
				i++;
				//E:54,
				out << altroMidy[j] <<" "<<E[k]<<"  "<<i<<endl;
			}
			continue;
		}

		for(int k=0;k<16;k++){
			i++;
			//C:58
			if(altroMidy[j]==58){
				out << altroMidy[j] <<" "<<C[k]<<"  "<<i<<endl;
			}

			//D:55,59
			if(altroMidy[j]==55||altroMidy[j]==59){
				out << altroMidy[j] <<" "<<D[k]<<"  "<<i<<endl;
			}
		}
	}

	//Down sTGC
	//X:
	i=0;
	for(int j=0;j<4;j++){
		for(int k=0;k<16;k++){
			i++;
			//B:30,32
			if(altroDownx[j]==30||altroDownx[j]==32){
				out << altroDownx[j] <<" "<<B[k]<<"  "<<i<<endl;
			}

			//A:31,33
			if(altroDownx[j]==31||altroDownx[j]==33){
				out << altroDownx[j] <<" "<<A[k]<<"  "<<i<<endl;
			}
		}
	}
	//Y:
	i=0;
	for(int j=0;j<8;j++){
		/*
		   if(altroDownx[j]==60){
		   for(int k=0;k<14;k++){
		   i++;
		//E:60
		out << altroDowny[j] <<" "<<E[k]<<"  "<<i<<endl;
		}
		continue;
		}
		 */
		if(j<4){
			cout<<i<<endl;	
			for(int k=0;k<16;k++){
				i++;
				//C:49,57,53,61
				if(altroDowny[j]==49||altroDowny[j]==57){
					out << altroDowny[j] <<" "<<C[k]<<"  "<<i<<endl;
				}

				//D:48,56,52,60
				if(altroDowny[j]==48||altroDowny[j]==56){
					out << altroDowny[j] <<" "<<D[k]<<"  "<<i<<endl;
				}

			}
		}
		if(j==4) i=0;
		if(j>3){
			for(int k=0;k<16;k++){
				i++;
				if(altroDowny[j]==52||altroDowny[j]==60){
					out << altroDowny[j] <<" "<<D[k]<<"  "<<i<<endl;}
				if(altroDowny[j]==53||altroDowny[j]==61){
					out << altroDowny[j] <<" "<<C[k]<<"  "<<i<<endl;}

			}
		}
	}

	out.close();
}
