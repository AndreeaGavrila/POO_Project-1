#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class NrComplex
{
private:
  double re,im;
public:
  NrComplex(){ re=0; im=0; }
  ~NrComplex(){}

  double get_real(NrComplex a);
  double get_imaginar(NrComplex a);

  void set_real(double d);
  void set_imaginar(double d);

  void afisare();

  friend istream & operator >>(istream & in, NrComplex &a);
  friend ostream & operator <<(ostream & out,const NrComplex a);

  double modul_complex(NrComplex a);

  NrComplex operator=(NrComplex a);

  bool operator ==(NrComplex a);
  bool operator <(NrComplex a);
  bool operator !=(NrComplex a);

  NrComplex operator+(NrComplex a);
  NrComplex operator*(NrComplex a);

  NrComplex suma_complex(NrComplex a,NrComplex b);
  NrComplex produs_complex(NrComplex a,NrComplex b);

  friend class VectorNrComplexe;
};

double NrComplex::get_real(NrComplex a) {   return a.re; }
double NrComplex::get_imaginar(NrComplex a) {   return a.im; }

void NrComplex::set_real(double d) { re=d; }
void NrComplex::set_imaginar(double d) { im=d; }

void NrComplex::afisare() { cout<<re<<" + "<<im<<"*i"; }



istream & operator >>(istream & in, NrComplex &a)
{
  in>>a.re>>a.im;
  return in;
}
ostream & operator <<(ostream & out,const NrComplex a)
{
  out<<a.re<<" + "<<a.im<<"*i\n";
  return out;
}



double NrComplex::modul_complex(NrComplex a)
{
   double r;
   r=sqrt(a.re*a.re+a.im*a.im);
   return r;
}


NrComplex NrComplex:: operator=(NrComplex a)
{
  re=a.re;
  im=a.im;
  return (*this);
}

bool NrComplex:: operator==(NrComplex a) { return (a.re==re && a.im==im); }
bool NrComplex:: operator<(NrComplex a)  { return (sqrt(re*re+im*im)<modul_complex(a)); }
bool NrComplex::operator!=(NrComplex a)  { return (a.re!=re || a.im!=im); }



NrComplex NrComplex::operator+(NrComplex a)
{
   NrComplex c;
   c.set_real(0);
   c.set_imaginar(0);
   c.re=re+get_real(a);
   c.im=im+get_imaginar(a);
   return c;
}

NrComplex NrComplex::operator*(NrComplex a)// const
{
   NrComplex c;
 ///(a+b*i)(c+d*i) = ac + ad*i + bc*i - bd = (ac-bd) + (ad+bc)*i
   c.re=get_real(a)*re-get_imaginar(a)*im; // c.real=(a c - b d)
   c.im=get_real(a)*im+get_imaginar(a)*re; // c.imag=(a d + b c)

   return c;
}

NrComplex suma_complex(NrComplex a,NrComplex b)      { a=a+b;  return a; }
NrComplex produs_complex(NrComplex a,NrComplex b)    { a=a*b;  return a; }

/*--------------------------------------------------------------------------------------------*/

class VectorNrComplexe
{
   private:
    int nrcomponente;
    NrComplex *a;

   public:

       NrComplex get_pozitie(int i);
       int get_nrcomponente();

       void set_pozitie(NrComplex t,int i);
       void set_nrcomponente(int n);


    VectorNrComplexe() {  nrcomponente=0;  a=NULL; }
    // constructor pentru initializarea cu un numar dat pe toate componentele
    // (primeste ca parametru numarul respectiv si numarul componentelor);

    ~VectorNrComplexe() { delete[] a; } //destructor

   friend double modul_complex(NrComplex a);

    //supraincarcarea operatorilor << și >> sa utilizeze supraincarea acestora în cadrul clasei Numar_Complex;
   friend istream & operator >>(istream & in, VectorNrComplexe &v);
   friend ostream & operator <<(ostream & out,const VectorNrComplexe v);

    void citire();

   void SortareDupaModule();

   NrComplex SumaVectorNrComplexe();
   NrComplex ProdusScalarVectori(VectorNrComplexe v,VectorNrComplexe t,VectorNrComplexe sol);

   NrComplex & operator[](int i);
};


NrComplex VectorNrComplexe::get_pozitie(int i) { return a[i]; }
int VectorNrComplexe::get_nrcomponente() { return nrcomponente; }

void VectorNrComplexe::set_pozitie(NrComplex t,int i) { a[i]=t; }
void VectorNrComplexe::set_nrcomponente(int n) { nrcomponente=n; }


istream & operator >>(istream & in, VectorNrComplexe &v)
{
   in>>v.nrcomponente;
   v.a=new NrComplex[v.nrcomponente];
   for(int i=0;i<v.nrcomponente;i++)
   {
       in>>v.a[i];
   }
   return in;
}


ostream & operator <<(ostream & out,const VectorNrComplexe v)
{
  for(int i=0;i<v.nrcomponente;i++)
  {
      out<<v.a[i];
  }
  return out;
}


void VectorNrComplexe::citire()
{
    cout<<"numarul componentelor vectorului= ";
    cin>>nrcomponente;
    cout<<"elementele vectorului: ";
    a=new NrComplex[nrcomponente];
    for(int i=0;i<nrcomponente;i++)
    {
        cin>>a[i];
    }
}


void VectorNrComplexe::SortareDupaModule() { int i,j;  sort(a,a+nrcomponente); }

NrComplex VectorNrComplexe::SumaVectorNrComplexe()
{
   NrComplex s,t;
   s.set_real(0);
   s.set_imaginar(0);
   int i;
   for(i=0;i<nrcomponente;i++)
   {
      s=s+a[i];
   }
   return s;
}

NrComplex VectorNrComplexe::ProdusScalarVectori(VectorNrComplexe v,VectorNrComplexe t,VectorNrComplexe sol)
{
   NrComplex s;
   int i,j,k=0;
//   cout<<"v=";  cin>>v;
//   cout<<"t=";  cin>>t;
    v.citire();
    t.citire();

   sol.a=new NrComplex[t.get_nrcomponente()];

   for(i=0;i<v.get_nrcomponente();i++)
   {
       cout<<"v.a["<<i<<"]= "<<v.a[i];
       cout<<"t.a["<<i<<"]= "<<t.a[i]<<"\n";

       cout<<"v.a["<<i<<"]*t.a["<<i<<"]= "<<v.a[i]*t.a[i]<<"\n";

       sol.a[k] = sol.a[k] + v.a[i]*t.a[i];
       k++;
   }


   for(i=0;i<v.get_nrcomponente();i++)
       { s=s+sol.a[i]; }

   cout<<"Rezultatul Produsului Scalar pentru cei doi vectori: ";

   return s;
}

NrComplex & VectorNrComplexe :: operator[](int i)
{
   if(i>=0 && i<nrcomponente)
   {
      get_pozitie(i);
   }

}


int main()
{

    //Testarea clasei NrComplex:

    //   NrComplex a,b;
    //   cout<<"a= ";  cin>>a;
    //   cout<<"b= ";  cin>>b;
    //   cout<<"a+b= "<<a+b;
    //   cout<<"a*b= "<<a*b;


   int i;
   VectorNrComplexe vect,v,t,sol;

   cout<<"Introduceti vectorul pentru care doriti sa se aplice Suma, respectiv Sortarea dupa module:\n\n";

    vect.citire();

//   cout<<"vect= ";  cin>>vect;

   for(i=0;i<vect.get_nrcomponente();i++)
   {
       cout<<"vect.["<<i<<"]= "<<vect.get_pozitie(i);
   }

   cout<<"Suma vectorului vect este: "<<vect.SumaVectorNrComplexe()<<'\n';

   cout<<"Vectorul vect sortat dupa module: \n";
   vect.SortareDupaModule();
   cout<<vect;


   cout<<'\n';
   cout<<"Introduceti vectorii pentru care doriti sa se aplice Produsul Scalar:\n";

   cout<<sol.ProdusScalarVectori(v,t,sol);

   return 0;
}
