const int numtrials = 1e6;


void LandauCalrissian()
{
  TF1* funG = new TF1("funG", "gaus", -10, 10);
  TF1* funL = new TF1("funL", "landau", -10, 10);

  TH1D* histG = new TH1D("histG", "", 200, -10, 10);
  TH1D* histL = new TH1D("histL", "", 200, -10, 10);
  TH1D* histC = new TH1D("histC", "", 200, -10, 10);

  funG->SetParameter(0,1.0);
  funG->SetParameter(1,0.0);
  funG->SetParameter(2,1.0);
  funL->SetParameter(0,1.0);
  funL->SetParameter(1,0.0);
  funL->SetParameter(2,1.0);

  
  for(int i = 0; i<numtrials; ++i)
    {
      double G = funG -> GetRandom();
      double L = funL -> GetRandom();
      double C = G+L;
      histG -> Fill(G);
      histL -> Fill(L);
      histC -> Fill(C);
    }


  TCanvas* c1 = new TCanvas("c1", "");

  
  histG -> Draw();
  c1 -> Print("lc_histG.png");
  histL -> Draw();
  c1 -> Print("lc_histL.png");
  histC -> Draw();
  c1 -> Print("lc_histC.png");

  TF1 *fgubmel = new TF1("fgumbel","([0]/sqrt(6.28))*TMath::Exp(-0.5((x-[1])/[2] + TMath::Exp(-(x-[1]/[2])))",-10,10);
  


}



