const int numtrials = 1e6;

void execute(); // function prototype, no arguments
void execute(double,double); // function prototype, two arguments
void execute(double,double,double&,double&,double&);

void RandomNum()
{
  execute(); // call the function from within the main
  execute(2,2); // call the function from within the main
  double mode=0;
  double mean=0;
  double sigma=0;
  execute(1,1,mode,mean,sigma);
  cout << "mode is " << mode << endl;
  cout << "mean is " << mean << endl;
  cout << "sigma is " << sigma << endl;
}

// function definition
void execute()
{
  execute(1.0,1.0);
}

// function definition
void execute(double sigma_x, double sigma_y)
{
  double blank;
  execute(sigma_x,sigma_y,blank,blank,blank);
}

void execute(double sigma_x, double sigma_y, double &mode, double &mean, double &sigma)
{

  TF1* funx = new TF1("funx", "gaus", -10, 10);
  TF1* funy = new TF1("funy", "gaus", -10, 10);

  TH1D* histx = new TH1D("histx", "", 200, -10, 10);
  TH1D* histy = new TH1D("histy", "", 200, -10, 10);
  TH1D* histr = new TH1D("histr", "", 100, 0, 10);

  funx->SetParameter(0,1.0);
  funx->SetParameter(1,0.0);
  funx->SetParameter(2,sigma_x);
  funy->SetParameter(0,1.0);
  funy->SetParameter(1,0.0);
  funy->SetParameter(2,sigma_y);

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
  // TH1D* hist2x = new TH1D("hist2x","", 200, -10,10);
  // TH1D* hist2y = new TH1D("hist2y","", 200, -10,10);
  // TH1D* hist2r = new TH1D("hist2r","", 100,0,10);

  histx -> Fit("funcFit","R");
  c1 -> Print("rn_hist2x.png");
  histy -> Fit("funcFit","R");
  c1 -> Print("rn_hist2y.png");
  // histr -> Fit("funcFit", "R");
  // c1 -> Print("rn_hist2r.png");

  TF1 *funcFit2 = new TF1("funcFit2", "gaus*x",0,10);
  funcFit2 -> SetParameter(0,funcFit -> GetParameter(0));
  funcFit2 -> SetParameter(1,funcFit -> GetParameter(1));
  funcFit2 -> SetParameter(2,funcFit -> GetParameter(2));
  histr -> Fit("funcFit2", "R");
  c1 -> Print("rn_hist2r.png");

  // mean = funcFit->GetParameter(1);
  // sigma = funcFit->GetParameter(2);
  mode = histr->GetBinCenter(histr->GetMaximumBin());
  mean = histr->GetMean();
  sigma = histr->GetRMS(); // it says RMS but means standard deviation



  TF1* funbg = new TF1("funbg","(([0]*x)/([2]*[2]))*TMath::Exp(-(x*x+[1]*[1])/(2*[2]*[2]))*TMath::BesselI0((x*[1])/([2]*[2]))",0,20);
  funbg->SetParameter(0,numtrials/6.28);
  funbg->SetParameter(1,1.0);
  funbg->SetParameter(2,1.0);
  histr -> Fit("funbg", "R");
  c1 -> Print("rn_histrbg.png");


  delete funbg;
  delete funcFit2;
  delete funcFit;
  delete histx;
  delete histy;
  delete histr;

  delete c1;

}
