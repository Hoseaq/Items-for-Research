void plot_rnbg()
{

  TCanvas c1("c1","");

  const int nbins = 149;
  const double low = 0.0;
  const double high = 0.15;

  double sigma_input[nbins];
  double mode[nbins];
  double mean[nbins];
  double sigma[nbins];
  double ratio[nbins];

  ifstream fin("rn_bg_out.txt");
  for ( int i = 0; i < nbins; ++i )
    {
      fin >> sigma_input[i] >> mode[i] >> mean[i] >> sigma[i];
      ratio[i] = sigma[i]/mean[i];
      cout << sigma_input[i] << " " <<  mode[i] << " " <<  mean[i] << " " <<  sigma[i] << endl;;
    }

  TGraph tg_mean(nbins,sigma_input,mean);
  tg_mean.SetMarkerStyle(kFullCircle);
  tg_mean.SetMarkerColor(kBlack);
  tg_mean.SetLineColor(kBlack);
  tg_mean.Draw("ap");
  tg_mean.SetMinimum(0.0);
  tg_mean.SetMaximum(1.1*mean[nbins-1]);
  tg_mean.GetXaxis()->SetTitle("Input Sigma");
  tg_mean.GetYaxis()->SetTitle("Output Mean");
  tg_mean.GetYaxis()->SetTitleOffset(1.6);

  TF1 fun_mean("fun_mean","pol1",low,high);
  tg_mean.Fit("fun_mean","R");

  c1.Print("fig_rn_bg_mean.png");

  // --

  TGraph tg_sigma(nbins,sigma_input,sigma);
  tg_sigma.SetMarkerStyle(kFullCircle);
  tg_sigma.SetMarkerColor(kBlack);
  tg_sigma.SetLineColor(kBlack);
  tg_sigma.Draw("ap");
  tg_sigma.SetMinimum(0.0);

  TF1 fun_sigma("fun_sigma","pol1",low,high);
  tg_sigma.Fit("fun_sigma","R");

  c1.Print("fig_rn_bg_sigma.png");

  // --

  TGraph tg_ratio(nbins,sigma_input,ratio);
  tg_ratio.SetMarkerStyle(kFullCircle);
  tg_ratio.SetMarkerColor(kBlack);
  tg_ratio.SetLineColor(kBlack);
  tg_ratio.Draw("ap");
  tg_ratio.SetMinimum(0.0);

  TF1 fun_ratio("fun_ratio","pol1",low,high);
  tg_ratio.Fit("fun_ratio","R");

  c1.Print("fig_rn_bg_ratio.png");

}
