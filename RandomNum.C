const int numtrials = 1e6;


void RandomNum()
{

  TF1* funx = new TF1("funx", "gaus", -10, 10);
  TF1* funy = new TF1("funy", "gaus", -10, 10);

  TH1D* histx = new TH1D("histx", "", 200, -10, 10);
  TH1D* histy = new TH1D("histy", "", 200, -10, 10);
  TH1D* histr = new TH1D("histr", "", 100, 0, 10);

  funx->SetParameter(0,1.0);
  funx->SetParameter(1,0.0);
  funx->SetParameter(2,1.0);
  funy->SetParameter(0,1.0);
  funy->SetParameter(1,0.0);
  funy->SetParameter(2,1.0);

  for(int i = 0; i<numtrials; ++i)
    {
      double x = funx -> GetRandom();
      double y = funy -> GetRandom();
      double r = sqrt(x*x+y*y);
      histx -> Fill(x);
      histy -> Fill(y);
      histr -> Fill(r);
    }

  TCanvas* c1 = new TCanvas("c1", "");

  histx -> Draw();
  c1 -> Print("rn_histx.png");
  histy -> Draw();
  c1 -> Print("rn_histy.png");
  histr -> Draw();
  c1 -> Print("rn_histr.png");

  TF1 *funcFit = new TF1("funcFit","gaus",-10, 10);
  TH1D* hist2x = new TH1D("hist2x","", 200, -10,10);
  TH1D* hist2y = new TH1D("hist2y","", 200, -10,10);
  TH1D* hist2r = new TH1D("hist2r","", 100,0,10);

  hist2x -> Fit("funcFit","R");
  c1 -> Print("rn_hist2x.png");
  hist2y -> Fit("funcFit","R");
  c1 -> Print("rn_hist2y.png");
  hist2r -> Fit("funcFit", "R");
  c1 -> Print("rn_hist2r.png");


}

