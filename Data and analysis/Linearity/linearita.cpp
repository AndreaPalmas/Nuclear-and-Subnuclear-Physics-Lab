#include<iostream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TF1.h>
#include<fstream>
#include<cmath>
using namespace std;

int linearita(){

int N = 10;

float Va[] = {1.16, 1.97, 3.06, 4.12, 5.08, 6.19, 7.41, 8.11, 9.08, 9.69}; //V
float errVa[] = {0.035, 0.075, 0.045, 0.085, 0.085, 0.07, 0.1255, 0.105, 0.135, 0.13}; //V
float CHN[] = {244, 399, 617, 835, 1021, 1239, 1519, 1645, 1863, 1985}; //chn
float errCHN[] = {2.5, 2.52, 2.44, 2.6, 2.53, 2.57, 2.45, 2.53, 2.57, 2.67}; // chn
float Vt[] = {-51.2, -85, -131, -175, -217, -260, -320, -343, -392, -416}; //mV
float errVt[] = {2.55, 2.25, 2.5, 5.5, 6, 7.5, 8, 8.5, 8.5, 8}; //mV

TCanvas *cgf = new TCanvas("cgf", "Va(Vt)", 200, 30, 1200, 800);
cgf->SetFillColor(0);
cgf->SetGrid();
cgf->cd();

TGraphErrors *ggf = new TGraphErrors (N, Vt, Va, errVt, errVa);
ggf->SetMarkerStyle(8);
ggf->SetTitle("Va(Vt)");
ggf->GetXaxis()->SetTitle("#it{Vt}[mV]");
ggf->GetYaxis()->SetTitle("#it{Va}[V]");


TF1* f1 = new TF1("f1", "[0]*x + [1]", 0, 10); 
f1->SetParameter(0,-0.025);
f1->SetParameter(1,0);
f1->SetParNames("a", "b");
f1->SetNpx(5000);
f1->SetLineColor(8);

gStyle->SetOptFit(1);

ggf->Fit(f1);
ggf->Draw("AP");

TCanvas *cgg = new TCanvas("cgg", "CHN(Vt)", 200, 30, 1200, 800);
cgg->SetFillColor(0);
cgg->SetGrid();
cgg->cd();

TGraphErrors *ggg = new TGraphErrors (N, Vt, CHN, errVt, errCHN);
ggg->SetMarkerStyle(8);
ggg->SetTitle("CHN(Vt)");
ggg->GetXaxis()->SetTitle("#it{Vt}[mV]");
ggg->GetYaxis()->SetTitle("#it{CHN}");


TF1* f2 = new TF1("f2", "[0]*x + [1]", 0, 10); 
f2->SetParameter(0,-5);
f2->SetParameter(1,0);
f2->SetParNames("a", "b");
f2->SetNpx(5000);
f2->SetLineColor(8);

gStyle->SetOptFit(1);

ggg->Fit(f2);
ggg->Draw("AP");



return 0;
}
