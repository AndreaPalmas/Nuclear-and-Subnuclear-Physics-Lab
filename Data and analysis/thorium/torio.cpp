#include<iostream>
#include<TGraph.h>
#include<TF1.h>
#include<TCanvas.h>
//#include<TMath.h>


using namespace std;

int torio(){

//Dati della calibrazione
float a = 4.98461e-3;
float b = 5.53085;
float erra = 9.20992e-5;
float errb = 4.96852e-3;
float x0 = 1100;

//Energie picchi Torio
float CHNT[7] = {1744, 1345, 1248, 1208, 1128, 1076, 795};
float err_CHNT[]={8,7,5,7,5,10,8}; // 
float ET[7];
float err_ET[7];

cout <<endl<< "Energie picchi torio: " << endl;
for(int i=0; i<7; i++){
	ET[i] = a*(CHNT[i]-x0)+b;
	err_ET[i]= sqrt(pow((CHNT[i]-x0)*erra,2)+pow(errb,2)+pow(a*err_CHNT[i],2));
	cout << ET[i] << "+-"<<err_ET[i]<<endl;
}


float MPb = 207.97665*931.49409; //MeV
float MHe = 3728.40; //MeV
float MH = 938.78304; //Mev
float Mn = 939.56541; // Mev 

bool type_1[]={false, true};
bool type_2[]={true,false};
bool type_3[]={false,true,true,true,true,false, false,true};
//bool type_alfa[]={

float M_1[] = {MPb, 0, 0};  // 1 in piu perche il bismuto si arriva con due percorsi diversi
float err_M_1[3];
err_M_1[0]=0;
float M_2[] = {MPb, 0, 0};  // 1 in piu perche il bismuto si arriva con due percorsi diversi
float err_M_2[3];
err_M_2[0]=0;
float M_3[]={0,0,0,0,0,0,0,0,0};
float err_M_3[9];


float Q_1[] = {5.001,0}; //MeV
float Q_2[] = { 0, 2.254}; //MeV
float Q_3[] = {0.5738, 0, 0, 0, 0, 2.127, 0.0459, 0}; //MeV

float A_1[]= {208,208,212};
float A_2[]={208,208,212};
float A_3[]= {212,212,216,220,224,228,228,228,232};

float Edec_1[]={0,ET[3]};
float err_Edec_1[]={0, err_ET[3]};
float Edec_2[]={ET[0],0};
float err_Edec_2[]={err_ET[0],0};
float Edec_3[] = {0,ET[1],ET[2],ET[4],ET[5],0,0,ET[6]};
float err_Edec_3[] = {0,err_ET[1],err_ET[2],err_ET[4],err_ET[5],0,0,err_ET[6]};


float err_Q_1[3];
float err_Q_2[3];
float err_Q_3[8];

cout<<endl<<"Q value dei decadimenti alfa:"<<endl;
for(int i=0; i<2; i++){
	if (Q_1[i] == 0){
	Q_1[i] = Edec_1[i]*(1+4/(A_1[i]-4));
	err_Q_1[i]= err_Edec_1[i]*(1+4/(A_1[i]-4));

	cout<<Q_1[i]<<"+-"<<err_Q_1[i]<<endl;
	}
	
	if(Q_2[i]==0){
		Q_2[i] = Edec_2[i]*(1+4/(A_2[i]-4));
		err_Q_2[i]= err_Edec_2[i]*(1+4/(A_2[i]-4));
		cout<<Q_2[i]<<"+-"<<err_Q_2[i]<<endl;
	}
}


for(int i=0; i<8;i++){
	if(type_3[i]){ // NON AVEVO MESSO QUESTO IF: ECCO L'ERRORE! NOTA CHE E' LA STESSA COSA DI SCRIVERE IF Q_3[i]==0 -> essenzialmente stavo sovrascrivendo suoi posti di beta i qvalue che avevo inserito a priori perche l'if, non essendoci, non faceva le modifiche solo per alfa come avrebbe dovuto fare.
		Q_3[i] = Edec_3[i]*(1+4/(A_3[i]-4));
	err_Q_3[i]= err_Edec_3[i]*(1+4/(A_3[i]-4));
		cout<<Q_3[i]<<"+-"<<err_Q_3[i]<<endl;
	}

}




cout<<endl<<"Massa percorso 1 \t Massa percorso 2: "<<endl;
cout << std::setprecision(5) << std::fixed;

for(int i=0;i<2;i++){
	if(type_1[i]){
		M_1[i+1]=Q_1[i]+M_1[i]+MHe; 
		err_M_1[i+1]=sqrt(pow(err_Q_1[i],2)+pow(err_M_1[i],2));

	}else{
		M_1[i+1]=Q_1[i]+M_1[i];
		err_M_1[i+1]=err_M_1[i];   // qui l'errore e' uguale a quello della massa precedente perche c'e' decadimento B

	}


	if(type_2[i]){
		M_2[i+1]=Q_2[i]+M_2[i]+MHe;
		err_M_2[i+1]=sqrt(pow(err_Q_2[i],2)+pow(err_M_2[i],2));

	}else{
		M_2[i+1]=Q_2[i]+M_2[i];
		err_M_2[i+1]=err_M_2[i];   // qui l'errore e' uguale a quello della massa precedente perche c'e' decadimento B

	}
	cout<<M_1[i+1]<<"+-"<<err_M_1[i+1]<<"\t "<<M_2[i+1]<<"+-"<<err_M_2[i+1]<<endl;
}

float MBi= (M_1[2]+M_2[2])/2;

M_3[0]=MBi;
double err_MBi= (0.5)*sqrt(pow(err_M_1[2],2)+pow(err_M_2[2],2)); 
err_M_3[0]= err_MBi;
cout<<endl<<M_3[0]<<"\t"<<err_MBi<<endl;

cout<<endl<<"Massa percorso 3:"<<endl;
for(int i=0;i<8;i++){
	if(type_3[i]){
		M_3[i+1]=Q_3[i]+M_3[i]+MHe;
		err_M_3[i+1]=sqrt(pow(err_Q_3[i],2)+pow(err_M_3[i],2));

	}else{
		M_3[i+1]=Q_3[i]+M_3[i];
		if(Q_3[i]==0){
			cout<<"ERRORE"<<endl;
		}
		err_M_3[i+1]=err_M_3[i]; // qui l'errore e' uguale a quello della massa precedente perche c'e' decadimento B

	}
	cout<<M_3[i+1]<<"+-"<<err_M_3[i+1]<<endl;
}

float MTh_teo= 232.0386*931.49409; // Mev

float zeta_1=(M_3[8]-MTh_teo)/err_M_3[8];

cout<<endl<<endl<<"Test Z sulla massa del torio ("<<MTh_teo<<" Mev) = "<< zeta_1<<endl<<endl;




// Calcolo dell'energia di legame B

float Masse[]={M_2[1],M_3[0],M_3[2],M_3[3],M_3[4],M_3[5],M_3[8]}; // Inserite nell'array le masse dei genitori dei decadimenti alfa
float Masse_err[]={err_M_2[1],err_M_3[0],err_M_3[2],err_M_3[3],err_M_3[4],err_M_3[5],err_M_3[8]};
float Z[]={84,83,84,86,88,90,90};
float A[]={212,212,216,220,224,228,232};
float B[7];
float B_A[7];

float A_err[]={0,0,0,0,0,0,0};
float B_err[7];
float B_A_err[7];


cout<<endl<<"B \t B/A:" <<endl;
for(int i=0;i<7;i++){
	B[i]=(Z[i]*MH)+((A[i]-Z[i])*Mn)-Masse[i];
	B_err[i]=Masse_err[i];
	B_A[i]=B[i]/A[i];
	B_A_err[i]=B_err[i]/A[i];
	cout<<B[i]<<"+-"<<B_err[i]<<"\t"<<B_A[i]<<"+-"<<B_A_err[i]<<endl;
}

TCanvas *c1= new TCanvas("c1","B/A(A)",200,30,1200,800);
c1->SetGrid();
c1->cd();


TGraphErrors *gr1= new TGraphErrors(7,A,B_A,A_err,B_A_err);
gr1->SetMarkerStyle(8);
gr1->SetMarkerSize(1);
gr1->SetTitle("#frac{B}{A}(A)");
gr1->GetXaxis()->SetTitle("#it{A}");
gr1->GetYaxis()->SetTitle("#it{#frac{B}{A}} [MeV]");
gr1->Draw("AP");

float Zeta[7];
float B_A_teo[] = {7810.2438,7803.3140,7758.8205,7717.2552,7679.9236,7645.0807,7615.0338}; //keV

cout<<endl<<"binding energy per nucleone e test Z:"<<endl;
for(int i=0;i<7;i++){
    Zeta[i] = (B_A[i]-B_A_teo[i]/1000)/B_A_err[i];
cout<<B_A[i]<<"  +-  "<< B_A_err[i]<< "\t Test Z: " << Zeta[i] <<endl;
}


// Fare test Z per le B/A con i valori teorici sottostanti!

// Dati per confronto:

// 1N-Z    N    Z   A  EL    O     MASS EXCESS           BINDING ENERGY/A        BETA-DECAY ENERGY               ATOMIC MASS

//  44  128   84  212 Po       -10369.408       1.153      7810.2438     0.0054  B-  -1741.2596     2.1066  211 988867.982       1.237
//  46  129   83  212 Bi        -8117.943       1.853      7803.3140     0.0087  B-   2251.4656     1.6671  211 991285.030       1.989
//  48  132   84  216 Po         1782.336       1.815      7758.8205     0.0084  B-   -474.3423     3.5713  216 001913.416       1.948
//  48  134   86  220 Rn        10611.994       1.814      7717.2552     0.0082  B-   -870.3384     4.0256  220 011392.443       1.947
//  48  136   88  224 Ra        18825.832       1.811      7679.9236     0.0081  B-  -1408.3152     4.0869  224 020210.361       1.944
//  48  138   90  228 Th        26770.899       1.806      7645.0807     0.0079  B-  -2152.6993     4.3399  228 028739.741       1.938
//  52  142   90  232 Th        35446.710       1.421      7615.0338     0.0061  B-   -499.8388     7.7338  232 038053.606       1.525




return 0;
}
