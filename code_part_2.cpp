#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int no_of_struct;
int countDatatypes;
template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	o<<"\n";
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}

int main(){
		FILE *fp;
		fp = fopen("./output/Symbol_table","r");
		if (fp == NULL)
	    {
	      fprintf(stderr, "Cannot open file for reading.\n");
	      exit(1);
	    }
		/*for(int i=0;i<tabel_count;i++){
			string str= ""+to_string(tabel[i].struct_or_not)+"@"+to_string(tabel[i].declared_with[0])+"@"+to_string(tabel[i].declared_with[1])+"@"+to_string(tabel[i].array_top)+"@"+tabel[i].variable_name+"@"+to_string(tabel[i].array_or_not)+"@"+tabel[i].datatype+"\n\0";
		
			for(int j=0;j<str.size();j++){
				fputc(str[j],fp);
			}
		}*/
		vector<string> testcase;
		char a1;
	    int i;
		//reading file 
		no_of_struct=0;
		string s;
		while(a1!=EOF){
			a1=fgetc(fp);
			if(a1=='\n'){
				no_of_struct++;
				testcase.push_back(s);
				s.clear();
			}
			s+=a1;
		}
		fclose(fp);
	
		vector<string> variables,datatype,set_datatype; 
		//for data type
		for(int i=0;i< testcase.size();i++){
			int j;
			for(j=testcase[i].size(); j>0;j--){
				if(testcase[i][j] == '@'){
					break;
				}
			}
			datatype.push_back(testcase[i].substr(j+1));
			int flag=1;
			for(int k=0;k<set_datatype.size();k++){
				if(datatype.back() == set_datatype[k]){
					flag=0;
					break;
				}
			}
			if(flag){
				set_datatype.push_back(datatype.back());
			}


			//moving to next char
			j--;
			for(;j>0;j--){
				if(testcase[i][j] == '@'){
					break;
				}
			}
			int k=j;
			j--;
			for(;j>0;j--){
				if(testcase[i][j] == '@'){
					break;
				}				
			}
			variables.push_back(testcase[i].substr(j+1,k-j-1));
		}
	
	
		// reading table truth_table from file
		fp = fopen("./output/truth_table","r");
		if (fp == NULL)
	    {
	      fprintf(stderr, "Cannot open file for reading.\n");
	      exit(1);
	    }
	    vector<vector<bool > > truth_table;
		vector<bool> v;
		//reading file 
		countDatatypes=0;
		a1='c';
		while(a1!=EOF){
			a1=fgetc(fp);
			if(a1=='\n'){
				countDatatypes++;
				truth_table.push_back(v);
				v.clear();
				continue;
			}
			v.push_back(a1-'0');
			a1=fgetc(fp);
		}
		fclose(fp);
	
		
		// reading table name_truth-table
		fp = fopen("./output/name_truth_table","r");
		if (fp == NULL)
	    {
	      fprintf(stderr, "Cannot open file for reading.\n");
	      exit(1);
	    }
	    vector<vector<bool > > name_truth_table;
	    v.clear();
		//reading file 
		a1='c';
		while(a1!=EOF){
			a1=fgetc(fp);
			if(a1=='\n'){
				name_truth_table.push_back(v);
				v.clear();
				continue;
			}
			v.push_back(a1-'0');
			a1=fgetc(fp);
		}
		fclose(fp);
	
		
		// reading table internal_truth-table
		fp = fopen("./output/internal_truth_table","r");
		if (fp == NULL)
	    {
	      fprintf(stderr, "Cannot open file for reading.\n");
	      exit(1);
	    }
	    vector<vector<bool > > internal_truth_table;
		v.clear();
		//reading file 
		a1='c';
		while(a1!=EOF){
			a1=fgetc(fp);
			if(a1=='\n'){
				internal_truth_table.push_back(v);
				v.clear();
				continue;
			}
			v.push_back(a1-'0');
			a1=fgetc(fp);
		}
		fclose(fp);
	
		// main UI

		while(1){																	//UI for user
			cout<<"Please enter two variables names:\n";
			string var1,var2;
			cin.clear();
			cin>>var1>>var2;
			
			int index1 = find(variables.begin(),variables.end(),var1) - variables.begin();
			int index2 = find(variables.begin(),variables.end(),var2) - variables.begin();
			if(index1 == no_of_struct || index2 == no_of_struct){
				cout<<"variables not found\n";
				goto exit;
			}

			if(datatype[index1].substr(0,min(6,(int)datatype[index1].size())) == "struct" && datatype[index2].substr(0,min(6,(int)datatype[index2].size())) == "struct")
				{	int i = find(set_datatype.begin(),set_datatype.end(),datatype[index1]) - set_datatype.begin();
					int j = find(set_datatype.begin(),set_datatype.end(),datatype[index2]) - set_datatype.begin();
					int flag = 0;
					if(i < countDatatypes && j < countDatatypes)
						 flag = truth_table[i][j];
cout<<(flag?"True":"False")<<", as "<<var1<<","<<var2<<" are"<<(flag?"":" not")<<" structurally equivalent\n";					
				}
			else {
				int flag = name_truth_table[index1][index2];
cout<<(flag?"True":"False")<<", as "<<var1<<","<<var2<<" are"<<(flag?"":" not")<<" name equivalent\n";					
			}
	exit:	cout<<"Do you want to continue ";
			char c;
			cin.clear();
			cin>>c;
		    if(c=='n'||c=='N') return 0;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}	
	return 0;
}