#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int	tabel_count;

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

template < typename T>
ostream& operator <<(ostream& o,vector<T> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<a[i]<<" ";
	}
	o<<"\n";
	return o;
}

void print_symboltabel(){
	for(int i=0;i<tabel_count;i++){
		cout<<tabel[i].datatype<<"    "<<tabel[i].variable_name
		<<"    "<<tabel[i].struct_or_not<<"    "<<tabel[i].array_or_not
		<<"    "<<tabel[i].array_top
		<<"    "<<endl; 
	}
}



int main(){
	char* datatypes;
	long lSize;
	FILE *f3;
	size_t nwritten3;


	f3 = fopen("./output/datatypes","rb");

	if (f3 == NULL)
    {
      fprintf(stderr, "Cannot open file for writing.\n");
      exit(1);
    }
    
   	// obtain file size:
    fseek (f3 , 0 , SEEK_END);
  	lSize = ftell (f3);
  	rewind (f3);
  	datatypes = (char*) malloc (sizeof(char)*lSize);

  	
  	//datatypes.resize(lSize);
  	//cout<<datatypes.size();
    nwritten3 = fread(&datatypes,sizeof(datatypes), lSize, f3);
    fclose(f3);
    cout<<nwritten3;
    if (nwritten3 < 1)
    {
      fprintf(stderr, "reading to file failed.\n");
      exit(1);
    }
    cout<<datatypes;
	exit(1);
	/*vector<vector<bool> >truth_table(datatypes.size(),vector<bool>(datatypes.size(),true) );
	FILE *f;
    size_t nwritten;

    f = fopen("./output/Symbol_table","rb");

    if (f == NULL)
    {
      fprintf(stderr, "Cannot open file for writing.\n");
      exit(1);
    }

    nwritten = fread(tabel, sizeof tabel, 1, f);
    fclose(f);

    /*if (nwritten < 1)
    {
      fprintf(stderr, "Writing to file failed.\n");
      exit(1);
    }
    FILE *f2;
    size_t nwritten2;

    f2 = fopen("./output/truth_table","rb");

    if (f2 == NULL)
    {
      fprintf(stderr, "Cannot open file for writing.\n");
      exit(1);
    }

    nwritten2 = fread(&truth_table, sizeof tabel, 1, f2);
    fclose(f2);

    /*if (nwritten < 1)
    {
      fprintf(stderr, "Writing to file failed.\n");
      exit(1);
    }
    tabel_count=sizeof(tabel)/sizeof(symbol_tabel);
    cout<<truth_table;
    */print_symboltabel();
	return 0;
}