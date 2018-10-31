#include<stdio.h>
#include <stdlib.h>
#include <math.h>
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
float Intrpy;
attributenode* Head;

class attributenode {
public:
int Myindex;
std::string Name;
std::vector<Valuenode*> MyValues;
Valuenode* Parentvalue;
float Myentropy;
attributenode();
friend class Valuenode;
};
attributenode::attributenode(void){
Parentvalue=0;
}
class Valuenode {
public:
std::string Name;
std::vector<attributenode*>Posatt;
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

bool isvaluepresent(Valuenode* val2,Data* D)
{
//if value node is present on the line of data return true
if(val2->Name.compare(D->features[val2->Myattribute->Myindex])==0)
    return true;
return false;
}
bool findresults(Valuenode* val1,Data* D1)
{
//for every parent value check if it's present, use recursion.
if(val1->Myattribute->Parentvalue!=0)
{
    //std::cout<<"yes";
    return (isvaluepresent(val1,D1))&&(findresults(val1->Myattribute->Parentvalue,D1));
}
return isvaluepresent(val1,D1);
}


float entropy (Valuenode* VN)
{
//for every possible result,do the algorithm based on number of(result)
float Nres=0;
    float ntrpy=0;
    float dsize;
    float p=0;
for(int i=0;i<Fresult->MyValues.size();i++)
{   VN->mysize=0;
    for(int j=0;j<Dset.size();j++)
    {
        if(findresults(VN,Dset[j]))
        {
            VN->mysize+=1;
            if(Dset[j]->label.compare(Fresult->MyValues[i]->Name)==0)
            Nres+=1;
        }

    }
    //if(VN->Myattribute->Parentvalue!=0)
    //std::cout<<VN->Myattribute->Parentvalue->Name;
    if(Nres>0)
    {
    dsize=VN->mysize;
    p=Nres/dsize;
    ntrpy+=-1*(p)* log2 (p);
    if(ntrpy<0.1)
       {VN->Myresult+=Fresult->MyValues[i]->Name;
    //std::cout<<"assigned"<<VN->Name;
    }
    }

    Nres=0;

}
if(VN->mysize==0){
        ntrpy=1;
       VN->Myresult+="Not Determined";
    }
VN->myentropy=ntrpy;
return ntrpy;
}

void Nextatt(Valuenode*parentv)
{
//calculate using the parentv entropy and the entropy of the values of the expanded attribute.
float ntrpy=0;
    float inG=parentv->myentropy;
    float maxinG=0;
    float dsize;
    int index=0;
    std::vector<attributenode*>buff;
    attributenode* pn=0;
    for(int i=0;i<parentv->Posatt.size();i++)
    {   inG=parentv->myentropy;
    //std::cout<<inG;

        for(int j=0;j<parentv->Posatt[i]->MyValues.size();j++)
        {
            dsize=parentv->mysize;
            ntrpy=entropy(parentv->Posatt[i]->MyValues[j]);
            //std::cout<<ntrpy;
            //std::cout<<parentv->Posatt[i]->MyValues[j]->mysize;
            inG-=(parentv->Posatt[i]->MyValues[j]->mysize/dsize)*ntrpy;
        //std::cout<<inG;
        }

        if(inG>maxinG)
            {
            maxinG=inG;
            pn=parentv->Posatt[i];
            index=i;
            }
    buff.push_back(parentv->Posatt[i]);
    }
    buff.erase(buff.begin()+index);
    for(int k=0;k<pn->MyValues.size();k++)
    {
         for(int m =0;m<buff.size();m++)
        {
            if(!buff[m]->MyValues.empty())
            {
            attributenode* r=new attributenode;
            r->Name+=buff[m]->Name;
            r->Myindex=buff[m]->Myindex;
            r->Parentvalue=pn->MyValues[k];
            for(int h=0;h<buff[m]->MyValues.size();h++)
                {
                    if(!buff[m]->MyValues.empty())
                        {
                            Valuenode* q=new Valuenode;
                            q->Name+=buff[m]->MyValues[h]->Name;
                            q->Myattribute=r;
                            r->MyValues.push_back(q);
                        }

                }
            pn->MyValues[k]->Posatt.push_back(r);
            }

        }
    }
    parentv->Nextattribute=pn;
    return ;
}

attributenode* inatt(void)
{
    float ntrpy=0;
    float inG=Intrpy;
    float maxinG=0;
    float dsize;
    int index=0;
    std::vector<attributenode*>buff;
    attributenode* p;
for(int i=0;i<attributes.size();i++)
    {   inG=Intrpy;
        for(int j=0;j<attributes[i]->MyValues.size();j++)
        {
            dsize=Dset.size();
            ntrpy=entropy(attributes[i]->MyValues[j]);
            inG-=(attributes[i]->MyValues[j]->mysize/dsize)*ntrpy;
        }
        if(inG>maxinG)
            {
            maxinG=inG;
            p=attributes[i];
            index=i;
            }
    buff.push_back(attributes[i]);
    }
    buff.erase(buff.begin()+index);
    for(int k=0;k<p->MyValues.size();k++)
    {
        for(int m =0;m<buff.size();m++)
        {
            if(!buff[m]->MyValues.empty())
            {
            attributenode* r=new attributenode;
            r->Name+=buff[m]->Name;
            r->Myindex=buff[m]->Myindex;
            r->Parentvalue=p->MyValues[k];
            //std::cout<<r->Parentvalue->Name;
            for(int h=0;h<buff[m]->MyValues.size();h++)
                {
                    if(!buff[m]->MyValues.empty())
                        {
                            Valuenode* q=new Valuenode;
                            q->Name+=buff[m]->MyValues[h]->Name;
                            q->Myattribute=r;
                            r->MyValues.push_back(q);
                        }

                }
            p->MyValues[k]->Posatt.push_back(r);
            }

        }
    }
    return p;
}


float initentropy(void){
    float Nres=0;
    float ntrpy=0;
    float dsize;
    float p=0;
for(int i=0;i<Fresult->MyValues.size();i++)
{
    for(int j=0;j<Dset.size();j++)
    {
        if(!Fresult->MyValues[i]->Name.compare(Dset[j]->label))
            Nres+=1;
    }

    if(Nres>0)
    {
    dsize=Dset.size();
    p=Nres/dsize;
    ntrpy+=-1*(p)* log2 (p);
    }
    Nres=0;

}
return ntrpy;
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
		while(line[0] == '%')
			std::getline(std::cin, line);
		if(line.find("@relation") != -1){
			std::string relation = line.substr(line.find(" ")+1);
			//std::cout << relation;
			std::getline(std::cin, line);
		}
		if(line.find("@attribute") != -1){
			attributenode* att=new attributenode;
			attributes.push_back(att);
			att->Name.clear();
			std::string buff,buff2;
			buff=line.substr(line.find(" ")+1);
			buff2=buff.substr(0,buff.find(" "));
			if(buff2.find("	")!=-1)
            {
            buff2=buff.substr(0,buff.find("	"));
            }
			//To do
			att->Name+=(buff2);
			//std::cout<<att->Name;
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
    			//std::cout << Van->Name << std::endl;
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
    			//std::cout << Van->Name << std::endl;
    			subline.erase(0, pos2 + delimiter2.length());
            }
			//std::getline(std::cin, line);
		}
		if(line.find("@data") != -1){
            fdata=1;
            //std::getline(std::cin, line);
            }
        else if (fdata==1){
            Data* D1=new Data;
            std::string tokend;
            std::string delimiterd = ",";
            size_t posd = 0;
            while ((posd = line.find(delimiterd)) != std::string::npos) {
    			tokend = line.substr(0, posd);
    			D1->features.push_back(tokend);
    			//std::cout << Van->Name << std::endl;
    			line.erase(0, posd + delimiterd.length());
			}
			D1->label.clear();
			D1->label+=line;
			Dset.push_back(D1);
        }
std::getline(std::cin, line);

}
	}
void solve(attributenode* AN,int spaces)
{
    for(int i=0;i<AN->MyValues.size();i++)
    {   for(int j=0;j<spaces;j++)
        std::cout<<"  ";
        std::cout<<AN->Name<<": "<<AN->MyValues[i]->Name<<std::endl;
        if(!AN->MyValues[i]->Myresult.empty())
        {
            for(int t=0;t<spaces+1;t++)
                std::cout<<"  ";
            std::cout<<"ANSWER: "<<AN->MyValues[i]->Myresult<<std::endl;
        }
        else{
            Nextatt(AN->MyValues[i]);
            solve(AN->MyValues[i]->Nextattribute,spaces+1);
        }
    }
    return;
}

int main(){
    while(!fdata)
    {
	read_data();
    }
    Fresult=attributes[(attributes.size()-1)];
    attributes.pop_back();
    //std::cout<<Dset.size();
    //std::cout<<attributes.size()<<std::endl;
    //std::cout<<attributes[(attributes.size()-1)]->Name<<std::endl;
    //std::cout<<Fresult->Name;
    Intrpy=initentropy();
    //std::cout<<Intrpy;

    Head=inatt();
    //std::cout<<Head->MyValues[0]->myentropy;
    solve(Head,0);

    //Nextatt(Head->MyValues[1]);
    //std::cout<<Head->MyValues[1]->Nextattribute->Name;
    //std::cout<<Head->MyValues[0]->Posatt[0]->MyValues[0]->Myattribute->Parentvalue->Name;

}
