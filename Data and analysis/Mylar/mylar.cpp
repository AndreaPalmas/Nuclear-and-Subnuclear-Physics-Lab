#include<iostream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TF1.h>



using namespace std;


void mylar(){
    double E[] = {4.00,4.50,5.00,5.50}; // [Mev]
    double dEdx[] = {948.5,875.9,814.3,762.0}; //[Mev*cm^2/g]

    TCanvas *c1= new TCanvas("c1","Mylar",200,30,1200,800);
    c1->SetFillColor(0);
    c1->SetGrid();
    c1->cd();

    TGraph*gr1 =new TGraph(4,E,dEdx);
    gr1->SetTitle("#frac{dE}{dX} [E]");
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerSize(0.8);
    gr1->GetXaxis()->SetTitle("#it{E} [MeV]");
    gr1->GetYaxis()->SetTitle("#it{#frac{dE}{dX}} [MeV*cm^{2}/g]");

    TF1 *fit= new TF1("fit", "[0]+[1]*x+[2]*pow(x,2)");
    fit->SetLineColor(8);
    fit->SetLineWidth(2);
    fit->SetParNames("a","b","c");
    gStyle->SetOptFit(1);
    gr1->Fit("fit");
    gr1->Draw("AP");


    double a= fit->GetParameter(0);
    double Err_a= fit-> GetParError(0);
    double b= fit->GetParameter(1);
    double Err_b= fit->GetParError(1);
    double c= fit->GetParameter(2);
    double Err_c= fit-> GetParError(2);

    double Spessore[]={0,0.9,1.4,2.8,4.2,5.1};
    double Err_spessore[]={0,0.05,0.07,0.2,0.4,0.5};
    double Spessoredeltap[]={0,0.9+0.05,1.4+0.07,2.8+0.2,4.2+0.4,5.1+0.5}; //spessore piu delta spessore
    double Spessoredeltam[]={0, 0.9-0.05,1.4-0.07,2.8-0.2,4.2-0.4,5.1-0.5}; //spessore meno delta spessore
   
    double p=1.39; //densità

    for(int i=0;i<6;i++){
        Spessore[i]=Spessore[i] * pow(10,-4)*p;
        Err_spessore[i]=Err_spessore[i] * pow(10,-4)*p ;
        Spessoredeltam[i]=Spessoredeltam[i]*pow(10,-4)*p;
        Spessoredeltap[i]=Spessoredeltap[i]*pow(10,-4)*p;

    };

    //Numero di cicli n
    double n= 1000;
    double E_cycle[6][1000];  
    double Err_E_cycle[6];
    double E_cyclep[6][1000];
    double E_cyclem[6][1000];

    for(int i=0; i<6; i++){
        E_cycle[i][0]=5.486; // Valore nominale e non quello misurato
        E_cyclep[i][0]=5.486;
        E_cyclem[i][0]=5.486;
    }
    

    cout<<"Energie integrazione numerica:"<<endl;
    double dx[6];
    double dxm[6];
    double dxp[6];

    for(int i=0;i<6;i++){
        dx[i]=Spessore[i]/n;
        dxm[i]=Spessoredeltam[i]/n;
        dxp[i]=Spessoredeltap[i]/n;

        for(int j=0;j<n-1;j++){
            E_cycle[i][j+1]= E_cycle[i][j]-(a+b*E_cycle[i][j]+c*pow(E_cycle[i][j],2))*dx[i];
            E_cyclep[i][j+1]= E_cyclep[i][j]-(a+b*E_cyclep[i][j]+c*pow(E_cyclep[i][j],2))*dxp[i];
            E_cyclem[i][j+1]= E_cyclem[i][j]-(a+b*E_cyclem[i][j]+c*pow(E_cyclem[i][j],2))*dxm[i];
        }
        Err_E_cycle[i]=(E_cyclem[i][999]-E_cyclep[i][999])/2;

        cout<<E_cycle[i][999]<<"\t";
        cout<<E_cyclep[i][999]<<"\t";
        cout<<E_cyclem[i][999]<<"\t";
        cout<<Err_E_cycle[i]<<endl;
      
    }

    double x0=1100;

    double ac=4.98461e-3; //parametri calibrazione
    double bc=5.53085;
    double errac=9.20991e-5;
    double errbc=4.96852e-3;

    double CHN[6]={1091,1071,1059,1028,996,973};
    double errCHN[6]={2,6,8,8,10,14};

    double ECHN[6];
    double ErrECHN[6];
    double Z[6];

    cout<<endl<<"Energie misurate:"<<endl;
    for(int i=0;i<6;i++){
        ECHN[i]=ac*(CHN[i]-x0)+bc;
        ErrECHN[i]= sqrt(pow((CHN[i]-x0)*errac,2)+pow(errbc,2)+pow(ac*errCHN[i],2));

        // TEST Z
        Z[i]=(E_cycle[i][999]-ECHN[i])/(hypot(Err_E_cycle[i],ErrECHN[i]));

        cout<<ECHN[i]<<"  +-  "<< ErrECHN[i]<< "  ;  Test Z = "<<Z[i]<<endl;

    }


}
