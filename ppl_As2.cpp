#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
struct symbol_tabel
{
	char datatype[10];
	int struct_or_not;
	char variable_name[10];
	int array_or_not;
	int array_top,array_bottom;
	int function_or_not;
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
	for(int i=0;i<row_count_dec;){
		int n=strlen(all_declaration[i]);
		if(all_declaration[i][n-2]=='}' && all_declaration[i][n-1]==';'){
			strcpy(structure_defination[row_count_struct++],all_declaration[i]);
			for(int k=i;k<row_count_dec-1;k++){
				strcpy(all_declaration[k],all_declaration[k+1]);
			}
			row_count_dec--;
		}
		else if(all_declaration[i][n-1]=='}'){
			strcpy(function_defination[row_count_func++],all_declaration[ 0]);
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
		int n = strlen(all_declaration[i]),j;
		for(j=0;j<n;j++){
			if(all_declaration[i][j]==' '){
				break;
			}
		}
		char check[5];
		int m=0;
		for(int k=j+1;k<n && k<j+6;k++){
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
		char tmp[6];
		for(int k=0;k<6 && k<strlen(data);k++){
			tmp[k]=data[k];
		}
		//cout<<data<<" "<<strlen(data)<<endl;
		for(int k=0;k<variable_count;k++){
			strcpy(tabel[tabel_count].datatype,data);
			strcpy(tabel[tabel_count].variable_name,variable[k]);
			//cout<<tabel[tabel_count].datatype<<"##"<<endl;
			if(strcmp(tmp,"struct")==0){
				tabel[tabel_count].struct_or_not = 1;	
			}
			else{
				tabel[tabel_count].struct_or_not = 0;
			}
			
			tabel[tabel_count].array_or_not = 0;
			tabel[tabel_count].array_top=-1;
			tabel[tabel_count].array_bottom = -1;
			tabel[tabel_count].function_or_not = 0;
			tabel_count++;
		}

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
			if(array_defination[i][k]=='['){
				j=k;
				break;
			}
		}
		char num1[5],num2[5];
		int z=0;
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]=='-'){
				j=k;
				break;
			}
			num1[z++]=array_defination[i][k];
		}
		num1[z]='\0';
		z=0;
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]==']'){
				j=k;
				break;
			}
			num2[z++]=array_defination[i][k];
		}
		num2[z]='\0';
		int up_limit = stoi(num1);
		int low_limit = stoi(num2);
		//cout<<up_limit<<" "<<low_limit<<endl;
		int variable_count=1;
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]==','){
				variable_count++;
			}
		}
		//cout<<variable_count<<endl;
		char variable[variable_count][10];
		int m=0,q=0;
		for(int k=j+1;k<len;k++){
			if(array_defination[i][k]==' '){
				continue;
			}
			if(array_defination[i][k]==',' || array_defination[i][k]==';'){
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
		for(int k=0;k<variable_count;k++){
			strcpy(tabel[tabel_count].datatype,data);
			strcpy(tabel[tabel_count].variable_name,variable[k]);
			//cout<<tabel[tabel_count].datatype<<"##"<<endl;
			tabel[tabel_count].struct_or_not=0;
			tabel[tabel_count].array_or_not = 1;
			tabel[tabel_count].array_top = up_limit;
			tabel[tabel_count].array_bottom = low_limit;
			tabel[tabel_count].function_or_not = 0;
			tabel_count++;
		}
	}
}
void create_symbol_tabel(){
	create_from_defination();
	create_from_array_defination();
}
int check_name_equvalence(char* str1,char *str2){
	int index1,index2;
	for(int i=0;i<tabel_count;i++){
		if(strcmp(str1,tabel[i].variable_name)==0){
			index1=i;
		}
		if(strcmp(str2,tabel[i].variable_name)==0){
			index2=i;
		}
	}
	if(tabel[index1].array_or_not==1  || tabel[index2].array_or_not==1){
		return 0;
	}
	if(strcmp(tabel[index1].datatype,tabel[index2].datatype)==0){
		return 1;
	}
	return 0;
}
void name_equvalence(char *str1,char *str2){
	if(check_name_equvalence(str1,str2)==0){
		cout<<"False "<<str1<<" and "<<str2<<" are not Name Equivalent"<<endl;
	}
	else{
		cout<<"True "<<str1<<" and "<<str2<<" are Name Equivalent"<<endl;
	}
}
int is_present(char *str1,char *arr){
	
}
int check_internalname_equvalence(char *str1,char *str2){
	int x = check_name_equvalence(str1,str2);
	if(x==0){
		return 0;
	}
	else{
		for(int i=0;i<row_count_dec;i++){
			if(is_present(str1,all_declaration[i])==1 && is_present(str2,all_declaration[i])==1){
				return 1;
			}
		}
		return 0;
	}
}

void internalname_equivalence(char *str1,char *str2){
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
		<<"    "<<tabel[i].array_top<<"    "<<tabel[i].array_bottom
		<<"    "<<tabel[i].function_or_not<<endl; 
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

int main(){
	FILE *fp,*gp;
	fp = fopen("Test_case.txt","r+");
	gp = fopen("Test_case.txt","r+");
	if(fp == NULL || gp == NULL){
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
		print_definations();
		create_symbol_tabel();
		print_symboltabel();
		char one[10],two[10];
		cout<<"Enter Variables to be checked:\n";
		cin>>one>>two;
		name_equvalence(one,two);
		internalname_equivalence(one,two);
	}
	return 0;
}