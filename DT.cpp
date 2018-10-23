#include<stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include<list>
#include<cmath>
#include<iomanip>
class attribute;
class attributenode;
class Valuenode;
class resultnode;

class attributenode {
public:
std::string Name;
std::vector<Valuenode*> MyValues;
Valuenode* Parentvalue;
float Myentropy;
friend class Valuenode;
};

class Valuenode {
public:
std::string Name;
attributenode* Nextattribute;
attributenode* Myattribute;
std::string Myresult;
int mysize;
float myentropy;
friend class attributenode;

};

bool isvaluepresent(Valuenode* val2)
{
//if value node is present on the line of data return true
}
bool findresults(Valuenode* val1)
{
//for every parent value check if it's present, use recursion.
}
int numofresults(Valuenode* val, std::string res)
{ int number=0;
//for every line of data
//if the result is there,
//if res==res of that line add 1 to number
return number;
}

float entropy (Valuenode* VN)
{
//for every possible result,do the algorithm based on number of(result)
}

float infoGain(Valuenode*parentv, attributenode*expanded)
{
//calculate using the parentv entropy and the entropy of the values of the expanded attribute.
}

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

