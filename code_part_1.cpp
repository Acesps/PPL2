#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}

template< typename T>
void display(T a[],int n){
        
        for( int i=0;i<n;i++){
                cout<<a[i]<<"\n\n\n";
        }
        cout<<endl;
}

struct symbol_tabel
{
	string datatype;
	int struct_or_not;
	string variable_name;
	int array_or_not;
	int array_top;
	int declared_with[2];
};
struct symbol_tabel tabel[30];


char testcase[2201];
char all_declaration[20][100];
char structure_defination[10][100];
char function_defination[10][100];
char array_defination[10][100];
int row_count_dec=0;
int row_count_func=0;
int row_count_struct=0;
int row_count_array=0;
int tabel_count = 0; 
vector<string> structures[2];
vector<string> datatypes;

void extracting_all_declarations(int count){

	int p=0;
	int f1=0;
	for(int i=0;i<count;i++){
		if(testcase[i]=='\n' && f1==0){
			continue;
		}
		all_declaration[row_count_dec][p++]=testcase[i];
		if(testcase[i]=='{'){
			f1=1;
		}
		if(testcase[i]=='}'){
			f1=0;
		}
		if(testcase[i]==';' && f1==0){
			row_count_dec++;
			p=0;
		}
	}
}


void removing_definations(){
	int h=0;
	for(int i=0;i<row_count_dec;){
		int n=strlen(all_declaration[i]);
		char typedef_check[8];
		if(all_declaration[i][n-2]=='}' && all_declaration[i][n-1]==';'){
			strcpy(structure_defination[row_count_struct++],all_declaration[i]);
			structures[h].push_back("int");
			structures[h].push_back("string");
			h++;
			for(int k=i;k<row_count_dec-1;k++){
				strcpy(all_declaration[k],all_declaration[k+1]);
			}
			row_count_dec--;
		}
		else if(all_declaration[i][n-1]=='}'){
			strcpy(function_defination[row_count_func++],all_declaration[0]);
			for(int k=i;k<row_count_dec-1;k++){
				strcpy(all_declaration[k],all_declaration[k+1]);
			}
			row_count_dec--;
		}
		else{
			i++;
		}
	}

	for(int i=0;i<row_count_dec;){
		int n = strlen(all_declaration[i]);
		char check[5];
		int m=0;
		for(int k=0;k<n && k<5;k++){
			check[m++]=all_declaration[i][k];
		}
		if(strcmp(check,"array")==0){
			//cout<<all_declaration[i]<<endl;
			strcpy(array_defination[row_count_array++],all_declaration[i]);
			for(int k=i;k<row_count_dec-1;k++){
				strcpy(all_declaration[k],all_declaration[k+1]);
			}
			row_count_dec--;
		}
		else{
			i++;
		}
	}
}

void create_from_defination(){
	for(int i=0;i<row_count_dec;i++){
		int len = strlen(all_declaration[i]),p=0;		
		char data[10];
		int j;
		for(j=0;j<strlen(all_declaration[i]);j++){
			//cout<<data<<" ";
			if(all_declaration[i][j]==' ' && strcmp(data,"typedef")== 0){
				j++;
				p=0;
			}
			if(all_declaration[i][j]==' ' && strcmp(data,"struct")!= 0){
				//p=0;				
				break;
			}
			data[p++]=all_declaration[i][j];
			data[p]='\0';
		}
		data[p]='\0';
		p=0;
		//cout<<data<<" "<<j<<endl;
		int variable_count=1;
		for(int k=j+1;k<len;k++){
			if(all_declaration[i][k]==','){
				variable_count++;
			}
		}
		//cout<<variable_count<<endl;
		char variable[variable_count][10];
		int m=0,q=0;
		for(int k=j+1;k<len;k++){
			if(all_declaration[i][k]==',' || all_declaration[i][k]==';'){
				variable[m][q]='\0';
				m++;
				q=0;
				continue;
			}
			variable[m][q]=all_declaration[i][k];
			q++;
		}
		/*for(int k=0;k<variable_count;k++){
			cout<<variable[k]<<" "<<strlen(variable[k])<<endl;
		}*/
		char tmp[7];
		for(int k=0;k<6 && k<strlen(data);k++){
			tmp[k]=data[k];
		}
		tmp[6]='\0';
		//cout<<data<<" "<<strlen(data)<<endl;
		int tabel_count_initial=tabel_count;
		for(int k=0;k<variable_count;k++){
			tabel[tabel_count].datatype=data;
			tabel[tabel_count].variable_name=variable[k];
			//cout<<tabel[tabel_count].datatype<<"##"<<endl;
			if(strcmp(tmp,"struct")==0){
				tabel[tabel_count].struct_or_not = 1;	
			}
			else{
				tabel[tabel_count].struct_or_not = 0;
			}
			
			tabel[tabel_count].array_or_not = 0;
			tabel[tabel_count].array_top=-1;
			tabel[tabel_count].declared_with[0]=tabel_count_initial;
			tabel[tabel_count].declared_with[1]=tabel_count_initial+variable_count;
			tabel_count++;
			auto it = find (myvector.begin(), myvector.end(), 30);
  			if (it == myvector.end())
 				datatypes.push_back(data);
	}
}
void create_from_array_defination(){
	for(int i=0;i<row_count_array;i++){
		//cout<<array_defination[i]<<endl;
		int len=strlen(array_defination[i]);
		char data[10];
		int j,p = 0;
		for(j=0;j<strlen(array_defination[i]);j++){
			if(array_defination[i][j]==' '){
				break;
			}
			data[p++]=array_defination[i][j];
			data[p]='\0';
		}
		data[p]='\0';
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]=='('){
				j=k;
				break;
			}
		}
		if(j==p){
			tabel[tabel_count].datatype="array<int>";
			tabel[tabel_count].variable_name="^s";
			//cout<<tabel[tabel_count].datatype<<"##"<<endl;
			tabel[tabel_count].struct_or_not=0;
			tabel[tabel_count].array_or_not = 1;
			tabel[tabel_count].array_top = 3;
			tabel[tabel_count].declared_with[0]=tabel_count-1;
			tabel[tabel_count].declared_with[1]=tabel_count-1;
			tabel_count++;
			break;
		}
		char num1[5];//,num2[5];
		int z=0;
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]==')'){
				j=k;
				break;
			}
			num1[z++]=array_defination[i][k];
		}
		num1[z]='\0';
		z=0;
		int up_limit = stoi(num1);
		//cout<<up_limit<<" "<<low_limit<<endl;
		int variable_count=1;
		
		//cout<<variable_count<<endl;
		char variable[variable_count][10];
		int m=0,q=0;
		for(int k=12;k<len && m<1;k++){
			if(array_defination[i][k]==' '){
				continue;
			}
			if(array_defination[i][k]=='='){
				variable[m][q]='\0';
				m++;
				q=0;
				continue;
			}
			variable[m][q]=array_defination[i][k];
			q++;
		}
		/*for(int k=0;k<variable_count;k++){
			cout<<variable[k]<<" "<<strlen(variable[k])<<endl;
		}*/
		int tabel_count_initial=tabel_count;
		for(int k=0;k<variable_count;k++){
			tabel[tabel_count].datatype=data;
			tabel[tabel_count].variable_name=variable[k];
			//cout<<tabel[tabel_count].datatype<<"##"<<endl;
			tabel[tabel_count].struct_or_not=0;
			tabel[tabel_count].array_or_not = 1;
			tabel[tabel_count].array_top = up_limit;
			tabel[tabel_count].declared_with[0]=tabel_count_initial;
			tabel[tabel_count].declared_with[1]=tabel_count_initial+variable_count;
			tabel_count++;
			auto it = find (myvector.begin(), myvector.end(), 30);
  			if (it == myvector.end())
 				datatypes.push_back(data);

		}
	}
}
void create_symbol_tabel(){
	create_from_defination();
	create_from_array_defination();
}
int check_name_equvalence(string str1,string str2){
	int index1,index2;
	for(int i=0;i<tabel_count;i++){
		if(str1==tabel[i].variable_name){
			index1=i;
		}
		if(str2==tabel[i].variable_name){
			index2=i;
		}
	}
	if(tabel[index1].array_or_not==1  || tabel[index2].array_or_not==1){
		return 0;
	}
	if(tabel[index1].datatype==tabel[index2].datatype){
		return 1;
	}
	return 0;
}
void name_equvalence(string str1,string str2){
	if(check_name_equvalence(str1,str2)==0){
		cout<<"False "<<str1<<" and "<<str2<<" are not Name Equivalent"<<endl;
	}
	else{
		cout<<"True "<<str1<<" and "<<str2<<" are Name Equivalent"<<endl;
	}
}
int check_internalname_equvalence(string str1,string str2){
	int index1,index2;
	
	for(int i=0;i<tabel_count;i++){
		if(str1==tabel[i].variable_name){
			index1=i;
		}
		if(str2==tabel[i].variable_name){
			index2=i;
		}
	}
	
	if(tabel[index1].datatype==tabel[index2].datatype){
		return 1;
	}
	
	if(tabel[index1].array_or_not==1  && tabel[index2].array_or_not==1){
		if(tabel[index1].declared_with[0]<=index2&&tabel[index1].declared_with[1]>=index2)
			return 1;
		if(tabel[index2].declared_with[0]<=index1&&tabel[index2].declared_with[1]>=index1)
			return 1;
	}
	
	return 0;
}

void internalname_equivalence(string str1,string str2){
	if(check_internalname_equvalence(str1,str2)==0){
		cout<<"False "<<str1<<" and "<<str2<<" are not Internal Name Equivalent"<<endl;
	}
	else{
		cout<<"True "<<str1<<" and "<<str2<<" are Internal Name Equivalent"<<endl;
	}
}

void print_symboltabel(){
	for(int i=0;i<tabel_count;i++){
		cout<<tabel[i].datatype<<"    "<<tabel[i].variable_name
		<<"    "<<tabel[i].struct_or_not<<"    "<<tabel[i].array_or_not
		<<"    "<<tabel[i].array_top
		<<"    "<<endl; 
	}
}
void print_definations(){
	for(int i=0;i<row_count_dec;i++){
		cout<<i<<" "<<all_declaration[i]<<endl;
	}
	cout<<"##"<<endl;
	for(int i=0;i<row_count_struct;i++){
		cout<<i<<" "<<structure_defination[i]<<endl;
	}
	cout<<"##"<<endl;
	for(int i=0;i<row_count_func;i++){
		cout<<i<<" "<<function_defination[i]<<endl;
	}
	cout<<"##"<<endl;
	for(int i=0;i<row_count_array;i++){
		cout<<i<<" "<<array_defination[i]<<endl;
	}
}

void structural_equivalence(vector<vector<bool> > &truth_table){
	int flag=1;
	while(flag){
		flag=0;
		for(int i=0;i<tabel_count;i++){
			for(int j=i+1;j<tabel_count;j++)
				if(truth_table[i][j]){	
					if(tabel[i].array_or_not==1 && tabel[j].array_or_not==1)
					{
						if(tabel[i].array_top==tabel[j].array_top){
							continue;
						}
					}
					else if(tabel[i].datatype==tabel[j].datatype){
						continue;
					}
					else if(tabel[i].struct_or_not==1 && tabel[j].struct_or_not==1){
						for(int k=0;k<structures[0].size() && k < structures[1].size();k++){
							if(structures[0][k]!=structures[1][k]){
								truth_table[i][j]=false;
								truth_table[j][i]=false;
								flag=1;
							}
						}
						continue;				
					}
					int index1=0,index2=0;
					int flag2=0;
					for(int k=0;k<tabel_count;k++){
						if(tabel[i].datatype==tabel[k].variable_name){
							index1=k;
							flag2++;
						}
						if(tabel[j].datatype==tabel[k].variable_name){
							index2=k;
							flag2++;
						}
					}

					if(flag2==2 && tabel[index2].datatype==tabel[index1].datatype){
						continue;
					}
					truth_table[i][j]=false;
					truth_table[j][i]=false;
					flag=1;
			}
		}
	}	
}

int main(){
	FILE *fp,*gp;
	fp = fopen("Test_case.txt","r+");
	if(fp == NULL){
		printf("File not found\n");
		return 0;
	}
	else{
		char a1,a2;
		int count=0,i;
		//reading file 
		while(a1!=EOF){
			a1=fgetc(fp);
			testcase[count++]=a1;
		}
		fclose(fp);
		//removing EOF cahar from testcase
		count--;
		testcase[count]='\0';

		//cout<<testcase;
		extracting_all_declarations(count);
		removing_definations();
		//print_definations();
		//display(all_declaration,row_count_dec);
		create_symbol_tabel();
		//print_symboltabel();
		vector<vector<bool> >truth_table(datatypes,vector<bool>(tabel_count,true) );
		structural_equivalence(truth_table);
		FILE *f;
	    size_t nwritten;

	    f = fopen("./output/Symbol_table","wb");

	    if (f == NULL)
	    {
	      fprintf(stderr, "Cannot open file for writing.\n");
	      exit(1);
	    }

	    nwritten = fwrite((void *)tabel, sizeof tabel, 1, f);
	    fclose(f);

	    if (nwritten < 1)
	    {
	      fprintf(stderr, "Writing to file failed.\n");
	      exit(1);
	    }
	    FILE *f2;
	    size_t nwritten2;

	    f2 = fopen("./output/Symbol_table","wb");

	    if (f2 == NULL)
	    {
	      fprintf(stderr, "Cannot open file for writing.\n");
	      exit(1);
	    }

	    nwritten2 = fwrite(truth_table, sizeof tabel, 1, f2);
	    fclose(f2);

	    if (nwritten < 1)
	    {
	      fprintf(stderr, "Writing to file failed.\n");
	      exit(1);
	    }



		string one,two;
		cout<<truth_table;
		cout<<"Enter Variables to be checked:\n";
		cin>>one>>two;
		name_equvalence(one,two);
		internalname_equivalence(one,two);
	}
	return 0;
}