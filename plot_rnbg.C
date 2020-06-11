void plot_rnbg()
{

  TCanvas c1("c1","");

  const int nbins = 9;

  double sigma_input[nbins];
  double mode[nbins];
  double mean[nbins];
  double sigma[nbins];

  ifstream fin("rn_bg_out.txt");
  for ( int i = 0; i < nbins; ++i )
    {
      fin >> sigma_input[i] >> mode[i] >> mean[i] >> sigma[i];
      cout << sigma_input[i] << " " <<  mode[i] << " " <<  mean[i] << " " <<  sigma[i] << endl;;
    }

  TGraph tg_mean(nbins,sigma_input,mean);
  tg_mean.SetMarkerStyle(kFullCircle);
  tg_mean.SetMarkerColor(kBlack);
  tg_mean.SetLineColor(kBlack);
  tg_mean.Draw("ap");

  TF1 fun_mean("fun_mean","pol1",0,1);
  tg_mean.Fit("fun_mean","R");

  c1.Print("fig_rn_bg_mean.png");

}
