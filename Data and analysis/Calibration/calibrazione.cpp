#include<iostream>
#include<TGraph.h>
#include<TF1.h>
#include<TCanvas.h>


using namespace std;

void calibrazione(){

const int n=3;

float E []= {5.157,5.486,5.805}; // Mev - Ordine:  Pu-Am-Cm
float Err_E[]={0,0,0};

float picchi[]= {1025,1091,1155};
float FWHM[]= {4,4,4}; // potrebbe essere 3 -> sovrastimati
float Err_picchi[n];
for(int i=0;i<3;i++){
    Err_picchi[i]=FWHM[i]/2.355;
};

TGraphErrors *cgf= new TGraphErrors(n, picchi, E, Err_picchi,Err_E);
cgf->SetTitle("Calibrazione");
cgf->SetMarkerStyle(8);
cgf->SetMarkerSize(0.8);
cgf->GetXaxis()->SetTitle("#it{CHN}");
cgf->GetYaxis()->SetTitle("#it{E} [Mev]");


TCanvas *c1= new TCanvas("cgf", "Calibrazione",200,30,1200,800);
c1->SetFillColor(0);
c1->SetGrid();
c1->cd();

TF1 *fit = new TF1("fit", "[0]*(x-1100)+[1]",800, 1300); // fit traslato con 1100 nuova origine
fit->SetParameter(0,0.005);
fit->SetParameter(1,1091);
fit->SetLineColor(8);
fit->SetLineWidth(2);
fit->SetParNames("a", "b");
gStyle->SetOptFit(1);
cgf->Fit("fit","RM+");

cgf->Draw("AP");

TFitResultPtr fitresults=cgf->Fit(fit,"MS");
cout<<endl<<"Chi^2"<<fit->GetChisquare()<<endl;
    
cout<<endl<<"Errori:"<<endl;

for(int i=0;i<3;i++){
cout<< Err_picchi[i]<<endl;
}

/////////////////////////////////////////////////////////////////////////
int x0=1100;

float b= fit->GetParameter(1);
float Err_b= fit->GetParError(1);
//float b=B-a*x0;

float a= fit->GetParameter(0);
float Err_a= fit->GetParError(0);

int CHN_2[]={1015,1083, 1146, 1072}; // tre picchi secondari + picco terziario
float FWHM_2[]={4,2,4,2};
float Err_CHN_2[4];
for(int i=0;i<4;i++){
    Err_CHN_2[i]=FWHM_2[i]/2.355;
}

float E_1[3];
float Err_E_1[3];
cout<<endl<<"Energie primarie:"<<endl;
for(int i=0;i<3;i++){
    E_1[i]=a*(picchi[i]-x0)+b;
    Err_E_1[i]= sqrt(pow((picchi[i]-x0)*Err_a,2)+pow(Err_b,2)+pow(a*Err_picchi[i],2));
cout<<E_1[i]<<"  +-  "<< Err_E_1[i]<<endl;
}

float E_2[4];
float Err_E_2[4];
float E_2_teo[] = {5.106, 5.443, 5.763, 5.388};
float Z[4];

cout<<endl<<"Energie:"<<endl;
for(int i=0;i<4;i++){
    E_2[i]=a*(CHN_2[i]-x0)+b;
    Err_E_2[i]= sqrt(pow((CHN_2[i]-x0)*Err_a,2)+pow(Err_b,2)+pow(a*Err_CHN_2[i],2));
    Z[i] = (E_2[i]-E_2_teo[i])/Err_E_2[i];
cout<<E_2[i]<<"  +-  "<< Err_E_2[i]<< "\t Test Z: " << Z[i] <<endl;
}



cout<<endl<<"dE per 1 chn:"<< a<<endl; //Risoluzione di energia per 1 canale -> il picco secondario di Pb è accorpato al primo, quello misurato dunque è il terziario.


}
