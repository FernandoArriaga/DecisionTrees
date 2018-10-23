#include<stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include<list>
#include<cmath>
#include<iomanip>
class attribute;

class attribute{
	public:
		std::string name;
		std::vector<std::string> values;
};
void read_data(){
	attribute att;
	std::string line;
	std::getline(std::cin, line);
	while(line.empty() != true){
		if(line[0] == '%')
			std::getline(std::cin, line);
		if(line.find("@relation") != -1){
			std::string relation = line.substr(line.find(" ")+1);
			std::cout << relation;
			std::getline(std::cin, line);
		}
		if(line.find("@attribute") != -1){
			att.name.clear();
			//To do
			att.name+=(line.substr(line.find(" ")+1));
			std::cout<<att.name;
			std::string subline = line.substr(line.find("{")+1,line.length()-(line.find("{")+2));
			std::cout<<"\n"<<subline;
			std::string token;
			size_t pos = 0;
			std::string delimiter = ",";
			while ((pos = subline.find(delimiter)) != std::string::npos) {
    			token = subline.substr(0, pos);
    			att.values.push_back(token);
    			//std::cout << token << std::endl;
    			subline.erase(0, pos + delimiter.length());
			}
			std::getline(std::cin, line);
		}
		else
			std::getline(std::cin, line);
		//if(str.find("@data") != -1){
			
		//}
	}
	
	
}

int main(){
	read_data();
}

