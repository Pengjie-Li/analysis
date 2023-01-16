{
//========= Macro generated from object: stats/A special TPaveText to draw histogram statistics.
//========= by ROOT version6.08/04
   
   TPaveStats *ptstats = new TPaveStats(0.6226,0.544098,0.979097,0.935021,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("hExTof-1-1");
   AText->SetTextSize(0.0449561);
   AText = ptstats->AddText("Entries = 1594   ");
   AText = ptstats->AddText("Mean  = 0.3401");
   AText = ptstats->AddText("Std Dev   =  2.827");
   AText = ptstats->AddText("#chi^{2} / ndf = 177.6 / 163");
   AText = ptstats->AddText("Constant = 22.72 #pm 0.86 ");
   AText = ptstats->AddText("Mean     = 0.2658 #pm 0.0669 ");
   AText = ptstats->AddText("Sigma    = 2.305 #pm 0.061 ");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(1);
   ptstats->Draw();
}
