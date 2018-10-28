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
class Data;
std::vector<Data*>Dset;
std::vector<attributenode*>attributes;
int attindex=0;
attributenode* Fresult;
bool fdata=0;

class attributenode {
public:
int Myindex;
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
class Data {
public:
std::vector<std::string> features;
std::string label;
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
float initentropy(void){

}
class attribute{
	public:
		std::string name;
		std::vector<std::string> values;
};

void read_data(){

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
			attributenode* att=new attributenode;
			attributes.push_back(att);
			att->Name.clear();
			std::string buff;
			buff=line.substr(line.find(" ")+1);
			//To do
			att->Name+=(buff.substr(0,buff.find(" ")));
			std::cout<<att->Name;
			att->Myindex=attindex;
			attindex+=1;
			//std::cout<<att->Myindex;
			std::string subline = line.substr(line.find("{")+1,line.length()-(line.find("{")+1));
			//std::cout<<"\n"<<subline;
			std::string token;
			size_t pos = 0;
			size_t pos2 = 0;
			std::string delimiter = ",";
			std::string delimiter2 = "}";
			while ((pos = subline.find(delimiter)) != std::string::npos) {
    			token = subline.substr(0, pos);
    			Valuenode*Van=new Valuenode;
    			Van->Name.clear();
    			Van->Name+=token;
    			Van->Myattribute=att;
    			att->MyValues.push_back(Van);
    			std::cout << Van->Name << std::endl;
    			subline.erase(0, pos + delimiter.length()+1);
			}
			while((pos2 = subline.find(delimiter2)) != std::string::npos)
            {
                token = subline.substr(0, pos2);
    			Valuenode*Van=new Valuenode;
    			Van->Name.clear();
    			Van->Name+=token;
    			Van->Myattribute=att;
    			att->MyValues.push_back(Van);
    			std::cout << Van->Name << std::endl;
    			subline.erase(0, pos2 + delimiter2.length());
            }
			//std::getline(std::cin, line);
		}
		if(line.find("@data") != -1){
            fdata=1;
            //std::getline(std::cin, line);
            }
std::getline(std::cin, line);

}
	}

int main(){
    while(!fdata)
    {
	read_data();
	std::cout<<fdata;
    }
}
