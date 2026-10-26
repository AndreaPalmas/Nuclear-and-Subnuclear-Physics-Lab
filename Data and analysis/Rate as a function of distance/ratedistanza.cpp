#include<iostream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TF1.h>
#include<fstream>
#include<TMath.h>
using namespace std;

int main(){

int N = 8;

double rate[8] = {2780.99, 1061.84, 397.74, 130.10, 81.59, 70.15, 54.48, 38.61}; //conteggi/s
double erate[8] = {14.66, 7.69, 2.75, 1.06, 0.74, 0.70, 0.57, 0.44}; //conteggi/s
//double r[8] = {1.7, 4.7, 11.7, 22.7, 30.7, 33.7, 38.7, 45.7}; //mm
double r[8] = {2,5,12,23,31,34,39,46};
double er[8] = {1, 1, 1, 1, 1, 1, 1};


//G = formula lunga
TCanvas *cgf = new TCanvas("cgf", "rate(r)", 200, 30, 1200, 800);
cgf->SetFillColor(0);
cgf->SetGrid();
cgf->cd();

TGraphErrors *ggf = new TGraphErrors (N, r, rate, er, erate);
ggf->SetMarkerStyle(8);
ggf->SetTitle("rate(r)");
ggf->GetXaxis()->SetTitle("#it{r}[mm]");
ggf->GetYaxis()->SetTitle("#it{rate}[s^{-1}]");


TF1 *f1 = new TF1("f1", "[0]*0.5*(1-(4/TMath::Pi())*TMath::ASin(1/TMath::Sqrt(2+100/(2*TMath::Power(x,2)))))", 0, 10);// [0] è A*efficienza 
f1->SetParameter(0, 9.775);
f1->SetParName(0, "A*E");
f1->SetNpx(5000);
f1->SetLineColor(8);

gStyle->SetOptFit(1);

ggf->Fit(f1);
ggf->Draw("AP");


// G = 1/r2
TCanvas *cgg = new TCanvas("cgg", "rate(r)", 200, 30, 1200, 800);
cgg->SetFillColor(0);
cgg->SetGrid();
cgg->cd();

TGraphErrors *ggg = new TGraphErrors (N, r, rate, er, erate);
ggg->SetMarkerStyle(8);
ggg->SetTitle("rate(r)");
ggg->GetXaxis()->SetTitle("#it{r}[mm]");
ggg->GetYaxis()->SetTitle("#it{rate}[s^{-1}]");


TF1 *f2 = new TF1("f2", "[0]*(100/(4*TMath::Power(x,2)))", 0, 10);// [0] è A*efficienza 
f2->SetParameter(0, 9.775);
f2->SetParName(0, "A*E");
f2->SetNpx(5000);
f2->SetLineColor(8);

gStyle->SetOptFit(1);

ggg->Fit(f2);
ggg->Draw("AP");





return 0;
}
