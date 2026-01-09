#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    ifstream infile;
	infile.open("DANE.txt");
	if(infile.is_open()){
        string l1,l2,l3;
        int paper=0;
        long long i=0;
        int wynik=0;
        infile >> l1 >> l2;
        std::cout << l1;
        while(i<l1.size()){
        	if(l1.substr(i,1)=="@"){
        		if (i==0){
        			wynik++;
				}else if (i==l1.size()-1){
					wynik++;
				}else{
					if(l1.substr(i-1,1)=="@"){
						paper++;
					}
					if(l1.substr(i+1,1)=="@"){
						paper++;
					}
					if(l2.substr(i-1,1)=="@"){
						paper++;
					}
					if(l2.substr(i,1)=="@"){
						paper++;
					}
					if(l2.substr(i+1,1)=="@"){
						paper++;
					}
					if (paper<4){
						wynik++;
					}
				}
			}
			i++;
			paper=0;
		}
		std::cout << wynik;
		while(infile >> l3){
			i=0;
			while(i<l2.size()){
            	if (l2.substr(i,1)=="@"){
					if (i==0){
        				if(l1.substr(i,1)=="@"){
							paper++;
						}
						if(l1.substr(i+1,1)=="@"){
							paper++;
						}
						if(l2.substr(i+1,1)=="@"){
							paper++;
						}
						if(l3.substr(i,1)=="@"){
							paper++;
						}
						if(l3.substr(i+1,1)=="@"){
							paper++;
						}
						if (paper<4){
							wynik++;
						}
					}else if (i==l1.size()-1){
						if(l1.substr(i-1,1)=="@"){
							paper++;
						}
						if(l1.substr(i,1)=="@"){
							paper++;
						}
						if(l2.substr(i-1,1)=="@"){
							paper++;
						}
						if(l3.substr(i,1)=="@"){
							paper++;
						}
						if(l3.substr(i-1,1)=="@"){
							paper++;
						}
						if (paper<4){
							wynik++;
						}
					}else{
						if(l1.substr(i-1,1)=="@"){
							paper++;
						}
						if(l1.substr(i,1)=="@"){
							paper++;
						}
						if(l1.substr(i+1,1)=="@"){
							paper++;
						}
						if(l2.substr(i-1,1)=="@"){
							paper++;
						}
						if(l2.substr(i+1,1)=="@"){
							paper++;
						}
						if(l3.substr(i-1,1)=="@"){
							paper++;
						}
						if(l3.substr(i,1)=="@"){
							paper++;
						}
						if(l3.substr(i+1,1)=="@"){
							paper++;
						}
						if (paper<4){
							wynik++;
							std::cout << "l" << i;
						}
					}
				}
				paper=0;
				i++;
			}
        	l1=l2;
        	l2=l3;
        	std::cout << "|" << wynik;
		}
		paper=0;
		i=0;
		while(i<l3.size()){
			if(l3.substr(i,1)=="@"){
				if (i==0){
        			wynik++;
				}else if (i==l1.size()-1){
					wynik++;
				}else{
					if(l1.substr(i-1,1)=="@"){
						paper++;
					}
					if(l1.substr(i,1)=="@"){
						paper++;
					}
					if(l1.substr(i+1,1)=="@"){
						paper++;
					}
					if(l3.substr(i-1,1)=="@"){
						paper++;
					}
					if(l3.substr(i+1,1)=="@"){
						paper++;
					}
					if (paper<4){
						wynik++;
						cout << "l" << i;
					}
				}
			}
			i++;
			paper=0;
		}
        cout << "|" << wynik;
    }else{
        cout << "nie otwarlo sie";
    }
}
