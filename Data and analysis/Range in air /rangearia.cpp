#include<iostream>
#include<TGraph.h>
#include<TF1.h>
#include<TCanvas.h>


using namespace std;

int rangearia(){

//Dati della calibrazione
float a = 4.98461e-3;
float b = 5.53085;
float erra = 9.20992e-5;
float errb = 4.96852e-3;
float x0 = 1100;

//Energia CHN 17
float CHNsoglia = 17;
float Esoglia;

cout << "Energia soglia (CHN 17): " << endl;
Esoglia = a*(CHNsoglia-x0)+b;
cout << Esoglia << endl;

//diagramma rate in funzione di p
float N = 13;
float p[13]= {0, 203.5, 402.5, 554.5, 652.5, 754.5, 806, 823.5, 827, 833, 836.5, 840.5, 846.5}; //mbar
float ep[13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float rate[13] = {38.1, 37.3, 38.2, 38.0, 36.7, 36.4, 32.8, 26.4, 22.5, 15.8, 9.8, 5.1, 1.5}; //conteggi/s
float erate[13] = {0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.4, 0.4, 0.3, 0.2, 0.1};

TCanvas *cgf = new TCanvas("cgf", "rate(p)", 200, 30, 1200, 800);
cgf->SetFillColor(0);
cgf->SetGrid();
cgf->cd();

TGraphErrors *ggf = new TGraphErrors (N, p, rate, ep, erate);
ggf->SetMarkerStyle(8);
ggf->SetTitle("rate(p)");
ggf->GetXaxis()->SetTitle("#it{p}[mbar]");
ggf->GetYaxis()->SetTitle("#it{rate}[s^{-1}]");

TF1 *f3 = new TF1("f3", "[0]*x + [1]", 0, 700);
f3->SetRange(0.,700.);
f3->SetParameters(0 , 40);
f3->SetParNames("a", "b");
f3->SetNpx(5000);
f3->SetLineColor(8);

gStyle->SetOptFit(1);

ggf->Fit(f3, "R");
ggf->Draw("AP");

//troviamo p 1/2
//array con pochi punti per fit
float n = 3;
float p1[3]= {823.5, 827, 833}; //mbar
float ep1[3] = {1, 1, 1};
float rate1[3] = {26.4, 22.5, 15.8}; //conteggi/s
float erate1[3] = {0.5, 0.4, 0.4};

TCanvas *cgg = new TCanvas("cgg", "p(rate)", 200, 30, 1200, 800);
cgg->SetFillColor(0);
cgg->SetGrid();
cgg->cd();

TGraphErrors *ggg = new TGraphErrors (n, rate1, p1, erate1, ep1);
ggg->SetMarkerStyle(8);
ggg->SetTitle("p(rate)");
ggg->GetXaxis()->SetTitle("#it{rate}[s^{-1}]");
ggg->GetYaxis()->SetTitle("#it{p}[mbar]");


TF1 *f1 = new TF1("f1", "[0]*(x-19) + [1]", 0, 10);
f1->SetParameters(-0.5 , 840);
f1->SetParNames("a", "b");
f1->SetNpx(5000);
f1->SetLineColor(8);

gStyle->SetOptFit(1);

ggg->Fit(f1);
ggg->Draw("AP");

int n2=5;
float p2[5]={0, 203.5, 402.5, 554.5, 652.5};
float ep2[5]={1,1,1,1,1};
float rate2[5]={38.1, 37.3, 38.2, 38.0, 36.7};
float erate2[5]={0.6, 0.6, 0.6, 0.6, 0.6};
/*
//non serve se lo mettiamo nel grafico con tutto in teoria (con il fit, hanno gli stessi risultati)
//media rate massimo
TCanvas *ccc = new TCanvas("ccc", "rate(p)", 200, 30, 1200, 800);
ccc->SetFillColor(0);
ccc->SetGrid();
ccc->cd();

TGraphErrors *cgc = new TGraphErrors (n2, p2, rate2, ep2, erate2);
cgc->SetMarkerStyle(8);
cgc->SetTitle("rate(p)");
cgc->GetXaxis()->SetTitle("#it{p}[mbar}]");
cgc->GetYaxis()->SetTitle("#it{rate}[s^{-1}]");


TF1 *f2 = new TF1("f2", "[0]*x + [1]", 0, 10);
f2->SetParameters(0 , 40);
f2->SetParNames("a", "b");
f2->SetNpx(5000);
f2->SetLineColor(8);

gStyle->SetOptFit(1);

cgc->Fit(f2);
cgc->Draw("AP");
*/

//supponiamo p 1/2
float ratemezzo = 38.0/2;
float eratemezzo = 0.5;
float c = f1->GetParameter(0); 
float errc = f1 -> GetParError(0);
float e = f1->GetParameter(1);
float erre = f1 -> GetParError(1);
float pmezzo = c*(ratemezzo-19) + e;
float errpmezzo = sqrt(pow(ratemezzo*errc, 2)+pow(c*eratemezzo, 2)+pow(erre, 2));

//distanza equivalente
float Pst = 1013.25; //mbar
float Tst = 20 + 273.15; //kelvin
float T = 21.3 + 273.15; //kelvin
float errT = 0.1;
float d = 4.87; //cm
float errd = 0.1;
float da = 1.205e-3; //g/cm^3

float deq = d * (pmezzo/Pst) * (Tst/T)*da; //g/cm^2
float errdeq = deq *sqrt(pow(errd/d, 2)+pow(errpmezzo/pmezzo, 2)+pow(errT/T, 2));

cout << "la distanza equivalente è " << deq << " +- " << errdeq << " g/cm^2" << endl;

//range in aria
float Rres = 1.94e-4; // corrisponde a 0.13 MeV
float R = deq + Rres;
float errR = errdeq;

cout << "il range in aria è " << R << " +- " << errR << " g/cm^2" <<endl;

//test Z
float Z = (R -  5.028e-3)/errR;
cout << "Test Z: " << endl;
cout << "Z = " << Z << endl;



return 0;
}
