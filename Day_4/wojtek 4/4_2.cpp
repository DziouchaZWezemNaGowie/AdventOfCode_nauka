#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int main() {
	ifstream infile;
	infile.open("DANE.txt");
	if (infile.is_open()) {
		string l1, l2, l3, rl;
		int it;
		int i=0;
		int i2=0;
		long long wynik=0;
		int paper=0;
		long long pwynik = 5;
		vector<string> lines;
		while (infile >> rl){
			lines.push_back(rl);
		}
		while(pwynik != wynik){
		pwynik = wynik;
		for (it=0; it < lines.size(); it++){
			if (!l2.empty()){
				l3 = lines.at(it);
				if(i==0){
					while(i2<l1.size()){
    			    	if(l1.substr(i2,1)=="@"){
  				      		if (i2==0){
		        				wynik++;
		        				l1.replace(i2,1,".");
							}else if (i2==l1.size()-1){
								wynik++;
								l1.replace(i2,1,".");
							}else{
								if(l1.substr(i2-1,1)=="@"){
									paper++;
								}
								if(l1.substr(i2+1,1)=="@"){
									paper++;
								}
								if(l2.substr(i2-1,1)=="@"){
									paper++;
								}
								if(l2.substr(i2,1)=="@"){
									paper++;
								}
								if(l2.substr(i2+1,1)=="@"){
									paper++;
								}
								if (paper<4){
									wynik++;
									l1.replace(i2,1,".");
								}
							}
						}
						i2++;
						paper=0;
					}
					lines.at(0) = l1;
					i++;
					i2=0;	
				}
				while(i2<l2.size()){
    	        	if (l2.substr(i2,1)=="@"){
						if (i2==0){
       						if(l1.substr(i2,1)=="@"){
								paper++;
							}
							if(l1.substr(i2+1,1)=="@"){
								paper++;
							}
							if(l2.substr(i2+1,1)=="@"){
								paper++;
							}
							if(l3.substr(i2,1)=="@"){
								paper++;
							}
							if(l3.substr(i2+1,1)=="@"){
								paper++;
							}
							if (paper<4){
								wynik++;
								l2.replace(i2,1,".");
							}
						}else if (i2==l1.size()-1){
							if(l1.substr(i2-1,1)=="@"){
								paper++;
							}
							if(l1.substr(i2,1)=="@"){
								paper++;
							}
							if(l2.substr(i2-1,1)=="@"){
								paper++;
							}
							if(l3.substr(i2,1)=="@"){
								paper++;
							}
							if(l3.substr(i2-1,1)=="@"){
								paper++;
							}
							if (paper<4){
								wynik++;
								l2.replace(i2,1,".");
							}
						}else{
							if(l1.substr(i2-1,1)=="@"){
								paper++;
							}
							if(l1.substr(i2,1)=="@"){
								paper++;
							}
							if(l1.substr(i2+1,1)=="@"){
								paper++;
							}
							if(l2.substr(i2-1,1)=="@"){
								paper++;
							}
							if(l2.substr(i2+1,1)=="@"){
								paper++;
							}
							if(l3.substr(i2-1,1)=="@"){
								paper++;
							}
							if(l3.substr(i2,1)=="@"){
								paper++;
							}
							if(l3.substr(i2+1,1)=="@"){
								paper++;
							}
							if (paper<4){
								wynik++;
								l2.replace(i2,1,".");
							}
						}
					}
					paper=0;
					i2++;
				}
				i2=0;
				lines.at(it-1) = l2;
				i++;
				if(lines.at(it) == lines.back()){
					while(i2<l3.size()){
						if(l3.substr(i2,1)=="@"){
							if (i2==0){
			        			wynik++;
			        			l3.replace(i2,1,".");
							}else if (i2==l1.size()-1){
								wynik++;
								l3.replace(i2,1,".");
							}else{
								if(l2.substr(i2-1,1)=="@"){
									paper++;
								}
								if(l2.substr(i2,1)=="@"){
									paper++;
								}
								if(l2.substr(i2+1,1)=="@"){
									paper++;
								}
								if(l3.substr(i2-1,1)=="@"){
									paper++;
								}
								if(l3.substr(i2+1,1)=="@"){
									paper++;
								}
								if (paper<4){
									wynik++;
									l3.replace(i2,1,".");
								}
							}
						}
						i2++;
						paper=0;
					}
					lines.at(it) = l3;
					i=0;
					i2=0;
				}
				l1 = l2;
				l2 = l3;	
			}else{
				if(l1.empty()){
					l1 = lines.at(it);
				}else{
					l2 = lines.at(it);
				}
			}	
		}
		l1.clear();
		l2.clear();
		l3.clear();
		}
		cout << wynik;
	}else{
		cout << "nie otwarlo sie";
	}
	return 0;
}
