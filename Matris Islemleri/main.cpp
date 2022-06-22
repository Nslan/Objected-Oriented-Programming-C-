#include<iostream>
#include<vector>
#include<cstdlib>//srand ve rand islemleri
#include<ctime>
#include<cmath> 
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

template<typename Tip> class Matris{
	
	protected:
		unsigned satir;
		unsigned sutun;
		vector< vector <double> > vct;
		
	public:
		//Constructorlar
		Matris(unsigned , unsigned , const Tip&);
		Matris();
		
		//matris islemleri
		Matris operator +(const Matris& nesne);
		Matris operator -(const Matris& nesne);
		Matris operator *(const Matris& nesne);
		
		Matris T();
		Matris resize(const int , const int );
		Matris emul(const Matris &nesne);
		 
		
		void det();
		int determinant( const Matris &nesne , int n);
		void inv();
		
		
		//skaler islemler
		Matris operator +(const Tip&);
		Matris operator -(const Tip&);
		Matris operator *(const Tip&);
		Matris operator /(const Tip&);
		Matris operator %(const Tip&);
		Matris operator ^(const Tip&);
		
		void print() const;
		Matris print( const char *FileName);
		
		~Matris(){
			satir = 0 ;
			sutun = 0 ;
		};
};


//Matris sinifindan Turetýlmýs Table
template<typename Tip> class Table : public Matris<Tip>{
	
	private:
		int t_satir;
		int t_sutun;
		
		vector<string> satirNames;
		vector<string> sutunNames;
		
	public:
	
		Table();
		Table(int r  , int c , const Tip&  );
		void MakeTable(int r , int c);
		int  itemAt(int r , int c);
		int itemAt(string s);
		int  itemAt(string rs , string cs);
		void setRowNames(string s[],int n);
		void setColNames(string s[],int n);
		void print();
		~Table(){
			t_satir = 0 ;
			t_sutun = 0 ;
			
		}
		
};

template<typename Tip> Table<Tip>::Table(){ 
		int t_satir=10;
		int t_sutun=10;
		
		this->vct.resize(t_satir);
	
		for(int i = 0 ; i<this->vct.size() ; i++){
			this->vct[i].resize(t_sutun , 0);
		}
		
		MakeTable(t_satir , t_sutun);
}

template<typename Tip> Table<Tip>::Table(int r ,int c ,const Tip& value){

	t_satir = r ;
	t_sutun = c ;
	
	this->vct.resize(t_satir);
	
	if( value == 'r'){
		
		srand(time(0));
		
		for(int i=0 ; i<t_satir ; i++){
		
			this->vct[i].resize(t_sutun,0);
		
			for(int j=0; j<t_sutun;j++){
				
					this->vct[i][j]=rand() % (255 - 0 + 1 ) + 0;
				
				
			}
	    
		}
	    
	}
	else{
		for(int i=0 ; i<t_satir ; i++){
		
			this->vct[i].resize(t_sutun,0);
		
			for(int j=0; j<t_sutun;j++){
				
					this->vct[i][j]=value;
				
				
			}
	    
		}
	}	
	MakeTable(t_satir,t_sutun);		
}
//table olustur
template<typename Tip> void Table<Tip>::MakeTable(int r, int c){
	satirNames.resize(r);//satirisimlerini t_satir boyu kadr genislet
	sutunNames.resize(c);//sutunisimlerini t_sutun boyu kadar genislet

	for (int i = 0; i < satirNames.size(); i++)
	{
		satirNames[i] = to_string(i);//sayilari stringe cevirerek satir isimleri 
	}

	char kr = 'A';
	for (int i = 0; i < sutunNames.size(); i++)
	{
		string sutunAd;
		sutunAd.clear();
		sutunAd.push_back(kr);
		sutunNames[i] = sutunAd;
		kr++;
	}	
}
//table da [rxc] indisindeki degeri dondurur
template<typename Tip> int Table<Tip>::itemAt(int r , int c){
			t_satir = r ;
			t_sutun = c ;
			
			int d;
			
			d=this->vct[t_satir][t_sutun];
			
			return d;			
}
//table dan belirtilen hücredeki deðeri geri döndür. eðer s==”A2” ise [2,0] indisindeki deðeri geri döndür demektir
template<typename Tip> int Table<Tip>::itemAt(string s){
	
			int value;
			char x = s[1] ;
	
			value = atoi(&x);
			char k='A';
				
					for(int i=0 ;i<sutunNames.size();i++){
				
						if( s[0] == k){
							value = itemAt(value , i);
							return value;
						}
						k++;
					}
					
}
template<typename Tip> int Table<Tip>::itemAt(string rs , string cs){
			  
			  int value, v1 , d;
			  
			  for(int i=0;i<satirNames.size();i++){
					if(rs == satirNames[i]){
						value = i ;
					}
				 
			 }
			 
			 
			 for(int i=0;i<sutunNames.size();i++){
					if( cs == sutunNames[i]){
						v1 = i ;
					}
				 
			}
			
			d = itemAt(value,v1);
			return d;
}

template<typename Tip>  void Table<Tip>::setRowNames(string s[] , int n){
	 	
	 	for(int i=0;i<n;i++){
	 	 	satirNames[i].resize(8);
	 	 	satirNames[i]=s[i];
		  }
		  
	 	
}

template<typename Tip> void Table<Tip>::setColNames(string s[] , int n){
	
			for(int i=0;i<n;i++){
	 	 		sutunNames[i].resize(8);
	 		 	sutunNames[i]=s[i];
		  }	
	
}

//table print
template<typename Tip> void Table<Tip>::print(){
	
	char bosluk = ' ';
	for (int i = 0; i < 10; i++)
	{
		cout << bosluk;
	}
	for (auto t_sutun : sutunNames)
	{
		cout << setw(5) << right << t_sutun;
	}
	cout << endl;
	for (int i = 0; i < this->vct.size(); i++)
	{
		cout << setw(9) << right << satirNames[i];
		for (int j = 0; j < this->vct[0].size(); j++)
		{
			cout << setw(5) << right << this->vct[i][j];
		}
		cout << endl;
	}
}

// m x n lik girilen degerli matris olusturan parametreli constructur
template<typename Tip> Matris<Tip>::Matris(unsigned  satir , unsigned sutun , const Tip& value){
	
	this->satir = satir ;
	this->sutun = sutun ;
	
	vct.resize(satir);
	
	if(value == 'e'){
		
		for(int i=0 ; i<satir ; i++){	
		
			vct[i].resize(sutun , 0);
		
			for(int j=0; j<sutun;j++){
		
				if(i==j){
		
					vct[i][j]=1;
				}
				
			}
			
	    }
	}
	if(value == 'r'){
		
		srand(time(0));
		
		for(int i=0 ; i<satir ; i++){
		
			vct[i].resize(sutun,0);//yazýmý duzgun olsun diye 3 rakamlý yaptým
		
			for(int j=0; j<sutun;j++){
				
					vct[i][j]=rand() % (255 - 0 + 1 ) + 0;
				
				
			}
	    
		}
	    
	    
	    
	    
	}
	if(value == 'L'){
		
		int k = 1 ;
		for(int i=0 ; i<satir ; i++){
			vct[i].resize(sutun,0);
			for(int j=0; j<sutun;j++){
				
						
				vct[i][j]=k;
				k++;
			}
	    
		}
	    
	    
	    
	    
	}
	else{
		
		for(int i=0 ; i<satir ; i++){
		
			vct[i].resize(sutun , value);
	    
		}
	}
}

// 10 x 10 luk 0 matrisi olusturan parametresiz constructur
template<typename Tip> Matris<Tip>::Matris(){
	
	this->satir = 10 ;
	this->sutun = 10 ;
	
	vct.resize(this->satir);
	
	for(int i = 0 ; i<vct.size() ; i++){
		vct[i].resize(sutun , 0);
	}
}


// iki matrisin toplanabilmesi icin ayni satir sutun uzunluguna sahip olmalilar!
template<typename Tip> Matris<Tip> Matris<Tip>::operator +(const Matris &nesne){
		
		if(satir==nesne.satir && sutun == nesne.sutun){
			for(unsigned i = 0 ; i<this->satir ; i++){
				for(unsigned j = 0 ; j<this->sutun ; j++){
					this->vct[i][j] = this->vct[i][j] + nesne.vct[i][j];
				}
			}
		
		return *this;
		}
		else{
		
			Matris a(0,0,0);
			cout<<"Matrislerin satir sutun sayilari ayni olmalidir! ";
			return a;
		}	
}

// iki matrisin cikarilabilmesi icin ayni satir sutun uzunluguna sahip olmalilar!
template<typename Tip> Matris<Tip> Matris<Tip>::operator -(const Matris &nesne){
	
		if(satir==nesne.satir && sutun == nesne.sutun){
			
			for(unsigned i = 0 ; i<this->satir ; i++){
				for(unsigned j = 0 ; j<this->sutun ; j++){
					this->vct[i][j] = this->vct[i][j] - nesne.vct[i][j];
				}
			}
		
		return *this;
		}
		else{
		
			Matris a(0,0,0);
			cout<<"Matrislerin satir sutun sayilari ayni olmalidir! ";
			return a;
		}
}

//  ( m x n ) * ( n x r ) =  m x r lik matris olusturur , birincinin sutunu ile ikincinin satiri esit olmali
template<typename Tip> Matris<Tip> Matris<Tip>::operator *(const Matris &nesne){
		
	   if(sutun==nesne.satir){
	   	
		Matris carp(satir , nesne.sutun , 0);
		
		for(int i = 0 ; i<satir ; i++){
			
			for(int j = 0 ; j<nesne.sutun ; j++){
				
				 	//carp.vct[i][j]=0; // buna gerek yok ama dursun
				 	
					for(int k = 0 ; k<sutun ; k++){
					
							carp.vct[i][j] += this->vct[i][k] * nesne.vct[k][j];
					
					}
				
			}
			

		}
	    
			return carp;
		
	   }
	   
	   else{
	   	 	Matris a(0,0,0);
			cout<<"Matrislerin satir sutun sayilari ayni olmalidir! ";
			return a;
	   }
	   	
		
}


//skaler toplama islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator +(const Tip& value){
	
	
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			this->vct[i][j] +=value; 		
		}
	}
	
	
	return *this;
}

//skaler cikarma islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator -(const Tip& value){
		
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			this->vct[i][j] -=value; 		
		}
	}
	
	
	return *this;
}


//skaler carpma islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator *(const Tip& value){
		
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			this->vct[i][j] *=value; 		
		}
	}
	
	return *this;
}

//skaler bolme islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator /(const Tip& value){
		
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			this->vct[i][j] /=value; 		
		}
	}
	
	
	return *this;
}	

//skaler mod islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator %(const Tip& value){
	
	int dizi[satir][sutun];
	
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			
			dizi[i][j] = this->vct[i][j]; 		
			dizi[i][j] = dizi[i][j]% value; 	
			this->vct[i][j]=dizi[i][j];	
		}
	}
	
	
	return *this;
}

//skaler us alma islemi
template<typename Tip> Matris<Tip> Matris<Tip>::operator ^(const Tip& value){
		
	for(unsigned i = 0 ; i<satir ; i++){
		for(unsigned j = 0 ; j<sutun ; j++){
			this->vct[i][j] = pow(this->vct[i][j],value); 		
		}
	}
	
	
	return *this;
}

//transpoze
template<typename Tip> Matris<Tip> Matris<Tip>::T(){
	
	Matris tr(sutun,satir,0);
	
	for(unsigned i = 0 ; i<sutun ; i++ ){
		for(unsigned j = 0 ; j<satir ; j++){
			tr.vct[i][j]=this->vct[j][i];		
		}
	}
	
	return tr;
	
}

template<typename Tip> Matris<Tip> Matris<Tip>::resize(const int satir , const int sutun ){
		
		this->satir = satir ;
		this->sutun = sutun ;
		
		vct.resize(satir);
		
		for(int i =0 ; i<vct.size() ; i++){
			
			vct[i].resize( sutun );
			
		}
		
		return *this;
		
}

//eleman duseyinde carpma islemi
template<typename Tip> Matris<Tip> Matris<Tip>::emul(const Matris &nesne){
	
	
	
 	if(satir<=nesne.satir && sutun<=nesne.sutun){
 	
	 	Matris ematris(satir, sutun , 1);
	 	for(unsigned i = 0 ; i<satir ; i++ ){
	
			for(unsigned j = 0 ; j<sutun ; j++){
			
				ematris.vct[i][j]=this->vct[i][j] * nesne.vct[i][j]; 	
		
			}
	
		}
	
		return ematris;
	 }
	 else if(satir>nesne.satir && sutun>nesne.sutun){
	 	
		Matris ematris(nesne.satir, nesne.sutun , 1); 
		 	
	 	for(unsigned i = 0 ; i<nesne.satir ; i++ ){
	
			for(unsigned j = 0 ; j<nesne.sutun ; j++){
			
				ematris.vct[i][j]=this->vct[i][j] * nesne.vct[i][j]; 	
		
			}
	
		}
	
		return ematris;
	 	
	 }
	 else if(satir<=nesne.satir && sutun>nesne.sutun){
	 	
	 	Matris ematris(satir, nesne.sutun , 1);
	 	
		 for(unsigned i = 0 ; i<satir ; i++ ){
	
			for(unsigned j = 0 ; j<nesne.sutun ; j++){
			
				ematris.vct[i][j]=this->vct[i][j] * nesne.vct[i][j]; 	
		
			}
	
		}	
	
		return ematris;
	 }
	 else if(satir>nesne.satir && sutun<nesne.sutun){
	 	
	 	Matris ematris(nesne.satir, sutun , 1);
	 	
	 	for(unsigned i = 0 ; i<nesne.satir ; i++ ){
	
			for(unsigned j = 0 ; j<sutun ; j++){
			
				ematris.vct[i][j]=this->vct[i][j] * nesne.vct[i][j]; 	
		
			}
	
		}
		return ematris; 	
	 }
	
	
}

//determinant kontrol islemleri kare olmak zorunda
template<typename Tip> void Matris<Tip>::det(){
		
	int toplam ;
	
	Matris dizi(satir,sutun,0);
	
	for(int i=0;i<satir;i++){
		
		for(int j=0;j<sutun;j++){
			
			dizi.vct[i][j] = this->vct[i][j];
			
		}
	}
	
	if(satir != sutun){//
		
		cout<<" Determinanti yok!";
	}
	else {

		toplam = determinant(dizi,satir);
	  	cout<<" Determinant :"<<toplam;
	}
	
	  
}

//determinanýtýný hesaplama
template<typename Tip> int Matris<Tip>::determinant(const Matris &nesne,int n)
{
 int det = 0;
   Matris submatrix(satir,sutun,0);
   
   if (n == 2)
      return (( nesne.vct[0][0] * nesne.vct[1][1]) - ( nesne.vct[1][0] * nesne.vct[0][1]));
   else {
      for (int x = 0; x < n; x++) {
            int subi = 0; 
            for (int i = 1; i < n; i++) {
               int subj = 0;
               for (int j = 0; j < n; j++) {
                  if (j == x)
                   continue;
                  submatrix.vct[subi][subj] = nesne.vct[i][j];
                  subj++;
               }
               subi++;
            }
            det = det + (pow(-1, x) * nesne.vct[0][x] * determinant( submatrix, n - 1 ));
      }
   }
   return det;
}

//matrisin tersini alma //Bir matrisin tersi, matrisin kendisi ile çarpýldýðýna birim matrisi veren matristir.
template<typename Tip> void Matris<Tip>::inv(){
	float d,k;
	Matris birim(satir,sutun,0);
	Matris nesne(satir,sutun,0);
	
	for( int i=0;i<satir;i++){
		for(int j=0;j<sutun;j++){
			nesne.vct[i][j]=this->vct[i][j];
			if(i==j){
				birim.vct[i][j]=1;
			}
		}
	}
	
	if( determinant(nesne , satir) != 0 ){
		
		for( int i=0;i<satir;i++){
		
		d=nesne.vct[i][i];
		
		for(int j=0;j<sutun;j++){
		
				nesne.vct[i][j]=nesne.vct[i][j] / d ;
	
				birim.vct[i][j]= birim.vct[i][j] / d ; 
			
		}
		
		for( int x=0;x<satir;x++){
			
			if(x!=i){
				k=nesne.vct[x][i];
			}
			for(int j=0;j<sutun;j++){
				
				nesne.vct[x][j] = nesne.vct[x][j] - ( nesne.vct[i][j] * k ) ;
	
				birim.vct[x][j] = birim.vct[x][j] - (birim.vct[i][j] * k ); 
				
			}
				
		}
	}
	
	for(int i =0;i<satir;i++){
		for(int j=0;j<sutun;j++){
			cout<<"   "<<birim.vct[i][j];
		}
		cout<<endl;
	}
		
	}
	else{
		cout<<"Determinant 0 sa matrisin tersi olmaz!";
	}
		
}


//dosyaya yazma
template<typename Tip> Matris<Tip> Matris<Tip>::print(const char *FileName){

	ofstream file(FileName); 
         
    if (file.is_open())
    {
       for(int i=0;i<satir;i++){
		
		for(int j=0;j<sutun;j++){
			
			file<<this->vct[i][j]<<"\t";
			
		}
		file<<endl;
		
	}
	
	file.close();
    }
    else
    {
        cout << " Dosya acilamadi! ";
    }
    
    
   
}

//matrisi ekrana yaz
template<typename Tip> void Matris<Tip>::print() const{
		
		for(int i=0 ; i<this->satir ; i++){
		
			for(int j=0 ; j<this->sutun ; j++){
				cout<<vct[i][j]<<" ";
			}
			cout<<endl;
		}
		
		cout<<endl;
}


int main(){
	
	Matris<double> a(2,3,1);
	
	/*
	Matris<double> a(2,3,1.);
	a.print();
	Matris<double> b(2,3,9.);
	b.print();
	
	a=b + a*1;
	//a.print("file.txt");
	
	
	Matris<double> m(2,2,'e');
	Matris<double> m1(2,2,'r');
	
	m = m * m1 ;
	
	m.print();
	
	Matris<double> m3(2,2,'L');
	m3.print();

	Matris<double> m4(2,2,0) ;
	m3.inv();
	//m4.print();
	*/
	
	// m ler pointer ise
	
	
	/*
	Matris<int> *m = new Matris<int>(2,8,5);
	Matris<int> *m1 = new Matris<int>(2,3,9);
	Matris<int> *m2 = new Matris<int>(4,1,'e');
	Matris<int> *m3 = new Matris<int>(2,2,'r');
	Matris<int> *m4 = new Matris<int>();

	(*m1) = (*m1 ) - 2; // pointer skaler islemler bu sekilde tanýmlayarak yapýlýr *,/,+,^,%,-
	m1->print(); 
	
	(*m1) = (*m1 ) - (*m);// pointer matris islemleri bu sekilde + , * , -
	m1->print();
	
	(*m)=(*m).emul(*m2);//  pointer emul
	m->print();
	
	m->~Matris();
	delete m;
	*/
	
	
	// m ler nesne ise
	
	
	/*Matris<int> m(10,10,5); 
	Matris<int> m1(2,5,9);
	Matris<int> m2(3,8,'e');
	Matris<int> m3(2,2,'r');
	Matris<int> m4;
	
	m1 = m1  - 2; // nesne skaler islemler bu sekilde tanýmlayarak yapýlýr *,/,+,^,%,-
	m1.print(); 
	
	m1 = m1 - m;// nesne matris islemleri bu sekilde + , * , -
	m1.print();
	
	
	
	m=m.emul(m2);   //nesne emul
	m.print();
	
	
	m3.print();
	m3=m3.T();
	m3.print();
	cout<<endl;
	m3.det();
	cout<<endl;*/
	
	/*
	Table<int> t1(4,4,'r');
	t1.print();
	string s[] = {"sat1","sat2"};
	t1.setRowNames(s,2);
	t1.print();
	
	
	cout<<t1.itemAt(1,1);
	cout<<t1.itemAt("A2")<<endl;
	
	string s1[]={"S1","S2","S3"};
	t1.setColNames(s1,3);
	t1.print();
	cout<<t1.itemAt("1","S2");*/
		/*Table<int> *t = new Table<int>(3,2,2); 
		Table<int> *t1 = new Table<int>(5,4,'r');
		t->print();
		
		t->itemAt(2,1);
		
		
	
	 	Table<int> tb(3,2,2);
		 tb.print();
		Table<int> tbl(5,4,'r');
		cout<<tbl.itemAt(2,2)<<endl;
		Table<int> tbl2(5,4,'r');
		tbl2.print();
		Table<int> tb2(5,4,'r');
		cout<<tb2.itemAt("A1")<<endl;
		cout<<Table<int>(5,4,'r').itemAt("2","C")<<endl;
	 	
	 	cout<<endl<<endl;
	 	
	 	string s[] = {"0. satýr","1. satýr","2. satýr"};
		Table<int> tb3(5,4,'r');
		tb3.setRowNames(s,3);
	 	cout<<tb3.itemAt("2. satýr","D");*/
	 
		 return 0 ; 

}
